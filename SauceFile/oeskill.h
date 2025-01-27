//================================================================================================================================================================
//
//ギア処理[gear.h]
//Author : Yuudai Takaya
//
//================================================================================================================================================================
#ifndef _OESKILL_H_
#define _OESKILL_H_

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "oeskill_cooldown.h"
#include "object2d.h"

//================================================================================================================================================================
//クラス定義
//================================================================================================================================================================

//********************************************オプティマスエネルギー管理****************************************************************
class COeSkill :public CObject2D
{
	//-----------------------------------------パブリック----------------------------------------------
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

//********************************************スラスター速冷却スキル****************************************************************
class COeSkill_Cool :public COeSkill
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	COeSkill_Cool();
	~COeSkill_Cool()  override;
	HRESULT Init() override;
	void Uninit()  override;
	void Update()  override;
	void Draw()    override;
	static COeSkill_Cool* Create(); //Object2D生成

private:
	CSkill_CoolDown* m_CoolSkilDownIcon;
};

//********************************************ジャミングカメラスキル****************************************************************
class COeSkill_Jamming :public COeSkill
{
	//-----------------------------------------パブリック----------------------------------------------
public:
	COeSkill_Jamming();
	~COeSkill_Jamming()  override;
	HRESULT Init() override;
	void Uninit()  override;
	void Update()  override;
	void Draw()    override;
	static COeSkill_Jamming* Create(); //Object2D生成
private:
	CSkill_CoolDown* m_RepairSkilDownIcon;
};
#endif