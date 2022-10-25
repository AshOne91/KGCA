#include "Frustum.h"

void Frustum::CreateFrustum(Matrix* matView, Matrix* matProj)
{
    TBASIS_EX::TMatrix view = *(TBASIS_EX::TMatrix*)matView;
    TBASIS_EX::TMatrix proj = *(TBASIS_EX::TMatrix*)matProj;

    TBASIS_EX::TMatrix matInvViewProj = view * proj;
    TBASIS_EX::D3DXMatrixInverse(&matInvViewProj, NULL, &matInvViewProj);

    // _vFrustum = v * world * (view * proj);
    // _vFrustum = v * world * view * invView * proj * invproj;
    // _vFrustum /= v.w     x,y = -1~+1     z = 0~1;
    _vFrustum[0] = TBASIS_EX::TVector3(-1.0f, -1.0f, 0.0f);
    _vFrustum[1] = TBASIS_EX::TVector3(-1.0f, 1.0f, 0.0f);
    _vFrustum[2] = TBASIS_EX::TVector3(1.0f, 1.0f, 0.0f);
    _vFrustum[3] = TBASIS_EX::TVector3(1.0f, -1.0f, 0.0f);
    _vFrustum[4] = TBASIS_EX::TVector3(-1.0f, -1.0f, 1.0f);
    _vFrustum[5] = TBASIS_EX::TVector3(-1.0f, 1.0f, 1.0f);
    _vFrustum[6] = TBASIS_EX::TVector3(1.0f, 1.0f, 1.0f);
    _vFrustum[7] = TBASIS_EX::TVector3(1.0f, -1.0f, 1.0f);

    for (int iVer = 0; iVer < 8; ++iVer)
    {
        // _vFrustum[iVer] = _vFrustum[iVer] * matInvViewProj;
        TBASIS_EX::D3DXVec3TransformCoord(&_vFrustum[iVer], &_vFrustum[iVer], &matInvViewProj);
    }
    // 5    6  
    // 4    7
    // ->   <-
    // 1    2
    // 0    3 
    _Plane[0].Create(*((Vector3D*)&_vFrustum[1]),
        *((Vector3D*)&_vFrustum[5]),
        *((Vector3D*)&_vFrustum[0])); // left
    _Plane[1].Create(*((Vector3D*)&_vFrustum[3]),
        *((Vector3D*)&_vFrustum[6]),
        *((Vector3D*)&_vFrustum[2])); // right
    _Plane[2].Create(*((Vector3D*)&_vFrustum[5]),
        *((Vector3D*)&_vFrustum[2]),
        *((Vector3D*)&_vFrustum[6])); // top
    _Plane[3].Create(*((Vector3D*)&_vFrustum[0]),
        *((Vector3D*)&_vFrustum[7]),
        *((Vector3D*)&_vFrustum[3])); // bottom
    _Plane[4].Create(*((Vector3D*)&_vFrustum[0]),
        *((Vector3D*)&_vFrustum[2]),
        *((Vector3D*)&_vFrustum[1])); // near
    _Plane[5].Create(*((Vector3D*)&_vFrustum[5]),
        *((Vector3D*)&_vFrustum[6]),
        *((Vector3D*)&_vFrustum[4])); // far
}

bool Frustum::ClassifyPoint(Vector3D v)
{
    for (int iPlane = 0; iPlane < 6; ++iPlane)
    {
        float fDistance =
            _Plane[iPlane].a * v.x +
            _Plane[iPlane].b * v.y +
            _Plane[iPlane].c * v.z +
            _Plane[iPlane].d;
        if (fDistance < 0) return false;
    }
    return true;
}

bool Frustum::ClassifySphere(Sphere v)
{
    float fPlaneToCenter;
    for (int iPlane = 0; iPlane < 6; ++iPlane)
    {
        {
            float fPlaneToCenter =
                _Plane[iPlane].a * v.vCenter.x +
                _Plane[iPlane].b * v.vCenter.y +
                _Plane[iPlane].c * v.vCenter.z +
                _Plane[iPlane].d;

            if (fPlaneToCenter <= -v.fRadius)
            {
                return false;
            }
        }
    }
    return true;
}

bool Frustum::ClassifyAABB(AABB v)
{
    return true;
}

bool Frustum::ClassifyOBB(OBB v)
{
    float		fPlaneToCenter = 0.0;
    float		fDistance = 0.0f;
    Vector3D vDir;
    for (int iPlane = 0; iPlane < 6; iPlane++)
    {
        vDir = v.vAxis[0] * v.fDistance[0];
        fDistance = fabs(_Plane[iPlane].a * vDir.x + _Plane[iPlane].b * vDir.y + _Plane[iPlane].c * vDir.z);
        vDir = v.vAxis[1] * v.fDistance[1];
        fDistance += fabs(_Plane[iPlane].a * vDir.x + _Plane[iPlane].b * vDir.y + _Plane[iPlane].c * vDir.z);
        vDir = v.vAxis[2] * v.fDistance[2];
        fDistance += fabs(_Plane[iPlane].a * vDir.x + _Plane[iPlane].b * vDir.y + _Plane[iPlane].c * vDir.z);

        fPlaneToCenter = _Plane[iPlane].a * v.vCenter.x + _Plane[iPlane].b * v.vCenter.y +
            _Plane[iPlane].c * v.vCenter.z + _Plane[iPlane].d;

        if (fPlaneToCenter <= -fDistance)
        {
            return FALSE;
        }
    }
    return true;
}

bool Frustum::ClassifyBox(K_BOX v)
{
    return true;
}
