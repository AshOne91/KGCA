#pragma once
#define PI 3.141592f
#define DegreeToRadian(x)  (x *(PI / 180.0f))
#define RadianToDegree(x) (x *(180.0f / PI))
#define Epsilon 0.001f

template<typename T>
class VectorInterface abstract
{
public:
	virtual void Zero() = 0;
	virtual bool IsZero() = 0;
	virtual float Length() const = 0;
	virtual float LengthSq() const = 0;
	static float Distance(const T& vector) { return 0.0f; };
	static float DistanceSq(const T& vector) { return 0.0f; };
	virtual void Normalize() = 0;
	virtual T Identity() = 0;
	virtual float Dot(const T& vector) const = 0;
	virtual float GetRadianBetweenVectorDot(const T& vector) = 0;
	virtual float GetDegreeBetweenVectorDot(const T& vector) = 0;
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
};

template<typename T>
class Vector3Interface abstract : public VectorInterface<T>
{
public:
	virtual T Cross(const T& vector) const = 0;
	virtual float GetRadianBetweenVectorCross(const T& vector) = 0;
	virtual float GetDegreeBetweenVectorCross(const T& vector) = 0;
};

struct Float2
{
	union
	{
		struct
		{
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
		struct
		{
			float x;
			float y;
			float z;
		};
		float v[3];
	};
};

class Vector2D : public Float2, public VectorInterface<Vector2D>
{
public:
	Vector2D();
	Vector2D(float x, float y);
	Vector2D(const Vector2D& vector);

public:
	virtual void Zero() override;
	virtual bool IsZero() override;
	virtual float Length() const override;
	virtual float LengthSq() const override;
	static float Distance(const Vector2D& vector1, const Vector2D& vector2);
	static float DistanceSq(const Vector2D& vector1, const Vector2D& vector2);
	virtual void Normalize() override;
	virtual Vector2D Identity() override;
	virtual float Dot(const Vector2D& vector) const override;
	virtual float GetRadianBetweenVectorDot(const Vector2D& vector) override;
	virtual float GetDegreeBetweenVectorDot(const Vector2D& vector) override;

public:
	virtual Vector2D operator + (const Vector2D& vector) override;
	virtual Vector2D operator - (const Vector2D& vector) override;
	virtual Vector2D operator * (float scala) override;
	virtual Vector2D operator / (float scala) override;
	virtual Vector2D& operator = (const Vector2D& vector) override;
	virtual Vector2D& operator *= (float scala) override;
	virtual Vector2D& operator += (const Vector2D& vector) override;
	virtual Vector2D& operator -= (const Vector2D& vector) override;
	virtual Vector2D& operator /= (const Vector2D& vector) override;
	virtual bool operator == (const Vector2D& vector) override;
	virtual bool operator > (const Vector2D& vector) override;
	virtual bool operator < (const Vector2D& vector) override;
	virtual bool operator >= (const Vector2D& vector) override;
	virtual bool operator <= (const Vector2D& vector) override;
};

class Vector3D : public Float3, public Vector3Interface<Vector3D>
{
public:
	Vector3D();
	Vector3D(float x, float y, float z);
	Vector3D(const Vector3D& vector);

public:
	virtual void Zero() override;
	virtual bool IsZero() override;
	virtual float Length() const override;
	virtual float LengthSq() const override;
	static float Distance(const Vector3D& vector1, const Vector3D& vector2);
	static float DistanceSq(const Vector3D& vector1, const Vector3D& vector2);
	virtual void Normalize() override;
	virtual Vector3D Identity() override;
	virtual float Dot(const Vector3D& vector) const override;
	virtual Vector3D Cross(const Vector3D& vector) const override;
	virtual float GetRadianBetweenVectorDot(const Vector3D& vector) override;
	virtual float GetRadianBetweenVectorCross(const Vector3D& vector) override;
	virtual float GetDegreeBetweenVectorDot(const Vector3D& vector) override;
	virtual float GetDegreeBetweenVectorCross(const Vector3D& vector) override;

public:
	virtual Vector3D operator + (const Vector3D& vector) override;
	virtual Vector3D operator - (const Vector3D& vector) override;
	virtual Vector3D operator * (float scala) override;
	virtual Vector3D operator / (float scala) override;
	virtual Vector3D& operator = (const Vector3D& vector) override;
	virtual Vector3D& operator *= (float scala) override;
	virtual Vector3D& operator += (const Vector3D& vector) override;
	virtual Vector3D& operator -= (const Vector3D& vector) override;
	virtual Vector3D& operator /= (const Vector3D& vector) override;
	virtual bool operator == (const Vector3D& vector) override;
	virtual bool operator > (const Vector3D& vector) override;
	virtual bool operator < (const Vector3D& vector) override;
	virtual bool operator >= (const Vector3D& vector) override;
	virtual bool operator <= (const Vector3D& vector) override;
};