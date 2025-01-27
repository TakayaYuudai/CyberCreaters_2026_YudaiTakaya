//================================================================================================================================================================
//
//プレイヤー処理[player3D.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "player_3d.h"
#include "enemy_boss.h"
#include "manager.h"
#include "effect_backpack.h"
#include "effect_explosion.h"
#include "effect_charge.h"
#include "effect_cool.h"
#include "field.h"
#include "damageeff.h"

bool CPlayer3D::m_bOeSkillBreak = false;

//================================================================================================================================================================
//コンストラクタ
//================================================================================================================================================================
CPlayer3D::CPlayer3D():CXcharacter(3),m_bRushAtk(false),m_nRushCoolTime(NULL), m_nOeSkillBreakTime(NULL), m_bRecovery(false){

}

//================================================================================================================================================================
//デストラクタ
//================================================================================================================================================================
CPlayer3D::~CPlayer3D()
{

}

//================================================================================================================================================================
//初期設定
//================================================================================================================================================================
HRESULT CPlayer3D::Init()
{
	CXcharacter::Init();

	LoadParts();
	LoadMotion();
	SetPos(0.0f,(float)NULL,1500.f);
	SetLife(100);
	SetState(STATEMODE::NONE);

	m_fChargeSum = (float)NULL;

	m_GageBack[0] = CGage_Back::Create(D3DXVECTOR2(SCREEN_WIDTH*0.5f, 576.f),130.f, 15.f,false);
	m_GageBack[1] = CGage_Back::Create(D3DXVECTOR2(200.f, 680.f), 130.f, 15.f, true); //ヒート
	m_GageBack[2] = CGage_Back::Create(D3DXVECTOR2(200.f, 620.f), 130.f, 15.f, true); //ライフ

	m_ChargeGage = Charge_Gage::Create();

	m_GageHeat  = CGage_Heat::Create();

	m_PlayerLifeGage = CGage_Player_Life::Create();

	m_GearSpeed = CSpeedgear::Create();

	m_GearAtk = CAtkgear::Create();

	m_Oeskill_Cool = COeSkill_Cool::Create();

	m_Oeskill_Repair = COeSkill_Jamming::Create();

	m_TargerPnt = CTarget_Pointer::Create();

	m_OldPos = D3DXVECTOR3((float)NULL, (float)NULL, (float)NULL);

	m_CameraRot = D3DXVECTOR3((float)NULL, D3DX_PI * 0.01f, (float)NULL);

	m_nKeyCnt = NULL;

	m_nFrameCnt = NULL;

	m_bFlowEnemMode = false;

	m_bAtk = false;

	m_nStepCnt = NULL;

	m_bStepMode = false;

	m_fHeatSum = (float)NULL;

	m_bStepVec = false;

	m_MotionSet = NONE;

	m_nGap = NULL;

	m_nAtkTime = NULL;

	m_bAtkPanchi = false;

	m_Step = { 0.f,0.f,0.f };

	m_vVelocity = { 0.f,0.f,0.f };

	m_bOverheat = false;

	m_bUseOeSkill = false;

	m_nAtkSum = NULL;

	m_PowerRank = FIRST;

	m_nOeSkillTime = NULL;

	return S_OK;
}

//================================================================================================================================================================
//終了処理
//================================================================================================================================================================
void CPlayer3D::Uninit()
{
	m_ChargeGage->Uninit();
	m_ChargeGage = nullptr;

	m_GageHeat->Uninit();
	m_GageHeat = nullptr;

	for (int i = 0; i < MAX_GAGE_BACK; i++)
	{
		m_GageBack[i]->Uninit();
		m_GageBack[i] = nullptr;
	}

	m_GearSpeed->Uninit();
	m_GearSpeed = nullptr;

	m_GearAtk->Uninit();
	m_GearAtk = nullptr;

	m_Oeskill_Cool->Uninit();
	m_Oeskill_Cool = nullptr;

	m_Oeskill_Repair->Uninit();
	m_Oeskill_Repair = nullptr;

	m_TargerPnt->Uninit();
	m_TargerPnt = nullptr;

	m_PlayerLifeGage->Uninit();
	m_PlayerLifeGage = nullptr;


	for (int i = 0; i < NUM; i++)
	{
		m_PlayerParts[i]->Uninit();
		m_PlayerParts[i]=nullptr;
	}

	CManager::GetInstance()->GetScene()->FadeTrigger();

	CXcharacter::Uninit();
}

//================================================================================================================================================================
//更新処理
//================================================================================================================================================================
void CPlayer3D::Update()
{
	//演出中かどうか
	if (CManager::GetInstance()->GetCamera()->GetPlayStay()) {
		//以下の処理強制スキップ
		return;
	}

	//死んでいる場合
	if (GetLife()<=NULL){

		CManager::GetInstance()->GetScene()->SetLodeResult(false);
		return;
	}

	//位置取得
	D3DXVECTOR3* pPos = CObjectX::GetPos();
	//角度取得
	D3DXVECTOR3* pRot = CObjectX::GetRot();
	//入力情報確保
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	//パッド入力情報
	CInputJoypad* pJoy = CManager::GetInstance()->GetPad();
	// ライフゲージ
	m_PlayerLifeGage->GageAnim((float)GetLife());
	//オーバーヒート管理処理
	OverHeatManagement(*pPos);
	//カメラモード管理処理
	CameraManagement(*pPos,*pRot);
	//カメラ操作
	Rotation();

	//ギアシフト処理
	if (pJoy->GetTrigger(CInputJoypad::JOYKEY_LB)&&!m_bAtk) {
		m_GearSpeed->FlagShift();
	}

	//オプティマスエネルギー管理処理
	OeSkillManagement(*pPos);

	//チャージ度をゲージ化
	m_ChargeGage->GageAnim(m_fChargeSum);
	//スラスター熱量ゲージ化
	m_GageHeat->GageAnim(m_fHeatSum);

	//移動処理
	if (!m_bStepMode) {
		//チャージしていない
		MoveMent(*pRot,*pPos);
	}
	// ニュートラル時向き補正
	if (!MoveMent(*pRot,*pPos)) {
		//移動していないとき
		SetRot(D3DXVECTOR3(0.f, 0.f, 0.f));
	}

	//攻撃全般を管理
	AtkManagement(*pPos,*pRot);

	// 回避行動
	if ((pKeyboard->GetTrigger(DIK_LSHIFT) || pJoy->GetTrigger(CInputJoypad::JOYKEY_B))
		&& !m_bAtk && !m_bOverheat
		&& GetState() != STATEMODE::DAMAGE) {
		// ステップ回避
		m_bStepMode = true;
	}

	//モーションステイト管理処理
	MotionStateManagement(*pPos,*pRot);

	//モーション実行
	Motion();

	//前の位置を設定
	m_OldPos = *pPos;

	m_ChargeGage->SetDraw(m_bAtk);
	m_GageBack[0]->SetDraw(m_bAtk);

	CXcharacter::Update();
}

