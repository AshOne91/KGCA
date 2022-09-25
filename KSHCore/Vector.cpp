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
	return sqrtf(LengthSq());
}

float Vector2D::LengthSq() const
{
	auto length = x * x + y * y;
	return length;
}

float Vector2D::Distance(const Vector2D& vector1, const Vector2D& vector2)
{
	auto distance = sqrtf(DistanceSq(vector1, vector2));
	return distance;
}

float Vector2D::DistanceSq(const Vector2D& vector1, const Vector2D& vector2)
{
	auto dx = vector1.x - vector2.x;
	auto dy = vector1.y - vector2.y;
	return (dx * dx + dy * dy);
}

/*float Vector2D::Distance(const Vector2D& vector)
{
	auto distance = sqrtf(DistanceSq(vector));
	return distance;
}

float Vector2D::DistanceSq(const Vector2D& vector)
{
	auto dx = x - vector.x;
	auto dy = y - vector.y;
	return (dx * dx + dy * dy);
}*/

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

void Vector2D::Truncate(float max)
{
	if (this->Length() > max)
	{
		this->Normalize();
		*this *= max;
	}
}

Vector2D Vector2D::Perp() const
{
	return Vector2D(-y, x);
}

Sign Vector2D::Sign(const Vector2D& v2) const
{
	if (y * v2.x > x * v2.y)
	{
		return Sign::anticlockwise;
	}
	else
	{
		return Sign::clockwise;
	}
}

Vector2D Vector2D::operator+(const Vector2D& vector) const
{
	return Vector2D(x + vector.x, y + vector.y);
}

Vector2D Vector2D::operator-(const Vector2D& vector) const
{
	return Vector2D(x - vector.x, y - vector.y);
}

Vector2D Vector2D::operator*(float scala) const
{
	return Vector2D(x * scala, y * scala);
}

Vector2D Vector2D::operator/(float scala) const
{
	return Vector2D(x / scala, y / scala);
}

