#include "pch.h"
#include "KFbxFile.h"

bool KFbxFile::Init()
{
    _pFbxManager = FbxManager::Create();
    _pFbxImporter = FbxImporter::Create(_pFbxManager, "");
    _pFbxScene = FbxScene::Create(_pFbxManager, "");
    return true;
}

bool KFbxFile::Load(C_STR filename)
{
    _pFbxImporter->Initialize(filename.c_str());
    _pFbxImporter->Import(_pFbxScene);

    FbxAxisSystem SceneAxisSystem = _pFbxScene->GetGlobalSettings().GetAxisSystem();
    // 단위
    FbxSystemUnit::m.ConvertScene(_pFbxScene);
    // 기저(행렬)
    FbxAxisSystem::MayaZUp.ConvertScene(_pFbxScene);

    //FbxGeometryConverter converter(_pFbxmanager);
    // 면 -> 삼각형으로
    //converter.Triangulate(_pFbxScene, true);

    InitAnimation();

    _pRootNode = _pFbxScene->GetRootNode();
    PreProcess(_pRootNode);

    for (auto kObj : _pObjectList)
    {
        if (kObj->_pFbxParentNode != nullptr)
        {
            auto data = _pObjectMap.find(kObj->_pFbxParentNode);
            kObj->SetParent(data->second);
        }
        //LoadAnimation(kObj);
        FbxMesh* pFbxMesh = kObj->_pFbxNode->GetMesh();
        if (pFbxMesh)
        {
            ParseMesh(pFbxMesh, kObj);
        }
    }
    // animation
    FbxTime time;
    for (FbxLongLong t = _AnimScene.iStartFrame; t <= _AnimScene.iEndFrame; ++t)
    {
        time.SetFrame(t, _AnimScene.TimeMode);
        LoadAnimation(t, time);
    }

    return true;
}

