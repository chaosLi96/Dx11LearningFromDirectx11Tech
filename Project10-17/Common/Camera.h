#pragma once

#include"WinMin.h"
#include<d3d11_1.h>
#include<DirectXMath.h>
#include "Transform.h"

using namespace DirectX;

class Camera
{
public:
	Camera() = default;
	virtual ~Camera() = 0;

	XMVECTOR GetPositionXM() const;
	XMFLOAT3 GetPosition() const;

	float GetRotationX() const;
	float GetRotationY() const;

	XMVECTOR GetRightAxisXM() const;
	XMFLOAT3 GetRightAxis() const;
	XMVECTOR GetUpAxisXM()const;
	XMFLOAT3 GetUpAxis() const;
	XMVECTOR GetLookAxisXM() const;
	XMFLOAT3 GetLookAxis() const;


	XMMATRIX GetViewXM() const;
	XMMATRIX GetProjXM() const;
	XMMATRIX GetViewProjXM() const;

	D3D11_VIEWPORT GetViewPort() const;

	void SetFrustum(float fovY, float aspect, float nearZ, float farZ);
	
	void SetViewPort(const D3D11_VIEWPORT& viewPort);
	void SetViewPort(float topLeftX, float topLeftY, float width, float height, float minDepth = 0.f, float maxDepth = 1.0f);

protected:
	Transform m_Transform = {};
	float m_NearZ = 0.f;
	float m_FarZ = 0.f;
	float m_Aspect = 0.f;
	float m_FovY = 0.f;

	D3D11_VIEWPORT m_viewPort = {};	
};


class FirstPersonCamera : public Camera
{
public:
	FirstPersonCamera() = default;
	~FirstPersonCamera() override;

	void SetPosition(float x, float y, float z);
	void SetPosition(const XMFLOAT3& pos);

	void LookAt(const XMFLOAT3& pos, const XMFLOAT3& target, const XMFLOAT3& up);
	void LookTo(const XMFLOAT3& pos, const XMFLOAT3& to, const XMFLOAT3& up);

	void Strafe(float d);
	void Walk(float d);
	void MoveForward(float d);
	void Pitch(float rad);
	void RotateY(float rad);
};