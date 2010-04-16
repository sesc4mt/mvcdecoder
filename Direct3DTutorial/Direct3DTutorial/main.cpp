// include the basic windows header files and the Direct 3D header file
#include <windows.h>
#include <windowsx.h>
#include <d3d9.h>
#include <d3dx9.h>

#include <strsafe.h>

#include "utils.h"

// include the Direct3D Libary file
#pragma comment (lib, "d3d9.lib")



//HWND g_hWnd = NULL;
IDirect3DSurface9*	gImageSrc = NULL; //Source stereo image
IDirect3DSurface9* gBackBuf = NULL;

// screen and image size
int					gImageWidth = 1680;
int					gImageHeight = 1050;




// global declarations
LPDIRECT3D9 d3d;  //pointer to our Direct3D interface
LPDIRECT3DDEVICE9 d3ddev;  // the pointer to the device class

RECT destRect; // rectangle to change the destination of the 2 image we are loading

//function prototypes
void initD3D(HWND hWnd);  // set up and initializes Direct3D
void render_frame(void);  // renders a single frame
void cleanD3D(void);  // closes Direct3D and releases memory

// 3D Vision
void render3D(void); // stretches our surface to the backbuffer

// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd,
                         UINT message,
                         WPARAM wParam,
                         LPARAM lParam);

// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    // the handle for the window, filled by a function
    HWND hWnd;
    // this struct holds information for the window class
    WNDCLASSEX wc;

    // clear out the window class for use
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    // fill in the struct with the needed information
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    // wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = L"WindowClass1";

    // register the window class
    RegisterClassEx(&wc);

    // create the window and use the result as the handle
    hWnd = CreateWindowEx(NULL,
                          L"WindowClass1",    // name of the window class
                          L"3DVision Test",   // title of the window
                          WS_EX_TOPMOST | WS_POPUP,    // fullscreen values
                          0,    // x-position of the window
                          0,    // y-position of the window
                          gImageWidth,    // width of the window
                          gImageHeight,    // height of the window
                          NULL,    // we have no parent window, NULL
                          NULL,    // we aren't using menus, NULL
                          hInstance,    // application handle
                          NULL);    // used with multiple windows, NULL

    // display the window on the screen
    ShowWindow(hWnd, nCmdShow);

	// set up and initialize Direct3D
	initD3D(hWnd);
	
	// set up destRect
	destRect.left = 0;
	destRect.top = 0;
	destRect.bottom = gImageHeight;
	destRect.right = gImageWidth;

	//3D VISION
	// create the surface
	d3ddev->CreateOffscreenPlainSurface(gImageWidth *2, gImageHeight + 1, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &gImageSrc, NULL);
	
	// load left image
	D3DXLoadSurfaceFromFile(gImageSrc, NULL, &destRect, L"../Direct3DTutorial/img/3L.jpg", NULL, D3DX_DEFAULT, 0, NULL);

	// shift destRect to the right
	destRect.left = gImageWidth;
	destRect.top = 0;
	destRect.bottom = gImageHeight;
	destRect.right = gImageWidth*2;
	
	// load right image
	D3DXLoadSurfaceFromFile(gImageSrc, NULL, &destRect, L"../Direct3DTutorial/img/3R.jpg", NULL, D3DX_DEFAULT, 0, NULL);

	// Lock the stereo image
	D3DLOCKED_RECT lr;
	gImageSrc->LockRect(&lr,NULL,0);
	// write stereo signature in the last raw of the stereo image
	LPNVSTEREOIMAGEHEADER pSIH =
	(LPNVSTEREOIMAGEHEADER)(((unsigned char *) lr.pBits) + (lr.Pitch * (gImageHeight)));
	
	// Update the signature header values
	pSIH->dwSignature = NVSTEREO_IMAGE_SIGNATURE;
	pSIH->dwBPP = 32;
	//pSIH->dwFlags = SIH_SWAP_EYES; // Src image has left on left and right on right, thats why this flag is not needed.
	pSIH->dwWidth = gImageWidth*2;
	pSIH->dwHeight = gImageHeight;
	
	// Unlock surface
	gImageSrc->UnlockRect();
	
    // enter the main loop:

    // this struct holds Windows event messages
    MSG msg;

    while(TRUE)
	{
		// wait for the next message in the queue, store the result in 'msg'
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// translate keystroke messages into the right format
			TranslateMessage(&msg);

			// send the message to the WindowProc function
			DispatchMessage(&msg);
		}

		// If the message is WM_QUIT, exit the while loop
		if(msg.message == WM_QUIT)
			break;
		
		render_frame();

	}

	// clean up DirectX and COM
	cleanD3D();

    // return this part of the WM_QUIT message to Windows
    return msg.wParam;
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    // sort through and find what code to run for the message given
    switch(message)
    {
        // this message is read when the window is closed
        case WM_DESTROY:
            {
                // close the application entirely
                PostQuitMessage(0);
                return 0;
            } break;
    }

    // Handle any messages the switch statement didn't
    return DefWindowProc (hWnd, message, wParam, lParam);
} 

// this function initializes and prepares Direct3D for use
void initD3D(HWND hWnd)
{
    d3d = Direct3DCreate9(D3D_SDK_VERSION);    // create the Direct3D interface

    D3DPRESENT_PARAMETERS d3dpp;    // create a struct to hold various device information

    ZeroMemory(&d3dpp, sizeof(d3dpp));    // clear out the struct for use
    d3dpp.Windowed = FALSE;    // program fullscreen
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;    // discard old frames
    d3dpp.hDeviceWindow = hWnd;    // set the window to be used by Direct3D
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;  // set the back buffer format to 32 bit
	d3dpp.BackBufferWidth = gImageWidth;
	d3dpp.BackBufferHeight = gImageHeight;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.BackBufferCount = 1;


    // create a device class using this information and information from the d3dpp stuct
    d3d->CreateDevice(D3DADAPTER_DEFAULT,
                      D3DDEVTYPE_HAL,
                      hWnd,
                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                      &d3dpp,
                      &d3ddev);
}

// this is the function used to render a single frame
void render_frame(void)
{
    // clear the window to a deep blue
    d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 40, 100), 1.0f, 0);

    d3ddev->BeginScene();    // begins the 3D scene

    // do 3D rendering on the back buffer here
	render3D();


    d3ddev->EndScene();    // ends the 3D scene

    d3ddev->Present(NULL, NULL, NULL, NULL);    // displays the created frame
}


// this is the function that cleans up Direct3D and COM
void cleanD3D(void)
{
    d3ddev->Release();    // close and release the 3D device
    d3d->Release();    // close and release Direct3D
}


// this is the function that combines two images.
void render3D(void)
{
	// set destRect
	destRect.left = 0;
	destRect.top = 0;
	destRect.bottom = gImageHeight;
	destRect.right = gImageWidth;
	
	// Get the Backbuffer then Stretch the Surface on it.
	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &gBackBuf);
	d3ddev->StretchRect(gImageSrc, NULL, gBackBuf, &destRect, D3DTEXF_NONE); 

}