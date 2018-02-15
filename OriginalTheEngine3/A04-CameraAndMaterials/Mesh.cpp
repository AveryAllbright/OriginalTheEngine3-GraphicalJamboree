#include "Mesh.h"


Mesh::Mesh(Vertex * a_pVertex, int a_nVertexCount, int * a_pIndices, int a_nIndexCount, ID3D11Device * a_pDevice)
{

	// Create the VERTEX BUFFER description -----------------------------------
	// - The description is created on the stack because we only need
	//    it to create the buffer.  The description is then useless.
	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex) * a_nVertexCount;       // 3 = number of vertices in the buffer
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER; // Tells DirectX this is a vertex buffer
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;

	// Create the proper struct to hold the initial vertex data
	// - This is how we put the initial data into the buffer
	D3D11_SUBRESOURCE_DATA initialVertexData;
	initialVertexData.pSysMem = a_pVertex;

	// Actually create the buffer with the initial data
	// - Once we do this, we'll NEVER CHANGE THE BUFFER AGAIN
	a_pDevice->CreateBuffer(&vbd, &initialVertexData, &m_pVertBuffer);
	

	// Create the INDEX BUFFER description ------------------------------------
	// - The description is created on the stack because we only need
	//    it to create the buffer.  The description is then useless.
	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(int) * a_nIndexCount;         // 3 = number of indices in the buffer
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER; // Tells DirectX this is an index buffer
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;

	// Create the proper struct to hold the initial index data
	// - This is how we put the initial data into the buffer
	D3D11_SUBRESOURCE_DATA initialIndexData;
	initialIndexData.pSysMem = a_pIndices;

	// Actually create the buffer with the initial data
	// - Once we do this, we'll NEVER CHANGE THE BUFFER AGAIN
	a_pDevice->CreateBuffer(&ibd, &initialIndexData, &m_pIndexBuffer);

	m_nIndexCount = a_nIndexCount;
}

Mesh::~Mesh()
{
	if (m_pVertBuffer) { m_pVertBuffer->Release(); }
	if (m_pIndexBuffer) { m_pIndexBuffer->Release(); }
}

ID3D11Buffer* Mesh::GetVertexBuffer()
{
	return m_pVertBuffer;
}

ID3D11Buffer* Mesh::GetIndexBuffer()
{
	return m_pIndexBuffer;
}

int Mesh::GetIndexCount()
{
	return m_nIndexCount;
}
