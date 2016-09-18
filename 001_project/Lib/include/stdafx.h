#pragma once

#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <time.h>
#include <d3dx9core.h>
#include <dsound.h>
#include <tchar.h>

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION ( 0x800 )

#endif

#include <dinput.h>

#define M_PI	3.14159265358979323846
#define M_E		2.71828182845904523536
#define M_TRIANGLE 180.0



//マルチメディアライブラリー、タイマーを使えるようにする
#pragma comment(lib,"winmm.lib")


#pragma comment(lib,"dsound.lib")



#define SAFE_RELEASE(x){if(x){(x)->Release();(x) =  NULL;}}