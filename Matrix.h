#pragma once

#include "stdafx.h"

struct Matrix2
{
public:
	float _11, _12;
	float _21, _22;

	Matrix2()
	{ 
		SetIdentity(); 
	}

	void SetScale(float a, float b)
	{
		SetIdentity();
		_11 = a;
		_22 = b;
	}

	void SetIdentity()
	{
		_11 = 1.0f;
		_12 = 0.0f;

		_21 = 0.0f;
		_22 = 1.0f;
	}

	void SetRotation(float degree)
	{
		float radian = Deg2Rad(degree);
		_11 = cosf(radian);
		_12 = -sinf(radian);
		_21 = sinf(radian);
		_22 = cosf(radian);
	}

	Matrix2 operator *(const Matrix2 Other) const;
};

struct Matrix3
{
public:
	float _11, _12, _13;
	float _21, _22, _23;
	float _31, _32, _33;

	Matrix3()
	{
		SetIdentity();
	}

	void SetTranslation(float InX, float InY)
	{
		SetIdentity();
		_13 = InX;
		_23 = InY;
	}

	void SetScale(float a)
	{
		SetIdentity();
		_11 = a;
		_22 = a;
	}

	void SetIdentity()
	{
		_11 = 1.0f;
		_12 = 0.0f;
		_13 = 0.0f;
		_21 = 0.0f;
		_22 = 1.0f;
		_23 = 0.0f;
		_31 = 0.0f;
		_32 = 0.0f;
		_33 = 1.0f;
	}

	void SetRotation(float degree)
	{
		SetIdentity();
		_11 = cosf(Deg2Rad(degree));
		_12 = -sinf(Deg2Rad(degree));
		_21 = -_12;
		_22 = _11;
	}

	void Tranpose()
	{
		float temp = _12;
		_12 = _21;
		_21 = temp;

		temp = _13;
		_13 = _31;
		_31 = temp;

		temp = _23;
		_23 = _32;
		_32 = temp;
	}

	Matrix3 operator *(const Matrix3 Other) const;
};

struct Matrix4 
{
public:
	float _11, _12, _13, _14;
	float _21, _22, _23, _24;
	float _31, _32, _33, _34;
	float _41, _42, _43, _44;

	Matrix4()
	{
		SetIdentity();
	}

	void SetTranslation(float InX, float InY, float InZ)
	{
		SetIdentity();
		_14 = InX;
		_24 = InY;
		_34 = InZ;
	}

	void SetScale(float InScale)
	{
		SetIdentity();
		_11 = InScale;
		_22 = InScale;
		_33 = InScale;
	}

	void SetScale(float InX, float InY, float InZ)
	{
		SetIdentity();
		_11 = InX;
		_22 = InY;
		_33 = InZ;
	}

	void SetRotationX(float Degree)
	{
		SetIdentity();
		float s = sinf(Deg2Rad(Degree));
		float c = cosf(Deg2Rad(Degree));
		_22 = c;
		_32 = -s;
		_23 = s;
		_33 = c;
	}

	void SetRotationY(float Degree)
	{
		SetIdentity();
		float s = sinf(Deg2Rad(Degree));
		float c = cosf(Deg2Rad(Degree));
		_11 = c;
		_13 = -s;
		_31 = s;
		_33 = c;
	}

	void SetRotationZ(float Degree)
	{
		SetIdentity();
		float s = sinf(Deg2Rad(Degree));
		float c = cosf(Deg2Rad(Degree));
		_11 = c;
		_12 = -s;
		_21 = s;
		_22 = c;
	}

	void SetIdentity()
	{
		_11 = 1.0f;
		_12 = 0.0f;
		_13 = 0.0f;
		_14 = 0.0f;

		_21 = 0.0f;
		_22 = 1.0f;
		_23 = 0.0f;
		_24 = 0.0f;

		_31 = 0.0f;
		_32 = 0.0f;
		_33 = 1.0f;
		_34 = 0.0f;

		_41 = 0.0f;
		_42 = 0.0f;
		_43 = 0.0f;
		_44 = 1.0f;
	};

	void Transpose()
	{
		float Temp;
		Temp = _12;
		_12 = _21;
		_21 = Temp;

		Temp = _13;
		_13 = _31;
		_31 = Temp;

		Temp = _14;
		_14 = _41;
		_41 = Temp;

		Temp = _23;
		_23 = _32;
		_32 = Temp;

		Temp = _24;
		_24 = _42;
		_42 = Temp;

		Temp = _34;
		_34 = _43;
		_43 = Temp;
	}

	Matrix4 operator *(const Matrix4 Other) const;
};
