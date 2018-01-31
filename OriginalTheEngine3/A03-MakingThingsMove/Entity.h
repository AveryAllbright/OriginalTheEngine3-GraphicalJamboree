#pragma once
#include "Mesh.h"
#include <DirectXMath.h>
using vec3 = DirectX::XMFLOAT3;
using mat4 = DirectX::XMFLOAT4X4;


class Entity
{
private:
	
	DirectX::XMFLOAT3 m_vRotation;
	DirectX::XMFLOAT3 m_vScale;
	DirectX::XMFLOAT3 m_vPos;
	DirectX::XMFLOAT4X4 m_mWorld;
	Mesh* m_pMesh;

	bool m_bDirty = false;


public:
	Entity(Mesh* a_pMesh, DirectX::XMFLOAT4X4 a_mWorld, DirectX::XMFLOAT3 a_vPos, DirectX::XMFLOAT3 a_vRotation, DirectX::XMFLOAT3 a_vScale);
	
	/*
	 *		Accessors
	 */
	void SetRotation(DirectX::XMFLOAT3 a_vRotation);
	void SetScale(DirectX::XMFLOAT3 a_vScale);
	void SetPos(DirectX::XMFLOAT3 a_vPos);
	void SetWorld(DirectX::XMFLOAT4X4 a_mWorld);

	DirectX::XMFLOAT3 GetRotation();
	DirectX::XMFLOAT3 GetScale();
	DirectX::XMFLOAT3 GetPos();
	DirectX::XMFLOAT4X4 GetWorld();
	Mesh* GetMesh();

	void Move(DirectX::XMFLOAT3 a_vDisplaceBy);
	void MoveForward(float a_fDisplaceBy);

	void Draw();

	virtual ~Entity();
};
