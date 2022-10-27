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
	void Create(Vector3D v0, Vector3D v1, Vector3D v2)
	{
		Vector3D vE0 = v1 - v0;
		Vector3D vE1 = v2 - v0;
		Vector3D vNormal = vE0 ^ vE1;
		vNormal.Normalized();
		a = vNormal.x;
		b = vNormal.y;
		c = vNormal.z;
		d = -(vNormal | v0);
		// p = n.x*v.x + n.y*v.y + n.z*v.z + d = 0;
		// p = n.x*v.x + n.y*v.y + n.z*v.z = -d;
		// p = (n.x*v.x + n.y*v.y + v.z*v.z)*-1.0f = d;
		// p = -(n dot v) = d;
	}
	void Create(Vector3D normal, Vector3D v0)
	{
		normal.Normalized();
		a = normal.x;
		b = normal.y;
		c = normal.z;
		d = -(normal | v0);
	}
};

class Frustum
{
	Matrix _matView;
	Matrix _matProj;

public:
	TBASIS_EX::TVector3 _vFrustum[8];
	Plane _Plane[6];
public:
	void CreateFrustum(Matrix*, Matrix*);
	/*bool ClassifyPoint(Vector3D v);
	bool ClassifySphere(Sphere v);
	bool ClassifyAABB(AABB v);
	bool ClassifyOBB(OBB v);
	bool ClassifyBox(K_BOX v);*/
	K_POSITION ClassifyPoint(Vector3D v);
	K_POSITION ClassifySphere(Sphere v);
	K_POSITION ClassifyAABB(AABB v);
	K_POSITION ClassifyOBB(OBB v);
	K_POSITION ClassifyBox(K_BOX v);



};

