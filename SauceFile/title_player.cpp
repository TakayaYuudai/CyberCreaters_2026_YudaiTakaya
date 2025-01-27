//================================================================================================================================================================
//
//�v���C���[����[player3D.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================

//================================================================================================================================================================
//���C�u���������N
//================================================================================================================================================================
#include "title_player.h"
#include "title_guide.h"
#include "effect_backpack.h"
#include "manager.h"

//================================================================================================================================================================
//�R���X�g���N�^
//================================================================================================================================================================
CPlayer_Title::CPlayer_Title() :CXcharacter(3)
{

}

//================================================================================================================================================================
//�f�X�g���N�^
//================================================================================================================================================================
CPlayer_Title::~CPlayer_Title()
{

}

//================================================================================================================================================================
//�����ݒ�
//================================================================================================================================================================
HRESULT CPlayer_Title::Init()
{
	CXcharacter::Init();

	LoadParts();
	LoadMotion();
	SetPos(0.0f, (float)NULL, 1500.f);
	SetLife(100);
	SetState(STATEMODE::NONE);
	m_CameraPos={(float)NULL,(float)NULL, (float)NULL};

	return S_OK;
}

//================================================================================================================================================================
//�I������
//================================================================================================================================================================
void CPlayer_Title::Uninit()
{
	for (int i = 0; i < NUM; i++){
		m_PlayerParts[i]->Uninit();
		m_PlayerParts[i] = nullptr;
	}

	CXcharacter::Uninit();
}

//================================================================================================================================================================
//�X�V����
//================================================================================================================================================================
void CPlayer_Title::Update()
{
	//�ʒu�擾
	D3DXVECTOR3* pPos = CObjectX::GetPos();
	D3DXVECTOR3* pRot = CObjectX::GetRot();

	// �X�^�[�g���ǂ���
	bool bStart = CTitle_Guide::GetStart();

	// �o�����o�\�m�F
	bool bSortie = CTitle_Logo::GetSortie();

	if (CManager::GetInstance()->GetScene()->GetMode() == CScene::MODE::MODE_RESULT)
	{
		m_CameraRot.y += 0.01f;
		m_CameraPos = *pPos;
	}

	if (!bStart){
		m_CameraRot.y += 0.01f;
		m_CameraPos = *pPos;
	}

	else {

	    if (CManager::GetInstance()->GetScene()->GetMode() != CScene::MODE::MODE_RESULT)
	    {
	    	m_CameraRot.y = 0.f;
	    	m_CameraRot.x += 5.f;
	    
	    	if (m_CameraRot.x > 100){
	    		m_CameraRot.x = 100.f;
	    
	    		if (bSortie){
	    
	    			SetUpMove({ 0.f,0.f, -0.5f });
	    
	    			if (pPos->z < (float)NULL){
	    				SetUpMove({ 0.f,0.5f, -0.5f });
	    			}
	    
	    			for (int i = 0; i < 3; i++){
	    				CBack_Effect::Create(*pPos, *pRot);
	    			}
	    		}
	    	}
	    
	    	if (pPos->z < (float)NULL - 200.f) {
	    		CManager::GetInstance()->GetScene()->FadeTrigger();
	    	}
	    }

	}

	//�v���C���[�̌�����ɒǂ�
	CManager::GetInstance()->GetCamera()->FollowCameraTargetPlayer(m_CameraPos, m_CameraRot);

	SetMotion(NONE);

	//���[�V����
	Motion();

	CXcharacter::Update();
}

//================================================================================================================================================================
//�`�揈���i�S�I�u�W�F�N�g�j
//================================================================================================================================================================
void CPlayer_Title::Draw()
{
	//�ʒu�擾
	D3DXVECTOR3* pPos = CObjectX::GetPos();
	//�ʒu�擾
	D3DXVECTOR3* pRot = CObjectX::GetRot();
	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	//���݂̃}�e���A���ۑ��p
	D3DMATERIAL9 matDef;
	//�}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATERIAL* pMat;

	CRenderer* pRenderer = nullptr;
	pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 RendererDivice = pRenderer->GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, pRot->y, pRot->x, pRot->z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pPos->x, pPos->y, pPos->z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	RendererDivice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int i = 0; i < NUM; i++) {
		m_PlayerParts[i]->Draw();
	}
}

