#include "Graphics.h"
#include "CubePrimitive.h"

#define NUM_CUBE 200

LPDIRECT3D9			m_d3dObject;
LPDIRECT3DDEVICE9	m_d3dDevice;
bool rotateEnable = true;

CubePrimitive cube[NUM_CUBE];

CGraphics::CGraphics()
{
	eyePositionX = 0.0f;
	eyePositionY = 0.0f;
	eyePositionZ = -30.0f;
}

CGraphics::~CGraphics(void)
{
	if (m_d3dDevice)
		m_d3dDevice->Release();

	if (m_d3dObject)
		m_d3dObject->Release();
}

/* --------------------------------------------------------------
It is important, to aid debugging, to check the return code from DirectX calls
DirectX also provides a means of getting the error code in terms of an error string and
description. To use this we need to include dxerr.h and link with dxerr.lib. I find it
convenient to wrap this in this helper function.
Note: the function returns false if there was an error
 -------------------------------------------------------------- */

bool 
CheckHR (
	HRESULT hr)		// result of most recent COM call
{
	if (SUCCEEDED(hr))
		return true;

	// An error occured so find out what it was and output it to the output pane in Vis
	OutputDebugString("\nDirectX Error Reported:\n");
	OutputDebugString(DXGetErrorString(hr));
	OutputDebugString(" : ");
	OutputDebugString(DXGetErrorDescription(hr));
	OutputDebugString("\n\n");

	return false;
}

/* --------------------------------------------------------------
 return random # 0..max
  -------------------------------------------------------------- */

float 
Random (
	int max)	// max value returned
{
	if(max <= 0) return 1;
	return float(rand()) / ( float( RAND_MAX ) / float(max));
}

/* --------------------------------------------------------------
initialize OpenGL graphics
  -------------------------------------------------------------- */

bool 
CGraphics::Initialise (
	HWND hWnd)	// parent window
{
	if (!InitialiseDirect3D(hWnd))
		return false;

	if (!SetupLighting())
		return false;

	if (!SetupMatrices())
		return false;

	for(int i=0;i<NUM_CUBE;++i)
		cube[i].Create(5.0f + Random(50),  5.0f + Random(50));

	return true;
}

/* --------------------------------------------------------------
initialize OpenGL graphics
  -------------------------------------------------------------- */

bool 
CGraphics::InitialiseDirect3D (
	HWND hWnd) // parent window
{
	m_d3dObject = Direct3DCreate9(D3D_SDK_VERSION);
	if (!m_d3dObject)
		return false;

	/* When creating our device we can specify a number of parameters describing our required device
	Since this demo runs in a window we are limited to the display depth and size etc. set by the user
	This means we only fill in a few parameters (we want a z buffer, run in a window). If you were
	wishing to run full screen you would need to fill in many more. See the site for details.*/
	D3DPRESENT_PARAMETERS presParams;
	ZeroMemory(&presParams,sizeof(presParams));

	presParams.Windowed =				FALSE;
	presParams.SwapEffect =				D3DSWAPEFFECT_DISCARD;
	presParams.BackBufferFormat =		D3DFMT_UNKNOWN;
	presParams.EnableAutoDepthStencil = TRUE;
	presParams.EnableAutoDepthStencil = TRUE;
	presParams.AutoDepthStencilFormat = D3DFMT_D16;
	presParams.BackBufferWidth =		1680;
	presParams.BackBufferHeight =		1050;
	presParams.BackBufferFormat =		D3DFMT_A8R8G8B8;
	presParams.PresentationInterval =	D3DPRESENT_INTERVAL_ONE;
	presParams.BackBufferCount =		1;

	/*
	Once we have filled in our structure we can ask Direct3D to create us a device matching our requirements
	This call also takes some further parameters including the type of vertex processing support we need
	Since some computers do not support hardware vertex processing in a window I back off if hardware vertex
	processing is not available and instead try mixed vertex processing. If that fails I try software vertex
	processing which is obviously slower but supported by more machines. If all these fail we cannot create a
	device capable of running the demo.
	*/
	HRESULT hr = m_d3dObject->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_HARDWARE_VERTEXPROCESSING,&presParams, &m_d3dDevice);
	if (FAILED(hr))
	{
		hr = m_d3dObject->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_MIXED_VERTEXPROCESSING,	&presParams, &m_d3dDevice);
		if (FAILED(hr))
		{
			hr = m_d3dObject->CreateDevice(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,D3DCREATE_SOFTWARE_VERTEXPROCESSING,&presParams, &m_d3dDevice);
			if (FAILED(hr))
				return false;
		}
	}

	// As well as specifying that we want a z buffer (above) we also need to turn it on
	m_d3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	return true;
}

