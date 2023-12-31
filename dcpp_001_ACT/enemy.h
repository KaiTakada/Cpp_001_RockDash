//===============================================
//
// G(enemy.h)
// Author ûüc ÀË
//
//===============================================
#ifndef _ENEMY_H_		//±Ì}Nè`ª³êÄÈ©Á½ç
#define _ENEMY_H_		//ñdCN[hh~Ì}Nðè`·é

//=========================
// CN[ht@C
//=========================
#include "objectX.h"

//=========================
// }Nè`
//=========================

//=========================
// Oûé¾
//=========================
class CState_Life;

//=========================
// vC[NX
//=========================
class CEnemy : public CObjectX
{
public:

	//=========================
	// GÌíÞ
	//=========================
	enum TYPE
	{
		ET_NONE = 0,
		ET_SPEED,
		ET_HP,
		ET_BOSS,
		ET_MAX
	};

	//====================
	// LÌp[^
	//====================
	struct Param
	{
		float fLife;		//ÌÍ
		float fLifeMax;		//ÅåÌÍ
		float fSpeed;		//Ú®¬x
		float fAttack;		//UÍ
	};

	CEnemy(int nPriority = 2);		//RXgN^
	~CEnemy();		//fXgN^

	HRESULT Init(void);							//ú»(ftH)
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);		//ú»(Io)
	void Uninit(void);							//I¹
	void Update(void);							//XV
	void Draw(void);							//`æ
	static CEnemy *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, TYPE type = ET_NONE);		//¶¬
	bool CollisionRect(void);
	void Damage(int nDamege = 1);
	void StalkPlayer();
	void SetMove(const D3DXVECTOR3 move) { m_move = move; }		//Ú®ÊÝè
	bool CollisionCircle(D3DXVECTOR3 pos);
	void InitialState(CEnemy::TYPE type);
	void InitialMove();
	void MoveSpeed();
	void MoveBoss();

	void SetTypeE(CEnemy::TYPE type) { m_type = type; }
	CEnemy::TYPE GetTypeE() { return m_type; }

	void SetParam(Param param) { m_param = param; }
	Param GetParam() { return m_param; }

	void SetMoveFrag(bool bMove) { m_bMove = bMove; }
	bool GetMoveFrag() { return m_bMove; }
	void MoveCtrl() { m_bMove = !m_bMove; }

protected:

private:
	D3DXVECTOR3 m_move;		//Ú®Ê
	CEnemy::TYPE m_type;	//Gí
	Param m_param;			//p[^
	bool m_bMove;			//®«ªÜÁÄ¢ézÍtrueA½¾Ç¢©¯ézÍfalse
	CState_Life *m_pStateLife;		//óÔ
};

#endif
