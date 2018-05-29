
#include "stdafx.h"
#include "Matrix.h"


Matrix2 Matrix2::operator *(const Matrix2 Other) const
{
	Matrix2 result;

	result._11 = _11 * Other._11 + _12 * Other._21;
	result._12 = _11 * Other._12 + _12 * Other._22;
	result._21 = _21 * Other._11 + _22 * Other._21;
	result._22 = _21 * Other._12 + _22 * Other._22;

	return result;
}

Matrix3 Matrix3::operator *(const Matrix3 Other) const
{
	Matrix3 result;

	result._11 = _11 * Other._11 + _12 * Other._21 + _13 * Other._31;
	result._12 = _11 * Other._12 + _12 * Other._22 + _13 * Other._32;
	result._13 = _11 * Other._13 + _12 * Other._23 + _13 * Other._33;
	result._21 = _21 * Other._11 + _22 * Other._21 + _23 * Other._31;
	result._22 = _21 * Other._12 + _22 * Other._22 + _23 * Other._32;
	result._23 = _21 * Other._13 + _22 * Other._23 + _23 * Other._33;
	result._31 = _31 * Other._11 + _32 * Other._21 + _33 * Other._31;
	result._32 = _31 * Other._12 + _32 * Other._22 + _33 * Other._32;
	result._33 = _31 * Other._13 + _32 * Other._23 + _33 * Other._33;

	return result;
}

Matrix4 Matrix4::operator*(const Matrix4 Other) const
{
	Matrix4 result;

	result._11 = _11 * Other._11 + _12 * Other._21 + _13 * Other._31 + _14 * Other._41;
	result._12 = _11 * Other._12 + _12 * Other._22 + _13 * Other._32 + _14 * Other._42;
	result._13 = _11 * Other._13 + _12 * Other._23 + _13 * Other._33 + _14 * Other._43;
	result._14 = _11 * Other._14 + _12 * Other._24 + _13 * Other._34 + _14 * Other._44;

	result._21 = _21 * Other._11 + _22 * Other._21 + _23 * Other._31 + _24 * Other._41;
	result._22 = _21 * Other._12 + _22 * Other._22 + _23 * Other._32 + _24 * Other._42;
	result._23 = _21 * Other._13 + _22 * Other._23 + _23 * Other._33 + _24 * Other._43;
	result._24 = _21 * Other._14 + _22 * Other._24 + _23 * Other._34 + _24 * Other._44;

	result._31 = _31 * Other._11 + _32 * Other._21 + _33 * Other._31 + _34 * Other._41;
	result._32 = _31 * Other._12 + _32 * Other._22 + _33 * Other._32 + _34 * Other._42;
	result._33 = _31 * Other._13 + _32 * Other._23 + _33 * Other._33 + _34 * Other._43;
	result._34 = _31 * Other._14 + _32 * Other._24 + _33 * Other._34 + _34 * Other._44;

	result._41 = _41 * Other._11 + _42 * Other._21 + _43 * Other._31 + _44 * Other._41;
	result._42 = _41 * Other._12 + _42 * Other._22 + _43 * Other._32 + _44 * Other._42;
	result._43 = _41 * Other._13 + _42 * Other._23 + _43 * Other._33 + _44 * Other._43;
	result._44 = _41 * Other._14 + _42 * Other._24 + _43 * Other._34 + _44 * Other._44;

	return result;
}