//================================================================================================================================================================
//描画処理（全オブジェクト）
//================================================================================================================================================================
void CPlayer3D::Draw()
{
	//位置取得
	D3DXVECTOR3* pPos = CObjectX::GetPos();
	//位置取得
	D3DXVECTOR3* pRot = CObjectX::GetRot();
	//計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
	//現在のマテリアル保存用
	D3DMATERIAL9 matDef;
	//マテリアルデータへのポインタ
	D3DXMATERIAL* pMat;

	CRenderer* pRenderer = nullptr;
	pRenderer = CManager::GetInstance()->GetRenderer();
	LPDIRECT3DDEVICE9 RendererDivice = pRenderer->GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	
	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, pRot->y, pRot->x, pRot->z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, pPos->x, pPos->y, pPos->z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	RendererDivice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int i = 0; i < NUM; i++){
		m_PlayerParts[i]->Draw();
	}
}

//================================================================================================================================================================
// オーバーヒート管理処理
//================================================================================================================================================================
void CPlayer3D::OverHeatManagement(D3DXVECTOR3 pos) {

	// オーバーヒート
	if (m_fHeatSum >= 100.f && !m_bOverheat) {
		//オーバーヒートモード突入
		m_bOverheat = true;
		CExplosion_Effect::Create(pos);
	}

	//　オーバーヒート処理
	if (m_bOverheat) {
		//冷却割合
		float fCoolvalue = 0.3;
		CoolThruster(fCoolvalue);
		SetMotion(OVERHEAT);
		if (m_fHeatSum <= 0.f) {
			m_bOverheat = false;
		}
	}
}

//================================================================================================================================================================
// カメラモード管理処理
//================================================================================================================================================================
void CPlayer3D::CameraManagement(D3DXVECTOR3& pos, D3DXVECTOR3& rot) {

	//入力情報確保
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	//パッド入力情報
	CInputJoypad* pJoy = CManager::GetInstance()->GetPad();

	//追跡モード時
	if (m_bFlowEnemMode) {
		//敵の方向に向かせる
		SearchRot(rot, pos);
		DistanceSum(rot, pos);
	}

	//周辺サーチモード
	else {
		//プレイヤーの後ろを常に追う
		CManager::GetInstance()->GetCamera()->FollowCameraTargetPlayer(pos, m_CameraRot);

		if (m_TargerPnt->GetDraw()) {
			m_TargerPnt->SetDraw(false);
		}
	}

	//カメラモード変換
	if (pKeyboard->GetTrigger(DIK_L) || pJoy->GetTrigger(CInputJoypad::JOYKEY_R3)) {
		m_bFlowEnemMode = m_bFlowEnemMode ? false : true;
	}

}

//================================================================================================================================================================
// オプティマスエネルギー管理処理
//================================================================================================================================================================
void CPlayer3D::OeSkillManagement(D3DXVECTOR3 pos) {

	//入力情報確保
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	//パッド入力情報
	CInputJoypad* pJoy = CManager::GetInstance()->GetPad();

	//最大後隙の時間
	const int nMaxBreakSkillTime = 600;

	//スキルシフト処理
	if (pJoy->GetTrigger(CInputJoypad::JOYKEY_RB) && !m_bUseOeSkill) {
		m_Oeskill_Cool->FlagShift();
	}

	//オプティマスエネルギースキル使用
	if (pJoy->GetRTrigger().y >= 0.7f && !m_bUseOeSkill && !m_bOeSkillBreak) {
		//スキル使用状態
		m_bUseOeSkill = true;
	}

	//オプティマスエネルギー内部処理
	if (m_bUseOeSkill) {
		//スキル使用処理
		OeSkill(pos);
	}

	//使用されてない際にリセット処理
	else {
		m_GageBack[1]->SetCollar(255, 255, 255, 255);
	}

	//スキル使用完了後のクールタイム
	if (m_bOeSkillBreak && !m_bUseOeSkill){
		++m_nOeSkillBreakTime;
		OeSkillBreakTime(600);
	}

}

//================================================================================================================================================================
// オプティマスエネルギー使用処理
//================================================================================================================================================================
void CPlayer3D::OeSkill(D3DXVECTOR3 pos) {

	//スキル継続時間インクリ
	++m_nOeSkillTime;

	//オプティマスエネルギー変数
	bool bOeSkill = m_Oeskill_Cool->GetOeSkillMode();
	const int nLife = GetLife();
	const int nMaxLife = GetMaxLife();

	//リペアスキル処理
	if (bOeSkill){
		if (nLife < nMaxLife || m_bRecovery){
			OeSkill_Repair(pos);
		}
		else {
			m_bUseOeSkill = false;
		}
	}

	//スラスター冷却スキル
	else {
		OeSkill_CoolThruster(pos);
	}
}

//================================================================================================================================================================
// スラスター冷却スキル処理
//================================================================================================================================================================
void CPlayer3D::OeSkill_CoolThruster(D3DXVECTOR3 pos){

	//効果継続時間
	int nTimeLimit = 60;
	//スラスター速冷却処理
	D3DXVECTOR3 TargetPos = { pos.x,pos.y + m_PlayerParts[0]->GetPos().y,pos.z };//目標地点計算
	//エフェクト生成
	CCool_Effect::Create(TargetPos);
	//熱量低下
	CoolThruster(0.5f);
	//一時的にゲージを水色に
	m_GageBack[1]->SetCollar(0, 255, 255, 255);
	//オプティマスエネルギースキルステータスリセット処理
	OeSkillStatusrReset(nTimeLimit);
}

//================================================================================================================================================================
// リペアスキル処理
//================================================================================================================================================================
void CPlayer3D::OeSkill_Repair(D3DXVECTOR3 pos) {

	//効果継続時間
	int nTimeLimit = 800;
	//スラスター速冷却処理
	D3DXVECTOR3 TargetPos = { pos.x,pos.y + m_PlayerParts[0]->GetPos().y,pos.z };//目標地点計算
	//エフェクト生成
	CCool_Effect::Create(TargetPos);
	//オプティマスエネルギースキルステータスリセット処理
	OeSkillStatusrReset(nTimeLimit);

	if (m_bRecovery){
		return;
	}

	const int nRecoveryValue = 20;

	RecoveryLife(nRecoveryValue);

	m_bRecovery = true;
}

