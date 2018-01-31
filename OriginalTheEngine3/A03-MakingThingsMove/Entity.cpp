#include "Entity.h"

Entity::Entity(Mesh * a_pMesh, DirectX::XMFLOAT4X4 a_mWorld, DirectX::XMFLOAT3 a_vPos, DirectX::XMFLOAT3 a_vRotation, DirectX::XMFLOAT3 a_vScale) : m_pMesh(a_pMesh), m_mWorld(a_mWorld),
m_vPos(a_vPos), m_vRotation(a_vRotation), m_vScale(a_vScale)
{

}

void Entity::SetRotation(DirectX::XMFLOAT3 a_vRotation)
{
}

void Entity::SetScale(DirectX::XMFLOAT3 a_vScale)
{
}

void Entity::SetPos(DirectX::XMFLOAT3 a_vPos)
{
}

void Entity::SetWorld(DirectX::XMFLOAT4X4 a_mWorld)
{
}

DirectX::XMFLOAT3 Entity::GetRotation()
{
	return DirectX::XMFLOAT3();
}

DirectX::XMFLOAT3 Entity::GetScale()
{
	return DirectX::XMFLOAT3();
}

DirectX::XMFLOAT3 Entity::GetPos()
{
	return DirectX::XMFLOAT3();
}

DirectX::XMFLOAT4X4 Entity::GetWorld()
{
	return DirectX::XMFLOAT4X4();
}

Mesh * Entity::GetMesh()
{
	return m_pMesh;
}

void Entity::Move(DirectX::XMFLOAT3 a_vDisplaceBy)
{
}

void Entity::MoveForward(float a_fDisplaceBy)
{
}

void Entity::Draw()
{

}

Entity::~Entity()
{
}


