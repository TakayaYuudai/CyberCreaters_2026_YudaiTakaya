//================================================================================================================================================================
//
//3D弾処理[bullet3D.cpp]
//Author : Yuudai Takaya
//
//================================================================================================================================================================

//================================================================================================================================================================
//ライブラリリンク
//================================================================================================================================================================
#include "targetpointer.h"
#include "enemy_boss.h"
#include "manager.h"

//================================================================================================================================================================
//マクロ定義
//================================================================================================================================================================
#define	BLOCK_WIDE   (50.0f) //3D弾の横半径
#define	BLOCK_HEIGHT (50.0f) //3D弾の縦半径

//================================================================================================================================================================
//グローバル変数
//================================================================================================================================================================

//================================================================================================================================================================
//コンストラクタ
//================================================================================================================================================================
CTarget_Pointer::CTarget_Pointer() :CBillboard(5)
{

}

//================================================================================================================================================================
//デストラクタ
//================================================================================================================================================================
CTarget_Pointer::~CTarget_Pointer()
{

}

//================================================================================================================================================================
//初期設定
//================================================================================================================================================================
HRESULT CTarget_Pointer::Init()
{
    CBillboard::Init();

    SetSize(BLOCK_WIDE, BLOCK_WIDE);

    SetCollar(0, 255, 0, 255);

    SetDraw(false);

    SetTexture("data\\TEXTURE\\targetPointer.png");

    return S_OK;
}

//================================================================================================================================================================
//終了処理
//================================================================================================================================================================
void CTarget_Pointer::Uninit()
{
    CBillboard::Uninit();
}

//================================================================================================================================================================
//更新処理（全オブジェクト）
//================================================================================================================================================================
void CTarget_Pointer::Update()
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
				float x = pBoss->GetPos()->x;
				float z = pBoss->GetPos()->z;
				float y = pBoss->GetPos()->y + 150.f;

				SetPos(x,y,z);
			}
		}
		// 次のオブジェクトに移動
		pObject = pObject->GetNext();
	}
    CBillboard::Update();
}

//================================================================================================================================================================
//描画処理（全オブジェクト）
//================================================================================================================================================================
void CTarget_Pointer::Draw()
{
	//レンダラー情報取得
	LPDIRECT3DDEVICE9 DEVICE = CManager::GetInstance()->GetRenderer()->GetDevice();

	// DEVICE を使って深度テストを設定する
	DEVICE->SetRenderState(D3DRS_ZENABLE, FALSE);

	//描画
	CBillboard::Draw();

	// DEVICE　による深度テストを元に戻す
	DEVICE->SetRenderState(D3DRS_ZENABLE, TRUE);
}

//================================================================================================================================================================
// 3D弾生成
//================================================================================================================================================================
CTarget_Pointer* CTarget_Pointer::Create()
{
    // エフェクトの新規生成
    CTarget_Pointer* pCTarget_Pointer = new CTarget_Pointer();

    // 初期化
    pCTarget_Pointer->Init();

    // エフェクトの基準位置を設定（プレイヤーの位置を基準）
    //pCTarget_Pointer->SetPos(pos.x, pos.y, pos.z);

    return pCTarget_Pointer;
}