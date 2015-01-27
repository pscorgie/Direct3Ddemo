#include "OrthoCamera.h"


OrthoCamera::OrthoCamera()
{
	_eye = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_up = XMFLOAT3(0.0f, 0.0f, 1.0f);
	_look = XMFLOAT3(0.0f, -1.0f, 0.0f);
}


OrthoCamera::~OrthoCamera()
{
}
void OrthoCamera::UpdateViewMatrix()
{
	XMVECTOR Eye = XMLoadFloat3(&_eye);
	XMVECTOR At = XMLoadFloat3(&_look);
	XMVECTOR Up = XMLoadFloat3(&_up);

	XMStoreFloat4x4(&_view, XMMatrixLookAtLH(Eye, At, Up));

}
void OrthoCamera::setLens(float width, float height, float zNear, float zFar)
{
	XMStoreFloat4x4(&_projection, XMMatrixOrthographicLH(width, height, zNear, zFar));

	UpdateViewMatrix();
}
void OrthoCamera::Reset()
{
	_eye = XMFLOAT3(0.0f, 0.0f, 0.0f);
	_up = XMFLOAT3(0.0f, 0.0f, 1.0f);
	_look = XMFLOAT3(0.0f, -1.0f, 0.0f);

	XMVECTOR Eye = XMLoadFloat3(&_eye);
	XMVECTOR At = XMLoadFloat3(&_look);
	XMVECTOR Up = XMLoadFloat3(&_up);

	XMStoreFloat4x4(&_view, XMMatrixLookAtLH(Eye, At, Up));
}