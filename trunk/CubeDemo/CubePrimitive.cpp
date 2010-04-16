#include <assert.h>
#include "Graphics.h"
#include "CubePrimitive.h"

#define D3DFVF_CUBEVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL)

// A structure for our custom vertex
struct TCubeVertex
{
	D3DXVECTOR3 position; // The 3D position for the vertex
	D3DXVECTOR3 normal;   // The surface normal for the vertex
};

CubePrimitive::~CubePrimitive()
{
	if (m_vertexBuffer)
		m_vertexBuffer->Release();

	if (m_indexBuffer)
		m_indexBuffer->Release();
}

/* --------------------------------------------------------------
 initialize data points for a cube
-------------------------------------------------------------- */

bool 
CubePrimitive::Create (
	float xoffset,	// X offset from 0.0
	float yoffset)  // Y offset from 0.0
{
	HRESULT hr = m_d3dDevice->CreateVertexBuffer( 4*6*sizeof(TCubeVertex),D3DUSAGE_WRITEONLY,
		D3DFVF_CUBEVERTEX,D3DPOOL_DEFAULT, &m_vertexBuffer, NULL );
	if (!CheckHR(hr))
		return false;

	D3DXVECTOR3 front[4];	
	front[0]=D3DXVECTOR3(FLOAT(-1.0f+xoffset),FLOAT(-1.0f+yoffset),-1.0f);
	front[1]=D3DXVECTOR3(FLOAT(-1.0f+xoffset),FLOAT(+1.0f+yoffset),-1.0f);
	front[2]=D3DXVECTOR3(FLOAT(+1.0f+xoffset),FLOAT(+1.0f+yoffset),-1.0f); 
	front[3]=D3DXVECTOR3(FLOAT(+1.0f+xoffset),FLOAT(-1.0f+yoffset),-1.0f);

	D3DXVECTOR3 back[4];	
	back[0]=D3DXVECTOR3(FLOAT(+1.0f+xoffset),FLOAT(-1.0f+yoffset),1.0f);
	back[1]=D3DXVECTOR3(FLOAT(+1.0f+xoffset),FLOAT(+1.0f+yoffset),1.0f);
	back[2]=D3DXVECTOR3(FLOAT(-1.0f+xoffset),FLOAT(+1.0f+yoffset),1.0f);
	back[3]=D3DXVECTOR3(FLOAT(-1.0f+xoffset),FLOAT(-1.0f+yoffset),1.0f);

	TCubeVertex* pVertices;
	hr = m_vertexBuffer->Lock( 0, 0, (void**)&pVertices, 0 );
	if (!CheckHR(hr))
		return false;

	// Front facing, note: normals face away from face
	pVertices[0].position=front[0];
	pVertices[0].normal=D3DXVECTOR3(0.0f,0.0f,-1.0f);
	pVertices[1].position=front[1];
	pVertices[1].normal=D3DXVECTOR3(0.0f,0.0f,-1.0f);
	pVertices[2].position=front[2];
	pVertices[2].normal=D3DXVECTOR3(0.0f,0.0f,-1.0f);
	pVertices[3].position=front[3];
	pVertices[3].normal=D3DXVECTOR3(0.0f,0.0f,-1.0f);

	// Left face, remember to define in clockwise fashion (if looking at face)
	pVertices[4].position=back[3];
	pVertices[4].normal=D3DXVECTOR3(-1.0f,0.0f,0.0f);
	pVertices[5].position=back[2];
	pVertices[5].normal=D3DXVECTOR3(-1.0f,0.0f,0.0f);
	pVertices[6].position=front[1];
	pVertices[6].normal=D3DXVECTOR3(-1.0f,0.0f,0.0f);
	pVertices[7].position=front[0];
	pVertices[7].normal=D3DXVECTOR3(-1.0f,0.0f,0.0f);

	// Back face
	pVertices[8].position=back[0];
	pVertices[8].normal=D3DXVECTOR3(0.0f,0.0f,1.0f);
	pVertices[9].position=back[1];
	pVertices[9].normal=D3DXVECTOR3(0.0f,0.0f,1.0f);
	pVertices[10].position=back[2];
	pVertices[10].normal=D3DXVECTOR3(0.0f,0.0f,1.0f);
	pVertices[11].position=back[3];
	pVertices[11].normal=D3DXVECTOR3(0.0f,0.0f,1.0f);

	// Right face
	pVertices[12].position=front[3];
	pVertices[12].normal=D3DXVECTOR3(1.0f,0.0f,0.0f);
	pVertices[13].position=front[2];
	pVertices[13].normal=D3DXVECTOR3(1.0f,0.0f,0.0f);
	pVertices[14].position=back[1];
	pVertices[14].normal=D3DXVECTOR3(1.0f,0.0f,0.0f);
	pVertices[15].position=back[0];
	pVertices[15].normal=D3DXVECTOR3(1.0f,0.0f,0.0f);

	// Top face
	pVertices[16].position=front[1];
	pVertices[16].normal=D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVertices[17].position=back[2];
	pVertices[17].normal=D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVertices[18].position=back[1];
	pVertices[18].normal=D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVertices[19].position=front[2];
	pVertices[19].normal=D3DXVECTOR3(0.0f,1.0f,0.0f);

	// Bottom face
	pVertices[20].position=back[3];
	pVertices[20].normal=D3DXVECTOR3(0.0f,-1.0f,0.0f);
	pVertices[21].position=front[0];
	pVertices[21].normal=D3DXVECTOR3(0.0f,-1.0f,0.0f);
	pVertices[22].position=front[3];
	pVertices[22].normal=D3DXVECTOR3(0.0f,-1.0f,0.0f);
	pVertices[23].position=back[0];
	pVertices[23].normal=D3DXVECTOR3(0.0f,-1.0f,0.0f);

	m_vertexBuffer->Unlock();

	hr = m_d3dDevice->CreateIndexBuffer(36* sizeof(WORD),D3DUSAGE_WRITEONLY,D3DFMT_INDEX16,D3DPOOL_MANAGED,&m_indexBuffer,NULL);
	if (!CheckHR(hr))
		return false;

	WORD *indices = NULL;
	hr=m_indexBuffer->Lock( 0, 0, (void**)&indices, 0 );
	if (!CheckHR(hr))
		return false;

	// Front face
	WORD indexStart=0;
	int count=0;
	indices[count+0]=indexStart+0;indices[count+1]=indexStart+1;indices[count+2]=indexStart+2;
	indices[count+3]=indexStart+0;indices[count+4]=indexStart+2;indices[count+5]=indexStart+3;

	// Left face
	indexStart+=4;
	count+=6;
	indices[count+0]=indexStart+0;indices[count+1]=indexStart+1;indices[count+2]=indexStart+2;
	indices[count+3]=indexStart+0;indices[count+4]=indexStart+2;indices[count+5]=indexStart+3;

	// Back face
	indexStart+=4;
	count+=6;
	indices[count+0]=indexStart+0;indices[count+1]=indexStart+1;indices[count+2]=indexStart+2;
	indices[count+3]=indexStart+0;indices[count+4]=indexStart+2;indices[count+5]=indexStart+3;

	// Right face
	indexStart+=4;
	count+=6;
	indices[count+0]=indexStart+0;indices[count+1]=indexStart+1;indices[count+2]=indexStart+2;
	indices[count+3]=indexStart+0;indices[count+4]=indexStart+2;indices[count+5]=indexStart+3;

	// Top face
	indexStart+=4;
	count+=6;
	indices[count+0]=indexStart+0;indices[count+1]=indexStart+1;indices[count+2]=indexStart+2;
	indices[count+3]=indexStart+0;indices[count+4]=indexStart+2;indices[count+5]=indexStart+3;

	// Bottom face
	indexStart+=4;
	count+=6;
	indices[count+0]=indexStart+0;indices[count+1]=indexStart+1;indices[count+2]=indexStart+2;
	indices[count+3]=indexStart+0;indices[count+4]=indexStart+2;indices[count+5]=indexStart+3;
	count+=6;

	assert(count==36);
	m_indexBuffer->Unlock();

	ZeroMemory( &m_material, sizeof(D3DMATERIAL9) );
	m_material.Diffuse.r = m_material.Ambient.r = Random(1);
	m_material.Diffuse.g = m_material.Ambient.g = Random(1);
	m_material.Diffuse.b = m_material.Ambient.b = Random(1);
	m_material.Diffuse.a = m_material.Ambient.a = Random(1);    

	return true;
}

