#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include "game.h"
#include "dxgraphics.h"
#include "dxinput.h"

LPDIRECTINPUT8 dinput;
LPDIRECTINPUTDEVICE8 dikeyboard;

char keys[256];

int Init_DirectInput(HWND hwnd)
{
	//initialize DirectInput object
	HRESULT result = DirectInput8Create(
		GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&dinput,
		NULL);

	if (result != DI_OK)
		return 0;

	//initialize the keyboard
	result = dinput->CreateDevice(GUID_SysKeyboard, &dikeyboard, NULL);
	if (result != DI_OK)
		return 0;

	return 1;
}

int Init_Keyboard(HWND hwnd)
{
	HRESULT result = dikeyboard->SetDataFormat(&c_dfDIKeyboard);
	if (result != DI_OK)
		return 0;

	result = dikeyboard->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (result != DI_OK)
		return 0;

	//---------------------------------------------------//
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = 1024; 

	result = dikeyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	//////////////////////////////////////////////////////////////////////////
	result = dikeyboard->Acquire();
	if (result != DI_OK)
		return 0;

	return 1;
}

void Poll_Keyboard()
{
	dikeyboard->GetDeviceState(sizeof(keys), (LPVOID)&keys);
}

int Key_Down(int key)
{
	return (keys[key] & 0x80);
}

void Kill_Keyboard()
{
	if (dikeyboard != NULL)
	{
		dikeyboard->Unacquire();
		dikeyboard->Release();
		dikeyboard = NULL;
	}
}
