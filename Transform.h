#pragma once

#include "Vector.h"

struct Transform2D
{
public:
	Transform2D() {}
	Transform2D(Vector2 InLocation, float InRotation, float InScale = 1.0f) : Location(InLocation), Rotation(InRotation), Scale(InScale){}

	void SetLocation(const Vector2& InLocation) { Location = InLocation; }
	void SetRotation(const float InRotation) { Rotation = InRotation; }
	void SetScale(const float InScale) { Scale = InScale; }
	Matrix3 GetTRSMatrix();
	Matrix3 GetViewMatrix();

	Vector2 Location;
	float Rotation;
	float Scale;
};

struct Transform
{
public:
	Transform() {}
	Transform(Vector3 InLocation, Vector3 InRotation, Vector3 InScale) : Location(InLocation), Rotation(InRotation), Scale(InScale) {}

	void SetLocation(const Vector3& InLocation) { Location = InLocation; }
	Matrix4 GetTRSMatrix();

	Vector3 Location;
	Vector3 Rotation;
	Vector3 Scale;
};