/* --------------------------------------------------------------
	rotate and draw a cube
-------------------------------------------------------------- */

bool 
CubePrimitive::Render (
	float xrotationAmount,
	float yrotationAmount)
{
	static int lastTime = timeGetTime();

	// rotaion is enabled (toggled with <Space>, and randommly stop the movement
	if(rotateEnable && (rand() % 1024) < 200)
	{
		if (rotateY)
			yRotation = float(yRotation + yrotationAmount);
		else
			xRotation = float(xRotation + xrotationAmount);
	}

	// periodically switch which axis is updated
	if (timeGetTime()-lastTime > DWORD(500 + rand() % 1024))
	{
		rotateY = !rotateY;
		lastTime = timeGetTime();
	}

	/* Create our world matrix by using the D3DX helper functions to define rotation 
	and translation matrices. The final world matrix is made by multiplying these together*/

	D3DXMATRIX matRotX,matRotY;
	D3DXMatrixRotationY( &matRotY, yRotation);
	D3DXMatrixRotationX( &matRotX, xRotation);

	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans,0,0,0);

	// Note: the order of multiplication here is very important
	D3DXMATRIX matWorld=(matRotY*matRotX)*matTrans;

	// Set all the values to render our cube
	m_d3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
	m_d3dDevice->SetMaterial( &m_material );
	m_d3dDevice->SetStreamSource( 0, m_vertexBuffer,0, sizeof(TCubeVertex) );
	m_d3dDevice->SetFVF( D3DFVF_CUBEVERTEX );
	m_d3dDevice->SetIndices( m_indexBuffer);

	// draw a triangle list using our 24 vertices and 12 triangles
	return CheckHR(m_d3dDevice->DrawIndexedPrimitive( D3DPT_TRIANGLELIST,0,0,24,0,12));
}
