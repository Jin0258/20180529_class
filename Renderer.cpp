
#include "stdafx.h"
#include "Vector.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
#include "Renderer.h"
#include "Triangle.h"
#include "Transform.h"
#include "Texture.h"
#include "Camera.h"

Mesh g_Quad;
Transform2D g_MeshTransform2D;
Transform2D g_CameraTransform2D;

Camera g_Camera;
Transform g_MeshTransform;

//Matrix3 g_ShaderMatrix;
Matrix4 g_ShaderMatrix;
bool g_Init = false;

VertInOut VertexShader(VertInOut v);
ULONG FragmentShader(FragIn f);

bool IsInRange(int x, int y)
{
	return (abs(x) < (g_nClientWidth / 2)) && (abs(y) < (g_nClientHeight / 2));
}

void PutPixel(IntPoint pt)
{
	if (!IsInRange(pt.X, pt.Y)) return;

	ULONG* dest = (ULONG*)g_pBits;

	int halfWidth = RoundToInt(g_nClientWidth * 0.5f);
	int halfHeight = RoundToInt(g_nClientHeight * 0.5f);

	DWORD offset = (halfHeight * g_nClientWidth - g_nClientWidth * pt.Y) + (halfWidth + pt.X);
	*(dest + offset) = g_CurrentColor;
}

void DrawLine(const Vector3& start, const Vector3& end)
{
	float length = (end - start).Dist();
	float inc = 1.0f / length;

	int maxLength = RoundToInt(length);
	for (int i = 0; i <= maxLength; i++)
	{
		float t = inc * i;
		if (t >= length) t = 1.0f;
		Vector3 Pt = start * (1.0f - t) + end * t;
		PutPixel(Pt.ToIntPoint());
	}
}

void InitFrame(void)
{
	//Vertex Vertices[4] = { 
	//	{ { -30.0f, -30.0f, 1.0f }, RGB32(255, 0, 0) ,{ 0.125f, 0.25f } },
	//	{ { -30.0f, 30.0f, 1.0f }, RGB32(0, 255, 0) ,{ 0.125f, 0.125f } },
	//	{ { 30.0f, 30.0f, 1.0f }, RGB32(0, 0, 255) ,{ 0.25f, 0.125f } },
	//	{ { 30.0f, -30.0f, 1.0f }, RGB32(255, 0, 255) ,{ 0.25f, 0.25f } }
	//};

	//int Indices[6] = { 0, 1, 2, 0, 2, 3 };
	//g_Quad.VSize = 4;
	//g_Quad.ISize = 6;

	Vertex Vertices[3] = {
		{ { 30.0f, 0, 0 }, RGB32(255, 0, 0) ,{ 0.125f, 0.25f } },
		{ { 0, 0, 30.0f }, RGB32(0, 255, 0) ,{ 0.125f, 0.125f } },
		{ { 0, 30.0f, 0 }, RGB32(0, 0, 255) ,{ 0.25f, 0.125f } }
	};

	int Indices[6] = { 0, 1, 2 };
	g_Quad.VSize = 3;
	g_Quad.ISize = 3;


	g_Quad.Vertices = new Vertex[g_Quad.VSize];
	memcpy(g_Quad.Vertices, Vertices, sizeof(Vertex) * g_Quad.VSize);
	g_Quad.Indices = new int[g_Quad.ISize];
	memcpy(g_Quad.Indices, Indices, sizeof(int) * g_Quad.ISize);

	g_Camera.SetLocation(Vector3(50.0f, 50.0f, 50.0f));
	g_Init = true;
}

