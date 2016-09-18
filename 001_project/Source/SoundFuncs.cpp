#include "TaskFuncs.h"

// 音楽再生のためのタスク
SoundFuncs::SoundFuncs(DxSound* sound){
	m_pSound = new DxSound;
	*m_pSound = *sound;
}

void SoundFuncs::main(){
	//音楽が終了したら
	if(m_pSound->GethEvent() == (HANDLE)0xfeeefeee){
		Delete();
	}
}

void SoundFuncs::Play( bool loop)
{
	m_pSound->EnableDeleteByEnd();
	m_pSound->Play(loop);
}
void SoundFuncs::Stop()
{
	if(m_pSound)
		m_pSound->Stop();
}
void SoundFuncs::EnableDeleteByEnd()
{
	m_pSound->EnableDeleteByEnd();
}
