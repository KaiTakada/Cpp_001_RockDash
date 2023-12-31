//===============================================
//
// {XG(enemy_boss.h)
// Author ûüc ÀË
//
//===============================================
#ifndef _ENEMY_BOSS_H_		//±Ì}Nè`ª³êÄÈ©Á½ç
#define _ENEMY_BOSS_H_		//ñdCN[hh~Ì}Nðè`·é

//=========================
// CN[ht@C
//=========================
#include "enemy.h"

//=========================
// }Nè`
//=========================

//=========================
// Oûé¾
//=========================

//=========================
// vC[NX
//=========================
class CEnemy_Boss : public CEnemy
{
public:

	//=========================
	// GÌíÞ
	//=========================
	enum ATACKSTATE
	{
		AS_NONE = 0,
		AS_STALK,
		AS_BURST,
		AS_TACKLE,
		AS_MAX
	};

	CEnemy_Boss(int nPriority = 2);		//RXgN^
	~CEnemy_Boss();		//fXgN^

	HRESULT Init(void);							//ú»(ftH)
	HRESULT Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);		//ú»(Io)
	void Uninit(void);							//I¹
	void Update(void);							//XV
	void Draw(void);							//`æ
	static CEnemy_Boss *Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot);		//¶¬
	void SetAttack(CEnemy_Boss::ATACKSTATE state);		//s®Ýè
	void Attack();		//UàeÄà
	bool Burst();		//Uàe
	bool Tackle();		//Uàe

protected:

private:
	CEnemy_Boss::ATACKSTATE m_AttackState;		//s®í
	int m_nCoolTime;		//s®p^[ÉCTÝè
	bool m_bClear;			//s®®¹tO
	int m_nMoveCnt;			//s®JE^[
};

#endif
