#pragma once
//====================================================================================================
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
//====================================================================================================
#include<stdio.h>
#include <tchar.h>
#include <dsound.h>
#include "Macro.h"
//====================================================================================================

/*=================================================================
						サウンドクラス
=================================================================*/
class DxSound
{
private:
	friend int APIENTRY _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int);

	static LPDIRECTSOUND8 pDSound;
	static void CreateDirectSound(HWND hWnd);
	static void ReleaseDirectSound();

	LPDIRECTSOUNDBUFFER pDSBuffer;

	// 再生終了を関知
	LPDIRECTSOUNDNOTIFY pDSNotify;
	HANDLE hEvent;
	static DWORD WINAPI NotifyFunction(LPVOID param);

	void Reset();
public:
	DxSound();
	DxSound(LPCTSTR filename);
	~DxSound();

	DxSound(const DxSound&);
	DxSound& operator=(const DxSound&);

	BOOL Load(LPCTSTR filename);
	void Play(bool loop);
	void Stop();
	void SetVolume(LONG volume);
	void SetPan(LONG lPan);

	void EnableDeleteByEnd();
	HANDLE GethEvent(){return hEvent;}
};

