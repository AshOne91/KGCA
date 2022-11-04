#include "Matrix.h"

namespace K_TEST
{
    Matrix3x3::Matrix3x3()
    {
        Identity();
    }

    void Matrix3x3::Identity()
    {
        _12 = _13 = 0.0f;
        _21 = _23 = 0.0f;
        _31 = _32 = 0.0f;
        _11 = _22 = _33 = 1.0f;
    }

    Matrix3x3 Matrix3x3::Transpose()
    {
        Matrix3x3 m;
        m._11 = _11; m._12 = _21; m._13 = _31;
        m._21 = _12; m._22 = _22; m._23 = _32;
        m._31 = _13; m._32 = _23; m._33 = _33;
        return m;
    }

    Matrix3x3 Matrix3x3::Rotation(float fRadian)
    {
        float fCosTheta = cos(fRadian);
        float fSinTheta = sin(fRadian);
        Matrix3x3 m;
        m._11 = fCosTheta; m._12 = fSinTheta;
        m._21 = -fSinTheta; m._22 = fCosTheta;
        return m;
    }

    Matrix3x3 Matrix3x3::Scale(float x, float y)
    {
        Matrix3x3 m;
        m._11 = x;
        m._22 = y;
        return m;
    }

    Matrix3x3 Matrix3x3::Translation(float x, float y)
    {
        Matrix3x3 m;
        m._31 = x;
        m._32 = y;
        return m;
    }

    Matrix3x3 Matrix3x3::operator*(Matrix3x3& matrix)
    {
        Matrix3x3 mat;
        for (int iColumn = 0; iColumn < 3; iColumn++)
        {
            for (int iRow = 0; iRow < 3; iRow++)
            {
                mat.m[iRow][iColumn] =
                    m[iRow][0] * matrix.m[0][iColumn] +
                    m[iRow][1] * matrix.m[1][iColumn] +
                    m[iRow][2] * matrix.m[2][iColumn];
            }
        }
        return mat;
    }

    Matrix::Matrix()
    {
        Identity();
    }

    void Matrix::Identity()
    {
        _12 = _13 = _14 = 0.0f;
        _21 = _23 = _24 = 0.0f;
        _31 = _32 = _34 = 0.0f;
        _41 = _42 = _43 = 0.0f;
        _11 = _22 = _33 = _44 = 1.0f;
    }

    Matrix Matrix::Transpose()
    {
        Matrix matrix;
        matrix._11 = _11; matrix._12 = _21; matrix._13 = _31; matrix._14 = _41;
        matrix._21 = _12; matrix._22 = _22; matrix._23 = _32; matrix._24 = _42;
        matrix._31 = _13; matrix._32 = _23; matrix._33 = _33; matrix._34 = _43;
        matrix._41 = _14; matrix._42 = _24; matrix._43 = _34; matrix._44 = _44;
        return matrix;
    }

    void Matrix::RotationX(float fRadian)
    {
        Identity();
        float fCosTheta = cos(fRadian);
        float fSinTheta = sin(fRadian);
        _22 = fCosTheta; _23 = fSinTheta;
        _32 = -fSinTheta; _33 = fCosTheta;
    }

    void Matrix::RotationY(float fRadian)
    {
        Identity();
        float fCosTheta = cos(fRadian);
        float fSinTheta = sin(fRadian);
        _11 = fCosTheta; _13 = -fSinTheta;
        _31 = fSinTheta; _33 = fCosTheta;
    }

    void Matrix::RotationZ(float fRadian)
    {
        Identity();
        float fCosTheta = cos(fRadian);
        float fSinTheta = sin(fRadian);
        _11 = fCosTheta; _12 = fSinTheta;
        _21 = -fSinTheta; _22 = fCosTheta;
    }

    void Matrix::Scale(float x, float y, float z)
    {
        Identity();
        _11 = x;
        _22 = y;
        _33 = z;
    }

    void Matrix::Translation(float x, float y, float z)
    {
        Identity();
        _41 = x;
        _42 = y;
        _43 = z;
    }

    void Matrix::ObjectLookAt(Vector3D& vPosition, Vector3D& vTarget, Vector3D& vUp)
    {
        Vector3D vDirection = vTarget - vPosition;
        vDirection = vDirection.Normal();
        float fDot = vUp | vDirection;
        Vector3D vD = vDirection * fDot;
        Vector3D vUpVector = vUp - vD;
        vUpVector = vUpVector.Normal();
        Vector3D vRightVector = vUpVector ^ vDirection;

        _11 = vRightVector.x;	_12 = vRightVector.y;	_13 = vRightVector.z;
        _21 = vUpVector.x;		_22 = vUpVector.y;		_23 = vUpVector.z;
        _31 = vDirection.x;		_32 = vDirection.y;		_33 = vDirection.z;
        _41 = vPosition.x;
        _42 = vPosition.y;
        _43 = vPosition.z;
    }

