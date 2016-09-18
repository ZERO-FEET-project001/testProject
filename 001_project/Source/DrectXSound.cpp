/*--------------------------------------------------------------------
		リンカ

--------------------------------------------------------------------*/

//====================================================================================================
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
//====================================================================================================

/*--------------------------------------------------------------------
		インクルード

--------------------------------------------------------------------*/
#include<stdio.h>
#include <tchar.h>
#include <dsound.h>
#include "Macro.h"


/*--------------------------------------------------------------------
		オブジェクト解放マクロ

--------------------------------------------------------------------*/
//解放処理のマクロ定義、解放はクリエイトした時の逆順で
#define SAFE_RELEASE(x) {if(x){(x)->Release();(x)=NULL;}}
#define MAX_WAVE_SOUND (20)

LPDIRECTSOUND8 lpdSound;//サウンドではどの関数でも使用するのでグローバル宣言
LPDIRECTSOUNDBUFFER lpdSoundBuffer[MAX_WAVE_SOUND];//セカンダリバッファ


/*=============================================================================
			関数名 HRESULT InitDirectSound(HWND hWnd)
			引  数 HWND hWnd
			戻り値 HRESULT hr
			概　要 DirectSoundの初期化
==============================================================================*/
HRESULT InitDirectSound(HWND hWnd)
{
	HRESULT         hr;    // 結果用
	DSBUFFERDESC dsBuffer;    // バッファ記述子
	WAVEFORMATEX waveFormat;    // 波形オーディオデータのフォーマット
	LPDIRECTSOUNDBUFFER PrimaryBuffer = NULL;    // プライマリバッファを確保するための仮のバッファ


	SAFE_RELEASE(lpdSound);    // 念のための初期化

	// プライマリサウンドデバイスを使って探す
	if(FAILED(hr = DirectSoundCreate8(NULL,&lpdSound,NULL)))
	{return(hr);}

	// 協調レベルを設定する
	// 協調レベルは実際に音を再生させる前に必ず設定しなければならない
	// 通常はDSSCL_PRIORITYを設定することが推奨される
	if(FAILED(hr = lpdSound->SetCooperativeLevel(hWnd,DSSCL_PRIORITY)))
	{
		return(hr);
	}

	// プライマリバッファを取得する
	// プライマリバッファはセカンダリバッファより前に確保しなければならない
	// またDSBCAPS_PRIMARYBUFFERとDSBCAPS_CTRLFXと組み合わせることはできない
	// 構造体のゼロリセット（必ず行う）
	ZeroMemory(&dsBuffer, sizeof(DSBUFFERDESC));
	// 必ずsizeof（ DSBUFFERDESC ）を行う
	dsBuffer.dwSize = sizeof(DSBUFFERDESC); 
	// プライマリバッファ
	dsBuffer.dwFlags = DSBCAPS_PRIMARYBUFFER;
	// プライマリバッファの場合は必ず0
	dsBuffer.dwBufferBytes = 0; 
	// プライマリバッファの場合は必ずNULL
	dsBuffer.lpwfxFormat = NULL;

	// CreateSoundBufferのチェックは必ずFAILEDマクロで行う
	if(FAILED(hr = lpdSound->CreateSoundBuffer(&dsBuffer, &PrimaryBuffer , NULL)))
	{return(hr);}

	// 構造体のゼロリセット（必ず行う）
	ZeroMemory(&waveFormat, sizeof(WAVEFORMATEX)); 
	// PCM波形フォーマットを用いる
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;//(WORD) WAVE_FORMAT_PCM;      
	// チャネル数、周波数、ビットレートはヘッダを参照
	waveFormat.nChannels = 1;//(WORD) kPrimaryChannels;//1はモノラル2はステレオ        
	waveFormat.nSamplesPerSec = 44100;//(DWORD) kPrimaryFreq; 
	waveFormat.wBitsPerSample = 16;//(WORD) kPrimaryBitRate; //8 or 16のどちらか

	// ここの2行は必ずこうする
	waveFormat.nBlockAlign = (WORD)(waveFormat.wBitsPerSample / 8 * waveFormat.nChannels);    
	waveFormat.nAvgBytesPerSec = (DWORD)(waveFormat.nSamplesPerSec * waveFormat.nBlockAlign);

	// プライマリバッファのフォーマットを設定
	// SetFormat関数はプライマリバッファの設定を行うための特別な関数である
	if(FAILED(hr = PrimaryBuffer ->SetFormat(&waveFormat)))
	{return(hr);}

	// SetFormat関数が正常に終わったので、もういらない
	SAFE_RELEASE(PrimaryBuffer );


	return(S_OK);
}
/*=============================================================================
			関数名 LoadSoundData
			引き数 char *file_name, int buffer_num
			戻り値 BOOL型
			概　要 wavデータ読み込み用関数。
=============================================================================*/
BOOL LoadSoundData(LPCWSTR file_name,BYTE buffer_num)
{
	HANDLE hFile = CreateFile(					
						file_name,
						GENERIC_READ,
						0,
						NULL,
						OPEN_EXISTING,
						FILE_ATTRIBUTE_NORMAL,
						NULL );

	if( hFile == INVALID_HANDLE_VALUE )
	{
		return (false);
	}
	BY_HANDLE_FILE_INFORMATION file_Info;
	GetFileInformationByHandle(hFile, &file_Info);

	char *pt;
	DWORD read_size;
	pt = (char *)malloc(file_Info.nFileSizeLow);

	if(!ReadFile( hFile, pt, file_Info.nFileSizeLow, &read_size, NULL))
	{
		free(pt);
		CloseHandle(hFile);
		return (false);
	}
	if(read_size == 0)
	{
		free(pt);
		CloseHandle(hFile);
		return (false);
	}

	char check_type[4];
	strncpy(check_type, pt + 8, 4);
	
	if( strncmp(check_type, "WAVE", 4) )
	{
		free(pt);
		CloseHandle(hFile);
		return (false);
	}

	WAVEFORMATEX waveFormat;
	CopyMemory(&waveFormat, pt + 20, 16);

	DSBUFFERDESC dsBuffer;
	ZeroMemory( &dsBuffer, sizeof(DSBUFFERDESC));
	dsBuffer.dwSize = sizeof(DSBUFFERDESC);
	dsBuffer.dwFlags =	DSBCAPS_CTRLVOLUME	|
						DSBCAPS_GLOBALFOCUS	|
						DSBCAPS_CTRLPAN;
	dsBuffer.dwBufferBytes = file_Info.nFileSizeLow;
	dsBuffer.lpwfxFormat = &waveFormat;
	//GETCURRENTPOSTTION2 - 再生位置（カーソル）を取得可能する
	//GLOBALFOCUS - グローバルなサウンドバッファ、他のアプリケーションでもDirectSound使用してもバッファを使える
	//LOCDEFER　-　再生時バァファがハードウェアの他のアプリケーションでDirectSound使用してバァファを使える
	//CTRLVOLUME - サウンドのボリュームを変更できる

	lpdSound->CreateSoundBuffer(&dsBuffer, &lpdSoundBuffer[buffer_num], NULL );

	DWORD offset = 0, first_block_byte, second_block_byte;
	LPVOID first_block, second_block;
	HRESULT hResult;

	hResult = lpdSoundBuffer[buffer_num]->Lock(
										offset,
										file_Info.nFileSizeLow,
										&first_block, &first_block_byte,
										&second_block, &second_block_byte,
										0);
	if(hResult == DSERR_BUFFERLOST)
	{
		lpdSoundBuffer[buffer_num]->Restore();
		hResult = lpdSoundBuffer[buffer_num]->Lock(
											offset,
											file_Info.nFileSizeLow,
											&first_block, &first_block_byte,
											&second_block, &second_block_byte,
											0 );
	}
	if( FAILED(hResult))
	{
		return (false);
	}

	CopyMemory(first_block, pt, first_block_byte);
	if(second_block_byte != 0)
	{
		CopyMemory(second_block, pt + first_block_byte, second_block_byte);
	}
	lpdSoundBuffer[buffer_num]->Unlock(first_block, first_block_byte, second_block, second_block_byte);

	free(pt);
	CloseHandle(hFile);
	return (true);
}

/*=============================================================================
			関数名 void PlaySound(BYTE play_num,bool LOOPFLG)
			引き数 (BYTE play_num,bool LOOPFLG)
			戻り値 void型
			概　要 再生用関数。
=============================================================================*/
void PlaySound(BYTE play_num,bool LOOPFLG)
{
	lpdSoundBuffer[play_num]->Play(0, 0, LOOPFLG);
}
/*=============================================================================
			関数名 void StopSound(BYTE play_num)
			引き数 int play_num
			戻り値 void型
			概　要 停止用関数。
=============================================================================*/
void StopSound(BYTE play_num)
{   
	lpdSoundBuffer[play_num]->Stop();			//ストップするために必要
	lpdSoundBuffer[play_num]->SetCurrentPosition(0);//再生位置を元に戻す
}
/*=============================================================================
			関数名 ReleaseSound
			引き数 void
			戻り値 void型
			概　要 DirectSound解放用関数。
=============================================================================*/
void ReleaseSound(void)
{
	for(int i = 0; i < MAX_WAVE_SOUND; i++)
	{
		SAFE_RELEASE(lpdSoundBuffer[i]);		//解放処理を行う
	}
	SAFE_RELEASE(lpdSound);
}