//================================================================================================================================================================
// 攻撃管理処理
//================================================================================================================================================================
void CPlayer3D::AtkManagement(D3DXVECTOR3& pos, D3DXVECTOR3& rot) {

	// ラッシュ攻撃
	if (!m_GearSpeed->GetFlagGear()){
		RushAtk(pos, rot);
	}

	// チャージ攻撃
	else {
		ChargeAtkManagement(pos,rot);
	}
}

//================================================================================================================================================================
// ラッシュ攻撃管理処理
//================================================================================================================================================================
void CPlayer3D::RushAtk(D3DXVECTOR3 pos , D3DXVECTOR3& rot) {

	//ラッシュ攻撃クールタイム設定
	const int nMaxRushCoolTime = 20;
	//入力情報確保
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	//パッド入力情報
	CInputJoypad* pJoy = CManager::GetInstance()->GetPad();

	//クールタイム処理
	if (m_bRushAtk){
		++m_nRushCoolTime;
		//クールタイム終了処理
		if (m_nRushCoolTime > nMaxRushCoolTime) {
			m_nRushCoolTime = NULL;
			m_bRushAtk = false;
		}
	}

	// 連打で攻撃
	if ((!pKeyboard->GetTrigger(DIK_SPACE) && !pJoy->GetTrigger(CInputJoypad::JOYKEY_X))||
		m_bRushAtk) {
		return;
	}

	m_bRushAtk = true;

	//ヒット判定の位置
	D3DXVECTOR3 HitPos = { pos.x, pos.y + m_PlayerParts[0]->GetPos().y, pos.z };
	//リストの先頭オブジェクトから開始
	CObject* pObject = CObject::GetTop();
	//ヒット判定
	bool bAtkHit = false;
	//攻撃数値設定
	const int nAtkValue = 1;

	while (pObject != nullptr)
	{
		CObject::TYPE type = pObject->GetType();

		// ボスタイプのチェック
		if (type == CObject::TYPE::BOSS)
		{
			// 安全にダウンキャスト
			CEnemy_Boss* pBoss = dynamic_cast<CEnemy_Boss*>(pObject);

			// ダウンキャストに成功した場合
			if (pBoss)
			{
				// 当たっているか判断
				if (CManager::GetInstance()->GetCollision()->HitCircleCollision(HitPos, *pBoss->GetPos(),
					m_PlayerParts[0]->GetPartsRadhiusu(),{ 50.f,50.f,50.f })) {
					// 攻撃反転ON
					bAtkHit = true;
				}

				// アタックモード解除
				if (bAtkHit) {
					// 敵にダメージを与える
					pBoss->Damage(nAtkValue);
					pBoss->SetState(STATEMODE::DAMAGE);
				}
				break; // 一つのボスに当たったらループを抜ける
			}

		}
		// 次のオブジェクトに移動
		pObject = pObject->GetNext();
	}
	rot.y = CManager::GetInstance()->GetCamera()->GetRot().y;
}

//================================================================================================================================================================
// チャージ攻撃管理処理
//================================================================================================================================================================
void CPlayer3D::ChargeAtkManagement(D3DXVECTOR3 pos, D3DXVECTOR3& rot) {

	D3DXVECTOR3 pPos = pos;

	//入力情報確保
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	//パッド入力情報
	CInputJoypad* pJoy = CManager::GetInstance()->GetPad();

	//チャージ行動
	if ((pKeyboard->GetPress(DIK_SPACE) || pJoy->GetPress(CInputJoypad::JOYKEY_X))
		&& GetState() != STATEMODE::DAMAGE
		&& !m_bStepMode) {
		// チャージ処理
		Charge(rot);

		// 目標地点計算
		D3DXVECTOR3 TargetPos = { pPos.x, pPos.y + m_PlayerParts[0]->GetPos().y, pPos.z };

		// チャージ用エフェクト
		for (int i = 0; i < m_PowerRank; i++) {
			CCharge_Effect::Create(TargetPos, m_PowerRank);
		}
	}

	else if (!pJoy->GetPress(CInputJoypad::JOYKEY_X)
		&& m_fChargeSum > 0.0f && m_bAtk) {
		// チャージしていない場合
		m_bAtkPanchi = true;
	}
}

//================================================================================================================================================================
// モーション実行処理
//================================================================================================================================================================
void CPlayer3D::MotionStateManagement(D3DXVECTOR3 pos, D3DXVECTOR3& rot) {

	//チャージ攻撃
	if (m_bAtkPanchi) {
		ChargeAtk(pos,rot);
	}

	//チャージ中
	else if (m_bAtk) {
		SetMotion(CHARGE);
	}

	//ステップ
	else if (m_bStepMode && !m_bAtk && !m_bOverheat) {
		Step(rot);
	}

	//歩いている状態
	else if (MoveMent(rot, pos)) {
		SetMotion(WALK);
	}

	//待機中
	else {
		SetMotion(NONE);
	}
}