void KFbxFile::ParseMesh(FbxMesh* pFbxMesh, FbxObjectSkinning* pObject)
{
    // 스키닝 정보 확인
    pObject->_bSkinned = ParseMeshSkinning(pFbxMesh, pObject);

    FbxNode* pNode = pFbxMesh->GetNode();
    FbxAMatrix geom; // 기하(로칼)행렬(초기 정점 위치를 변환할 때 사용한다.)
    FbxVector4 trans = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
    FbxVector4 rot = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
    FbxVector4 scale = pNode->GetGeometricScaling(FbxNode::eSourcePivot);
    geom.SetT(trans);
    geom.SetR(rot);
    geom.SetS(scale);

    FbxAMatrix normalLocalMatrix = geom;
    normalLocalMatrix = normalLocalMatrix.Inverse();
    normalLocalMatrix = normalLocalMatrix.Transpose();

    // 월드행렬
    /*FbxVector4 Translation;
    if (pNode->LclTranslation.IsValid())
        Translation = pNode->LclTranslation.Get();

    FbxVector4 Rotation;
    if (pNode->LclRotation.IsValid())
        Rotation = pNode->LclRotation.Get();

    FbxVector4 Scale;
    if (pNode->LclScaling.IsValid())
        Scale = pNode->LclScaling.Get();

    FbxAMatrix matWorldTransform(Translation, Rotation, Scale);
    FbxAMatrix normalWorldMatrix = matWorldTransform;
    normalWorldMatrix = normalWorldMatrix.Inverse();
    normalWorldMatrix = normalWorldMatrix.Transpose();*/

    //FbxAMatrix matWorldTransform= pObject->m_fbxLocalMatrix;
    ////// 최종월드행렬 = 자기(에니메이션) 행렬 * 부모((에니메이션))행렬
    ////if (pObject->m_pParent)
    ////{
    ////    matWorldTransform = 
    ////        pObject->m_pParent->m_fbxLocalMatrix * 
    ////        pObject->m_fbxLocalMatrix;
    ////}        
    //FbxAMatrix normalWorldMatrix = matWorldTransform;
    //normalWorldMatrix = normalWorldMatrix.Inverse();
    //normalWorldMatrix = normalWorldMatrix.Transpose();


    //Layer 개념
    FbxLayerElementUV* VertexUVSet = nullptr;
    FbxLayerElementVertexColor* VertexColorSet = nullptr;
    FbxLayerElementNormal* VertexNormalSet = nullptr;
    FbxLayerElementMaterial* MaterialSet = nullptr;
    FbxLayer* pFbxLayer = pFbxMesh->GetLayer(0);
    if (pFbxLayer->GetUVs() != nullptr)
    {
        VertexUVSet = pFbxLayer->GetUVs();
    }
    if (pFbxLayer->GetVertexColors() != nullptr)
    {
        VertexColorSet = pFbxLayer->GetVertexColors();
    }
    if (pFbxLayer->GetNormals() != nullptr)
    {
        VertexNormalSet = pFbxLayer->GetNormals();
    }
    if (pFbxLayer->GetMaterials() != nullptr)
    {
        MaterialSet = pFbxLayer->GetMaterials();
    }

    std::string szFileName;
    int iNumMtrl = pNode->GetMaterialCount();
    std::vector<C_STR> texFullNameList;
    texFullNameList.resize(iNumMtrl);

    for (int iMtrl = 0; iMtrl < iNumMtrl; ++iMtrl)
    {
        // 24 이상의 정보가 있다.
        FbxSurfaceMaterial* pSurface = pNode->GetMaterial(iMtrl);
        if (pSurface)
        {
            auto property = pSurface->FindProperty(FbxSurfaceMaterial::sDiffuse);
            if (property.IsValid())
            {
                const FbxFileTexture* tex = property.GetSrcObject<FbxFileTexture>(0);
                if (tex)
                {
                    szFileName = tex->GetFileName();
                    texFullNameList[iMtrl] = szFileName;
                }
            }
        }
    }

    if (iNumMtrl == 1)
    {
        pObject->_szTextureName = I_Tex.GetSplitName(szFileName);
    }
    if (iNumMtrl > 1)
    {
        pObject->vbDataList.resize(iNumMtrl);
        pObject->vbDataList_IW.resize(iNumMtrl);

        pObject->vbTexList.resize(iNumMtrl);
        for (int iTex = 0; iTex < iNumMtrl; ++iTex)
        {
            pObject->vbTexList[iTex] = I_Tex.GetSplitName(texFullNameList[iTex]);
        }
    }

    int iNumPolyCount = pFbxMesh->GetPolygonCount();
    // 3 정점 -> 1폴리곤( 삼각형)
    // 4 정점 -> 1폴리곤( 쿼드 )
    int iNumFace = 0;
    int iBasePolyIndex = 0;
    int iSubMtrl = 0;
    // 제어점
    FbxVector4* pVertexPositions = pFbxMesh->GetControlPoints();
    for (int iPoly = 0; iPoly < iNumPolyCount; ++iPoly)
    {
        int iPolySize = pFbxMesh->GetPolygonSize(iPoly);
        iNumFace = iPolySize - 2;
        if (MaterialSet)
        {
            iSubMtrl = GetSubMaterialIndex(iPoly, MaterialSet);
        }
        for (int iFace = 0; iFace < iNumFace; ++iFace)
        {
            // 정점컬러인덱스
            int VertexColor[3] = { 0, iFace + 2, iFace + 1 };
            // 정점인덱스
            int iCornerIndex[3];
            iCornerIndex[0] = pFbxMesh->GetPolygonVertex(iPoly, 0);
            iCornerIndex[1] = pFbxMesh->GetPolygonVertex(iPoly, iFace + 2);
            iCornerIndex[2] = pFbxMesh->GetPolygonVertex(iPoly, iFace + 1);

            int iUVIndex[3];
            iUVIndex[0] = pFbxMesh->GetTextureUVIndex(iPoly, 0);
            iUVIndex[1] = pFbxMesh->GetTextureUVIndex(iPoly, iFace + 2);
            iUVIndex[2] = pFbxMesh->GetTextureUVIndex(iPoly, iFace + 1);

            for (int iIndex = 0; iIndex < 3; ++iIndex)
            {
                int vertexID = iCornerIndex[iIndex];
                FbxVector4 v2 = pVertexPositions[vertexID];
                PNCT_VERTEX tVertex;
                IW_VERTEX  IWVertex;
                FbxVector4 v = geom.MultT(v2);//결과만 저장한다.
                //v = matWorldTransform.MultT(v);
                tVertex.p.x = v.mData[0];
                tVertex.p.y = v.mData[2];
                tVertex.p.z = v.mData[1];
                tVertex.c = TVector4(1, 1, 1, 1);
                if (VertexColorSet)
                {
                    FbxColor c = ReadColor(pFbxMesh, VertexColorSet, iCornerIndex[iIndex], iBasePolyIndex + VertexColor[iIndex]);
                    tVertex.c.x = c.mRed;
                    tVertex.c.y = c.mGreen;
                    tVertex.c.z = c.mBlue;
                    tVertex.c.w = 1.0f;
                }
                if (VertexUVSet)
                {
                    FbxVector2 t = ReadTextureCoord(pFbxMesh, VertexUVSet, iCornerIndex[iIndex], iUVIndex[iIndex]);
                    tVertex.t.x = t.mData[0];
                    tVertex.t.y = 1.0f - t.mData[1];
                }
                if (VertexNormalSet)
                {
                    FbxVector4 n = ReadNormal(
                        pFbxMesh,
                        VertexNormalSet,
                        iCornerIndex[iIndex],
                        iBasePolyIndex + VertexColor[iIndex]);
                    n = normalLocalMatrix.MultT(n);
                    //n = normalWorldMatrix.MultT(n);
                    tVertex.n.x = n.mData[0];
                    tVertex.n.y = n.mData[2];
                    tVertex.n.z = n.mData[1];
                }
                if (pObject->_bSkinned == false)
                {
                    IWVertex.i.x = _pObjectIDMap.find(pNode)->second;
                    IWVertex.i.y = 0;
                    IWVertex.i.z = 0;
                    IWVertex.i.w = 0;
                    IWVertex.w.x = 1.0f;
                    IWVertex.w.y = 0.0f;
                    IWVertex.w.z = 0.0f;
                    IWVertex.w.w = 0.0f;
                }
                else
                {
                    KWeight* pWeight = &pObject->_WeightList[vertexID];
                    IWVertex.i.x = pWeight->Index[0];
                    IWVertex.i.y = pWeight->Index[1];
                    IWVertex.i.z = pWeight->Index[2];
                    IWVertex.i.w = pWeight->Index[3];
                    IWVertex.w.x = pWeight->weight[0];
                    IWVertex.w.y = pWeight->weight[1];
                    IWVertex.w.z = pWeight->weight[2];
                    IWVertex.w.w = pWeight->weight[3];
                }

                if (iNumMtrl <= 1)
                {
                    pObject->_VertexList.push_back(tVertex);
                    pObject->_VertexListIW.push_back(IWVertex);
                }
                else
                {
                    pObject->vbDataList[iSubMtrl].push_back(tVertex);
                    pObject->vbDataList_IW[iSubMtrl].push_back(IWVertex);
                }
            }
        }
        iBasePolyIndex += iPolySize;
    }

    _pDrawObjList.push_back(pObject);
}

