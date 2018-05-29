
#include "stdafx.h"
#include "Vector.h"

float Vector2::Dist(const Vector2 &V1, const Vector2 &V2)
{
	return sqrtf(Vector2::DistSquared(V1, V2));
}

float Vector2::DistSquared(const Vector2 &V1, const Vector2 &V2)
{
	return (V2.X - V1.X) * (V2.X - V1.X) + (V2.Y - V1.Y) * (V2.Y - V1.Y);
}

Vector2 Vector2::operator *(float Scale) const
{
	Vector2 result;
	result.X = X * Scale;
	result.Y = Y * Scale;
	return result;
}


Vector2 Vector2::operator*(const Matrix2& Mat) const
{
	Vector2 result;
	result.X = X * Mat._11 + Y * Mat._12;
	result.Y = X * Mat._21 + Y * Mat._22;
	return result;
}

Vector2 Vector2::operator-(const Vector2& Other) const
{
	Vector2 result;
	result.X = X - Other.X;
	result.Y = Y - Other.Y;
	return result;
}

Vector2 Vector2::operator+(const Vector2& Other) const
{
	Vector2 result;
	result.X = X + Other.X;
	result.Y = Y + Other.Y;
	return result;
}

Vector3 Vector3::operator*(float Scale) const
{
	Vector3 result;
	result.X = X * Scale;
	result.Y = Y * Scale;
	result.Z = Z * Scale;
	return result;
}

Vector3 Vector3::operator-(const Vector3& Other) const
{
	Vector3 result;
	result.X = X - Other.X;
	result.Y = Y - Other.Y;
	result.Z = Z - Other.Z;
	return result;
}


Vector3 Vector3::operator+(const Vector3& Other) const
{
	Vector3 result;
	result.X = X + Other.X;
	result.Y = Y + Other.Y;
	result.Z = Z + Other.Z;
	return result;
}

Vector3 Vector3::operator*(const Matrix3& Mat) const
{
	Vector3 result;
	result.X = X * Mat._11 + Y * Mat._12 + Z * Mat._13;
	result.Y = X * Mat._21 + Y * Mat._22 + Z * Mat._23;
	result.Z = X * Mat._31 + Y * Mat._32 + Z * Mat._33;
	return result;
}

Vector3 Vector3::operator*(const Matrix4& Mat) const
{
	Vector3 result;
	result.X = X * Mat._11 + Y * Mat._12 + Z * Mat._13 + Mat._14;
	result.Y = X * Mat._21 + Y * Mat._22 + Z * Mat._23 + Mat._24;
	result.Z = X * Mat._31 + Y * Mat._32 + Z * Mat._33 + Mat._34;
	return result;
}