//================================================================================================================================================================
// 移動処理（慣性付き、重みのある移動で急に止まらないように調整）
//================================================================================================================================================================
bool CPlayer3D::MoveMent(D3DXVECTOR3& rot ,D3DXVECTOR3 pos)
{
	if (GetState() == STATEMODE::DAMAGE){
		return false;
	}

	// 入力情報確保
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();

	CInputJoypad* pJoy = CManager::GetInstance()->GetPad();

	// カメラの方向情報
	D3DXVECTOR3 CameraRot = m_CameraRot;

	// スラスター倍率変数
	float fThruster = 1.f;

	// スラスター倍率変数
	float fHeat = 0.05f;

	// 重力 (強化して重さを感じさせる)
	float fGrav = m_fGav * 1.2f;  // 元の重力に1.2倍の重みを追加

	// 移動中か確認
	bool bMove = false;

	// スラスター使用確認
	bool bUseThruster = false;

	// 現在のギアモードの判別
	bool bGearMode = m_GearSpeed->GetFlagGear();

	// 速度倍率
	float fSpeedSplit;

	// 摩擦係数（慣性を増やして重厚な減速に）
	float fFriction = 0.925f; // 摩擦による速度減衰を少なくして、慣性が長く続くように

	// 最大速度の設定
	float fMaxSpeed; // 最大移動速度の上限を少し下げて重さを強調

	// カメラ角度情報
	float fCameraSpeed = CManager::GetInstance()->GetCamera()->GetRot().y + D3DX_PI;

	// フェード位置取得
	D3DXVECTOR2 pFpos = CManager::GetInstance()->GetFade()->GetFadePos();

	// パンチ中やフェード処理中は移動できない
	if (pFpos.y > 0.f - SCREEN_HEIGHT * 0.25f || m_bAtkPanchi || m_bStepMode|| m_bOverheat){
		m_vVelocity.x = 0.f;
		m_vVelocity.z = 0.f;
		SetMove({0.f,fGrav,0.f});
		return false;
	}

	// ギアモードによるスピード調整
	if (bGearMode) {
		fSpeedSplit = 6.f;  // 少し遅くして重みを強調
		fMaxSpeed = 7.f;
		if (m_bAtk){
			fMaxSpeed = 2.f;
		}
	}

	else {
		fSpeedSplit = 6.f;
		fMaxSpeed = 12.f;
	}

	// 入力に基づく移動方向
	D3DXVECTOR3 vecDirection(0.0f, 0.0f, 0.0f);

	if (pKeyboard->GetPress(DIK_W) || pJoy->GetPress(CInputJoypad::JOYKEY_UP) == true) { // 上
		vecDirection.z = 0.5f;
		bMove = true;
	}
	if (pKeyboard->GetPress(DIK_S) || pJoy->GetPress(CInputJoypad::JOYKEY_DOWN) == true) { // 下
		vecDirection.z = -0.5f;
		bMove = true;
	}
	if (pKeyboard->GetPress(DIK_A) || pJoy->GetPress(CInputJoypad::JOYKEY_LEFT) == true) { // 左
		vecDirection.x = 0.5f;
		bMove = true;
	}
	if (pKeyboard->GetPress(DIK_D) || pJoy->GetPress(CInputJoypad::JOYKEY_RIGHT) == true) { // 右
		vecDirection.x = -0.5f;
		bMove = true;
	}

	// 徐々に向く回転速度の設定
	float rotationSpeed = 0.25f; // 回転速度を調整（0.1 = ゆっくり回転, 1.0 = 即座に回転）

	// 移動方向がある場合、向きを徐々に更新する
	if (bMove) {
		// 移動方向の角度を取得
		float targetDirection = atan2f(-vecDirection.x, vecDirection.z) + fCameraSpeed;

		// 目標方向と現在の方向の差を計算
		float delta = targetDirection - rot.y - D3DX_PI;

		// -π～πの範囲に収めるため、差分を正規化
		if (delta > D3DX_PI) {
			delta -= D3DX_PI * 2;
		}
		else if (delta < -D3DX_PI) {
			delta += D3DX_PI * 2;
		}

		// 角度を線形補間
		rot.y += rotationSpeed * delta;

		// 角度を -π ～ π の範囲に正規化する
		if (rot.y > D3DX_PI) {
			rot.y -= D3DX_PI * 2.0f;
		}
		else if (rot.y < -D3DX_PI) {
			rot.y += D3DX_PI * 2.0f;
		}
	}

	// スラスター機動装置
	if (pKeyboard->GetPress(DIK_P) || (pJoy->GetLTrigger().y >= 0.3f && bMove && !m_bAtk)) {
		bUseThruster = true;
		fThruster = 2.f;
		fGrav = 0.f;  // スラスター使用中は重力を無効化
	}

	// スラスター上昇処理
	if (pKeyboard->GetPress(DIK_M) && !m_bAtk || (pJoy->GetLTrigger().y >= 0.7f && 
		vecDirection.x == 0.f && vecDirection.z == 0.f)) {
		bUseThruster = true;
		fGrav = 5.f; // 重力無効
	}

	// 攻撃やステップ中の移動制限
	if (m_bStepMode) {
		vecDirection.x = 0.f;
		vecDirection.z = 0.f;
	}

	// スラスター未使用時のヒート減少
	if (!bUseThruster && m_fHeatSum > 0.f) {
		//スラスター冷却処理
		CoolThruster(fHeat);
	}

	// スラスター使用時のヒート増加
	else if (bUseThruster){
		//ヒートゲージ増加処理
		HeatThruster(fHeat);
		// ギアモードによるスピード調整
		if (bGearMode) {
			fMaxSpeed = 10.f;
		}
		else {
			fMaxSpeed = 17.f;
		}
		CBack_Effect::Create(pos, rot);
	}

	// 慣性による速度処理
	if (bMove) {
		// 方向を三平方に変換
		float rotMoveY = atan2f(-vecDirection.x, vecDirection.z);  // x方向を逆転させる
		float sin = sinf(rotMoveY + fCameraSpeed);
		float cos = cosf(rotMoveY + fCameraSpeed);

		// 加速処理（加速速度を少し低く）
		m_vVelocity.x += sin * fSpeedSplit * fThruster * 0.05f;  // 加速係数を低くして重厚感を追加
		m_vVelocity.z += cos * fSpeedSplit * fThruster * 0.05f;
	}

	//停止距離減衰処理
	else {
		// 入力がない場合は摩擦による減速処理
		m_vVelocity.x *= fFriction;
		m_vVelocity.z *= fFriction;
	}

	// 現在の速度の大きさを計算
	float speed = sqrtf(m_vVelocity.x * m_vVelocity.x + m_vVelocity.z * m_vVelocity.z);

	// 速度が最大速度を超えていたら制限する
	if (speed > fMaxSpeed) {
		float scale = fMaxSpeed / speed;
		m_vVelocity.x *= scale;
		m_vVelocity.z *= scale;
	}

	// プレイヤーが完全に停止した場合の処理
	if (fabs(m_vVelocity.x) < 0.2f && fabs(m_vVelocity.z) < 0.2f) {
		m_vVelocity.x = 0.0f;
		m_vVelocity.z = 0.0f;
		SetMove({ 0.f, fGrav, 0.f });
		return false;
	}

	// 慣性を加味した移動処理
	D3DXVECTOR3 MoveValue = { m_vVelocity.x, fGrav, m_vVelocity.z };

	//　移動値代入
	SetMove(MoveValue);

	return bMove;
}

