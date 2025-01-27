//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : Yuudai Takaya
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "Pch.h"

//================================================================================================================================================================
//�N���X��`
//================================================================================================================================================================

class CSound
{
	//-----------------------------------------�p�u���b�N----------------------------------------------
public:

	//*****************************************************************************
	// �T�E���h�ꗗ
	//*****************************************************************************
	typedef enum
	{
		//-----------------------------------------BGM----------------------------------------------
		TITLE_BGM = 0, //�^�C�g��BGM
		TUTORIAL_BGM,  //�`���[�g���A��BGM
		BATTLE_BGM ,   //�o�g��BGM

		//-----------------------------------------SE----------------------------------------------
		SOUND_ATTACK_SE,    //�U����
		SOUND_SQUIRT_SE,    //�U����
		SOUND_EXPLOSION_SE, //�U����
		SOUND_FIRING_SE,    //�U����
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

	//-----------------------------------------�v���C�x�[�g----------------------------------------------
private:
	IXAudio2* m_pXAudio2 = NULL;								// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice* m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE* m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y
};
#endif