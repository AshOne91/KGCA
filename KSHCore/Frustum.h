#pragma once
#include "Shape.h"

enum K_POSITION
{
	P_BACK = 0,
	P_FRONT,
	P_ONPLANE,
	P_SPANNING
};

struct Plane
{
	float a, b, c, d;
	void Create(TVector3 v0, TVector3 v1, TVector3 v2)
	{
		TVector3 vE0 = v1 - v0;
		TVector3 vE1 = v2 - v0;
		//TVector3 vNormal = vE0 ^ vE1;
		TVector3 vNormal;
		D3DXVec3Cross(&vNormal, &vE0, &vE1);
		D3DXVec3Normalize(&vNormal, &vNormal);
		//vNormal.Normalized();
		a = vNormal.x;
		b = vNormal.y;
		c = vNormal.z;
		//d = -(vNormal | v0);
		d = -D3DXVec3Dot(&vNormal, &v0);
		// p = n.x*v.x + n.y*v.y + n.z*v.z + d = 0;
		// p = n.x*v.x + n.y*v.y + n.z*v.z = -d;
		// p = (n.x*v.x + n.y*v.y + v.z*v.z)*-1.0f = d;
		// p = -(n dot v) = d;
	}
	void Create(TVector3 normal, TVector3 v0)
	{
		//normal.Normalized();
		D3DXVec3Normalize(&normal, &normal);
		a = normal.x;
		b = normal.y;
		c = normal.z;
		//d = -(normal | v0);
		d = -D3DXVec3Dot(&normal, &v0);
	}
};

class Frustum
{
	TMatrix _matView;
	TMatrix _matProj;

public:
	TBASIS_EX::TVector3 _vFrustum[8];
	Plane _Plane[6];
public:
	void CreateFrustum(TMatrix*, TMatrix*);
	/*bool ClassifyPoint(Vector3D v);
	bool ClassifySphere(Sphere v);
	bool ClassifyAABB(AABB v);
	bool ClassifyOBB(OBB v);
	bool ClassifyBox(K_BOX v);*/
	K_POSITION ClassifyPoint(TVector3 v);
	K_POSITION ClassifySphere(Sphere v);
	K_POSITION ClassifyAABB(AABB v);
	K_POSITION ClassifyOBB(OBB v);
	K_POSITION ClassifyBox(K_BOX v);



};