//================================================================================================================================================================
//���f���ǂݍ��ݏ���
//================================================================================================================================================================
void CPlayer_Title::LoadParts()
{
	const int nMaxData = 2048;
	char Datacheck[nMaxData];	// �f�[�^����
	char cModelPath[nMaxData];	// �f�[�^����
	int nCnt = 0;				//�g�p���̃f�[�^��
	int PlayerModelNumSeve = 0;			//�ǂݎ�������f������ۑ�����
	int Id = NULL;
	int nPair = NULL;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;

	// �t�@�C���̓ǂݍ���
	FILE* pFile = fopen("data\\MODEL\\player\\file.txt", "r");

	//�t�@�C�������݂��Ȃ����Ǖ����܂�
	if (pFile == NULL)
	{
		return;
	}

	// END��������܂œǂݍ��݂܂�
	while (1)
	{
		fscanf(pFile, "%s", Datacheck);	// �����ō��G����

		if (!strcmp(Datacheck, "END_SCRIPT"))
		{// �S�Ă�ǂݍ��񂾂̂Ń��[�h���I��
			fclose(pFile);
			break;
		}

		if (Datacheck[0] == '#')
		{// �߂�܂�
			continue;
		}

		//�p�[�c����ݒ�
		if (!strcmp(Datacheck, "NUM_PARTS"))
		{
			fscanf(pFile, "%s", Datacheck);
			fscanf(pFile, "%d", &PlayerModelNumSeve);
		}

		//���f���̖��O������
		if (!strcmp(Datacheck, "MODEL_FILENAME"))
		{
			fscanf(pFile, "%s", Datacheck);
			fscanf(pFile, "%s", cModelPath);
			m_FileModel[PlayerModelNumSeve] = cModelPath;
			m_PlayerParts[PlayerModelNumSeve] = CModelParts::Create({ 0.f,0.f,0.f }, m_FileModel[PlayerModelNumSeve]);
			PlayerModelNumSeve++;
		}

		//�e�p�[�c�̐ݒ�
		if (!strcmp(Datacheck, "PARTSSET"))
		{
			// ���ڂ��ƂɃf�[�^����
			while (1)
			{
				fscanf(pFile, "%s", Datacheck); //	���G

				if (!strcmp(Datacheck, "END_PARTSSET"))
				{
					// �ǂݍ��݂��I��
					break;
				}

				//�e�q��ݒ�
				else if (!strcmp(Datacheck, "INDEX"))
				{
					fscanf(pFile, "%s", Datacheck);
					fscanf(pFile, "%d", &Id);
				}

				//�p�[�c�̎��
				else if (!strcmp(Datacheck, "PARENT"))
				{
					fscanf(pFile, "%s", Datacheck);
					fscanf(pFile, "%d", &nPair);
				}

				//�e�p�[�c�̈ʒu
				else if (!strcmp(Datacheck, "POS"))
				{
					fscanf(pFile, "%s", Datacheck);
					fscanf(pFile, "%f", &pos.x);
					fscanf(pFile, "%f", &pos.y);
					fscanf(pFile, "%f", &pos.z);
				}

				//�e�p�[�c�̊p�x 
				else if (!strcmp(Datacheck, "ROT"))
				{
					fscanf(pFile, "%s", Datacheck);
					fscanf(pFile, "%f", &rot.x);
					fscanf(pFile, "%f", &rot.y);
					fscanf(pFile, "%f", &rot.z);
				}
			}

			m_PlayerParts[nCnt]->SetPos(pos);
			m_PlayerParts[nCnt]->SetRot(rot);

			m_PlayerParts[nCnt]->SetDeffalt();
			m_PlayerParts[nCnt]->SetId(Id);
			m_PlayerParts[nCnt]->ModelSizeSum();

			if (nPair != -1)
			{
				m_PlayerParts[nCnt]->SetParent(m_PlayerParts[nPair]);
			}

			nCnt++;	// �f�[�^�����Z
		}
	}
}

