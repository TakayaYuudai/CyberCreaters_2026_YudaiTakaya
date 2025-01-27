//================================================================================================================================================================
//
//プレイヤー処理[player3D.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "title_player.h"
#include "title_guide.h"
#include "effect_backpack.h"
#include "manager.h"

//================================================================================================================================================================
//コンストラクタ
//================================================================================================================================================================
CPlayer_Title::CPlayer_Title() :CXcharacter(3)
{

}

//================================================================================================================================================================
//デストラクタ
//================================================================================================================================================================
CPlayer_Title::~CPlayer_Title()
{

}

//================================================================================================================================================================
//初期設定
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
//終了処理
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
//更新処理
//================================================================================================================================================================
void CPlayer_Title::Update()
{
	//位置取得
	D3DXVECTOR3* pPos = CObjectX::GetPos();
	D3DXVECTOR3* pRot = CObjectX::GetRot();

	// スタートかどうか
	bool bStart = CTitle_Guide::GetStart();

	// 出撃演出可能確認
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

	//プレイヤーの後ろを常に追う
	CManager::GetInstance()->GetCamera()->FollowCameraTargetPlayer(m_CameraPos, m_CameraRot);

	SetMotion(NONE);

	//モーション
	Motion();

	CXcharacter::Update();
}

//================================================================================================================================================================
//描画処理（全オブジェクト）
//================================================================================================================================================================
void CPlayer_Title::Draw()
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

	for (int i = 0; i < NUM; i++) {
		m_PlayerParts[i]->Draw();
	}
}

//================================================================================================================================================================
//モデル読み込み処理
//================================================================================================================================================================
void CPlayer_Title::LoadParts()
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
			m_PlayerParts[PlayerModelNumSeve] = CModelParts::Create({ 0.f,0.f,0.f }, m_FileModel[PlayerModelNumSeve]);
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
void CPlayer_Title::LoadMotion()
{
	char Datacheck[2048];	// データ検索
	int MotionCnt = 0;		//モーションカウント
	int keysetcnt = 0;		//モーションカウント
	int KeyCnt = 0;			//キーカウント

	// ファイルの読み込み
	FILE* pFile = fopen("data\\MODEL\\player\\file.txt", "r");

	//ファイルが存在しない時追放します
	if (pFile == NULL) {
		return;
	}

	while (1) {

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
void CPlayer_Title::Motion()
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
//プレイヤー生成
//================================================================================================================================================================
CPlayer_Title* CPlayer_Title::Create()
{
	CPlayer_Title* pCPlayer_Title = new CPlayer_Title();
	pCPlayer_Title->Init();
	pCPlayer_Title->SetType(CObject::TYPE::PLAYER);
	return pCPlayer_Title;
}