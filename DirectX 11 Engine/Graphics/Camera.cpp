#include "Camera.h"

Camera::Camera()
{
	this->pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->posVector = XMLoadFloat3(&this->pos);
	this->rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->rotVector = XMLoadFloat3(&this->rot);
	UpdateViewMatrix();
}

void Camera::SetProjectionValues(float fovDegrees, float aspectRatio, float nearZ, float farZ)
{
	float fovRadians = (fovDegrees / 360.0f) * XM_2PI;
	this->projectionMatrix = XMMatrixPerspectiveFovLH(fovRadians, aspectRatio, nearZ, farZ);
}

const XMMATRIX& Camera::GetViewMatrix() const
{
	return this->viewmatrix;
}

const XMMATRIX& Camera::GetProjectionMatrix() const
{
	return this->projectionMatrix;
}

const XMVECTOR& Camera::GetPositionVector() const
{
	return this->posVector;
}

const XMFLOAT3& Camera::GetPositionFloat3() const
{
	return this->pos;
}

const XMVECTOR& Camera::GetRotationVector() const
{
	return this->rotVector;
}

const XMFLOAT3& Camera::GetRotationFloat3() const
{
	return this->rot;
}

void Camera::SetPosition(const XMVECTOR& pos)
{
	XMStoreFloat3(&this->pos, pos);
	this->posVector = pos;
	this->UpdateViewMatrix();
}

void Camera::SetPosition(float x, float y, float z)
{
	this->pos = XMFLOAT3(x, y, z);
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateViewMatrix();
}

void Camera::AdjustPosition(const XMVECTOR& pos)
{
	this->posVector += pos;
	XMStoreFloat3(&this->pos, this->posVector);
	this->UpdateViewMatrix();
}

void Camera::AdjustPosition(float x, float y, float z)
{
	this->pos.x += x;
	this->pos.y += y;
	this->pos.z += z;
	this->posVector = XMLoadFloat3(&this->pos);
	this->UpdateViewMatrix();
}

void Camera::SetRotation(const XMVECTOR& rot)
{
	this->rotVector = rot;
	XMStoreFloat3(&this->rot, rot);
	this->UpdateViewMatrix();
}

void Camera::SetRotation(float x, float y, float z)
{
	this->rot = XMFLOAT3(x, y, z);
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateViewMatrix();
}

void Camera::AdjustRotation(const XMVECTOR& rot)
{
	this->rotVector += rot;
	XMStoreFloat3(&this->rot, this->rotVector);
	this->UpdateViewMatrix();
}

void Camera::AdjustRotation(float x, float y, float z)
{
	this->rot.x += x;
	this->rot.y += y;
	this->rot.z += z;
	this->rotVector = XMLoadFloat3(&this->rot);
	this->UpdateViewMatrix();
}

void Camera::SetLookAtPos(XMFLOAT3 lookAtPos)
{
	if (lookAtPos.x == this->pos.x && lookAtPos.y == this->pos.y && lookAtPos.z == this->pos.z)
		return;

	lookAtPos.x = this->pos.x - lookAtPos.x;
	lookAtPos.y = this->pos.y - lookAtPos.y;
	lookAtPos.z = this->pos.z - lookAtPos.z;

	float pitch = 0.0f;
	if (lookAtPos.y != 0.0f)
	{
		const float distance = sqrt(lookAtPos.x * lookAtPos.x + lookAtPos.z * lookAtPos.z);
		pitch = atan(lookAtPos.y / distance);
	}

	float yaw = 0.0f;
	if (lookAtPos.x != 0.0f)
	{
		yaw = atan(lookAtPos.x / lookAtPos.z);
	}
	if (lookAtPos.z > 0)
		yaw += XM_PI;

	this->SetRotation(pitch, yaw, 0.0f);
}

const XMVECTOR& Camera::GetForwardVector()
{
	return this->vec_forward;
}

const XMVECTOR& Camera::GetRightVector()
{
	return this->vec_right;
}

const XMVECTOR& Camera::GetBackwardVector()
{
	return this->vec_backward;
}

const XMVECTOR& Camera::GetLeftVector()
{
	return this->vec_left;
}

void Camera::UpdateViewMatrix()
{
	XMMATRIX camRotationMatrix = XMMatrixRotationRollPitchYaw(this->rot.x, this->rot.y, this->rot.z);
	XMVECTOR camTarget = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, camRotationMatrix);
	camTarget += this->posVector;
	XMVECTOR upDir = XMVector3TransformCoord(this->DEFAULT_UP_VECTOR, camRotationMatrix);
	this->viewmatrix = XMMatrixLookAtLH(this->posVector, camTarget, upDir);

	XMMATRIX vecRotationMatrix = XMMatrixRotationRollPitchYaw(0.0f, this->rot.y, 0.0f);
	this->vec_forward = XMVector3TransformCoord(this->DEFAULT_FORWARD_VECTOR, vecRotationMatrix);
	this->vec_backward = XMVector3TransformCoord(this->DEFAULT_BACKWARD_VECTOR, vecRotationMatrix);
	this->vec_left = XMVector3TransformCoord(this->DEFAULT_LEFT_VECTOR, vecRotationMatrix);
	this->vec_right = XMVector3TransformCoord(this->DEFAULT_RIGHT_VECTOR, vecRotationMatrix);
}
