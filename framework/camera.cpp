#include "pch.h"

Camera::Camera(Window& window) : window(window)
{
	DisableLens();
	UpdateViewMatrix();
}

void Camera::SetPosition(float x, float y, float z)
{
	Position = Vector3(x, y, z);
	UpdateViewMatrix();
}

void Camera::SetPosition(Vector3 pos)
{
	Position = pos;
	UpdateViewMatrix();
}

void Camera::SetLook(float x, float y, float z)
{
	Look = Vector3(x, y, z);
	UpdateViewMatrix();
}

void Camera::SetLook(Vector3 target)
{
	Look = target;
	UpdateViewMatrix();
}

void Camera::SetUp(float x, float y, float z)
{
	Up = Vector3(x, y, z);
	UpdateViewMatrix();
}

void Camera::SetUp(Vector3 up)
{
	Up = up;
	UpdateViewMatrix();
}

void Camera::LookAt(Vector3 target, Vector3 worldUp)
{
	XMVECTOR L = XMVector3Normalize(target - Position);
	XMVECTOR R = XMVector3Normalize(XMVector3Cross(worldUp, L));
	XMVECTOR U = XMVector3Cross(L, R);

	XMStoreFloat3(&Look, L);
	XMStoreFloat3(&Right, R);
	XMStoreFloat3(&Up, U);

	UpdateViewMatrix();
}

void Camera::Walk(float distance)
{
	SetPosition(Position + Look * distance);
}

void Camera::Strafe(float distance)
{
	SetPosition(Position + Right * distance);
}

void Camera::Pitch(float angle)
{
	XMMATRIX rotation = XMMatrixRotationAxis(XMLoadFloat3(&Right), angle);

	XMStoreFloat3(&Up, XMVector3TransformNormal(XMLoadFloat3(&Up), rotation));
	XMStoreFloat3(&Look, XMVector3TransformNormal(XMLoadFloat3(&Look), rotation));

	UpdateViewMatrix();
}

void Camera::RotateY(float angle)
{
	XMMATRIX rotation = XMMatrixRotationY(angle);

	XMStoreFloat3(&Right, XMVector3TransformNormal(XMLoadFloat3(&Right), rotation));
	XMStoreFloat3(&Up, XMVector3TransformNormal(XMLoadFloat3(&Up), rotation));
	XMStoreFloat3(&Look, XMVector3TransformNormal(XMLoadFloat3(&Look), rotation));

	UpdateViewMatrix();
}

void Camera::DisableLens()
{
	this->fovY = -1;
	this->zNear = -1;
	this->zFar = -1;

	ProjectionMatrix = XMMatrixIdentity();
}

void Camera::SetLens(float fovY, float zNear, float zFar)
{
	this->fovY = fovY;
	this->zNear = zNear;
	this->zFar = zFar;

	nearWindowHeight = 2.0f * zNear * tanf(0.5f * fovY);
	farWindowHeight = 2.0f * zFar * tanf(0.5f * fovY);
	
	UpdateProjectionMatrix();
}

void Camera::UpdateViewMatrix()
{
	XMVECTOR pos = XMLoadFloat3(&Position);
	XMVECTOR look = XMLoadFloat3(&Look);
	XMVECTOR up = XMLoadFloat3(&Up);
	XMVECTOR right = XMLoadFloat3(&Right);

	look = XMVector3Normalize(look);
	right = XMVector3Normalize(XMVector3Cross(up, look));
	up = XMVector3Cross(look, right);

	XMStoreFloat3(&Look, look);
	XMStoreFloat3(&Right, right);
	XMStoreFloat3(&Up, up);

	ViewMatrix = XMMatrixLookAtLH(pos, pos + look, up);
}

void Camera::UpdateProjectionMatrix()
{
	if (fovY > 0 && zNear > 0 && zFar > 0)
	{
		ProjectionMatrix = XMMatrixPerspectiveFovLH(fovY, window.GetAspectRatio(), zNear, zFar);
	}
}

XMFLOAT4X4 Camera::GetWVPMatrix(Transform& transform)
{
	auto wvpMatrix = transform.GetWorldMatrix() * ViewMatrix * ProjectionMatrix;

	auto transposed = XMMatrixTranspose(wvpMatrix);

	XMFLOAT4X4 result;
	XMStoreFloat4x4(&result, transposed);
	return result;
}