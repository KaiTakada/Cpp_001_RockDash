//===============================================
//
// Xモデルオブジェクト(Xmodel.cpp)
// Author: ��田 佳依
//
//===============================================
#ifndef _XMODEL_H_								//このマクロ定義がされてなかったら
#define _XMODEL_H_								//二重インクルード防止のマクロを定義する

//================================
// インクルードファイル
//================================
#include "object.h"

//================================
// マクロ定義
//================================
#define DEF_VERTEX3D D3DXVECTOR3(0.0f,0.0f,0.0f)				//デフォルトサイズ
#define MAX_XMODEL (128)				//モデルの受け皿容量
#define XMODEL_SIZE_META (0.1f)				//モデルの出力倍率

//================================
// モデルクラス
//================================
class CXModel
{
public:
	typedef struct
	{
		D3DXMATRIX mtxWorld;				//ワールドマトリックス
		LPD3DXMESH pMesh;					//メッシュ(頂点情報)へのポインタ
		LPD3DXBUFFER pBuffMat;				//マテリアルへのポインタ
		LPDIRECT3DTEXTURE9 *pTexture;		//テクスチャへのポインタ
		DWORD dwNumMat;						//マテリアルの数
		D3DXVECTOR3 vtxMin;					//矩形の最小座標
		D3DXVECTOR3 vtxMax;					//矩形の最大座標
	}Model;

	CXModel();
	~CXModel();

	HRESULT Load(void);		//テクスチャ読み込み
	void Unload(void);		//テクスチャ破棄
	int Regist(const char *pFilename, D3DXVECTOR3 *vtxMin = nullptr, D3DXVECTOR3 *vtxMax = nullptr);		//モデル追加読込
	Model *GetAddress(int nIdx); /*{ return m_apModel[nIdx]; }*/		//モデル情報取得
	D3DXVECTOR3 GetVtxMin(int nIdx) { return m_aModel[nIdx].vtxMin; }		//モデル情報取得
	D3DXVECTOR3 GetVtxMax(int nIdx) { return m_aModel[nIdx].vtxMax; }		//モデル情報取得

protected:

private:
	Model m_aModel[MAX_XMODEL];		//モデル情報格納
	char *m_apFilename[MAX_XMODEL];		//ファイル文字列
	static int m_nNumAll;		//総モデル数
};

#endif