Vector2D& Vector2D::operator=(const Vector2D& vector)
{
	this->x = vector.x;
	this->y = vector.y;
	return *this;
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

Vector2D& Vector2D::operator /= (float scala)
{
	x /= scala;
	y /= scala;
	return *this;
}

bool Vector2D::operator==(const Vector2D& vector) const
{
	if (fabsf(x - vector.x) < Epsilon)
	{
		if (fabsf(y - vector.y) < Epsilon)
		{
			return true;
		}
	}
	return false;
}

bool Vector2D::operator>(const Vector2D& vector) const
{
	if (fabsf(x - vector.x) > Epsilon)
	{
		if (fabsf(y - vector.y) > Epsilon)
		{
			return true;
		}
	}
	return false;
}

bool Vector2D::operator<(const Vector2D& vector) const
{
	if (fabsf(x - vector.x) < Epsilon)
	{
		if (fabsf(y - vector.y) < Epsilon)
		{
			return true;
		}
	}
	return false;
}

bool Vector2D::operator>=(const Vector2D& vector) const
{
	if (fabsf(x - vector.x) >= Epsilon)
	{
		if (fabsf(y - vector.y) >= Epsilon)
		{
			return true;
		}
	}
	return false;
}

bool Vector2D::operator<=(const Vector2D& vector) const
{
	if (fabsf(x - vector.x) <= Epsilon)
	{
		if (fabsf(y - vector.y) <= Epsilon)
		{
			return true;
		}
	}
	return false;
}

Vector3D::Vector3D()
{
	x = y = z = 0.0f;
}

Vector3D::Vector3D(float x, float y, float z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

Vector3D::Vector3D(const Vector3D& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
}

void Vector3D::Zero()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

bool Vector3D::IsZero()
{
	if (x == 0.0f && y == 0.0f && z == 0.0f)
	{
		return true;
	}
	return false;
}

float Vector3D::Length() const
{
	auto length = sqrtf(LengthSq());
	return sqrtf(LengthSq());
}

float Vector3D::LengthSq() const
{
	auto length = x * x + y * y + z * z;
	return length;
}

float Vector3D::Distance(const Vector3D& vector1, const Vector3D& vector2)
{
	auto distance = sqrtf(DistanceSq(vector1, vector2));
	return distance;
}

float Vector3D::DistanceSq(const Vector3D& vector1, const Vector3D& vector2)
{
	auto dx = vector1.x - vector2.x;
	auto dy = vector1.y - vector2.y;
	auto dz = vector1.z - vector2.z;
	return (dx * dx + dy * dy + dz * dz);
}

/*float Vector3D::Distance(const Vector3D& vector)
{
	auto distance = sqrtf(DistanceSq(vector));
	return distance;
}

float Vector3D::DistanceSq(const Vector3D& vector)
{
	auto dx = x - vector.x;
	auto dy = y - vector.y;
	auto dz = z - vector.z;
	return (dx * dx + dy * dy);
}*/

void Vector3D::Normalize()
{
	auto invertLength = Length();
	if (invertLength != 0.0f)
	{
		invertLength = 1.0f / invertLength;
		x = x * invertLength;
		y = y * invertLength;
		z = z * invertLength;
	}
}

Vector3D Vector3D::Identity()
{
	auto result = *this;
	auto invertLength = Length();
	if (invertLength != 0.0f)
	{
		invertLength = 1.0f / invertLength;
		result.x = result.x * invertLength;
		result.y = result.y * invertLength;
		result.z = result.z * invertLength;
	}
	return result;
}

float Vector3D::Dot(const Vector3D& vector) const
{
	return x * vector.x + y * vector.y + z * vector.z;
}

/*Vector3D Vector3D::Cross(const Vector3D& vector) const
{
	return Vector3D(y * vector.z - z * vector.y, z * vector.x - x * vector.z, x * vector.y - y * vector.x);
}*/

float Vector3D::GetRadianBetweenVectorDot(const Vector3D& vector)
{
	return acosf(Dot(vector) / (Length() * vector.Length()));
}

/*float Vector3D::GetRadianBetweenVectorCross(const Vector3D& vector)
{
	return asinf(Cross(vector).Length() / (Length() * vector.Length()));
}*/

float Vector3D::GetDegreeBetweenVectorDot(const Vector3D& vector)
{
	return RadianToDegree(GetRadianBetweenVectorDot(vector));
}

void Vector3D::Truncate(float max)
{
	if (this->Length() > max)
	{
		this->Normalize();
		*this *= max;
	}
}

/*float Vector3D::GetDegreeBetweenVectorCross(const Vector3D& vector)
{
	return RadianToDegree(GetRadianBetweenVectorCross(vector));
}*/

Vector3D Vector3D::operator+(const Vector3D& vector) const
{
	return Vector3D(x + vector.x, y + vector.y, z + vector.z);
}

Vector3D Vector3D::operator-(const Vector3D& vector) const
{
	return Vector3D(x - vector.x, y - vector.y, z - vector.z);
}

Vector3D Vector3D::operator*(float scala) const
{
	return Vector3D(x * scala, y * scala, z * scala);
}

Vector3D Vector3D::operator/(float scala) const
{
	return Vector3D(x / scala, y / scala, z / scala);
}

Vector3D& Vector3D::operator=(const Vector3D& vector)
{
	this->x = vector.x;
	this->y = vector.y;
	this->z = vector.z;
	return *this;
}

Vector3D& Vector3D::operator*=(float scala)
{
	x *= scala;
	y *= scala;
	z *= scala;
	return *this;
}

Vector3D& Vector3D::operator+=(const Vector3D& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	return *this;
}

Vector3D& Vector3D::operator-=(const Vector3D& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	return *this;
}

Vector3D& Vector3D::operator/=(const Vector3D& vector)
{
	x /= vector.x;
	y /= vector.y;
	z /= vector.z;
	return *this;
}

bool Vector3D::operator==(const Vector3D& vector) const
{
	if (fabsf(x - vector.x) < Epsilon)
	{
		if (fabsf(y - vector.y) < Epsilon)
		{
			if (fabsf(z - vector.z) < Epsilon)
			{
				return true;
			}
		}
	}
	return false;
}

bool Vector3D::operator>(const Vector3D& vector) const
{
	if (fabsf(x - vector.x) > Epsilon)
	{
		if (fabsf(y - vector.y) > Epsilon)
		{
			if (fabsf(z - vector.z) > Epsilon)
			{
				return true;
			}
		}
	}
	return false;
}

bool Vector3D::operator<(const Vector3D& vector) const
{
	if (fabsf(x - vector.x) < Epsilon)
	{
		if (fabsf(y - vector.y) < Epsilon)
		{
			if (fabsf(z - vector.z) < Epsilon)
			{
				return true;
			}
		}
	}
	return false;
}

bool Vector3D::operator>=(const Vector3D& vector) const
{
	if (fabsf(x - vector.x) >= Epsilon)
	{
		if (fabsf(y - vector.y) >= Epsilon)
		{
			if (fabsf(z - vector.z) >= Epsilon)
			{
				return true;
			}
		}
	}
	return false;
}

bool Vector3D::operator<=(const Vector3D& vector) const
{
	if (fabsf(x - vector.x) <= Epsilon)
	{
		if (fabsf(y - vector.y) <= Epsilon)
		{
			if (fabsf(z - vector.z) <= Epsilon)
			{
				return true;
			}
		}
	}
	return false;
}

Vector4D::Vector4D()
{
	x = y = z = w = 0.0f;
}

Vector4D::Vector4D(float x, float y, float z, float w)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = w;
}

Vector4D::Vector4D(const Vector4D& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
	w = vector.w;
}

void Vector4D::Zero()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

bool Vector4D::IsZero()
{
	if (x == 0.0f && y == 0.0f && z == 0.0f && w == 0.0f)
	{
		return true;
	}
	return false;
}

float Vector4D::Length() const
{
	auto length = sqrtf(LengthSq());
	return sqrtf(LengthSq());
}

float Vector4D::LengthSq() const
{
	auto length = x * x + y * y + z * z + w * w;
	return length;
}

float Vector4D::Distance(const Vector4D& vector1, const Vector4D& vector2)
{
	auto distance = sqrtf(DistanceSq(vector1, vector2));
	return distance;
}

float Vector4D::DistanceSq(const Vector4D& vector1, const Vector4D& vector2)
{
	auto dx = vector1.x - vector2.x;
	auto dy = vector1.y - vector2.y;
	auto dz = vector1.z - vector2.z;
	auto dw = vector1.w - vector2.z;
	return (dx * dx + dy * dy + dz * dz + dw * dw);
}

/*float Vector3D::Distance(const Vector3D& vector)
{
	auto distance = sqrtf(DistanceSq(vector));
	return distance;
}

float Vector3D::DistanceSq(const Vector3D& vector)
{
	auto dx = x - vector.x;
	auto dy = y - vector.y;
	auto dz = z - vector.z;
	return (dx * dx + dy * dy);
}*/

void Vector4D::Normalize()
{
	auto invertLength = Length();
	if (invertLength != 0.0f)
	{
		invertLength = 1.0f / invertLength;
		x = x * invertLength;
		y = y * invertLength;
		z = z * invertLength;
		w = w * invertLength;
	}
}

Vector4D Vector4D::Identity()
{
	auto result = *this;
	auto invertLength = Length();
	if (invertLength != 0.0f)
	{
		invertLength = 1.0f / invertLength;
		result.x = result.x * invertLength;
		result.y = result.y * invertLength;
		result.z = result.z * invertLength;
		result.w = result.w * invertLength;
	}
	return result;
}

float Vector4D::Dot(const Vector4D& vector) const
{
	return x * vector.x + y * vector.y + z * vector.z + w * vector.w;
}

/*Vector3D Vector3D::Cross(const Vector3D& vector) const
{
	return Vector3D(y * vector.z - z * vector.y, z * vector.x - x * vector.z, x * vector.y - y * vector.x);
}*/

float Vector4D::GetRadianBetweenVectorDot(const Vector4D& vector)
{
	return acosf(Dot(vector) / (Length() * vector.Length()));
}

/*float Vector3D::GetRadianBetweenVectorCross(const Vector3D& vector)
{
	return asinf(Cross(vector).Length() / (Length() * vector.Length()));
}*/

float Vector4D::GetDegreeBetweenVectorDot(const Vector4D& vector)
{
	return RadianToDegree(GetRadianBetweenVectorDot(vector));
}

void Vector4D::Truncate(float max)
{
	if (this->Length() > max)
	{
		this->Normalize();
		*this *= max;
	}
}

/*float Vector3D::GetDegreeBetweenVectorCross(const Vector3D& vector)
{
	return RadianToDegree(GetRadianBetweenVectorCross(vector));
}*/

Vector4D Vector4D::operator+(const Vector4D& vector)
{
	return Vector4D(x + vector.x, y + vector.y, z + vector.z, w + vector.w);
}

Vector4D Vector4D::operator-(const Vector4D& vector)
{
	return Vector4D(x - vector.x, y - vector.y, z - vector.z, w + vector.w);
}

Vector4D Vector4D::operator*(float scala)
{
	return Vector4D(x * scala, y * scala, z * scala, w * scala);
}

Vector4D Vector4D::operator/(float scala)
{
	return Vector4D(x / scala, y / scala, z / scala, w / scala);
}

Vector4D& Vector4D::operator=(const Vector4D& vector)
{
	this->x = vector.x;
	this->y = vector.y;
	this->z = vector.z;
	this->w = vector.w;
	return *this;
}

Vector4D& Vector4D::operator*=(float scala)
{
	x *= scala;
	y *= scala;
	z *= scala;
	w *= scala;
	return *this;
}

Vector4D& Vector4D::operator+=(const Vector4D& vector)
{
	x += vector.x;
	y += vector.y;
	z += vector.z;
	w += vector.w;
	return *this;
}

Vector4D& Vector4D::operator-=(const Vector4D& vector)
{
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	w -= vector.w;
	return *this;
}

Vector4D& Vector4D::operator/=(const Vector4D& vector)
{
	x /= vector.x;
	y /= vector.y;
	z /= vector.z;
	w /= vector.w;
	return *this;
}

bool Vector4D::operator==(const Vector4D& vector)
{
	if (fabsf(x - vector.x) < Epsilon)
	{
		if (fabsf(y - vector.y) < Epsilon)
		{
			if (fabsf(z - vector.z) < Epsilon)
			{
				if (fabsf(w - vector.w) < Epsilon)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Vector4D::operator>(const Vector4D& vector)
{
	if (fabsf(x - vector.x) > Epsilon)
	{
		if (fabsf(y - vector.y) > Epsilon)
		{
			if (fabsf(z - vector.z) > Epsilon)
			{
				if (fabsf(w - vector.w) > Epsilon)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Vector4D::operator<(const Vector4D& vector)
{
	if (fabsf(x - vector.x) < Epsilon)
	{
		if (fabsf(y - vector.y) < Epsilon)
		{
			if (fabsf(z - vector.z) < Epsilon)
			{
				if (fabsf(w - vector.w) < Epsilon)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Vector4D::operator>=(const Vector4D& vector)
{
	if (fabsf(x - vector.x) >= Epsilon)
	{
		if (fabsf(y - vector.y) >= Epsilon)
		{
			if (fabsf(z - vector.z) >= Epsilon)
			{
				if (fabsf(z - vector.z) >= Epsilon)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool Vector4D::operator<=(const Vector4D& vector)
{
	if (fabsf(x - vector.x) <= Epsilon)
	{
		if (fabsf(y - vector.y) <= Epsilon)
		{
			if (fabsf(z - vector.z) <= Epsilon)
			{
				if (fabsf(w - vector.w) <= Epsilon)
				{
					return true;
				}
			}
		}
	}
	return false;
}