FbxVector4 KFbxFile::ReadNormal(FbxMesh* pFbxMesh, FbxLayerElementNormal* VertexNormalSet, int posIndex, int colorIndex)
{
    FbxVector4 normal(1, 1, 1, 1);
    FbxLayerElement::EMappingMode mode = VertexNormalSet->GetMappingMode();
    switch (mode)
    {
        case FbxLayerElementUV::eDirect:
        {
            switch (VertexNormalSet->GetReferenceMode())
            {
                case FbxLayerElementUV::eDirect:
                {
                    normal = VertexNormalSet->GetDirectArray().GetAt(posIndex);
                }break;
                case FbxLayerElementUV::eIndexToDirect:
                {
                    int index = VertexNormalSet->GetIndexArray().GetAt(posIndex);
                    normal = VertexNormalSet->GetDirectArray().GetAt(index);
                }break;
            }
        }break;
        case FbxLayerElementUV::eByPolygonVertex:
        {
            switch (VertexNormalSet->GetReferenceMode())
            {
                case FbxLayerElementUV::eDirect:
                {
                    normal = VertexNormalSet->GetDirectArray().GetAt(colorIndex);
                }break;
                case FbxLayerElementUV::eIndexToDirect:
                {
                    int index = VertexNormalSet->GetIndexArray().GetAt(colorIndex);
                    normal = VertexNormalSet->GetDirectArray().GetAt(index);
                }break;
            }
        }break;
    }
    return normal;
}

