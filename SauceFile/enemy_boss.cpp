//================================================================================================================================================================
//
//ボスエネミー処理[enemy_boss.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "enemy_boss.h"
#include "effect_backpack.h"
#include "player_3d.h"
#include "manager.h"
#include "sound.h"
#include "nova_eff.h"
#include "nova.h"
#include "missile.h"
#include "atk_time_effect.h"

//================================================================================================================================================================
//コンストラクタ
//================================================================================================================================================================
CEnemy_Boss::CEnemy_Boss():CXcharacter(8)
{

}

//================================================================================================================================================================
//デストラクタ
//================================================================================================================================================================
CEnemy_Boss::~CEnemy_Boss()
{

}

//================================================================================================================================================================
//初期設定
//================================================================================================================================================================
HRESULT CEnemy_Boss::Init()
{
	const int nMaxLife = 200;

	CXcharacter::Init();
	SetPos(100.0f, 0.f,-500.0f);
	SetLife(nMaxLife);
	LoadParts();
	LoadMotion();
	m_EnemyHp_Gage = CGage_Enemy_Hp::Create();
	m_GageBack = CGage_Back::Create({SCREEN_WIDTH *0.503f+50.f,30.f}, 65.f*4.f, 15.f, true);

	//攻撃関係の時間全て
	m_nAtkCnt = NULL, m_nStayCnt = NULL, m_nMaxStayCnt = NULL;
	m_bAtk = true;
	m_MotionSet = STAY;
	m_AtkStay = TACKLE;
	m_bTutorial = false;

	return S_OK;
}

//================================================================================================================================================================
//終了処理
//================================================================================================================================================================
void CEnemy_Boss::Uninit()
{
	m_EnemyHp_Gage->Uninit();
	m_EnemyHp_Gage = nullptr;

	m_GageBack->Uninit();
	m_GageBack = nullptr;

	if (!m_bTutorial) {
		CManager::GetInstance()->GetScene()->FadeTrigger();
	}

	CXcharacter::Uninit();
}

//================================================================================================================================================================
//更新処理
//================================================================================================================================================================
void CEnemy_Boss::Update()
{
	if (GetLife() <= NULL){
		
		DelParts();

		//チュートリアルは無限生成
		if (m_bTutorial){
			Create(true);
		}

		CManager::GetInstance()->GetScene()->SetLodeResult(true);

		return;
	}

	//相手の残りライフ量をゲージ化
	m_EnemyHp_Gage->GageAnim((float)GetLife());

	D3DXVECTOR3* pPos = GetPos();
	D3DXVECTOR3* pRot = GetRot();

	//重力
	SetMove({ 0.f,-5.f,0.f });

	if (!m_bTutorial)
	{
		//攻撃までのインターバル状態
		if (!m_bAtk) {
			SetMotion(STAY);
			m_nAtkCnt = NULL;
			++m_nStayCnt;

			//ステイから攻撃モードへ
			if (m_nStayCnt >= m_nMaxStayCnt) {
				m_nStayCnt = NULL;
				m_bAtk = true;
				//攻撃体勢を知らせるSE
				CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_ATTACK_SE);

				D3DXVECTOR3 PosBody = { pPos->x,pPos->y + 100.f,pPos->z };

				//タックル
				if (m_AtkStay == TACKLE) {
					CAtk_Time_Effect::Create(300, 0.35f);
				}
				//ノヴァ
				else if (m_AtkStay == NOVA) {
					CAtk_Time_Effect::Create(420, 0.25f);
					CNova_Eff::Create(PosBody);
				}
				//ミサイル
				else if (m_AtkStay == SNIPER) {
					CAtk_Time_Effect::Create(120, 0.8f);
				}
			}
		}

		//攻撃体勢
		else {
			//前方インクリメント
			++m_nAtkCnt;
			if (m_AtkStay == TACKLE) {
				Tackle(*pPos, *pRot);
			}
			else if (m_AtkStay == NOVA) {
				Nova(*pPos, *pRot);
			}
			else if (m_AtkStay == SNIPER) {
				Sniper(*pPos);
			}
		}
	}

	Motion();

	CXcharacter::Update();
}

