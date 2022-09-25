#pragma once
#include <Windows.h>
#include <iostream>
#include <math.h>
#define PI 3.141592f
#define DegreeToRadian(x) (x *(PI / 180.0f))
#define RadianToDegree(x) (x *(180.0f / PI))
#define Epsilon 0.001f
enum class Sign { clockwise = 1, anticlockwise = -1 };
struct Float2
{
	union
	{
		struct {
			float x;
			float y;
		};
		float v[2];
	};
};

struct Float3
{
	union
	{
		struct {
			float x;
			float y;
			float z;
		};
		float v[3];
	};
};

struct Float4
{
	union
	{
		struct {
			float x;
			float y;
			float z;
			float w;
		};
		float v[4];
	};
};

//상속을 받을시 사이즈가 vptr부터 잡혀 virtual로 사용하면 안됨
/*template<typename T>
class VectorInterface abstract
{
public:
	virtual void Zero() {}
	virtual bool IsZero() { return false;}
	virtual float Length() const { return 0.0f; }
	virtual float LengthSq() const { return 0.0f; }
	static float Distance(const T& vector1, const T& vector2) { return 0.0f; };
	static float DistanceSq(const T& vector1, const T& vector2) { return 0.0f; };
	virtual void Normalize() {}
	virtual T Identity() { return T(); }
	virtual float Dot(const T& vector) const { return 0.0f; }
	virtual float GetRadianBetweenVectorDot(const T& vector) { return 0.0f; }
	virtual float GetDegreeBetweenVectorDot(const T& vector) { return 0.0f; }

public:
	virtual T operator + (const T& vector) = 0;
	virtual T operator - (const T& vector) = 0;
	virtual T operator * (float scala) = 0;
	virtual T operator / (float scala) = 0;
	virtual T& operator = (const T& vector) = 0;
	virtual T& operator *= (float scala) = 0;
	virtual T& operator += (const T& vector) = 0;
	virtual T& operator -= (const T& vector) = 0;
	virtual T& operator /= (const T& vector) = 0;
	virtual bool operator == (const T& vector) = 0;
	virtual bool operator > (const T& vector) = 0;
	virtual bool operator < (const T& vector) = 0;
	virtual bool operator >= (const T& vector) = 0;
	virtual bool operator <= (const T& vector) = 0;

	friend T operator*(float scala, const T& vector)
	{
		T result(vector);
		result *= scala;
		return result;
	}
};*/

class Vector2D : public Float2//, public VectorInterface<Vector2D>
{
public:
	Vector2D();
	Vector2D(float x, float y);
	Vector2D(const Vector2D& v);

public:
	Vector2D operator + (const Vector2D& vector) const;
	Vector2D operator - (const Vector2D& vector) const;
	Vector2D operator * (float scala) const;
	Vector2D operator / (float scala) const;
	Vector2D& operator = (const Vector2D& vector);
	Vector2D& operator *= (float scala);
	Vector2D& operator += (const Vector2D& vector);
	Vector2D& operator -= (const Vector2D& vector);
	Vector2D& operator /= (float scala);
	bool operator == (const Vector2D& vector) const;
	bool operator > (const Vector2D& vector) const;
	bool operator < (const Vector2D& vector) const;
	bool operator >= (const Vector2D& vector) const;
	bool operator <= (const Vector2D& vector) const;
	friend Vector2D operator*(float scala, const Vector2D& vector)
	{
		Vector2D result(vector);
		result *= scala;
		return result;
	}
	friend Vector2D operator/(float scala, const Vector2D& vector)
	{
		Vector2D result(vector);
		result = result / scala;
		return result;
	}

public:
	void Zero();
	bool IsZero();
	float Length() const;
	float LengthSq() const;
	static float Distance(const Vector2D& vector1, const Vector2D& vector2);
	static float DistanceSq(const Vector2D& vector1, const Vector2D& vector2);
	void Normalize();
	Vector2D Identity();
	float Dot(const Vector2D& vector) const;
	float GetRadianBetweenVectorDot(const Vector2D& vector);
	float GetDegreeBetweenVectorDot(const Vector2D& vector);
	void Truncate(float max);
	Vector2D Perp() const;
	Sign Sign(const Vector2D& v2) const;
};

class Vector3D : public Float3//, public VectorInterface<Vector3D>
{
public:
	Vector3D();
	Vector3D(float x, float y, float z);
	Vector3D(const Vector3D& v);

public:
	Vector3D operator + (const Vector3D& vector) const;
	Vector3D operator - (const Vector3D& vector) const;
	Vector3D operator * (float scala) const;
	Vector3D operator / (float scala) const;
	Vector3D& operator = (const Vector3D& vector);
	Vector3D& operator *= (float scala);
	Vector3D& operator += (const Vector3D& vector);
	Vector3D& operator -= (const Vector3D& vector);
	Vector3D& operator /= (const Vector3D& vector);
	bool operator == (const Vector3D& vector) const;
	bool operator > (const Vector3D& vector) const;
	bool operator < (const Vector3D& vector) const;
	bool operator >= (const Vector3D& vector) const;
	bool operator <= (const Vector3D& vector) const;
	friend Vector3D operator*(float scala, const Vector3D& vector)
	{
		Vector3D result(vector);
		result *= scala;
		return result;
	}

public:
	void Zero();
	bool IsZero();
	float Length() const;
	float LengthSq() const;
	static float Distance(const Vector3D& vector1, const Vector3D& vector2);
	static float DistanceSq(const Vector3D& vector1, const Vector3D& vector2);
	void Normalize();
	Vector3D Identity();
	float Dot(const Vector3D& vector) const;
	float GetRadianBetweenVectorDot(const Vector3D& vector);
	float GetDegreeBetweenVectorDot(const Vector3D& vector);
	void Truncate(float max);
};

class Vector4D : public Float4//, public VectorInterface<Vector4D>
{
public:
	Vector4D();
	Vector4D(float x, float y, float z, float w);
	Vector4D(const Vector4D& v);

public:
	Vector4D operator + (const Vector4D& vector);
	Vector4D operator - (const Vector4D& vector);
	Vector4D operator * (float scala);
	Vector4D operator / (float scala);
	Vector4D& operator = (const Vector4D& vector);
	Vector4D& operator *= (float scala);
	Vector4D& operator += (const Vector4D& vector);
	Vector4D& operator -= (const Vector4D& vector);
	Vector4D& operator /= (const Vector4D& vector);
	bool operator == (const Vector4D& vector);
	bool operator > (const Vector4D& vector);
	bool operator < (const Vector4D& vector);
	bool operator >= (const Vector4D& vector);
	bool operator <= (const Vector4D& vector);
	friend Vector4D operator*(float scala, const Vector4D& vector)
	{
		Vector4D result(vector);
		result *= scala;
		return result;
	}

public:
	void Zero();
	bool IsZero();
	float Length() const;
	float LengthSq() const;
	static float Distance(const Vector4D& vector1, const Vector4D& vector2);
	static float DistanceSq(const Vector4D& vector1, const Vector4D& vector2);
	void Normalize();
	Vector4D Identity();
	float Dot(const Vector4D& vector) const;
	float GetRadianBetweenVectorDot(const Vector4D& vector);
	float GetDegreeBetweenVectorDot(const Vector4D& vector);
	void Truncate(float max);
};

