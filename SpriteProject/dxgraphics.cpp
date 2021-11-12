#include <d3dx9.h>
#include <windows.h>
#include <d3d9.h>
#include "dxgraphics.h"
#include "game.h"

LPDIRECT3D9 d3d = NULL;
LPDIRECT3DDEVICE9 d3ddev = NULL;

LPDIRECT3DSURFACE9 backbuffer = NULL;
LPDIRECT3DSURFACE9 surface = NULL;

int Init_Direct3D(HWND hwnd, int width, int height, int fullscreen)
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (d3d == NULL)
	{
		MessageBox(hwnd, "Error initializing Direct3D", "Error",
			MB_OK);
		return 0;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = (!fullscreen);
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.hDeviceWindow = hwnd;

	d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	if (d3ddev == NULL)
	{
		MessageBox(hwnd, "Error creating Direct3D device",
			"Error", MB_OK);
		return 0;
	}

	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO,
		&backbuffer);

	return 1;
}

LPDIRECT3DSURFACE9 LoadSurface(char* filename, D3DCOLOR transcolor)
{
	LPDIRECT3DSURFACE9 surface = NULL;
	D3DXIMAGE_INFO info;
	HRESULT result;

	result = D3DXGetImageInfoFromFile(filename, &info);
	if (result != D3D_OK)
		return NULL;

	result = d3ddev->CreateOffscreenPlainSurface(
		info.Width, //width of the surface
		info.Height, //height of the surface
		D3DFMT_X8R8G8B8, //surface format
		D3DPOOL_DEFAULT, //memory pool to use
		&surface, //pointer to the surface
		NULL); //reserved (always NULL)

	if (result != D3D_OK)
		return NULL;

	result = D3DXLoadSurfaceFromFile(
		surface, //destination surface
		NULL, //destination palette
		NULL, //destination rectangle
		filename, //source filename
		NULL, //source rectangle
		D3DX_DEFAULT, //controls how image is filtered
		transcolor, //for transparency (0 for none)
		NULL); //source image info (usually NULL)

	if (result != D3D_OK)
		return NULL;

	return surface;
}

LPDIRECT3DTEXTURE9 LoadTexture(char* filename, D3DCOLOR transcolor)
{
	LPDIRECT3DTEXTURE9 texture = NULL;
	D3DXIMAGE_INFO info;
	HRESULT result;

	result = D3DXGetImageInfoFromFile(filename, &info);

	if (result != D3D_OK)
		return NULL;

	result = D3DXCreateTextureFromFileEx(
		d3ddev, //Đối tượng Direct3D
		filename, //tên tệp bitmap
		2 * info.Width, //Width của tệp bitmap
		2 * info.Height, //Height của tệp bitmap
		1, //kết nối level(1 nếu không có thay đổi)
		D3DPOOL_DEFAULT, //kiểu của surface (thông thường)
		D3DFMT_UNKNOWN, //định dạng surface (mặc định)
		D3DPOOL_DEFAULT, //lớp bộ nhớ cho texture
		D3DX_DEFAULT, //bộ lọc hình ảnh
		D3DX_DEFAULT, //bộ lọc mip
		transcolor, //màu chỉ ra trong suốt
		&info, //thông tin tệp bitmap (từ tệp tải lên)
		NULL, //đổ màu
		&texture); //texture đích
		// Đảm bảo texture đã được tải lên thành công
	if (result != D3D_OK)
		return NULL;

	return texture;
}
