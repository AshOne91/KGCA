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
    // ����
    FbxSystemUnit::m.ConvertScene(_pFbxScene);
    // ����(���)
    FbxAxisSystem::MayaZUp.ConvertScene(_pFbxScene);

    //FbxGeometryConverter converter(_pFbxmanager);
    // �� -> �ﰢ������
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
        // ���ۿ�����Ʈ + ������Ʈ�� ������Ʈ
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
    FbxAMatrix geom; // ����(��Į)���(�ʱ� ���� ��ġ�� ��ȯ�� �� ����Ѵ�.)
    FbxVector4 trans = pNode->GetGeometricTranslation(FbxNode::eSourcePivot);
    FbxVector4 rot = pNode->GetGeometricRotation(FbxNode::eSourcePivot);
    FbxVector4 scale = pNode->GetGeometricScaling(FbxNode::eSourcePivot);
    geom.SetT(trans);
    geom.SetR(rot);
    geom.SetS(scale);

    FbxAMatrix normalLocalMatrix = geom;
    normalLocalMatrix = normalLocalMatrix.Inverse();
    normalLocalMatrix = normalLocalMatrix.Transpose();

    // �������
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
    ////// ����������� = �ڱ�(���ϸ��̼�) ��� * �θ�((���ϸ��̼�))���
    ////if (pObject->m_pParent)
    ////{
    ////    matWorldTransform = 
    ////        pObject->m_pParent->m_fbxLocalMatrix * 
    ////        pObject->m_fbxLocalMatrix;
    ////}        
    //FbxAMatrix normalWorldMatrix = matWorldTransform;
    //normalWorldMatrix = normalWorldMatrix.Inverse();
    //normalWorldMatrix = normalWorldMatrix.Transpose();


    //Layer ����
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
        // 24 �̻��� ������ �ִ�.
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
    // 3 ���� -> 1������( �ﰢ��)
    // 4 ���� -> 1������( ���� )
    int iNumFace = 0;

    int iBasePolyIndex = 0;
    int iSubMtrl = 0;
    // ������
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
            // �����÷��ε���
            int VertexColor[3] = { 0, iFace + 2, iFace + 1 };
            // �����ε���
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
                FbxVector4 v = geom.MultT(v2);//����� �����Ѵ�.
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
        eNone,                // ������ �������� �ʾҴ�.
        eByControlPoint,    // ������ �� ������ 1���� ������ �Ǿ� �ִ�.
        eByPolygonVertex,    // �� ������ ���� �������� ���ο� ��ǥ�� �ִ�.
        eByPolygon,         // ��ü �����￡ ���� ��ǥ�� �ִ�.
        eByEdge,            // ������ 1���� ���� ��ǥ�� �ִ�.
        eAllSame            // ��ü �����￡ 1���� ���� ��ǥ�� �ִ�.
    };*/
    //enum EReferenceMode
    //{
    //    eDirect,   // n��° ���������� mDirectArray�� n��° ��ġ�� �ִ�.
    //    eIndex,    // fbx 5.0 ���� �������� ���Ǿ�����. �̻� ���������� eIndexToDirect�� ��ü�Ǿ���.
    //    eIndexToDirect
    //};
    // �ؽ�ó ���� ����� ����?
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
    // ���ι��
    //eNone,
    //eByControlPoint,  // ������
    //eByPolygonVertex, //  
    //eByPolygon, // �����︶�� �ٸ��� �ִ�.
    //eAllSame - ��üǥ�鿡 1���� ������ǥ�� �ִ�.
    int iSubMtrl = 0;
    if (pMaterialSetList != nullptr)
    {
        switch (pMaterialSetList->GetMappingMode())
        {
        case FbxLayerElement::eByPolygon:
        {
            // ���� ������ �迭�� ����Ǵ� ���
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