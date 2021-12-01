#ifndef _DXINPUT_H
#define _DXINPUT_H 1
#include <dinput.h>

extern LPDIRECTINPUT8 dinput;
extern LPDIRECTINPUTDEVICE8 dikeyboard;

int Init_DirectInput(HWND);
int Init_Keyboard(HWND);
void Poll_Keyboard();
int Key_Down(int);
void Kill_Keyboard();

#endif