void UpdateFrame(void)
{
	// First Frame Init
	if(!g_Init) InitFrame();

	// Buffer Clear
	SetColor(32, 128, 255);
	Clear();

	// Mesh Transform and Camera Setting
	static Vector3 meshLocation(0.0f, 0.0f, 0.0f);

	// Set Camera
	if (GetAsyncKeyState(VK_LSHIFT))
	{
		if (GetAsyncKeyState(VK_LEFT)) g_Camera.AddRotationYaw(1.0f);
		if (GetAsyncKeyState(VK_RIGHT)) g_Camera.AddRotationYaw(-1.0f);
		if (GetAsyncKeyState(VK_UP)) g_Camera.AddRotationPitch(1.0f);
		if (GetAsyncKeyState(VK_DOWN)) g_Camera.AddRotationPitch(-1.0f);
		if (GetAsyncKeyState(VK_PRIOR)) g_Camera.AddFOV(1.0f);
		if (GetAsyncKeyState(VK_NEXT)) g_Camera.AddFOV(-1.0f);
	}
	else
	{
		if (GetAsyncKeyState(VK_LEFT)) meshLocation.X -= 1.0f;
		if (GetAsyncKeyState(VK_RIGHT)) meshLocation.X += 1.0f;
		if (GetAsyncKeyState(VK_UP)) meshLocation.Y += 1.0f;
		if (GetAsyncKeyState(VK_DOWN)) meshLocation.Y -= 1.0f;
		if (GetAsyncKeyState(VK_PRIOR)) meshLocation.Z += 1.0f;
		if (GetAsyncKeyState(VK_NEXT)) meshLocation.Z -= 1.0f;
	}

	g_MeshTransform.SetLocation(meshLocation);
	Matrix4 MMat = g_MeshTransform.GetTRSMatrix();
	Matrix4 VMat = g_Camera.GetViewMatrix(Vector3(0.0f, 0.0f, 0.0f));
	Matrix4 PMat = g_Camera.GetPerspectiveMatrix();
	g_ShaderMatrix = PMat * VMat * MMat;
	
	// Draw Axis
	Vector3 Origin(0.0f, 0.0f, 0.0f);
	Vector3 XAxis(5000.0f, 0.0f, 0.0f);
	Vector3 YAxis(0.0f, 5000.0f, 0.0f);
	Vector3 ZAxis(0.0f, 0.0f, 5000.0f);

	SetColor(255, 0, 0);
	DrawLine(Origin * VMat * PMat, XAxis * VMat * PMat);
	SetColor(0, 255, 0);
	DrawLine(Origin * VMat * PMat, YAxis * VMat * PMat);
	SetColor(0, 0, 255);
	DrawLine(Origin * VMat * PMat, ZAxis * VMat * PMat);

	// Draw
	DrawCall(&g_Quad);

	// Buffer Swap 
	BufferSwap();
}

void DrawCall(Mesh * MeshToDraw)
{
	if (MeshToDraw->IsInitialized())
	{
		VertInOut* vOut = new VertInOut[MeshToDraw->VSize];
		// Vertex Shader
		for (int i = 0; i < MeshToDraw->VSize; i++)
		{
			Vertex vt = MeshToDraw->Vertices[i];
			VertInOut vIn(vt.position, vt.uv, vt.color);
			vOut[i] = VertexShader(vIn);
		}

		// Rasterization
		for (int i = 0; i < MeshToDraw->ISize; i += 3)
		{
			int index1 = MeshToDraw->Indices[i];
			int index2 = MeshToDraw->Indices[i + 1];
			int index3 = MeshToDraw->Indices[i + 2];

			Triangle t(vOut[index1], vOut[index2], vOut[index3]);
			for (int y = t.Min.Y; y <= t.Max.Y; y++)
			{
				for (int x = t.Min.X; x <= t.Max.X; x++)
				{
					IntPoint target(x, y);
					float outS, outT;
					t.CalcBaryCentricCoord(target, &outS, &outT);
					if (t.IsInTrianble(outS, outT))
					{
						// Fragment Shader
						FragIn frag = t.GetFragment(outS, outT);
						g_CurrentColor = FragmentShader(frag);
						PutPixel(target);
					}
				}
			}
		}
	}
}

VertInOut VertexShader(VertInOut v)
{
	VertInOut result;
	result.color = v.color;
	result.uv = v.uv;
	result.position = v.position * g_ShaderMatrix;
	return result;
}

ULONG FragmentShader(FragIn f)
{
	ULONG finalColor;
	if (g_Texture->IsLoaded())
	{
		finalColor = g_Texture->GetTexturePixel(f.uv);
	}
	else
	{
		finalColor = f.color;
	}

	return finalColor;
}