//================================================================================================================================================================
//パワーチャージ処理
//================================================================================================================================================================
void CPlayer3D::Charge(D3DXVECTOR3 &rot)
{
	int nAtk = 0;
	float fHeat = 0.025f;
	float fChargeTime = 1.5f;
	//現在のギアモードの判別

	if (m_fChargeSum <= 100.1f){

		//5段階
		if (m_fChargeSum >= (float)80){

			m_fChargeSum += 0.1f * fChargeTime;
			nAtk = 20;
			m_ChargeGage->SetCollar(255, 255, 0,255);
			m_PowerRank = FIVE;
		}

		//４段階
		else if (m_fChargeSum >= (float)60){
			m_fChargeSum += 0.15f * fChargeTime;
			nAtk = 13;
			m_ChargeGage->SetCollar(255, 0, 255,255);
			m_PowerRank = FORTH;
		}

		//3段階
		else if (m_fChargeSum >= (float)40){
			m_fChargeSum += 0.2f * fChargeTime;
			nAtk = 8;
			m_ChargeGage->SetCollar(0, 0, 255,255);
			m_PowerRank = THIRD;
		}

		//2段階
		else if (m_fChargeSum >= (float)20){
			m_fChargeSum += 0.25f * fChargeTime;
			nAtk = 4;
			m_ChargeGage->SetCollar(0,255, 0,255);
			m_PowerRank = SECOND;
		}

		//初期段階
		else if (m_fChargeSum >= (float)0){
			m_fChargeSum += 0.3f * fChargeTime;
			nAtk = 1;
			m_ChargeGage->SetCollar(255, 0, 0,255);
			m_PowerRank = FIRST;
		}
	}

	//フルチャージ
	else{
		nAtk = 35;
		m_ChargeGage->SetCollar(0, 255, 255, 255);
		m_PowerRank = FULLPOWER;
	}

	rot.y = CManager::GetInstance()->GetCamera()->GetRot().y;

	m_bAtk    = true;
	m_nAtkSum = nAtk;
}

//================================================================================================================================================================
// 攻撃処理
//================================================================================================================================================================
void CPlayer3D::ChargeAtk(D3DXVECTOR3 pos, D3DXVECTOR3 &rot)
{
	CBack_Effect::Create(pos, rot);

	// 現在のギアモードの判別
	bool bGearMode = m_GearSpeed->GetFlagGear();

	// 速度倍率
	float fSpeedSplit = 16.f;

	// 攻撃判定ヒット時
	bool bAtk = false;

	//タイムオーバー
	bool bEnd = false;
	
	// カメラ角度情報
	float fCameraRotY = CManager::GetInstance()->GetCamera()->GetRot().y + D3DX_PI;

	// 攻撃力保存変数
	int nAtkValue = m_nAtkSum;

	int nMaxAtkTime;

	if (m_PowerRank == FULLPOWER)
	{
		nMaxAtkTime = 120;
	}

	else if (m_PowerRank == FIVE)
	{
		nMaxAtkTime = 100;
	}

	else if (m_PowerRank == FORTH)
	{
		nMaxAtkTime = 80;
	}

	else if (m_PowerRank == THIRD)
	{
		nMaxAtkTime = 80;
	}

	else if (m_PowerRank == SECOND)
	{
		nMaxAtkTime = 40;
	}

	else {
		nMaxAtkTime = 20;
	}

	// アタック継続時間
	m_nAtkTime++;
	
	CManager::GetInstance()->GetCamera()->SetCameraCloseDistance(550.f);

	//タイムオーバー
	if (m_nAtkTime > nMaxAtkTime) {
		bEnd = true;
	}

	//ヒット判定の位置
	D3DXVECTOR3 HitPos = { pos.x, pos.y + m_PlayerParts[0]->GetPos().y, pos.z };

	CObject* pObject = CObject::GetTop(); // リストの先頭オブジェクトから開始

	while (pObject != nullptr)
	{
		CObject::TYPE type = pObject->GetType();

		// ボスタイプのチェック
		if (type == CObject::TYPE::BOSS)
		{
			// 安全にダウンキャスト
			CEnemy_Boss* pBoss = dynamic_cast<CEnemy_Boss*>(pObject);

			// ダウンキャストに成功した場合
			if (pBoss)
			{
				if (pBoss->GetState()!=DAMAGE)
				{
					//CModelParts BossParts = pBoss->GetBossParts();

					// 当たっているか判断
					if (CManager::GetInstance()->GetCollision()->HitCircleCollision(HitPos, *pBoss->GetPos(),
						m_PlayerParts[0]->GetPartsRadhiusu(), /*BossParts.GetPartsRadhiusu())*/{50.f,50.f,50.f})) {
						// 攻撃反転ON
						bAtk = true;
					}

					// アタックモード解除
					if (bAtk) {

						if (bAtk) {
							// 敵にダメージを与える
							pBoss->Damage(nAtkValue);
							pBoss->SetState(STATEMODE::DAMAGE);
							bEnd = true;
						}
					}

					// プレイヤーの移動処理
					if (!m_bFlowEnemMode) {
						// カメラの向きを考慮して移動
						float moveSpeedX = fSpeedSplit * sinf(fCameraRotY);
						float moveSpeedZ = fSpeedSplit * cosf(fCameraRotY);
						SetMove({ moveSpeedX, 0.f, moveSpeedZ });
						rot.y = fCameraRotY + D3DX_PI;
					}

					else {
						// 敵との距離の差分計算
						float dx = pBoss->GetPos()->x - pos.x; // x座標の差
						float dz = pBoss->GetPos()->z - pos.z; // z座標の差
						float dy = pBoss->GetPos()->y - pos.y; // y座標の差

						// 距離の平方根を使って正規化
						float distance = sqrtf(dx * dx + dz * dz + dy * dy);

						// 方向の角度を計算（xy平面での角度）
						float fAngle = atan2f(dz, dx);

						// 移動量の計算
						float mx = cosf(fAngle) * fSpeedSplit;    // x方向
						float my = (dy / distance) * fSpeedSplit; // y方向の移動
						float mz = sinf(fAngle) * fSpeedSplit;    // z方向

						// 移動値を設定
						SetMove({ mx, my, mz });


						// 進める距離を計算: nMaxAtkTimeに応じた移動距離
						float moveDistance = fSpeedSplit * nMaxAtkTime;  // nMaxAtkTimeの間に進む距離

						// 方向ベクトルを計算
						D3DXVECTOR3 direction = { pBoss->GetPos()->x - pos.x,pBoss->GetPos()->y - pos.y,pBoss->GetPos()->z - pos.z, };

						float dist = D3DXVec3Length(&direction);

						// 進むべき距離が目的地に向けて進める距離より大きい場合
						if (dist > moveDistance) {
							m_TargerPnt->SetCollar(255, 0, 0, 255);
						}

						else {
							m_TargerPnt->SetCollar(0, 255, 0, 255);
						}
					}
					break; // 一つのボスに当たったらループを抜ける
				}
			}
				
		}
		// 次のオブジェクトに移動
		pObject = pObject->GetNext();
	}

	if (bEnd)
	{
		// 攻撃に関する変数のリセット
		m_fChargeSum = NULL; //チャージ段階
		m_bAtk = false;		 //チャージ状態
		m_bAtkPanchi = false;//パンチ状態
		m_nAtkTime = NULL;	 //合計移動距離
		m_nAtkSum = NULL;	 //合計攻撃値
		CManager::GetInstance()->GetCamera()->SetCameraCloseDistance(400.f);
	}

	else {
		rot.y = CManager::GetInstance()->GetCamera()->GetRot().y;
	}
}

