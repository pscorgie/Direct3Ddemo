#include "Camera.h"


Camera::Camera(XMFLOAT3 position, XMFLOAT3 at, XMFLOAT3 up, FLOAT windowWidth, FLOAT windowHeight, FLOAT nearDepth, FLOAT farDepth)
	: _position(position), _lookAt(at), _up(up), _windowWidth(windowWidth), _windowHeight(windowHeight), _nearDepth(nearDepth), _farDepth(farDepth)
{
	// Calculate the lookAt vector by the difference between points "at" and position
	XMFLOAT3 Look = XMFLOAT3(at.x - position.x, at.y - position.y, at.z - position.z);
	XMVECTOR L = XMLoadFloat3(&Look);
	L = XMVector3Normalize(L);
	XMStoreFloat3(&_lookAt, L);

	// Calculate the Right vector 
	XMVECTOR Up = XMLoadFloat3(&_up);
	XMVECTOR Right = XMVector3Cross(Up, L);
	Right = XMVector3Normalize(Right);
	XMStoreFloat3(&_right, Right);

	// reCalculate the Up vector
	Up = XMVector3Cross(L, Right);
	Up = XMVector3Normalize(Up);
	XMStoreFloat3(&_up, Up);

	XMStoreFloat4x4(&_projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, _windowWidth / _windowHeight, _nearDepth, _farDepth));
}


Camera::~Camera()
{
}
void Camera::Reset()
{
	XMFLOAT3 Look = _lookAt;
	XMVECTOR L = XMLoadFloat3(&Look);
	L = XMVector3Normalize(L);
	XMStoreFloat3(&_lookAt, L);

	// Calculate the Right vector 
	XMVECTOR Up = XMLoadFloat3(&_up);
	XMVECTOR Right = XMVector3Cross(Up, L);
	Right = XMVector3Normalize(Right);
	XMStoreFloat3(&_right, Right);

	// reCalculate the Up vector
	Up = XMVector3Cross(L, Right);
	Up = XMVector3Normalize(Up);
	XMStoreFloat3(&_up, Up);

	XMStoreFloat4x4(&_projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, _windowWidth / _windowHeight, _nearDepth, _farDepth));
}


void Camera::CalculateViewProjection()
{
	XMVECTOR Look = XMLoadFloat3(&_lookAt);
	XMVECTOR Up = XMLoadFloat3(&_up);
	XMVECTOR Right = XMLoadFloat3(&_right);
	XMVECTOR Position = XMLoadFloat3(&_position); // need for dot calculations later

	Look = XMVector3Normalize(Look);
	XMStoreFloat3(&_lookAt, Look);

	// Calculate the Up vector
	
	Up = XMVector3Cross(Look, Right);
	Up = XMVector3Normalize(Up);
	XMStoreFloat3(&_up, Up);
	
	// Calculate the Right vector 
	Right = XMVector3Cross(Up, Look);
	XMStoreFloat3(&_right, Right);

	_view(0, 0) = _right.x;
	_view(1, 0) = _right.y;
	_view(2, 0) = _right.z;
	_view(3, 0) = -XMVectorGetX(XMVector3Dot(Position, Right));

	_view(0, 1) = _up.x;
	_view(1, 1) = _up.y;
	_view(2, 1) = _up.z;
	_view(3, 1) = -XMVectorGetX(XMVector3Dot(Position, Up));

	_view(0, 2) = _lookAt.x;
	_view(1, 2) = _lookAt.y;
	_view(2, 2) = _lookAt.z;
	_view(3, 2) = -XMVectorGetX(XMVector3Dot(Position, Look));

	_view(0, 3) = 0.0f;
	_view(1, 3) = 0.0f;
	_view(2, 3) = 0.0f;
	_view(3, 3) = 1.0f;
	
}


XMFLOAT4X4 Camera::GetViewProjection() const
{
	XMMATRIX view = XMLoadFloat4x4(&_view);
	XMMATRIX projection = XMLoadFloat4x4(&_projection);

	XMFLOAT4X4 viewProj;
	
	XMStoreFloat4x4(&viewProj, view * projection);

	return viewProj;
}


void Camera::Reshape(FLOAT windowWidth, FLOAT windowHeight, FLOAT nearDepth, FLOAT farDepth)
{
	_windowWidth = windowWidth;
	_windowHeight = windowHeight;
	_nearDepth = nearDepth;
	_farDepth = farDepth;

	XMStoreFloat4x4(&_projection, XMMatrixPerspectiveFovLH(XM_PIDIV2, _windowWidth / _windowHeight, _nearDepth, _farDepth));
}
void Camera::Pitch(float p)
{
	XMMATRIX rotate = XMMatrixRotationAxis(XMLoadFloat3(&_right), p);

	XMStoreFloat3(&_up, XMVector3TransformNormal(XMLoadFloat3(&_up), rotate));
	XMStoreFloat3(&_lookAt, XMVector3TransformNormal(XMLoadFloat3(&_lookAt), rotate));
}
void Camera::RotateY(float r)
{
	XMMATRIX rotate = XMMatrixRotationY(r);

	XMStoreFloat3(&_up, XMVector3TransformNormal(XMLoadFloat3(&_up), rotate));
	XMStoreFloat3(&_right, XMVector3TransformNormal(XMLoadFloat3(&_right), rotate));
	XMStoreFloat3(&_lookAt, XMVector3TransformNormal(XMLoadFloat3(&_lookAt), rotate));
}
void Camera::Move(float d)
{
	// move position vector by distance d along the look vector
	XMVECTOR moveVec = XMVectorReplicate(d);
	XMVECTOR look = XMLoadFloat3(&_lookAt);
	XMVECTOR position = XMLoadFloat3(&_position);

	XMStoreFloat3(&_position, XMVectorMultiplyAdd(moveVec, look, position));
}
void Camera::Strafe(float d)
{
	// move position vector by distance d along the right vector
	XMVECTOR moveVec = XMVectorReplicate(d);
	XMVECTOR right = XMLoadFloat3(&_right);
	XMVECTOR position = XMLoadFloat3(&_position);

	XMStoreFloat3(&_position, XMVectorMultiplyAdd(moveVec, right, position));
}