FbxColor KFbxFile::ReadColor(FbxMesh* pFbxMesh, FbxLayerElementVertexColor* VertexColorSet, int posIndex, int colorIndex)
{
    FbxColor color(1, 1, 1, 1);
    FbxLayerElement::EMappingMode mode = VertexColorSet->GetMappingMode();
    switch (mode)
    {
        case FbxLayerElementUV::eDirect:
        {
            switch (VertexColorSet->GetReferenceMode())
            {
                case FbxLayerElementUV::eDirect:
                {
                    color = VertexColorSet->GetDirectArray().GetAt(posIndex);
                }break;
                case FbxLayerElementUV::eIndexToDirect:
                {
                    int index = VertexColorSet->GetIndexArray().GetAt(posIndex);
                    color = VertexColorSet->GetDirectArray().GetAt(index);
                }break;
            }
        }break;
        case FbxLayerElementUV::eByPolygonVertex:
        {
            switch (VertexColorSet->GetReferenceMode())
            {
                case FbxLayerElementUV::eDirect:
                {
                    color = VertexColorSet->GetDirectArray().GetAt(colorIndex);
                }break;
                case FbxLayerElementUV::eIndexToDirect:
                {
                    int index = VertexColorSet->GetIndexArray().GetAt(colorIndex);
                    color = VertexColorSet->GetDirectArray().GetAt(index);
                }break;
            }
        }break;
    }
    return color;
}

FbxVector2 KFbxFile::ReadTextureCoord(FbxMesh* pFbxMesh, FbxLayerElementUV* pUVSet, int vertexIndex, int uvIndex)
{
    FbxVector2 t;
    /*enum EMappingMode
    {
        eNone,                // 매핑이 결정되지 않았다.
        eByControlPoint,    // 제어점 및 정점에 1개의 매핑이 되어 있다.
        eByPolygonVertex,    // 각 정점이 속한 폴리곤의 매핑에 좌표가 있다.
        eByPolygon,         // 전체 폴리곤에 매핑 좌표가 있다.
        eByEdge,            // 에지에 1개의 매핑 좌표가 있다.
        eAllSame            // 전체 폴리곤에 1개의 매핑 좌표가 있다.
    };*/
    //enum EReferenceMode
    //{
    //    eDirect,   // n번째 매핑정보가 mDirectArray의 n번째 위치에 있다.
    //    eIndex,    // fbx 5.0 이하 버전에서 사용되었었다. 이상 버전에서는 eIndexToDirect로 대체되었다.
    //    eIndexToDirect
    //};
    // 텍스처 매핑 방식이 뭐냐?
    FbxLayerElement::EMappingMode mode = pUVSet->GetMappingMode();
    switch (mode)
    {
        case FbxLayerElementUV::eByControlPoint:
        {
            switch (pUVSet->GetReferenceMode())
            {
                case FbxLayerElementUV::eDirect:
                {
                    t = pUVSet->GetDirectArray().GetAt(vertexIndex);
                }break;
                case FbxLayerElementUV::eIndexToDirect:
                {
                    int index = pUVSet->GetIndexArray().GetAt(vertexIndex);
                    t = pUVSet->GetDirectArray().GetAt(index);
                }break;
            }
        }break;
        case FbxLayerElementUV::eByPolygonVertex:
        {
            switch (pUVSet->GetReferenceMode())
            {
                case FbxLayerElementUV::eDirect:
                case FbxLayerElementUV::eIndexToDirect:
                {
                    t = pUVSet->GetDirectArray().GetAt(uvIndex);
                }break;
            }
        }break;
    }
    return t;
}

