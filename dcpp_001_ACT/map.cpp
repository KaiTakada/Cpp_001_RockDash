//===============================================
//
// マップ(map.cpp)
// Author:Kai Takada
//
//===============================================

//============================
// インクルードファイル
//============================
#include "manager.h"	//大元
#include "game.h"
#include "map.h"
#include "input.h"
#include "block.h"

//=======================
//マクロ定義
//=======================

//=======================
// ファイルパス
//=======================
const char *c_apFilenameMap[CMap::MAP_MAX] =
{
	"data\\SET\\MAP\\save.txt",
	"data\\SET\\MAP\\load.txt",
};

//=======================
// 静的メンバ変数
//=======================

//============================
// コンストラクタ
//============================
CMap::CMap(int nPriority) : CObject(nPriority)
{
	m_pBlock = nullptr;
}

//============================
// デストラクタ
//============================
CMap::~CMap()
{

}

//====================================
// 初期化(位置オバロ)
//====================================
HRESULT CMap::Init()
{
	if (m_pBlock != nullptr)
	{
		m_pBlock->Uninit();
		m_pBlock = nullptr;
	}

	m_pBlock->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//====================================
// 初期化(位置オバロ)
//====================================
HRESULT CMap::Init(const D3DXVECTOR3 pos)
{
	if (m_pBlock != nullptr)
	{
		m_pBlock->Uninit();
		m_pBlock = nullptr;
	}

	m_pBlock->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//============================
// 終了
//============================
void CMap::Uninit(void)
{
	if (m_pBlock != nullptr)
	{
		m_pBlock->Uninit();
		m_pBlock = nullptr;
	}

	Release();
}

//============================
// 更新
//============================
void CMap::Update(void)
{
	//キーボード取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CBlock *pBlock;
	D3DXVECTOR3 pos;
	
	if (m_pBlock != nullptr)
	{
		pos = m_pBlock->GetPos();
	}

	//カーソルの移動
	if (pInputKeyboard->GetTrigger(DIK_W))
	{//上
		pos.y += 10.0f;
	}
	if (pInputKeyboard->GetTrigger(DIK_S))
	{//下
		pos.y -= 10.0f;
	}
	if (pInputKeyboard->GetTrigger(DIK_A))
	{//西
		pos.x -= 10.0f;
	}
	if (pInputKeyboard->GetTrigger(DIK_D))
	{//東
		pos.x += 10.0f;
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN))
	{//ブロック設置
		pBlock = CBlock::Create(pos);
		pBlock->SetSize(m_pBlock->GetSize());
	}
}

//============================
// 描画
//============================
void CMap::Draw(void)
{

}

//============================
// ポーズの生成
//============================
CMap * CMap::Create(D3DXVECTOR3 pos)
{
	CMap *pMap = nullptr;

	//オブジェクト生成&初期化
	pMap = new CMap;

	if (pMap != nullptr)
	{
		if (FAILED(pMap->Init(pos)))
		{
			return nullptr;
		}
		else
		{

		}
	}
	else
	{
		return nullptr;
	}

	return pMap;
}