//================================================================================================================================================================
// 攻撃処理
//================================================================================================================================================================
void CEnemy_Boss::Tackle(D3DXVECTOR3 pos, D3DXVECTOR3& rot)
{
	SetMotion(TACKLE);

	// ボスのタックル速度
	const float fBaseSpeed = 5.f;
	const float fDamping = 0.95f; // 減衰係数
	const float fRatio = 0.5f;    // 加速度調整変数
	const int nTackleStay = 300;
	const int nEndTackleTime = 420;
	const int nTackleAttackWindow = 60;
	const int nIntervalTime = 180;

	// 攻撃位置を設定（ボスのパーツの高さを加味）
	D3DXVECTOR3 HitPos = { pos.x, pos.y + m_EnemBossParts[0]->GetPos().y, pos.z };

	// 攻撃エフェクトを作成
	CBack_Effect::Create(HitPos, rot);

	// タックル中の速度を保持する変数
	static D3DXVECTOR3 velocity = { 0.f, 0.f, 0.f }; // 慣性効果用の速度ベクトル

	// オブジェクトリストを走査
	CObject* pObject = CObject::GetTop(); // リストの先頭オブジェクトから開始

	while (pObject != nullptr)
	{
		CObject::TYPE type = pObject->GetType();

		// プレイヤータイプのオブジェクトかどうかチェック
		if (type == CObject::TYPE::PLAYER)
		{
			CPlayer3D* pPlayer = dynamic_cast<CPlayer3D*>(pObject);

			if (pPlayer)
			{
				// ボスの角度をプレイヤーへ
				if (m_nAtkCnt < nTackleStay)
				{
					float dx = pPlayer->GetPos()->x - HitPos.x;
					float dz = pPlayer->GetPos()->z - HitPos.z;
					float dy = pPlayer->GetPos()->y - HitPos.y;
					float distance = sqrtf(dx * dx + dz * dz + dy * dy);

					float fAngleY = atan2f(dx, dz);
					float fAngleX = asinf(dy / distance);

					const float fMinPitch = -30.f * (D3DX_PI / 180.f);
					const float fMaxPitch = 30.f * (D3DX_PI / 180.f);

					if (fAngleX < fMinPitch) {
						fAngleX = fMinPitch;
					}

					if (fAngleX > fMaxPitch) {
						fAngleX = fMaxPitch;
					}

					rot.y = fAngleY + D3DX_PI;
					rot.x = fAngleX;
					rot.z = 0.0f;
				}

				else if (m_nAtkCnt > nEndTackleTime){
					SetIntervalTime(nIntervalTime);
					rot = { 0.f, rot.y, 0.f };
					velocity = { 0.f, 0.f, 0.f }; // 慣性をリセット
				}

				else if (m_nAtkCnt > nTackleStay && m_nAtkCnt < nTackleStay + nTackleAttackWindow){
					CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_FIRING_SE);

					// プレイヤーに向かって加速
					float mx = sinf(rot.y + D3DX_PI) * fBaseSpeed;
					float my = sinf(rot.x) * fBaseSpeed;
					float mz = cosf(rot.y + D3DX_PI) * fBaseSpeed;

					D3DXVECTOR3 acceleration = { mx, my, mz }; // 加速ベクトル
					velocity += acceleration * fRatio;                  // 速度に加算
				
				// プレイヤーに衝突判定
				CModelParts PlayerParts = pPlayer->GetPlayerParts();
				D3DXVECTOR3 HitPlayerPos = { pPlayer->GetPos()->x,
					pPlayer->GetPos()->y + PlayerParts.GetPartsRadhiusu().y,
					pPlayer->GetPos()->z };

				//　ヒット判定
				if (CManager::GetInstance()->GetCollision()->HitCircleCollision(
					HitPos, HitPlayerPos, m_EnemBossParts[0]->GetPartsRadhiusu(), PlayerParts.GetPartsRadhiusu()*0.5f))
				{
					D3DXVECTOR3 knockbackDir = D3DXVECTOR3(pPlayer->GetPos()->x - HitPos.x,
						pPlayer->GetPos()->y - HitPos.y,
						pPlayer->GetPos()->z - HitPos.z);

					D3DXVec3Normalize(&knockbackDir, &knockbackDir);

					float knockbackSpeed = 30.f;
					D3DXVECTOR3 knockbackForce = knockbackDir * knockbackSpeed;

					pPlayer->SetMove(knockbackForce);
					pPlayer->PlayerDamage(10);

					m_nAtkCnt = NULL;
					velocity = { 0.f, 0.f, 0.f }; // 慣性をリセット

					SetIntervalTime(nIntervalTime);

					break;
				}

				}
			}
		}

		pObject = pObject->GetNext();
	}

	// 慣性を減衰させつつ移動量を設定
	velocity *= fDamping;        // 減衰を適用
	SetMove(velocity);           // 現在の速度で移動
}

//================================================================================================================================================================
//爆発攻撃
//================================================================================================================================================================
void CEnemy_Boss::Nova(D3DXVECTOR3 pos, D3DXVECTOR3 rot) {
	
	//SetMotion(NOVA);
	SetMove({ 0.f,0.f,0.f });

	//テスト演出
	if (m_nAtkCnt < 120) {
		CManager::GetInstance()->GetCamera()->SetDirectionTime(120);
		CManager::GetInstance()->GetCamera()->DirectionCamera(pos,rot,1000.f);
	}

	//ノヴァ発生
	if (m_nAtkCnt >= 420){
		pos.y = pos.y + 100;
		CNova::Create(pos,1000.f,240);
		CManager::GetInstance()->GetCamera()->SetShake(240,1.f);
		SetIntervalTime(600);
	}
}

//================================================================================================================================================================
//ミサイル銃撃攻撃
//================================================================================================================================================================
void CEnemy_Boss::Sniper(D3DXVECTOR3 pos) {

	D3DXVECTOR3 PosBody = { pos.x,pos.y + 100.f,pos.z };
	
	if (m_nAtkCnt > 120){
		CMissile::Create(PosBody, 5.f, true);
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_FIRING_SE);
		CMissile::Create(PosBody, 8.f, false);
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_FIRING_SE);
		SetIntervalTime(360);
	}
}