//================================================================================================================================================================
// 攻撃処理
//================================================================================================================================================================
void CPlayer3D::DistanceSum(D3DXVECTOR3 pos, D3DXVECTOR3& rot)
{
	// 現在のギアモードの判別
	bool bGearMode = m_GearSpeed->GetFlagGear();

	// 速度倍率
	float fSpeedSplit = bGearMode ? 8.f : 16.f;

	// カメラ角度情報
	float fCameraRotY = CManager::GetInstance()->GetCamera()->GetRot().y + D3DX_PI;

	// 攻撃力保存変数
	int nAtkValue = m_nAtkSum;

	// 最大攻撃継続時間変数
	int nMaxAtkTime;

	if (m_PowerRank == FULLPOWER){
		nMaxAtkTime = 120;
	}

	else if (m_PowerRank == FIVE){
		nMaxAtkTime = 100;
	}

	else if (m_PowerRank == FORTH){
		nMaxAtkTime = 80;
	}

	else if (m_PowerRank == THIRD){
		nMaxAtkTime = 80;
	}

	else if (m_PowerRank == SECOND){
		nMaxAtkTime = 40;
	}

	else {
		nMaxAtkTime = 20;
	}

	//ヒット判定の位置
	D3DXVECTOR3 HitPos = { pos.x, pos.y + m_PlayerParts[0]->GetPos().y, pos.z };

	CObject* pObject = CObject::GetTop(); // リストの先頭オブジェクトから開始

	while (pObject != nullptr){

		CObject::TYPE type = pObject->GetType();

		// ボスタイプのチェック
		if (type == CObject::TYPE::BOSS)
		{
			// 安全にダウンキャスト
			CEnemy_Boss* pBoss = dynamic_cast<CEnemy_Boss*>(pObject);

			// ダウンキャストに成功した場合
			if (pBoss)
			{
				// 敵との距離の差分計算
				float dx = pBoss->GetPos()->x - pos.x; // x座標の差
				float dz = pBoss->GetPos()->z - pos.z; // z座標の差
				float dy = pBoss->GetPos()->y - pos.y; // y座標の差

				// 距離の平方根を使って正規化
				float distance = sqrtf(dx * dx + dz * dz + dy * dy);

				// 方向の角度を計算（xy平面での角度）
				float fAngle = atan2f(dz, dx);

				// 移動量の計算
				float mx = cosf(fAngle) * fSpeedSplit;    // x方向
				float my = (dy / distance) * fSpeedSplit; // y方向の移動
				float mz = sinf(fAngle) * fSpeedSplit;    // z方向

				// 進める距離を計算: nMaxAtkTimeに応じた移動距離
				float moveDistance = fSpeedSplit * nMaxAtkTime;  // nMaxAtkTimeの間に進む距離

				// 方向ベクトルを計算
				D3DXVECTOR3 direction = { pBoss->GetPos()->x - pos.x,pBoss->GetPos()->y - pos.y,pBoss->GetPos()->z - pos.z, };

				float dist = D3DXVec3Length(&direction);

				// 進むべき距離が目的地に向けて進める距離より大きい場合
				if (dist > moveDistance) {
					m_TargerPnt->SetCollar(0, 255, 0, 255);
				}
				else {
					m_TargerPnt->SetCollar(255, 0, 0, 255);
				}
				break; // 一つのボスに当たったらループを抜ける
			}
		}
		// 次のオブジェクトに移動
		pObject = pObject->GetNext();
	}
}

//================================================================================================================================================================
// 敵Search処理
//================================================================================================================================================================
void CPlayer3D::SearchRot(D3DXVECTOR3& rot, D3DXVECTOR3 pos)
{
	CObject* pObject = CObject::GetTop(); // リストの先頭オブジェクトから開始

	while (pObject != nullptr)
	{
		// nullptrチェックは不要。whileループで pObject != nullptr が保証される

		// オブジェクトの種類取得
		CObject::TYPE type = pObject->GetType();

			if (type == CObject::TYPE::BOSS)
			{
				// 安全にダウンキャスト
				CEnemy_Boss* pBoss = dynamic_cast<CEnemy_Boss*>(pObject);

				// ダウンキャストに成功した場合
				if (pBoss)
				{
					float x = pBoss->GetPos()->x - pos.x; //敵との距離の差分計算（横）
					float z = pBoss->GetPos()->z - pos.z; //敵との距離の差分計算（縦）

					float fAngle = atan2f(x, z);

					m_CameraRot.y = fAngle + D3DX_PI;

					//位置設定
					CManager::GetInstance()->GetCamera()->SetRot(m_CameraRot);

					D3DXVECTOR3 LocalPos = {pos.x,pos.y+ m_PlayerParts[0]->GetPos().y,pos.z};

					//敵を常に追跡し、プレイヤーの後ろを追う
					CManager::GetInstance()->GetCamera()->FollowCameraTargetEnem(LocalPos, *pBoss->GetPos(), m_CameraRot);
				}
			}
		// 次のオブジェクトに移動
		pObject = pObject->GetNext();
	}

	//ターゲットポインター表記
	if (!m_TargerPnt->GetDraw())
	{
		m_TargerPnt->SetDraw(true);
	}
}

//================================================================================================================================================================
// 向き処理
//================================================================================================================================================================
void CPlayer3D::Rotation() {
	// 入力情報確保
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	CInputJoypad* pJoy = CManager::GetInstance()->GetPad();

	// 倒し具合の参照値
	float fStickSum = 100.f;
	// 向き情報変数
	float fRot = 0.0f;
	float fRotx = 0.0f;

	// カメラ感度
	const float fRotSpeed = 0.025f;
	const float fRotSpeedx = 0.75f;
	const float fRotFirstSp = 2.5f;

	const float min = -90.0f; // 上下回転の制限
	const float max = 90.0f;

	// 上下左右の入力によるカメラ回転
	if (pKeyboard->GetPress(DIK_I) || pJoy->GetRInputState().x <= -fStickSum) { // 上
		fRot -= fRotSpeed * fRotFirstSp;
	}
	if (pKeyboard->GetPress(DIK_O) || pJoy->GetRInputState().x >= fStickSum) { // 下
		fRot += fRotSpeed * fRotFirstSp;
	}
	if (pKeyboard->GetPress(DIK_UP) || pJoy->GetRInputState().y >= fStickSum) { // 上
		if (m_CameraRot.x <= max) {
			fRotx += fRotSpeedx * fRotFirstSp;
		}
	}
	if (pKeyboard->GetPress(DIK_DOWN) || pJoy->GetRInputState().y <= -fStickSum) { // 下
		if (m_CameraRot.x >= min) {
			fRotx -= fRotSpeedx * fRotFirstSp;
		}
	}

	// 回転値の適用
	m_CameraRot.y += fRot; // 水平回転
	m_CameraRot.x += fRotx; // 垂直回転

	// y軸の回転が -π ～ +π の範囲に収まるように補正
	if (m_CameraRot.y > D3DX_PI) {
		m_CameraRot.y -= D3DX_PI * 2; // +π を超えた場合、-π へ補正
	}
	if (m_CameraRot.y < -D3DX_PI) {
		m_CameraRot.y += D3DX_PI * 2; // -π を下回った場合、+π へ補正
	}

	// カメラの回転をセット
	CManager::GetInstance()->GetCamera()->SetRot(D3DXVECTOR3(m_CameraRot.x, m_CameraRot.y, m_CameraRot.z));
}

