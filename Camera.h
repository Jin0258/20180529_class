#pragma once

#include "SphericalCoord.h"

class Camera
{
public:
	Camera() : FOV(45.0f), Aspect(1.33333f), NearZ(128.0f), FarZ(100000.0f)
	{
	}

	Vector3 GetLocation()
	{ 
		return SC.ToCartesian(); 
	}

	void SetLocation(const Vector3& InLocation)
	{
		SC.SetCoordinate(InLocation);
	}

	Vector3 AddRotationYaw(float DeltaDegree)
	{
		return SC.AddRotationYaw(DeltaDegree);
	}

	Vector3 AddRotationPitch(float DeltaDegree)
	{
		return SC.AddRotationPitch(DeltaDegree);
	}

	float AddFOV(float DeltaMove)
	{
		FOV += DeltaMove;
		return FOV;
	}

	Matrix4 GetViewMatrix(Vector3 TargetLocation)
	{
		Vector3 Location = GetLocation();
		Matrix4 TMat;
		TMat.SetTranslation(-Location.X, -Location.Y, -Location.Z);
		Vector3 Up(0.0f, 1.0f, 0.0f);
		Vector3 Z = (TargetLocation - Location).Normalize();
		Vector3 X = Up.Cross(Z).Normalize();
		Vector3 Y = Z.Cross(X).Normalize();;

		Matrix4 RMat;
		RMat.SetIdentity();

		RMat._11 = X.X;
		RMat._12 = X.Y;
		RMat._13 = X.Z;
		RMat._21 = Y.X;
		RMat._22 = Y.Y;
		RMat._23 = Y.Z;
		RMat._31 = Z.X;
		RMat._32 = Z.Y;
		RMat._33 = Z.Z;

		return TMat * RMat;
	}

	Matrix4 GetPerspectiveMatrix()
	{
		Matrix4 PMat;
		PMat.SetIdentity();
		PMat._44 = 0.0f;

		float FOVRadian = Deg2Rad(FOV * 0.5f);
		float d = 1.0f / tanf(FOVRadian);
		float a = Aspect;
		float n = NearZ;
		float f = FarZ;

		PMat._11 = d / a;
		PMat._22 = d;
		PMat._33 = (n + f) / (n - f);
		PMat._34 = (2.0f * n*f) / (n - f);
		PMat._43 = -1;
		return PMat;
	}

private:
	float FOV;
	float Aspect;
	float NearZ;
	float FarZ;
	SphericalCoordinate SC;
};