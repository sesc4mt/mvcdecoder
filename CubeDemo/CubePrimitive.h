#pragma once

class CubePrimitive
{
public:
	CubePrimitive() {}
	~CubePrimitive();

	bool Create(float xoffset,float yoffset);
	bool Render(float xrot,float yrot);

private:
	D3DMATERIAL9 m_material;
	LPDIRECT3DVERTEXBUFFER9 m_vertexBuffer;
	LPDIRECT3DINDEXBUFFER9  m_indexBuffer;
	bool  rotateY;
	float yRotation;
	float xRotation;
};
