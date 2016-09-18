/*--------------------------------------------------------------------
		�����J

--------------------------------------------------------------------*/

//====================================================================================================
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
//====================================================================================================

/*--------------------------------------------------------------------
		�C���N���[�h

--------------------------------------------------------------------*/
#include<stdio.h>
#include <tchar.h>
#include <dsound.h>
#include "Macro.h"


/*--------------------------------------------------------------------
		�I�u�W�F�N�g����}�N��

--------------------------------------------------------------------*/
//��������̃}�N����`�A����̓N���G�C�g�������̋t����
#define SAFE_RELEASE(x) {if(x){(x)->Release();(x)=NULL;}}
#define MAX_WAVE_SOUND (20)

LPDIRECTSOUND8 lpdSound;//�T�E���h�ł͂ǂ̊֐��ł��g�p����̂ŃO���[�o���錾
LPDIRECTSOUNDBUFFER lpdSoundBuffer[MAX_WAVE_SOUND];//�Z�J���_���o�b�t�@


/*=============================================================================
			�֐��� HRESULT InitDirectSound(HWND hWnd)
			��  �� HWND hWnd
			�߂�l HRESULT hr
			�T�@�v DirectSound�̏�����
==============================================================================*/
HRESULT InitDirectSound(HWND hWnd)
{
	HRESULT         hr;    // ���ʗp
	DSBUFFERDESC dsBuffer;    // �o�b�t�@�L�q�q
	WAVEFORMATEX waveFormat;    // �g�`�I�[�f�B�I�f�[�^�̃t�H�[�}�b�g
	LPDIRECTSOUNDBUFFER PrimaryBuffer = NULL;    // �v���C�}���o�b�t�@���m�ۂ��邽�߂̉��̃o�b�t�@


	SAFE_RELEASE(lpdSound);    // �O�̂��߂̏�����

	// �v���C�}���T�E���h�f�o�C�X���g���ĒT��
	if(FAILED(hr = DirectSoundCreate8(NULL,&lpdSound,NULL)))
	{return(hr);}

	// �������x����ݒ肷��
	// �������x���͎��ۂɉ����Đ�������O�ɕK���ݒ肵�Ȃ���΂Ȃ�Ȃ�
	// �ʏ��DSSCL_PRIORITY��ݒ肷�邱�Ƃ����������
	if(FAILED(hr = lpdSound->SetCooperativeLevel(hWnd,DSSCL_PRIORITY)))
	{
		return(hr);
	}

	// �v���C�}���o�b�t�@���擾����
	// �v���C�}���o�b�t�@�̓Z�J���_���o�b�t�@���O�Ɋm�ۂ��Ȃ���΂Ȃ�Ȃ�
	// �܂�DSBCAPS_PRIMARYBUFFER��DSBCAPS_CTRLFX�Ƒg�ݍ��킹�邱�Ƃ͂ł��Ȃ�
	// �\���̂̃[�����Z�b�g�i�K���s���j
	ZeroMemory(&dsBuffer, sizeof(DSBUFFERDESC));
	// �K��sizeof�i DSBUFFERDESC �j���s��
	dsBuffer.dwSize = sizeof(DSBUFFERDESC); 
	// �v���C�}���o�b�t�@
	dsBuffer.dwFlags = DSBCAPS_PRIMARYBUFFER;
	// �v���C�}���o�b�t�@�̏ꍇ�͕K��0
	dsBuffer.dwBufferBytes = 0; 
	// �v���C�}���o�b�t�@�̏ꍇ�͕K��NULL
	dsBuffer.lpwfxFormat = NULL;

	// CreateSoundBuffer�̃`�F�b�N�͕K��FAILED�}�N���ōs��
	if(FAILED(hr = lpdSound->CreateSoundBuffer(&dsBuffer, &PrimaryBuffer , NULL)))
	{return(hr);}

	// �\���̂̃[�����Z�b�g�i�K���s���j
	ZeroMemory(&waveFormat, sizeof(WAVEFORMATEX)); 
	// PCM�g�`�t�H�[�}�b�g��p����
	waveFormat.wFormatTag = WAVE_FORMAT_PCM;//(WORD) WAVE_FORMAT_PCM;      
	// �`���l�����A���g���A�r�b�g���[�g�̓w�b�_���Q��
	waveFormat.nChannels = 1;//(WORD) kPrimaryChannels;//1�̓��m����2�̓X�e���I        
	waveFormat.nSamplesPerSec = 44100;//(DWORD) kPrimaryFreq; 
	waveFormat.wBitsPerSample = 16;//(WORD) kPrimaryBitRate; //8 or 16�̂ǂ��炩

	// ������2�s�͕K����������
	waveFormat.nBlockAlign = (WORD)(waveFormat.wBitsPerSample / 8 * waveFormat.nChannels);    
	waveFormat.nAvgBytesPerSec = (DWORD)(waveFormat.nSamplesPerSec * waveFormat.nBlockAlign);

	// �v���C�}���o�b�t�@�̃t�H�[�}�b�g��ݒ�
	// SetFormat�֐��̓v���C�}���o�b�t�@�̐ݒ���s�����߂̓��ʂȊ֐��ł���
	if(FAILED(hr = PrimaryBuffer ->SetFormat(&waveFormat)))
	{return(hr);}

	// SetFormat�֐�������ɏI������̂ŁA��������Ȃ�
	SAFE_RELEASE(PrimaryBuffer );


	return(S_OK);
}
/*=============================================================================
			�֐��� LoadSoundData
			������ char *file_name, int buffer_num
			�߂�l BOOL�^
			�T�@�v wav�f�[�^�ǂݍ��ݗp�֐��B
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
	//GETCURRENTPOSTTION2 - �Đ��ʒu�i�J�[�\���j���擾�\����
	//GLOBALFOCUS - �O���[�o���ȃT�E���h�o�b�t�@�A���̃A�v���P�[�V�����ł�DirectSound�g�p���Ă��o�b�t�@���g����
	//LOCDEFER�@-�@�Đ����o�@�t�@���n�[�h�E�F�A�̑��̃A�v���P�[�V������DirectSound�g�p���ăo�@�t�@���g����
	//CTRLVOLUME - �T�E���h�̃{�����[����ύX�ł���

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
			�֐��� void PlaySound(BYTE play_num,bool LOOPFLG)
			������ (BYTE play_num,bool LOOPFLG)
			�߂�l void�^
			�T�@�v �Đ��p�֐��B
=============================================================================*/
void PlaySound(BYTE play_num,bool LOOPFLG)
{
	lpdSoundBuffer[play_num]->Play(0, 0, LOOPFLG);
}
/*=============================================================================
			�֐��� void StopSound(BYTE play_num)
			������ int play_num
			�߂�l void�^
			�T�@�v ��~�p�֐��B
=============================================================================*/
void StopSound(BYTE play_num)
{   
	lpdSoundBuffer[play_num]->Stop();			//�X�g�b�v���邽�߂ɕK�v
	lpdSoundBuffer[play_num]->SetCurrentPosition(0);//�Đ��ʒu�����ɖ߂�
}
/*=============================================================================
			�֐��� ReleaseSound
			������ void
			�߂�l void�^
			�T�@�v DirectSound����p�֐��B
=============================================================================*/
void ReleaseSound(void)
{
	for(int i = 0; i < MAX_WAVE_SOUND; i++)
	{
		SAFE_RELEASE(lpdSoundBuffer[i]);		//����������s��
	}
	SAFE_RELEASE(lpdSound);
}
