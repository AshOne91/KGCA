#include "FbxLoader.h"

bool FbxLoader::Init()
{
    _pFbxManager = FbxManager::Create();
    _pFbxImporter = FbxImporter::Create(_pFbxManager, "");
    _pFbxScene = FbxScene::Create(_pFbxManager, "");
    return true;
}

bool FbxLoader::Frame()
{
    for (auto obj : _pDrawObjList)
    {
        obj->Frame();
    }
    return true;
}

bool FbxLoader::Render()
{
    for (auto obj : _pDrawObjList)
    {
        obj->Render();
    }
    return true;
}

bool FbxLoader::Release()
{
    for (auto obj : _pDrawObjList)
    {
        obj->Release();
    }
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

bool FbxLoader::Load(C_STR filename)
{
    _pFbxImporter->Initialize(filename.c_str());
    _pFbxImporter->Import(_pFbxScene);
    // 단위
    FbxSystemUnit::m.ConvertScene(_pFbxScene);
    // 기저(행렬)
    FbxAxisSystem::MayaZUp.ConvertScene(_pFbxScene);

    //FbxGeometryConverter converter(_pFbxmanager);
    // 면 -> 삼각형으로
    //converter.Triangulate(_pFbxScene, true);

    _pRootNode = _pFbxScene->GetRootNode();
    PreProcess(_pRootNode);

    for (auto kObj : _pObjectList)
    {
        if (kObj->_pFbxParentNode != nullptr)
        {
            auto data = _pObjectMap.find(kObj->_pFbxParentNode);
            kObj->SetParent(data->second);
        }
        LoadAnimation(kObj);
        FbxMesh* pFbxMesh = kObj->_pFbxNode->GetMesh();
        if (pFbxMesh)
        {
            _pFbxMeshList.push_back(pFbxMesh);
            ParseMesh(pFbxMesh, kObj);
        }
    }
    return true;
}

void FbxLoader::PreProcess(FbxNode* pFbxNode)
{
    if (pFbxNode && (pFbxNode->GetCamera() || pFbxNode->GetLight()))
    //if (pFbxNode == nullptr)
    {
        return;
    }

    KFbxObject* pObject = new KFbxObject;
    std::string name = pFbxNode->GetName();
    pObject->_szName = to_mw(name);
    pObject->_pFbxNode = pFbxNode;
    pObject->_pFbxParentNode = pFbxNode->GetParent();

    _pObjectList.push_back(pObject);
    _pObjectMap.insert(std::make_pair(pFbxNode, pObject));

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

void FbxLoader::ParseMesh(FbxMesh* pFbxMesh, KFbxObject* pObject)
{
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
                if (iNumMtrl <= 1)
                {
                    pObject->_VertexList.push_back(tVertex);
                }
                else
                {
                    pObject->vbDataList[iSubMtrl].push_back(tVertex);
                }
            }
        }
        iBasePolyIndex += iPolySize;
    }

    _pDrawObjList.push_back(pObject);
}

FbxColor FbxLoader::ReadColor(FbxMesh* pFbxMesh, FbxLayerElementVertexColor* VertexColorSet, int posIndex, int colorIndex)
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

FbxVector4 FbxLoader::ReadNormal(FbxMesh* pFbxMesh, FbxLayerElementNormal* VertexNormalSet, int posIndex, int colorIndex)
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

FbxVector2 FbxLoader::ReadTextureCoord(FbxMesh* pFbxMesh, FbxLayerElementUV* pUVSet, int vertexIndex, int uvIndex)
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

int FbxLoader::GetSubMaterialIndex(int iPoly, FbxLayerElementMaterial* pMaterialSetList)
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

void FbxLoader::LoadAnimation(KFbxObject* pObj)
{
    FbxNode* pNode = pObj->_pFbxNode;
    FbxAnimStack* stackAnim = _pFbxScene->GetSrcObject<FbxAnimStack>(0);
    FbxLongLong s = 0;
    FbxLongLong n = 0;
    FbxTime::EMode TimeMode;
    if (stackAnim)
    {
        FbxString takeName = stackAnim->GetName();
        FbxTakeInfo* take = _pFbxScene->GetTakeInfo(takeName);
        FbxTime::SetGlobalTimeMode(FbxTime::eFrames30);
        TimeMode = FbxTime::GetGlobalTimeMode();
        FbxTimeSpan localTimeSpan = take->mLocalTimeSpan;
        FbxTime start = localTimeSpan.GetStart();
        FbxTime end = localTimeSpan.GetStop();
        FbxTime Duration = localTimeSpan.GetDirection();
        s = start.GetFrameCount(TimeMode);
        n = end.GetFrameCount(TimeMode);
    }
    pObj->_AnimScene.iStartFrame = s;
    pObj->_AnimScene.iEndFrame = n;
    pObj->_AnimScene.fFrameSpeed = 30.0f;
    pObj->_AnimScene.fTickPerFrame = 160;
    FbxTime time;
    for (FbxLongLong t = s; t <= n; ++t)
    {
        time.SetFrame(t, TimeMode);
        AnimTrack track;
        track.iFrame = t;
        FbxAMatrix fbxMatrix = pNode->EvaluateGlobalTransform(time);
        track.matAnim = DxConvertMatrix(fbxMatrix);
        D3DXMatrixDecompose(&track.s, &track.r, &track.t, &track.matAnim);
        pObj->_AnimTracks.push_back(track);
    }
}

TMatrix FbxLoader::ConvertMatrix(FbxAMatrix& fbxMatrix)
{
    TMatrix mat;
    float* tArray = (float*)(&mat);
    double* fbxArray = (double*)(&fbxMatrix);
    for (int i = 0; i < 16; ++i)
    {
        tArray[i] = fbxArray[i];
    }
    return mat;
}

TMatrix FbxLoader::DxConvertMatrix(FbxAMatrix& fbxMatrix)
{
    TMatrix m = ConvertMatrix(fbxMatrix);
    TMatrix mat;
    mat._11 = m._11; mat._12 = m._13; mat._13 = m._12;
    mat._21 = m._31; mat._22 = m._33; mat._23 = m._32;
    mat._31 = m._21; mat._32 = m._23; mat._33 = m._22;
    mat._41 = m._41; mat._42 = m._43; mat._43 = m._42;
    mat._14 = mat._24 = mat._34 = 0.0f;
    mat._44 = 1.0f;
    return mat;
}