//================================================================================================================================================================
//ステップ回避処理
//================================================================================================================================================================
void CPlayer3D::Step(D3DXVECTOR3 rot) {

	//入力情報確保
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();
	//カメラの方向情報
	D3DXVECTOR3 CameraRot = m_CameraRot;

	CInputJoypad* pJoy = CManager::GetInstance()->GetPad();

	//スラスター倍率変数
	const float fHeat = 0.85f;
	//重力
	const float fGrav = m_fGav;
	//ステップ係数
	const float fStepSum = 17.f;
	//ステップ力
	const float fStepMoveVec = 150.0f;

	m_nStepCnt++;

	//ステップ状態管理
	if (m_nStepCnt >= 60)
	{
		m_bStepMode = false;
		m_bStepVec = false;
		m_Step = { 0.f,0.f, 0.f };
		m_nStepCnt = NULL;
		return;
	}

	//ステップ中
	if (m_nStepCnt <= 20)
	{
		HeatThruster(fHeat);

		SetMotion(STEP);

		//移動距離を三平方で求めましょう
		if (!m_bStepVec)
		{
			if (pKeyboard->GetPress(DIK_W) || pJoy->GetPress(CInputJoypad::JOYKEY_UP))
			{ //上
				m_Step.z += fStepMoveVec;
				m_bStepVec = true;
			}

			if (pKeyboard->GetPress(DIK_S) || pJoy->GetPress(CInputJoypad::JOYKEY_DOWN))
			{ //下
				m_Step.z -= fStepMoveVec;
				m_bStepVec = true;

			}

			if (pKeyboard->GetPress(DIK_A) || pJoy->GetPress(CInputJoypad::JOYKEY_LEFT))
			{ //左
				m_Step.x -= fStepMoveVec;
				m_bStepVec = true;

			}

			if (pKeyboard->GetPress(DIK_D) || pJoy->GetPress(CInputJoypad::JOYKEY_RIGHT))
			{ //右
				m_Step.x += fStepMoveVec;
				m_bStepVec = true;
			}

			//入力なし
			if (!m_bStepVec)
			{
				m_Step.z -= fStepMoveVec;
				m_bStepVec = true;
			}
		}

		//方向を三平方に変換
		float rotMoveY = atan2f(m_Step.x, m_Step.z);

		//移動値代入
		if (m_bFlowEnemMode){
			//追従モード
			SetMove(D3DXVECTOR3(sinf(rotMoveY + CManager::GetInstance()->GetCamera()->GetRot().y + D3DX_PI) * fStepSum,
				fGrav,
				cosf(rotMoveY + CManager::GetInstance()->GetCamera()->GetRot().y + D3DX_PI) * fStepSum));
		}

		else{
			//視野拡張モード
			SetMove(D3DXVECTOR3(sinf(rotMoveY + CManager::GetInstance()->GetCamera()->GetRot().y + D3DX_PI) * fStepSum,
				fGrav,
				cosf(rotMoveY + CManager::GetInstance()->GetCamera()->GetRot().y + D3DX_PI) * fStepSum));
		}
	}

	else{
		SetMotion(NONE);
	}
}