    Matrix Matrix::ViewLookAt(Vector3D& vPosition, Vector3D& vTarget, Vector3D& vUp)
    {
        Matrix matrix;
        Vector3D vDirection = (vTarget - vPosition).Normal();
        Vector3D vRightVector = (vUp ^ vDirection).Normal();
        Vector3D vUpVector = (vDirection ^ vRightVector).Normal();

        _11 = vRightVector.x;	_12 = vUpVector.x;	_13 = vDirection.x;
        _21 = vRightVector.y;	_22 = vUpVector.y;	_23 = vDirection.y;
        _31 = vRightVector.z;	_32 = vUpVector.z;	_33 = vDirection.z;

        _41 = -(vPosition.x * _11 + vPosition.y * _21 + vPosition.z * _31);
        _42 = -(vPosition.x * _12 + vPosition.y * _22 + vPosition.z * _32);
        _43 = -(vPosition.x * _13 + vPosition.y * _23 + vPosition.z * _33);
        memcpy(&matrix, this, 16 * sizeof(float));
        return matrix;
    }

    Matrix Matrix::PerspectiveFovLH(float fNearPlane, float fFarPlane, float fovy, float Aspect)
    {
        float    h, w, Q;

        h = 1 / tan(fovy * 0.5f);  // 1/tans(x) = cot(x)
        w = h / Aspect;

        Q = fFarPlane / (fFarPlane - fNearPlane);

        Matrix ret;
        ZeroMemory(this, sizeof(Matrix));

        _11 = w;
        _22 = h;
        _33 = Q;
        _43 = -Q * fNearPlane;
        _34 = 1;

        memcpy((void*)&ret, this, 16 * sizeof(float));
        return ret;
    }

    Matrix Matrix::OrthoLH(float w, float h, float n, float f)
    {
        Identity();
        _11 = 2.0f / w;
        _22 = 2.0f / h;
        _33 = 1.0f / (f - n);
        _43 = -n / (f - n);
        return *this;
    }

    Matrix Matrix::OrthoOffCenterLH(float l, float r, float b, float t, float n, float f)
    {
        Identity();
        _11 = 2.0f / (r - l);
        _22 = 2.0f / (t - b);
        _33 = 1.0f / (f - n);
        _43 = -n / (f - n);
        _41 = (l + r) / (1 - r);
        _42 = (t + b) / (b - t);
        return *this;
    }

    Matrix Matrix::operator*(Matrix& matrix)
    {
        Matrix mat;
        for (int iColumn = 0; iColumn < 4; iColumn++)
        {
            for (int iRow = 0; iRow < 4; iRow++)
            {
                mat.m[iRow][iColumn] =
                    m[iRow][0] * matrix.m[0][iColumn] +
                    m[iRow][1] * matrix.m[1][iColumn] +
                    m[iRow][2] * matrix.m[2][iColumn] +
                    m[iRow][3] * matrix.m[3][iColumn];
            }
        }
        return mat;
    }

    Matrix OrthoLH(Matrix& mat, float w, float h, float n, float f)
    {
        mat.Identity();
        mat._11 = 2.0f / w;
        mat._22 = 2.0f / h;
        mat._33 = 1.0f / (f - n);
        mat._43 = -n / (f - n);
        return mat;
    }

    Matrix OrthoOffCenterLH(Matrix& mat, float l, float r, float b, float t, float n, float f)
    {
        mat.Identity();
        mat._11 = 2.0f / (r - l);
        mat._22 = 2.0f / (t - b);
        mat._33 = 1.0f / (f - n);
        mat._43 = -n / (f - n);
        mat._41 = (l + r) / (l - r);
        mat._42 = (t + b) / (b - t);
        return mat;
    }

    Matrix PerspectiveFovLH(Matrix& mat, float fNearPlane, float fFarPlane, float fovy, float Aspect)
    {
        float    h, w, Q;

        h = 1 / tan(fovy * 0.5f);  // 1/tans(x) = cot(x)
        w = h / Aspect;

        Q = fFarPlane / (fFarPlane - fNearPlane);

        mat._11 = w;
        mat._22 = h;
        mat._33 = Q;
        mat._43 = -Q * fNearPlane;
        mat._34 = 1;
        mat._44 = 0.0f;
        return mat;
    }
};
