#pragma once

#include <d3dx9.h>
#include <dxerr.h>

extern LPDIRECT3D9			m_d3dObject;
extern LPDIRECT3DDEVICE9	m_d3dDevice;
extern D3DMATERIAL9			m_material;
extern bool					rotateEnable;

bool CheckHR(HRESULT hr);
float Random(int max);	// return 0.0 ... max

class CGraphics
{
public:
	CGraphics();
	~CGraphics();

	float eyePositionX,eyePositionY,eyePositionZ;

	bool InitialiseDirect3D(HWND hWnd);
	bool SetupLighting();
	bool SetupMatrices();
	bool Initialise(HWND hWnd);
	bool Render();
	void MoveEye(float dx,float dy,float dz);
};
