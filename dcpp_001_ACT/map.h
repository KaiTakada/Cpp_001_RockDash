//===============================================
//
// マップ(map.h)
// Author: 髙田 佳依
//
//===============================================
#ifndef _MAP_H_
#define _MAP_H_

//=========================
// インクルードファイル
//=========================
#include "object.h"

//=========================
// マクロ定義
//=========================

//=========================
// 前方宣言
//=========================
class CBlock;

//=========================
// プレイヤークラス
//=========================
class CMap : public CObject
{
public:

	enum MAP_FILE
	{
		MAP_LOAD = 0,
		MAP_SAVE,
		MAP_MAX,
	};

	CMap(int nPriority = PRIORITY_PAUSE);		//コンストラクタ
	~CMap();		//デストラクタ

	HRESULT Init(void);							//初期化(デフォ)
	HRESULT Init(const D3DXVECTOR3 pos);		//初期化(オバロ)
	void Uninit(void);							//終了
	void Update(void);							//更新
	void Draw(void);							//描画
	static CMap *Create(const D3DXVECTOR3 pos);		//生成

protected:

private:
	CBlock *m_pBlock;			//ブロック(カーソル)
};

#endif