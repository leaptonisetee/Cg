#include "pch.h"

void Transform::SetPosition(float x, float y, float z)
{
	this->position = Vector3(x, y, z);
}

void Transform::OffsetPosition(float deltaX, float deltaY, float deltaZ)
{
	this->position += Vector3(deltaX, deltaY, deltaZ);
}

void Transform::SetScale(float scale)
{
	this->scale = Vector3(scale, scale, scale);
}

void Transform::SetScale(float x, float y, float z)
{
	this->scale = Vector3(x, y, z);
}

void Transform::SetRotation(float roll, float pitch, float yaw)
{
	this->rotation = XMQuaternionRotationRollPitchYaw(roll, pitch, yaw);
}

void Transform::SetRotation(Quaternion rotation)
{
	this->rotation = rotation;
}

Vector3 Transform::GetAbsolutePosition()
{
	if (parent != nullptr) return position + parent->GetAbsolutePosition();
	return position;
}

XMMATRIX Transform::GetWorldMatrix()
{
	auto scaleMatrix = XMMatrixScalingFromVector(scale);
	auto translationMatrix = XMMatrixTranslationFromVector( GetAbsolutePosition() );
	auto rotationMatrix = XMMatrixRotationQuaternion(rotation);

	return scaleMatrix * rotationMatrix * translationMatrix;
}