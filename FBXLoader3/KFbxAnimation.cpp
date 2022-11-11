#include "KFbxFile.h"
void KFbxFile::InitAnimation()
{
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
	_AnimScene.iStartFrame = s;
	_AnimScene.iEndFrame = n;
	_AnimScene.fFrameSpeed = 30.0f;
	_AnimScene.fTickPerFrame = 160;
	_AnimScene.TimeMode = TimeMode;
}

//void KFbxFile::LoadAnimation(FbxObjectSkinning* pObj)
void KFbxFile::LoadAnimation(FbxLongLong t, FbxTime time)
{
	for (auto kObj : _pObjectList)
	{
		FbxNode* pNode = kObj->_pFbxNode;
		AnimTrack track;
		track.iFrame = t;
		FbxAMatrix fbxMatrix = pNode->EvaluateGlobalTransform(time);
		track.matAnim = DxConvertMatrix(fbxMatrix);
		TBASIS_EX::D3DXMatrixDecompose(&track.s, &track.r, &track.t, &track.matAnim);
		kObj->_AnimTracks.push_back(track);
	}
}

TMatrix KFbxFile::ConvertMatrix(FbxAMatrix& fbxMatrix)
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

TMatrix KFbxFile::DxConvertMatrix(FbxAMatrix& fbxMatrix)
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

bool KFbxFile::ParseMeshSkinning(FbxMesh* pFbxMesh, FbxObjectSkinning* pObject)
{
	// 리깅 도구( 뼈대에 스킨을 붙이는 작업도구)
	int iDeformerCount = pFbxMesh->GetDeformerCount(FbxDeformer::eSkin);
	if (iDeformerCount == 0)
	{
		return false;
	}

	// iNumVertex == 메쉬의 정점 개수와 동일해야 한다.
	int iNumVertex = pFbxMesh->GetControlPointsCount();
	pObject->_WeightList.resize(iNumVertex);

	for (int iDeformer = 0; iDeformer < iDeformerCount; ++iDeformer)
	{
		FbxDeformer* deformer = pFbxMesh->GetDeformer(iDeformer, FbxDeformer::eSkin);
		FbxSkin* pSkin = (FbxSkin*)deformer;
		// 뼈대가 영향을 미치는 정점 덩어리
		int iNumClusterCount = pSkin->GetClusterCount();
		for (int iCluster = 0; iCluster < iNumClusterCount; ++iCluster)
		{
			FbxCluster* pCluster = pSkin->GetCluster(iCluster);
			FbxNode* pFbxNode = pCluster->GetLink();
			int iBoneIndex = _pObjectIDMap.find(pFbxNode)->second;

			// 뼈대공간으로 변환하는 행렬이 필요하다.
			FbxAMatrix matXBindPose;
			FbxAMatrix matReferenceGlobalInitPosition;
			pCluster->GetTransformLinkMatrix(matXBindPose);
			pCluster->GetTransformMatrix(matReferenceGlobalInitPosition);
			FbxAMatrix matBindPos = matReferenceGlobalInitPosition.Inverse() * matXBindPose;

			TMatrix matInvBindPos = DxConvertMatrix(matBindPos);
			matInvBindPos = matInvBindPos.Invert();
			pObject->_dxMatrixBindPseMap.insert(std::make_pair(iBoneIndex, matInvBindPos));

			// 임의의 1개 정점에 영향을 미치는 뼈대의 개수
			int iNumWeightCounter = pCluster->GetControlPointIndicesCount();
			int* pIndices = pCluster->GetControlPointIndices();
			double* pWeights = pCluster->GetControlPointWeights();
			for (int iVertex = 0; iVertex < iNumWeightCounter; ++iVertex)
			{
				int iVertexIndex = pIndices[iVertex];
				float fweight = pWeights[iVertex];
				pObject->_WeightList[iVertexIndex].insert(iBoneIndex, fweight);
			}
		}
	}
	return true;
}