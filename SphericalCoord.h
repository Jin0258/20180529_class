#pragma once

#include "Vector.h"

class SphericalCoordinate
{
public:
	SphericalCoordinate() : Radius(1.0f), Azimuth(0.0f), Elevation(1.0f)
	{

	}

	SphericalCoordinate(Vector3 Cartesian)
	{
		SetCoordinate(Cartesian);
	}

	void SetCoordinate(Vector3 Cartesian)
	{
		Radius = sqrtf(Cartesian.X * Cartesian.X + Cartesian.Y * Cartesian.Y + Cartesian.Z * Cartesian.Z);
		Azimuth = atan2f(Cartesian.Z, Cartesian.X);
		Elevation = asinf(Cartesian.Y / Radius);
	}

	Vector3 ToCartesian()
	{
		float t = Radius * cosf(Elevation);
		Vector3 Cartesian;
		Cartesian.X = t * cosf(Azimuth);
		Cartesian.Y = Radius * sinf(Elevation);
		Cartesian.Z = t * sinf(Azimuth);
		return Cartesian;
	}

	Vector3 AddRotationYaw(float Speed)
	{
		Azimuth += Deg2Rad(Speed);
		return ToCartesian();
	}

	Vector3 AddRotationPitch(float Speed)
	{
		Elevation += Deg2Rad(Speed);
		return ToCartesian();
	}

	Vector3 Zoom(float Speed)
	{
		Radius += Speed;
		return ToCartesian();
	}

private:
	float Radius, Azimuth, Elevation;
};
