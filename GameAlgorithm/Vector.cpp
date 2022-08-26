#include <math.h>
#include "Vector.h"

Vector2D::Vector2D()
{
	x = y = 0.0f;
}

Vector2D::Vector2D(float x, float y)
{
	v[0] = x;
	v[1] = y;
}

Vector2D::Vector2D(const Vector2D& vector)
{
	x = vector.x;
	y = vector.y;
}

void Vector2D::Zero()
{
	x = 0.0f;
	y = 0.0f;
}

bool Vector2D::IsZero()
{
	if (x == 0.0f && y == 0.0f)
	{
		return true;
	}
	return false;
}

float Vector2D::Length() const
{
	auto length = sqrtf(LengthSq());
	return sqrt(LengthSq());
}

float Vector2D::LengthSq() const
{
	auto length = x * x + y * y;
	return length;
}

float Vector2D::Distance(const Vector2D& vector)
{
	auto distance = sqrtf(DistanceSq(vector));
	return distance;
}

float Vector2D::DistanceSq(const Vector2D& vector)
{
	auto dx = x - vector.x;
	auto dy = y - vector.y;
	return (dx * dx + dy * dy);
}

void Vector2D::Normalize()
{
	auto invertLength = Length();
	if (invertLength != 0.0f)
	{
		invertLength = 1.0f / invertLength;
		x = x * invertLength;
		y = y * invertLength;
	}
}

Vector2D Vector2D::Identity()
{
	Vector2D result = *this;
	auto invertLength = Length();
	if (invertLength != 0.0f)
	{
		invertLength = 1.0f / invertLength;
		result.x = result.x * invertLength;
		result.y = result.y * invertLength;
	}
	return result;
}

float Vector2D::Dot(const Vector2D& vector) const
{
	return x * vector.x + y * vector.y;
}

float Vector2D::GetRadianBetweenVectorDot(const Vector2D& vector)
{
	return acosf(Dot(vector) / (Length() * vector.Length()));
}

float Vector2D::GetDegreeBetweenVectorDot(const Vector2D& vector)
{
	return RadianToDegree(GetRadianBetweenVectorDot(vector));
}

Vector2D Vector2D::operator+(const Vector2D& vector)
{
	return Vector2D(x + vector.x, y + vector.y);
}

Vector2D Vector2D::operator-(const Vector2D& vector)
{
	return Vector2D(x - vector.x, y - vector.y);
}

Vector2D Vector2D::operator*(float scala)
{
	return Vector2D(x * scala, y * scala);
}

Vector2D Vector2D::operator/(float scala)
{
	return Vector2D(x / scala, y / scala);
}

Vector2D& Vector2D::operator*=(float scala)
{
	x *= scala;
	y *= scala;
	return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D& vector)
{
	x += vector.x;
	y += vector.y;
	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& vector)
{
	x -= vector.x;
	y -= vector.y;
	return *this;
}

Vector2D& Vector2D::operator /= (const Vector2D& vector)
{
	x /= vector.x;
	y /= vector.y;
	return *this;
}

bool Vector2D::operator==(const Vector2D& vector)
{
	if (fabs(x - vector.x) < Epsilon)
	{
		if (fabs(y - vector.y) < Epsilon)
		{
			return true;
		}
	}
	return false;
}

bool Vector2D::operator>(const Vector2D& vector)
{
	if (fabs(x - vector.x) > Epsilon)
	{
		if (fabs(y - vector.y) > Epsilon)
		{
			return true;
		}
	}
	return false;
}

bool Vector2D::operator<(const Vector2D& vector)
{
	if (fabs(x - vector.x) < Epsilon)
	{
		if (fabs(y - vector.y) < Epsilon)
		{
			return true;
		}
	}
	return false;
}

bool Vector2D::operator>=(const Vector2D& vector)
{
	if (fabs(x - vector.x) >= Epsilon)
	{
		if (fabs(y - vector.y) >= Epsilon)
		{
			return true;
		}
	}
	return false;
}

bool Vector2D::operator<=(const Vector2D& vector)
{
	if (fabs(x - vector.x) <= Epsilon)
	{
		if (fabs(y - vector.y) <= Epsilon)
		{
			return true;
		}
	}
	return false;
}

Vector3D::Vector3D()
{
}

Vector3D::Vector3D(float x, float y)
{
}

Vector3D::Vector3D(const Vector3D& vector)
{
}

void Vector3D::Zero()
{
}

bool Vector3D::IsZero()
{
	return false;
}

float Vector3D::Length()
{
	return 0.0f;
}

float Vector3D::LengthSq()
{
	return 0.0f;
}

float Vector3D::Distance(const Vector3D& vector)
{
	return 0.0f;
}

float Vector3D::DistanceSq(const Vector3D& vector)
{
	return 0.0f;
}

void Vector3D::Normalize()
{
}

Vector3D Vector3D::Identity()
{
	return Vector3D();
}

float Vector3D::Dot(const Vector3D& vector) const
{
	return 0.0f;
}

Vector3D Vector3D::Cross(const Vector3D& vector) const
{
	return Vector3D();
}

float Vector3D::GetRadianBetweenVectorDot(const Vector3D& vector)
{
	return 0.0f;
}

float Vector3D::GetRadianBetweenVectorCross(const Vector3D& vector)
{
	return 0.0f;
}

float Vector3D::GetDegreeBetweenVectorDot(const Vector3D& vector)
{
	return 0.0f;
}

float Vector3D::GetDegreeBetweenVectorCross(const Vector3D& vector)
{
	return 0.0f;
}

Vector3D Vector3D::operator+(const Vector3D& vector)
{
	return Vector3D();
}

Vector3D Vector3D::operator-(const Vector3D& vector)
{
	return Vector3D();
}

Vector3D Vector3D::operator*(float scala)
{
	return Vector3D();
}

Vector3D Vector3D::operator/(float scala)
{
	return Vector3D();
}

Vector3D Vector3D::operator*=(float scala)
{
	return Vector3D();
}

Vector3D Vector3D::operator+=(const Vector3D& vector)
{
	return Vector3D();
}

Vector3D Vector3D::operator-=(const Vector3D& vector)
{
	return Vector3D();
}

bool Vector3D::operator==(const Vector3D& vector)
{
	return false;
}

bool Vector3D::operator>(const Vector3D& vector)
{
	return false;
}

bool Vector3D::operator<(const Vector3D& vector)
{
	return false;
}

bool Vector3D::operator>=(const Vector3D& vector)
{
	return false;
}

bool Vector3D::operator<=(const Vector3D& vector)
{
	return false;
}
