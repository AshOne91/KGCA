#pragma once
#include "Vector.h"

namespace K_TEST
{
	struct float3x3
	{
		union
		{
			struct {
				float _11, _12, _13;
				float _21, _22, _23;
				float _31, _32, _33;
			};
			float m[3][3];
		};
	};

	struct float4x4
	{
		union
		{
			struct {
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			float m[4][4];
		};
	};

	class Matrix3x3 : public float3x3
	{
	public:
		Matrix3x3();
		void Identity();
		Matrix3x3 Transpose();
		Matrix3x3 Rotation(float fRadian);
		Matrix3x3 Scale(float x, float y);
		Matrix3x3 Translation(float x, float y);

	public:
		Matrix3x3 operator* (Matrix3x3& m);
	};

	class Matrix : public float4x4
	{
	public:
		Matrix();
		void Identity();
		void RotationX(float fRadian);
		void RotationY(float fRadian);
		void RotationZ(float fRadian);
		void Scale(float x, float y, float z);
		void Translation(float x, float y, float z);
		Matrix Transpose();

		void ObjectLookAt(Vector3D& vPosition, Vector3D& vTarget, Vector3D& vUp);
		Matrix ViewLookAt(Vector3D& vPosition, Vector3D& vTarget, Vector3D& vUp);
		Matrix PerspectiveFovLH(float fNearPlane, float fFarPlane, float fovy, float Aspect);
		Matrix OrthoLH(float w, float h, float n, float f);
		Matrix OrthoOffCenterLH(float l, float r, float b, float t, float n, float f);

	public:
		friend Matrix OrthoLH(Matrix& mat, float w, float h, float n, float f);
		friend Matrix OrthoOffCenterLH(Matrix& mat, float l, float r, float b, float t, float n, float f);
		friend Matrix PerspectiveFovLH(Matrix& mat, float fNearPlane, float fFarPlane, float fovy, float Aspect);

	public:
		Matrix operator* (Matrix& m);
	};

	namespace Math
	{
		static Matrix RotationX(float fRadian)
		{
			float fCosTheta = cos(fRadian);
			float fSinTheta = sin(fRadian);
			Matrix m;
			m._22 = fCosTheta; m._23 = fSinTheta;
			m._32 = -fSinTheta; m._33 = fCosTheta;
			return m;
		}
		static Matrix RotationY(float fRadian)
		{
			float fCosTheta = cos(fRadian);
			float fSinTheta = sin(fRadian);
			Matrix m;
			m._11 = fCosTheta; m._13 = -fSinTheta;
			m._31 = fSinTheta; m._33 = fCosTheta;
			return m;
		}
		static Matrix RotationZ(float fRadian)
		{
			float fCosTheta = cos(fRadian);
			float fSinTheta = sin(fRadian);
			Matrix m;
			m._11 = fCosTheta; m._12 = fSinTheta;
			m._21 = -fSinTheta; m._22 = fCosTheta;
			return m;
		}
		static Matrix Scale(float x, float y, float z)
		{
			Matrix m;
			m._11 = x;
			m._22 = y;
			m._33 = z;
			return m;
		}
		static Matrix Translation(float x, float y, float z)
		{
			Matrix m;
			m._41 = x;
			m._42 = y;
			m._43 = z;
			return m;
		}
	};
};