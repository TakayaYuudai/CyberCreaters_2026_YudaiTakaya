#include "object.h"

// �ÓI�����o�ϐ��̏�����
int CObject::m_nNumAll = 0; // �S�I�u�W�F�N�g��
CObject* CObject::m_pTop = nullptr; // ���X�g�̐擪
CObject* CObject::m_pCur = nullptr; // ���݂̃I�u�W�F�N�g�i�Ō�ɒǉ����ꂽ�I�u�W�F�N�g�j

//====================================================================================================
// �R���X�g���N�^
//====================================================================================================
CObject::CObject(int nPriority) : m_nPriority(nPriority) {

    // ����I�u�W�F�N�g�̏ꍇ
    if (m_pTop == nullptr) {
        // �I�u�W�F�N�g�����X�g�Ɉ���Ȃ��ꍇ

        m_pTop = this;     // ���̃I�u�W�F�N�g���擪
        m_pCur = this;     // ���݂̃I�u�W�F�N�g�����̃I�u�W�F�N�g
        m_pPrev = nullptr; // �O�̃I�u�W�F�N�g�͂Ȃ�
        m_pNext = nullptr; // ���̃I�u�W�F�N�g���Ȃ�
    }

    else{
        CObject* pInsertPos = m_pTop; // �}���ʒu��T��
        CObject* pPrev = nullptr; // �}���ʒu�̑O�̃I�u�W�F�N�g

        // �D��x�Ɋ�Â��đ}���ʒu��T��
        while (pInsertPos != nullptr && pInsertPos->m_nPriority >= nPriority) {
            pPrev = pInsertPos;  // ���݂̃I�u�W�F�N�g��O�̃I�u�W�F�N�g�Ƃ��ĕۑ�
            pInsertPos = pInsertPos->m_pNext; // ���̃I�u�W�F�N�g�֐i��
        }

        // �}���ʒu�Ń|�C���^�̐ݒ�
        m_pPrev = pPrev;   // �O�̃I�u�W�F�N�g
        m_pNext = pInsertPos; // ���̃I�u�W�F�N�g

        if (pPrev == nullptr){  // �擪�ɑ}������ꍇ
            m_pTop = this; // ���̃I�u�W�F�N�g��擪�ɐݒ�
        }
        else{
            pPrev->m_pNext = this; // �O�̃I�u�W�F�N�g�̎��ɂ��̃I�u�W�F�N�g��ݒ�
        }
        if (pInsertPos != nullptr) {
            pInsertPos->m_pPrev = this; // ���̃I�u�W�F�N�g������΁A�O�ɂ��̃I�u�W�F�N�g��ݒ�
        }
    }

    m_bDeath = false;  // ���S�t���O��������
    m_nNumAll++;       // �S�I�u�W�F�N�g�����C���N�������g
}

//====================================================================================================
// �f�X�g���N�^
//====================================================================================================
CObject::~CObject() {
    Release(); // �I�u�W�F�N�g�̉������
}

//====================================================================================================
// ���ׂẴI�u�W�F�N�g�̉��
//====================================================================================================
void CObject::ReleaseAll() {
    CObject* pObj = m_pTop;  // �擪�I�u�W�F�N�g���珇�Ԃɉ��

    while (pObj != nullptr)
    {
        CObject* pNext = pObj->m_pNext; // ���̃I�u�W�F�N�g��ۑ�
        pObj->Release(); // �������
        pObj = pNext; // ���̃I�u�W�F�N�g�ɐi��
    }

    m_pTop = nullptr; // �擪�|�C���^��nullptr�Ƀ��Z�b�g
    m_pCur = nullptr; // ���݂̃|�C���^��nullptr�Ƀ��Z�b�g
}

//====================================================================================================
// ���ׂẴI�u�W�F�N�g�̍X�V
//====================================================================================================
void CObject::UpdateAll() {
    CObject* pObj = m_pTop;  // �擪�I�u�W�F�N�g���珇�ԂɍX�V

    while (pObj != nullptr)
    {
        CObject* pNext = pObj->m_pNext; // ���̃I�u�W�F�N�g��ۑ�
        pObj->Update(); // �I�u�W�F�N�g�̍X�V
        if (pObj->m_bDeath)  // ���S�t���O���m�F
        {
            delete pObj; // ���S���Ă�����I�u�W�F�N�g���폜
        }
        pObj = pNext; // ���̃I�u�W�F�N�g�ɐi��
    }
    int n = 0;
}

//====================================================================================================
// ���ׂẴI�u�W�F�N�g�̕`��
//====================================================================================================
void CObject::DrawAll() {
    CObject* pObj = m_pTop;  // �擪�I�u�W�F�N�g���珇�Ԃɕ`��

    while (pObj != nullptr)
    {
        pObj->Draw(); // �I�u�W�F�N�g�̕`��
        pObj = pObj->m_pNext; // ���̃I�u�W�F�N�g�ɐi��
    }
}

//====================================================================================================
// ���g�̉��
//====================================================================================================
void CObject::Release() {
    CObject* pPrev = m_pPrev; // �O�̃I�u�W�F�N�g
    CObject* pNext = m_pNext; // ���̃I�u�W�F�N�g

    if (pPrev == nullptr)  // �擪�̃I�u�W�F�N�g�̏ꍇ
    {
        m_pTop = pNext; // �擪�|�C���^�����̃I�u�W�F�N�g�ɐݒ�
        if (pNext != nullptr) {
            pNext->m_pPrev = nullptr; // ���̃I�u�W�F�N�g�̑O��nullptr�ɐݒ�
        }
    }
    else if (pNext == nullptr)  // �Ō�̃I�u�W�F�N�g�̏ꍇ
    {
        m_pCur = pPrev; // ���݂̃I�u�W�F�N�g�|�C���^��O�̃I�u�W�F�N�g�ɐݒ�
        pPrev->m_pNext = nullptr; // �O�̃I�u�W�F�N�g�̎���nullptr�ɐݒ�
    }
    else  // ���Ԃ̃I�u�W�F�N�g�̏ꍇ
    {
        pPrev->m_pNext = pNext; // �O�̃I�u�W�F�N�g�̎������̃I�u�W�F�N�g�ɐݒ�
        pNext->m_pPrev = pPrev; // ���̃I�u�W�F�N�g�̑O��O�̃I�u�W�F�N�g�ɐݒ�
    }

    m_pNext = nullptr; // ���̃I�u�W�F�N�g�|�C���^��nullptr�ɐݒ�
    m_pPrev = nullptr; // �O�̃I�u�W�F�N�g�|�C���^��nullptr�ɐݒ�
    m_bDeath = false;  // ���S�t���O�����Z�b�g
    m_nNumAll--;       // �S�I�u�W�F�N�g�����f�N�������g
}

//====================================================================================================
// �^�C�v�擾
//====================================================================================================
CObject::TYPE CObject::GetType() {
    return m_type; // �I�u�W�F�N�g�̃^�C�v��Ԃ�
}

//====================================================================================================
// �^�C�v�ݒ�
//====================================================================================================
void CObject::SetType(TYPE ntype) {
    m_type = ntype; // �I�u�W�F�N�g�̃^�C�v��ݒ�
}