//================================================================================================================================================================
//モデル読み込み処理
//================================================================================================================================================================
void CPlayer3D::LoadParts()
{
	const int nMaxData = 2048;
	char Datacheck[nMaxData];	// データ検索
	char cModelPath[nMaxData];	// データ検索
	int nCnt = 0;				//使用中のデータ数
	int PlayerModelNumSeve = 0;			//読み取ったモデル数を保存する
	int Id = NULL;
	int nPair = NULL;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;

	// ファイルの読み込み
	FILE* pFile = fopen("data\\MODEL\\player\\file.txt", "r");

	//ファイルが存在しない時追放します
	if (pFile == NULL)
	{
		return;
	}

	// ENDが見つかるまで読み込みます
	while (1)
	{
		fscanf(pFile, "%s", Datacheck);	// ここで索敵する

		if (!strcmp(Datacheck, "END_SCRIPT"))
		{// 全てを読み込んだのでロードを終了
			fclose(pFile);
			break;
		}

		if (Datacheck[0] == '#')
		{// 戻ります
			continue;
		}

		//パーツ数を設定
		if (!strcmp(Datacheck, "NUM_PARTS"))
		{
			fscanf(pFile, "%s", Datacheck);
			fscanf(pFile, "%d", &PlayerModelNumSeve);
		}

		//モデルの名前を検索
		if (!strcmp(Datacheck, "MODEL_FILENAME"))
		{
			fscanf(pFile, "%s", Datacheck);
			fscanf(pFile, "%s", cModelPath);
			m_FileModel[PlayerModelNumSeve] = cModelPath;
			m_PlayerParts[PlayerModelNumSeve] = CModelParts::Create({0.f,0.f,0.f}, m_FileModel[PlayerModelNumSeve]);
			PlayerModelNumSeve++;
		}

		//各パーツの設定
		if (!strcmp(Datacheck, "PARTSSET"))
		{
			// 項目ごとにデータを代入
			while (1)
			{
				fscanf(pFile, "%s", Datacheck); //	索敵

				if (!strcmp(Datacheck, "END_PARTSSET"))
				{
					// 読み込みを終了
					break;
				}

				//親子を設定
				else if (!strcmp(Datacheck, "INDEX"))
				{
					fscanf(pFile, "%s", Datacheck);
					fscanf(pFile, "%d", &Id);
				}

				//パーツの種類
				else if (!strcmp(Datacheck, "PARENT"))
				{
					fscanf(pFile, "%s", Datacheck);
					fscanf(pFile, "%d", &nPair);
				}

				//各パーツの位置
				else if (!strcmp(Datacheck, "POS"))
				{
					fscanf(pFile, "%s", Datacheck);
					fscanf(pFile, "%f", &pos.x);
					fscanf(pFile, "%f", &pos.y);
					fscanf(pFile, "%f", &pos.z);
				}

				//各パーツの角度 
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
	
			nCnt++;	// データ数加算
		}
	}
}

//================================================================================================================================================================
//モーション読み込み処理
//================================================================================================================================================================
void CPlayer3D::LoadMotion()
{
	char Datacheck[2048];	// データ検索
	int MotionCnt = 0;		//モーションカウント
	int keysetcnt = 0;		//モーションカウント
	int KeyCnt = 0;			//キーカウント

	// ファイルの読み込み
	FILE* pFile = fopen("data\\MODEL\\player\\file.txt", "r");

	//ファイルが存在しない時追放します
	if (pFile == NULL){
		return;
	}

	while (1){

		fscanf(pFile, "%s", Datacheck);	// ここで索敵する

		if (!strcmp(Datacheck, "END_SCRIPT"))
		{// 全てを読み込んだのでロードを終了
			fclose(pFile);
			break;
		}

		if (Datacheck[0] == '#')
		{// 戻ります
			continue;
		}

		//モーション状態の設定
		if (!strcmp(Datacheck, "MOTIONSET"))
		{
			while (1)
			{
				fscanf(pFile, "%s", Datacheck); //	索敵

				if (!strcmp(Datacheck, "END_MOTIONSET"))
				{
					// 読み込みを終了
					break;
				}
				//ループの判断
				else if (!strcmp(Datacheck, "LOOP"))
				{
					fscanf(pFile, "%s", Datacheck);
					fscanf(pFile, "%d", &m_Motion[MotionCnt].LoopCheck);
				}

				//全体キーの読み込み
				else  if (!strcmp(Datacheck, "NUM_KEY"))
				{
					fscanf(pFile, "%s", Datacheck);
					fscanf(pFile, "%d", &m_Motion[MotionCnt].NumKey);
				}

				//現在のキーの設定
				if (!strcmp(Datacheck, "KEYSET"))
				{
					while (1)
					{
						fscanf(pFile, "%s", Datacheck); //	索敵

						if (Datacheck[0] == '#')
						{// 戻ります
							fgets(Datacheck, 100, pFile);
							continue;
						}

						if (!strcmp(Datacheck, "END_KEYSET"))
						{
							// 読み込みを終了
							break;
						}

						//全体キーの読み込み
						else if (!strcmp(Datacheck, "FRAME"))
						{
							fscanf(pFile, "%s", Datacheck);
							fscanf(pFile, "%d", &m_Motion[MotionCnt].KeySet[keysetcnt].FrameRate);
						}

						//現在のキーの設定
						if (!strcmp(Datacheck, "KEY"))
						{
							while (1)
							{
								fscanf(pFile, "%s", Datacheck); //	索敵

								if (!strcmp(Datacheck, "END_KEY"))
								{
									// 読み込みを終了
									break;
								}

								//各パーツのモーションpos値
								else if (!strcmp(Datacheck, "POS"))
								{
									fscanf(pFile, "%s", Datacheck);
									fscanf(pFile, "%f", &m_Motion[MotionCnt].KeySet[keysetcnt].Key[KeyCnt].Motion_pos.x);
									fscanf(pFile, "%f", &m_Motion[MotionCnt].KeySet[keysetcnt].Key[KeyCnt].Motion_pos.y);
									fscanf(pFile, "%f", &m_Motion[MotionCnt].KeySet[keysetcnt].Key[KeyCnt].Motion_pos.z);
								}

								//各パーツのモーションrot値
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
//モーション動かすよ処理
//================================================================================================================================================================
void CPlayer3D::Motion()
{
	//モーション移動量の計算用関数
	D3DXVECTOR3 Mpos[NUM];
	D3DXVECTOR3 Mrot[NUM];

	int nKey = (m_nKeyCnt + 1) % m_Motion[m_MotionSet].NumKey; //次のキーとの向きの位置の差分を計算するためのint関数

	for (int i = 0; i < NUM; i++)
	{
		D3DXVECTOR3 pGetRot = m_PlayerParts[i]->GetRot();

		//求めた差分を全体フレームレートで割ることで1フレームの動作割合を適応させる
		Mrot[i] = ((m_Motion[m_MotionSet].KeySet[nKey].Key[i].Motion_rot)
			- (m_PlayerParts[i]->GetRot()))	
			/ (float)m_Motion[m_MotionSet].KeySet[m_nKeyCnt].FrameRate;

		pGetRot += Mrot[i];

		m_PlayerParts[i]->SetRot(pGetRot);
	}

	//毎フレームの加算処理をしましょう
	m_nFrameCnt++;

	//割合で出したフレームレート数をフレームレートカウントが上回った時
	if (m_nFrameCnt >= m_Motion[m_MotionSet].KeySet[m_nKeyCnt].FrameRate) 
	{
		//フレームリセット
		m_nFrameCnt = 0;

		//使用中のモーションをさらなる先へ進めます
		m_nKeyCnt = (m_nKeyCnt + 1) % m_Motion[m_MotionSet].NumKey;
	}
}

//================================================================================================================================================================
//モーション設定処理
//================================================================================================================================================================
void CPlayer3D::SetMotion(TYPE g_Motions)
{
	if (m_MotionSet != g_Motions)
	{
		m_nFrameCnt = 0;
		m_MotionSet = g_Motions;
		m_nKeyCnt = 0;
	}
}

//================================================================================================================================================================
//プレイヤー生成
//================================================================================================================================================================
CPlayer3D* CPlayer3D::Create()
{
	CPlayer3D* pCPlayer3D = new CPlayer3D();
	pCPlayer3D->Init();
	pCPlayer3D->SetType(CObject::TYPE::PLAYER);
	return pCPlayer3D;
}

//================================================================================================================================================================
//ダメージ処理
//================================================================================================================================================================
void CPlayer3D::PlayerDamage(int damage)
{
	if (GetState() != DAMAGE){

		CDamage_Eff::Create();
		CManager::GetInstance()->GetCamera()->CCamera::SetShake(30, 1.f);
		Damage(damage);
		SetState(DAMAGE);
		m_bFlowEnemMode = false;
		// 攻撃に関する変数のリセット
		m_fChargeSum = NULL; //チャージ段階
		m_bAtk = false;		 //チャージ状態
		m_bAtkPanchi = false;//パンチ状態
		m_nAtkTime = NULL;	 //合計移動距離
		m_nAtkSum = NULL;	 //合計攻撃値
	}
}