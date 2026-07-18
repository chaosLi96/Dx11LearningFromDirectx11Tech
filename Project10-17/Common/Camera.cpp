#include"Camera.h"

Camera::~Camera()
{

}

XMVECTOR Camera::GetPositionXM() const
{
	return m_Transform.GetPositionXM();
}

XMFLOAT3 Camera::GetPosition() const
{
	return m_Transform.GetPosition();
}

float Camera::GetRotationX() const
{
	return m_Transform.GetRotation().x;
}

float Camera::GetRotationY() const
{
	return m_Transform.GetRotation().y;
}

DirectX::XMVECTOR Camera::GetRightAxisXM() const
{
	return m_Transform.GetRightAxisXM();
}

DirectX::XMFLOAT3 Camera::GetRightAxis() const
{
	return m_Transform.GetRightAxis();
}

DirectX::XMVECTOR Camera::GetUpAxisXM() const
{
	return m_Transform.GetUpAxisXM();
}

DirectX::XMFLOAT3 Camera::GetUpAxis() const
{
	return m_Transform.GetUpAxis();
}

DirectX::XMVECTOR Camera::GetLookAxisXM() const
{
	return m_Transform.GetForwardAxisXM();
}

DirectX::XMFLOAT3 Camera::GetLookAxis() const
{
	return m_Transform.GetForwardAxis();
}

DirectX::XMMATRIX Camera::GetViewXM() const
{
	return m_Transform.GetWorldToLocalMatrixXM();
}

DirectX::XMMATRIX Camera::GetProjXM() const
{
	return XMMatrixPerspectiveFovLH(m_FovY, m_Aspect, m_NearZ, m_FarZ);
}

DirectX::XMMATRIX Camera::GetViewProjXM() const
{
	return GetViewXM() * GetProjXM();
}

D3D11_VIEWPORT Camera::GetViewPort() const
{
	return m_viewPort;
}

void Camera::SetFrustum(float fovY, float aspect, float nearZ, float farZ)
{
	m_FovY = fovY;
	m_Aspect = aspect;
	m_NearZ = nearZ;
	m_FarZ = farZ;
}

void Camera::SetViewPort(const D3D11_VIEWPORT& viewPort)
{
	m_viewPort = viewPort;
}

void Camera::SetViewPort(float topLeftX, float topLeftY, float width, float height, float minDepth /*= 0.f*/, float maxDepth /*= 1.0f*/)
{
	m_viewPort.TopLeftX = topLeftX;
	m_viewPort.TopLeftY = topLeftY;
	m_viewPort.Width = width;
	m_viewPort.Height = height;
	m_viewPort.MinDepth = minDepth;
	m_viewPort.MaxDepth = maxDepth;
}

FirstPersonCamera::~FirstPersonCamera()
{

}

void FirstPersonCamera::SetPosition(float x, float y, float z)
{
	SetPosition(XMFLOAT3(x, y, z));
}

void FirstPersonCamera::SetPosition(const XMFLOAT3& pos)
{
	m_Transform.SetPosition(pos);
}

void FirstPersonCamera::LookAt(const XMFLOAT3& pos, const XMFLOAT3& target, const XMFLOAT3& up)
{
	m_Transform.SetPosition(pos);
	m_Transform.LookAt(target,up);
}

void FirstPersonCamera::LookTo(const XMFLOAT3& pos, const XMFLOAT3& to, const XMFLOAT3& up)
{
	m_Transform.SetPosition(pos);
	m_Transform.LookTo(to, up);
}

void FirstPersonCamera::Strafe(float d)
{
	m_Transform.Translate(m_Transform.GetRightAxis(), d);
}

void FirstPersonCamera::Walk(float d)
{
	XMVECTOR rightVec = m_Transform.GetRightAxisXM();
	XMVECTOR frontVec = XMVector3Normalize(XMVector3Cross(rightVec, g_XMIdentityR1));
	XMFLOAT3 front;
	XMStoreFloat3(&front, frontVec);
	m_Transform.Translate(front,4);
}

void FirstPersonCamera::MoveForward(float d)
{
	m_Transform.Translate(m_Transform.GetForwardAxis(), d);
}

void FirstPersonCamera::Pitch(float rad)
{
	XMFLOAT3 rotation = m_Transform.GetRotation();
	rotation.x += rad;
	if (rotation.x > XM_PI * 7 / 18)
		rotation.x = XM_PI * 7 / 18;
	else if(rotation.x < -XM_PI * 7 / 18)
		rotation.x = - XM_PI * 7 / 18;
	m_Transform.SetRotation(rotation);
}

void FirstPersonCamera::RotateY(float rad)
{
	XMFLOAT3 rotation = m_Transform.GetRotation();
	rotation.y = XMScalarModAngle(rotation.y + rad);
	m_Transform.SetRotation(rotation);
}