/* --------------------------------------------------------------
  -------------------------------------------------------------- */

bool 
CGraphics::SetupLighting ()
{
	/* Set up a white, directional light. For details please see the notes on the site
	Note that many lights may be active at a time (normally limited by the graphic card to 8)*/
	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;
	ZeroMemory( &light, sizeof(D3DLIGHT9) );
	light.Type       = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r  = 1.0f;
	light.Diffuse.g  = 1.0f;
	light.Diffuse.b  = 0; //1.0f;

	vecDir = D3DXVECTOR3(0.0f,0.0f,1.0f);    
	D3DXVec3Normalize( (D3DXVECTOR3*)&light.Direction, &vecDir );

	light.Range = 1000.0f;
	if (!CheckHR(m_d3dDevice->SetLight( 0, &light )))
		return false;

	if (!CheckHR(m_d3dDevice->LightEnable( 0, TRUE )))
		return false;

	// Also turn on some ambient light.
	m_d3dDevice->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_XRGB(20,20,20));

	// Turn on the lighting generally
	m_d3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

	return true;
}

/* --------------------------------------------------------------
To render anything in Direct3D we need to set the three matrices
World Matrix - used to transform our geometry from object space into world space
i.e. position our geometry in the game world
View Matrix - used to transform the geometry form world space into view space
i.e. position the viewer (camera) in the world
Projection Matrix - transforms from view space into screen space
i.e. applies perspective projection to create the final 2D view
-------------------------------------------------------------- */

bool 
CGraphics::SetupMatrices ()
{
	/* For the projection matrix, we set up a perspective transform (which
	transforms geometry from 3D view space to 2D viewport space, with
	a perspective divide making objects smaller in the distance). To build
	a perpsective transform, we need the field of view (1/4 pi is common),
	the aspect ratio, and the near and far clipping planes (which define at
	what distances geometry should no longer be rendered).
	Note: we normally only set this matrix once */
	float aspectRation = 800.0f / 600.0f;

	D3DXMATRIX matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/2, aspectRation, 1.0f, 500.0f );

	m_d3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );

	// Now for our view matrix. A view matrix can be defined given an eye point,
	// a point to lookat, and a direction for which way is up. Here, we set the
	// eye 10 units back along the z-axis, look at the origin, 
	// and define "up" to be in the y-direction.
	// We normally set this matrix whenever the camera changes position or orientation

	MoveEye(0,0,0);

	// The world matrix is set just before rendering our cube
	return true;
}

/* --------------------------------------------------------------
	move eye position
-------------------------------------------------------------- */

void 
CGraphics::MoveEye (
	float dx,
	float dy,
	float dz)
{
	eyePositionX += dx;
	eyePositionY += dy;
	eyePositionZ += dz;

	D3DXVECTOR3 vEyePt( eyePositionX,eyePositionY,eyePositionZ );
	D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
	D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );

	m_d3dDevice->SetTransform( D3DTS_VIEW, &matView );
}

/* --------------------------------------------------------------
When rendering we always follow the same steps
1. Clear the screen (target) and z buffer
2. Call BeginScene to tell D3D we are about to draw
3. Render all our geometry
4. Call EndScene and Present to show the new scene
-------------------------------------------------------------- */

bool 
CGraphics::Render ()
{
	if(!CheckHR(m_d3dDevice->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(0,0,0),1.0f,0)))
		return false;

	if(!CheckHR(m_d3dDevice->BeginScene()))
		return false;

	for(int i=0;i<NUM_CUBE;++i)
		cube[i].Render(Random(1)/10.f, Random(1)/10.f);

	if(!CheckHR(m_d3dDevice->EndScene()))
		return false;

	if(!CheckHR(m_d3dDevice->Present(NULL,NULL,NULL,NULL)))
		return false;

	return true;
}

