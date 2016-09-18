#include "TaskFuncs.h"

// ���y�Đ��̂��߂̃^�X�N
SoundFuncs::SoundFuncs(DxSound* sound){
	m_pSound = new DxSound;
	*m_pSound = *sound;
}

void SoundFuncs::main(){
	//���y���I��������
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
