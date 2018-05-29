#pragma once

#include "stdafx.h"
#include "Matrix.h"

struct IntPoint
{
public:
	int X;
	int Y;

public:
	IntPoint() : X(0), Y(0) {}
	IntPoint(int InX, int InY) : X(InX), Y(InY) {}

};

struct Vector2
{
public:
	float X;
	float Y;

public:
	Vector2() : X(0), Y(0) {}
	Vector2(float InX, float InY) : X(InX), Y(InY) {}

	static float Dist(const Vector2 &V1, const Vector2 &V2);
	static float DistSquared(const Vector2 &V1, const Vector2 &V2);

	Vector2 operator *(float Scale) const;
	Vector2 operator *(const Matrix2& Mat) const;
	bool Equals(const Vector2& Other, float Tolerance = KINDA_SMALL_NUMBER) const;

	IntPoint ToIntPoint() 
	{
		return IntPoint((int)(X), (int)(Y));
	}

	float Dot(const Vector2& Other) const
	{
		return X * Other.X + Y * Other.Y;
	}

	Vector2 operator+(const Vector2& Other) const;
	Vector2 operator-(const Vector2& Other) const;

};

FORCEINLINE bool Vector2::Equals(const Vector2& Other, float Tolerance) const
{
	return fabs(X - Other.X) <= Tolerance && fabs(Y - Other.Y) <= Tolerance;
}

struct Vector3
{
public:
	float X;
	float Y;
	float Z;

	Vector3() : X(0), Y(0), Z(0) {}
	Vector3(float InX, float InY, float InZ) : X(InX), Y(InY), Z(InZ) {}

	void SetPoint(float InX, float InY)
	{
		X = InX;
		Y = InY;
		Z = 1.0f;
	}

	void SetVector(float InX, float InY)
	{
		X = InX;
		Y = InY;
		Z = 0.0f;
	}

	float Dist()
	{
		return sqrtf(DistSquared());
	}

	float DistSquared()
	{
		return X * X + Y * Y;
	}

	Vector2 ToVector2()
	{
		Vector2 result(X, Y);
		return result;
	}

	IntPoint ToIntPoint()
	{
		return IntPoint(RoundToInt(X), RoundToInt(Y));
	}

	float Dot(const Vector3 Other) const
	{
		return X * Other.X + Y * Other.Y + Z * Other.Z;
	}

	Vector3 Cross(const Vector3 &Other) const
	{
		Vector3 Result;
		Result.X = Y * Other.Z - Z * Other.Y;
		Result.Y = Z * Other.X - X * Other.Z;
		Result.Z = X * Other.Y - Y * Other.X;
		return Result;
	}

	Vector3 Normalize(void)
	{
		float invlength = 1 / sqrtf(X * X + Y * Y + Z * Z);
		return Vector3(X * invlength, Y * invlength, Z * invlength);
	}

	Vector3 operator*(float Scale) const;
	Vector3 operator+(const Vector3& Other) const;
	Vector3 operator-(const Vector3& Other) const;
	Vector3 operator *(const Matrix3& Mat) const;
	Vector3 operator *(const Matrix4& Mat) const;
};