//================================================================================================================================================================
//描画処理（全オブジェクト）
//================================================================================================================================================================
void CEnemy_Boss::Draw()
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
		m_EnemBossParts[i]->Draw();
	}
}

//================================================================================================================================================================
//ボスの次の行動を決める
//================================================================================================================================================================
void CEnemy_Boss::ShiftAtkState() {

	bool bEscapLoop = false;

	while(1)
	{
		//次の行動を選別
		int randomAttack = (rand() % MAX) + 1;

		//結果が今回の行動と異なる
		if (randomAttack != m_AtkStay){

			if (randomAttack == TACKLE){
				m_AtkStay = TACKLE;
				bEscapLoop = true;
			}

			else if (randomAttack == NOVA){
				m_AtkStay = NOVA;
				bEscapLoop = true;
			}

			else if (randomAttack == SNIPER){
				m_AtkStay = SNIPER;
				bEscapLoop = true;
			}
		}

		if (bEscapLoop){
			break;
		}
	}
}

//================================================================================================================================================================
//パーツ情報削除
//================================================================================================================================================================
void CEnemy_Boss::DelParts() {

	for (int i = 0; i < NUM; i++) {

		if (m_EnemBossParts[i] != nullptr) {
			m_EnemBossParts[i]->Uninit();
			delete m_EnemBossParts[i];
			m_EnemBossParts[i] = nullptr;
		}
	}
}

//================================================================================================================================================================
//モデル読み込み処理
//================================================================================================================================================================
void CEnemy_Boss::LoadParts(){

	char Datacheck[2048];	            // データ検索
	char cModelPath[2048];	            // データ検索
	int nCnt = 0;				        // 使用中のデータ数
	int PlayerModelNumSeve = 0;			// 読み取ったモデル数を保存する
	int Id = NULL;
	int nPair = NULL;
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;

	// ファイルの読み込み
	FILE* pFile = fopen("data\\MODEL\\enemy\\enemydata.txt", "r");

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
			m_EnemBossParts[PlayerModelNumSeve] = CModelParts::Create({ 0.f,0.f,0.f }, m_FileModel[PlayerModelNumSeve]);
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

			m_EnemBossParts[nCnt]->SetPos(pos);
			m_EnemBossParts[nCnt]->SetRot(rot);

			m_EnemBossParts[nCnt]->SetDeffalt();
			m_EnemBossParts[nCnt]->SetId(Id);
			m_EnemBossParts[nCnt]->ModelSizeSum();

			if (nPair != -1)
			{
				m_EnemBossParts[nCnt]->SetParent(m_EnemBossParts[nPair]);
			}

			nCnt++;	// データ数加算
		}
	}
}

//================================================================================================================================================================
//モーション読み込み処理
//================================================================================================================================================================
void CEnemy_Boss::LoadMotion()
{
	char Datacheck[2048];	// データ検索
	int MotionCnt = 0;		//モーションカウント
	int keysetcnt = 0;		//モーションカウント
	int KeyCnt = 0;			//キーカウント

	// ファイルの読み込み
	FILE* pFile = fopen("data\\MODEL\\enemy\\enemydata.txt", "r");

	//ファイルが存在しない時追放します
	if (pFile == NULL)
	{
		return;
	}

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
void CEnemy_Boss::Motion()
{
	//モーション移動量の計算用関数
	D3DXVECTOR3 Mpos[NUM];
	D3DXVECTOR3 Mrot[NUM];

	int nKey = (m_nKeyCnt + 1) % m_Motion[m_MotionSet].NumKey; //次のキーとの向きの位置の差分を計算するためのint関数

	for (int i = 0; i < NUM; i++)
	{
		D3DXVECTOR3 pGetRot = m_EnemBossParts[i]->GetRot();

		//求めた差分を全体フレームレートで割ることで1フレームの動作割合を適応させる
		Mrot[i] = ((m_Motion[m_MotionSet].KeySet[nKey].Key[i].Motion_rot)
			- (m_EnemBossParts[i]->GetRot()))
			/ (float)m_Motion[m_MotionSet].KeySet[m_nKeyCnt].FrameRate;

		pGetRot += Mrot[i];

		m_EnemBossParts[i]->SetRot(pGetRot);
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
void CEnemy_Boss::SetMotion(STATE g_Motions)
{
	if (m_MotionSet != g_Motions){
		m_nFrameCnt = 0;
		m_MotionSet = g_Motions;
		m_nKeyCnt = 0;
	}
}

//================================================================================================================================================================
//プレイヤー生成
//================================================================================================================================================================
CEnemy_Boss* CEnemy_Boss::Create(bool t){

	CEnemy_Boss* pCEnemy_Boss = new CEnemy_Boss();
	pCEnemy_Boss->Init();
	pCEnemy_Boss->SetType(CObject::TYPE::BOSS);
	pCEnemy_Boss->m_bTutorial = t;
	return pCEnemy_Boss;
}