//================================================================================================================================================================
//���[�V�����ǂݍ��ݏ���
//================================================================================================================================================================
void CPlayer_Title::LoadMotion()
{
	char Datacheck[2048];	// �f�[�^����
	int MotionCnt = 0;		//���[�V�����J�E���g
	int keysetcnt = 0;		//���[�V�����J�E���g
	int KeyCnt = 0;			//�L�[�J�E���g

	// �t�@�C���̓ǂݍ���
	FILE* pFile = fopen("data\\MODEL\\player\\file.txt", "r");

	//�t�@�C�������݂��Ȃ����Ǖ����܂�
	if (pFile == NULL) {
		return;
	}

	while (1) {

		fscanf(pFile, "%s", Datacheck);	// �����ō��G����

		if (!strcmp(Datacheck, "END_SCRIPT"))
		{// �S�Ă�ǂݍ��񂾂̂Ń��[�h���I��
			fclose(pFile);
			break;
		}

		if (Datacheck[0] == '#')
		{// �߂�܂�
			continue;
		}

		//���[�V������Ԃ̐ݒ�
		if (!strcmp(Datacheck, "MOTIONSET"))
		{
			while (1)
			{
				fscanf(pFile, "%s", Datacheck); //	���G

				if (!strcmp(Datacheck, "END_MOTIONSET"))
				{
					// �ǂݍ��݂��I��
					break;
				}
				//���[�v�̔��f
				else if (!strcmp(Datacheck, "LOOP"))
				{
					fscanf(pFile, "%s", Datacheck);
					fscanf(pFile, "%d", &m_Motion[MotionCnt].LoopCheck);
				}

				//�S�̃L�[�̓ǂݍ���
				else  if (!strcmp(Datacheck, "NUM_KEY"))
				{
					fscanf(pFile, "%s", Datacheck);
					fscanf(pFile, "%d", &m_Motion[MotionCnt].NumKey);
				}

				//���݂̃L�[�̐ݒ�
				if (!strcmp(Datacheck, "KEYSET"))
				{
					while (1)
					{
						fscanf(pFile, "%s", Datacheck); //	���G

						if (Datacheck[0] == '#')
						{// �߂�܂�
							fgets(Datacheck, 100, pFile);
							continue;
						}

						if (!strcmp(Datacheck, "END_KEYSET"))
						{
							// �ǂݍ��݂��I��
							break;
						}

						//�S�̃L�[�̓ǂݍ���
						else if (!strcmp(Datacheck, "FRAME"))
						{
							fscanf(pFile, "%s", Datacheck);
							fscanf(pFile, "%d", &m_Motion[MotionCnt].KeySet[keysetcnt].FrameRate);
						}

						//���݂̃L�[�̐ݒ�
						if (!strcmp(Datacheck, "KEY"))
						{
							while (1)
							{
								fscanf(pFile, "%s", Datacheck); //	���G

								if (!strcmp(Datacheck, "END_KEY"))
								{
									// �ǂݍ��݂��I��
									break;
								}

								//�e�p�[�c�̃��[�V����pos�l
								else if (!strcmp(Datacheck, "POS"))
								{
									fscanf(pFile, "%s", Datacheck);
									fscanf(pFile, "%f", &m_Motion[MotionCnt].KeySet[keysetcnt].Key[KeyCnt].Motion_pos.x);
									fscanf(pFile, "%f", &m_Motion[MotionCnt].KeySet[keysetcnt].Key[KeyCnt].Motion_pos.y);
									fscanf(pFile, "%f", &m_Motion[MotionCnt].KeySet[keysetcnt].Key[KeyCnt].Motion_pos.z);
								}

								//�e�p�[�c�̃��[�V����rot�l
								else if (!strcmp(Datacheck, "ROT"))
								{
									fscanf(pFile, "%s", Datacheck);
									fscanf(pFile, "%f", &m_Motion[MotionCnt].KeySet[keysetcnt].Key[KeyCnt].Motion_rot.x);
									fscanf(pFile, "%f", &m_Motion[MotionCnt].KeySet[keysetcnt].Key[KeyCnt].Motion_rot.y);
									fscanf(pFile, "%f", &m_Motion[MotionCnt].KeySet[keysetcnt].Key[KeyCnt].Motion_rot.z);
								}
							}
							KeyCnt++;
						}
					}
					KeyCnt = 0;
					keysetcnt++;
				}
			}
			keysetcnt = 0;
			MotionCnt++;
		}
	}
}

//================================================================================================================================================================
//���[�V�����������揈��
//================================================================================================================================================================
void CPlayer_Title::Motion()
{
	//���[�V�����ړ��ʂ̌v�Z�p�֐�
	D3DXVECTOR3 Mpos[NUM];
	D3DXVECTOR3 Mrot[NUM];

	int nKey = (m_nKeyCnt + 1) % m_Motion[m_MotionSet].NumKey; //���̃L�[�Ƃ̌����̈ʒu�̍������v�Z���邽�߂�int�֐�

	for (int i = 0; i < NUM; i++)
	{
		D3DXVECTOR3 pGetRot = m_PlayerParts[i]->GetRot();

		//���߂�������S�̃t���[�����[�g�Ŋ��邱�Ƃ�1�t���[���̓��슄����K��������
		Mrot[i] = ((m_Motion[m_MotionSet].KeySet[nKey].Key[i].Motion_rot)
			- (m_PlayerParts[i]->GetRot()))
			/ (float)m_Motion[m_MotionSet].KeySet[m_nKeyCnt].FrameRate;

		pGetRot += Mrot[i];

		m_PlayerParts[i]->SetRot(pGetRot);
	}

	//���t���[���̉��Z���������܂��傤
	m_nFrameCnt++;

	//�����ŏo�����t���[�����[�g�����t���[�����[�g�J�E���g����������
	if (m_nFrameCnt >= m_Motion[m_MotionSet].KeySet[m_nKeyCnt].FrameRate)
	{
		//�t���[�����Z�b�g
		m_nFrameCnt = 0;

		//�g�p���̃��[�V����������Ȃ��֐i�߂܂�
		m_nKeyCnt = (m_nKeyCnt + 1) % m_Motion[m_MotionSet].NumKey;
	}
}

//================================================================================================================================================================
//���[�V�����ݒ菈��
//================================================================================================================================================================
void CPlayer_Title::SetMotion(TYPE g_Motions)
{
	if (m_MotionSet != g_Motions)
	{
		m_nFrameCnt = 0;
		m_MotionSet = g_Motions;
		m_nKeyCnt = 0;
	}
}

//================================================================================================================================================================
//�v���C���[����
//================================================================================================================================================================
CPlayer_Title* CPlayer_Title::Create()
{
	CPlayer_Title* pCPlayer_Title = new CPlayer_Title();
	pCPlayer_Title->Init();
	pCPlayer_Title->SetType(CObject::TYPE::PLAYER);
	return pCPlayer_Title;
}