int KFbxFile::GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial* pMaterialSetList)
{
    // 매핑방식
    //eNone,
    //eByControlPoint,  // 제어점
    //eByPolygonVertex, //  
    //eByPolygon, // 폴리곤마다 다를수 있다.
    //eAllSame - 전체표면에 1개의 매핑좌표가 있다.
    int iSubMtrl = 0;
    if (pMaterialSetList != nullptr)
    {
        switch (pMaterialSetList->GetMappingMode())
        {
            case FbxLayerElement::eByPolygon:
            {
                // 매핑 정보가 배열에 저장되는 방식
                switch (pMaterialSetList->GetReferenceMode())
                {
                    case FbxLayerElement::eIndex:
                    {
                        iSubMtrl = iPoly;
                    }break;
                    case FbxLayerElement::eIndexToDirect:
                    {
                        iSubMtrl = pMaterialSetList->GetIndexArray().GetAt(iPoly);
                    }break;
                }
            }
            default:
            {
                break;
            }
        }
    }
    return iSubMtrl;
}

void KFbxFile::PreProcess(FbxNode* pFbxNode)
{
    if (pFbxNode && (pFbxNode->GetCamera() || pFbxNode->GetLight()))
        //if (pFbxNode == nullptr)
    {
        return;
    }

    FbxObjectSkinning* pObject = new FbxObjectSkinning;
    std::string name = pFbxNode->GetName();
    pObject->_szName = to_mw(name);
    pObject->_pFbxNode = pFbxNode;
    pObject->_pFbxParentNode = pFbxNode->GetParent();
    pObject->_iObjectBone = _pObjectList.size();

    _pObjectList.push_back(pObject);
    _pObjectMap.insert(std::make_pair(pFbxNode, pObject));
    _pObjectIDMap.insert(std::make_pair(pFbxNode, pObject->_iObjectBone));

    int iNumChild = pFbxNode->GetChildCount();
    for (int iChild = 0; iChild < iNumChild; ++iChild)
    {
        FbxNode* pChild = pFbxNode->GetChild(iChild);
        // 헬퍼오브젝트 + 지오메트리 오브젝트
        FbxNodeAttribute::EType type = pChild->GetNodeAttribute()->GetAttributeType();
        if (type == FbxNodeAttribute::eMesh ||
            type == FbxNodeAttribute::eSkeleton ||
            type == FbxNodeAttribute::eNull)
        {
            PreProcess(pChild);
        }
    }
}

bool KFbxFile::Release()
{
    if (_pAnimBoneCB)
    {
        _pAnimBoneCB->Release();
        _pAnimBoneCB = nullptr;
    }
    for (auto obj : _pObjectList)
    {
        obj->Release();
        delete obj;
    }
    _pObjectList.clear();

    _pFbxScene->Destroy();
    //_pFbxImporter->Destroy();
    //_pFbxManager->Destroy();

    if (_pFbxImporter != nullptr)
    {
        _pFbxImporter->Destroy();
        _pFbxImporter = nullptr;
    }
    if (_pFbxManager != nullptr)
    {
        _pFbxManager->Destroy();
        _pFbxManager = nullptr;
    }
    return true;
}