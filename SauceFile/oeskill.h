//================================================================================================================================================================
//
//�M�A����[gear.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _OESKILL_H_
#define _OESKILL_H_

//================================================================================================================================================================
//���C�u���������N
//================================================================================================================================================================
#include "oeskill_cooldown.h"
#include "object2d.h"

//================================================================================================================================================================
//�N���X��`
//================================================================================================================================================================

//********************************************�I�v�e�B�}�X�G�l���M�[�Ǘ�****************************************************************
class COeSkill :public CObject2D
{
	//-----------------------------------------�p�u���b�N----------------------------------------------
public:
	COeSkill();
	~COeSkill()       override;
	HRESULT Init() override;
	void Uninit()  override;
	void Update()  override;
	void Draw()    override;
	bool GetOeSkillMode() { return m_bOeskillShift; };
	void SkillFlag(bool flag) { m_bOeSkillCoolDown = flag; }
	void FlagShift() {
		m_bOeskillShift = m_bOeskillShift ? false : true;}
protected:
	static bool m_bOeskillShift;
	static bool m_bOeSkillCoolDown;
	float  m_fCoolDownTime;
	float m_SizeTime;
	const float m_fScrollSplit = 285.f;
	const float m_fBaseSplitStatus = 1.3f;
	const int m_nPlusAlpha = 5;
};

//********************************************�X���X�^�[����p�X�L��****************************************************************
class COeSkill_Cool :public COeSkill
{
	//-----------------------------------------�p�u���b�N----------------------------------------------
public:
	COeSkill_Cool();
	~COeSkill_Cool()  override;
	HRESULT Init() override;
	void Uninit()  override;
	void Update()  override;
	void Draw()    override;
	static COeSkill_Cool* Create(); //Object2D����

private:
	CSkill_CoolDown* m_CoolSkilDownIcon;
};

//********************************************�W���~���O�J�����X�L��****************************************************************
class COeSkill_Jamming :public COeSkill
{
	//-----------------------------------------�p�u���b�N----------------------------------------------
public:
	COeSkill_Jamming();
	~COeSkill_Jamming()  override;
	HRESULT Init() override;
	void Uninit()  override;
	void Update()  override;
	void Draw()    override;
	static COeSkill_Jamming* Create(); //Object2D����
private:
	CSkill_CoolDown* m_RepairSkilDownIcon;
};
#endif