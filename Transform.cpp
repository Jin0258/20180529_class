
#include "stdafx.h"
#include "Transform.h"

Matrix3 Transform2D::GetTRSMatrix()
{
	Matrix3 TMat, RMat, SMat;
	TMat.SetTranslation(Location.X, Location.Y);
	RMat.SetRotation(Rotation);
	SMat.SetScale(Scale);

	return TMat * RMat * SMat;
}

Matrix3 Transform2D::GetViewMatrix()
{
	Matrix3 TMat, RMat;
	TMat.SetTranslation(-Location.X, -Location.Y);
	RMat.SetRotation(Rotation);
	RMat.Tranpose();

	return RMat * TMat;
}

Matrix4 Transform::GetTRSMatrix()
{
	Matrix4 TMat;
	TMat.SetTranslation(Location.X, Location.Y, Location.Z);

	return TMat;
}
