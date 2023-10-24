//===============================================
//
// vC[(player.cpp)
// Author ûüc ÀË
//
//===============================================

//============================
// CN[ht@C
//============================
#include "manager.h"	//ÙÚmÅKv
#include "game.h"		//ÙÚmÅKv
#include "player.h"
#include "input.h"		//ì
#include "camera.h"		//Ú®ûü
#include "sound.h"		//oÉKv
#include "parts.h"		//eqÖW
#include "motion.h"		//[V
#include "Field.h"		//nÊÆÌ½è»è
//#include "weapon.h"		//í
#include "wp_boost.h"		//u[Xg
#include "gauge.h"		//HPQ[W
#include "Xmodel.h"		//f
#include "growselecter.h"		//i»E¬·V[
#include "debugproc.h"	//fobO
#include "state_life.h"		//óÔÇ

//fobOp(¨»ç­Á·)
#include "bullet.h"
#include "block.h"
#include "enemy.h"
#include "effect.h"
#include "item.h"
#include "explosion.h"
#include "score.h"
#include "experience.h"

//============================
// }Nè`
//============================
#define NUM_GETAREA (300.0f)		//æ¾ÌæÌ¼a
#define NUM_HYGETAREA (100.0f)		//æ¾Á¬ÌæÌ¼a
#define NUM_GETAREA_SPEED (8.0f)	//æ¾ÌæÌø«ñ¹¬x
#define NUM_COLL (30.0f)			//½è»è¼a
#define NUM_HP (1.0f)				//HPÊ
#define NUM_ATTACK (1.0f)			//UÍ
#define NUM_SPEED (1.5f)			//Ú®Ê
#define NUM_SPEED_STOP (0.0001f)	//Ú®Êð0É·éðl
#define NUM_HEART (50.0f)			//SÊu
#define NUM_JUMP (15.0f)			//WvÍ
#define NUM_BOOST (20.0f)			//u[XgÍ
#define NUM_GRAV (0.5f)				//dÍ
#define MOTION_FILE "data\\SET\\MOTION\\motion_player.txt"		//[Vt@CpX
#define READ_PSIZE (256)			//Ç|C^TCY
#define ARMR_IDX (17)				//Eèp[c
#define HP_HEIGHT (170.0f)			//HPQ[WÌ³
#define EXP_MAX (5.0f)				//expQ[WÌMaxÌúl
#define EXP_MAX_MGNFC (1.2f)		//expQ[WÌMaxÉ|¯é{¦
#define DAMAGE_CT (1)				//_[W³GÔ

//============================
// èè`
//============================
int g_anParts[MAX_PLAYER_WEAPON] = { 14,17 };

//============================
// ÃIoÏé¾
//============================

//============================
// RXgN^
//============================
CPlayer::CPlayer(int nPriority) : CObject(nPriority)
{
	m_nNumModel = 0;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_posOld = m_pos;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = m_rot;
	m_mtxWorld = {};
	m_fHeart = 0.0f;
	m_bJump = false;
	m_bBoost = false;
	m_pMotion = nullptr;
	m_pGaugeBoost = nullptr;
	ZeroMemory(&m_param, sizeof(m_param));
	m_pStateLife = nullptr;
	
	for (int nCntBst = 0; nCntBst < sizeof(m_pBoost) / sizeof(m_pBoost[0]); nCntBst++)
	{
		m_pBoost[nCntBst] = nullptr;
	}

	for (int nCntPart = 0; nCntPart < MAX_PLAYER_PARTS; nCntPart++)
	{
		m_apPart[nCntPart] = nullptr;
	}
}

//============================
// fXgN^
//============================
CPlayer::~CPlayer()
{

}

//====================================
// vC[Ìú»(ftH)
//====================================
HRESULT CPlayer::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = m_rot;
	m_fHeart = NUM_HEART;
	m_param.fLife = NUM_HP;
	m_param.fLifeMax = NUM_HP;
	m_param.fSpeed = NUM_SPEED;
	m_param.fColl = NUM_COLL;

	//t@CÇp[c¶¬Eú»
	ReadFile();

	//^CvÝè
	SetType(TYPE_PLAYER);

	return S_OK;
}

//====================================
// 2DvC[Ìú»(ÊuIo)
//====================================
HRESULT CPlayer::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot, int nNumParts)
{
	m_pos = pos;
	m_posOld = pos;
	m_rot = rot;
	m_rotDest = rot;
	m_nNumModel = nNumParts;
	m_fHeart = NUM_HEART;
	m_param.fLife = NUM_HP;
	m_param.fLifeMax = NUM_HP;
	m_param.fAttack = NUM_ATTACK;
	m_param.fSpeed = NUM_SPEED;
	m_param.fColl = NUM_COLL;

	//[VÌ¶¬Aú»
	if (m_pMotion != nullptr)
	{
		return E_FAIL;
	}

	m_pMotion = new CMotion;
	m_pMotion->Init();

	//t@CÇp[c¶¬Eú»
	ReadFile();

	//int nNumParts = 0;
	//CMotion::INFO *pInfo;

	////p[cft@CÇ
	//char **ppParts = m_pMotion->ReadParts(MOTION_FILE, &nNumParts);

	////fÌ¶¬(Sp[cª)
	//for (int nCntCrt = 0; nCntCrt < nNumParts; nCntCrt++)
	//{
	//	m_apPart[nCntCrt] = CParts::Create(ppParts[nCntCrt]);
	//}

	//m_pMotion->ReadSetUp(MOTION_FILE, m_apPart);
	//m_pMotion->ReadMotions(MOTION_FILE, pInfo);

	m_pMotion->SetModel(m_apPart, m_nNumModel);

	//íð½¹é	
	for (int nCntBst = 0; nCntBst < sizeof(m_pBoost) / sizeof(m_pBoost[0]); nCntBst++)
	{
		if (m_pBoost[nCntBst] != nullptr)
		{
			m_pBoost[nCntBst] = nullptr;
		}

		m_pBoost[nCntBst] = CBoost::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		if (m_pBoost[nCntBst] != nullptr)
		{
			if (m_apPart[g_anParts[nCntBst]] != nullptr)
			{//è`ÊuÌp[cª¶Ý·é±ÆðmF

				float fposX = m_apPart[g_anParts[nCntBst]]->GetMaxVtx().x * 0.5f;
				m_pBoost[nCntBst]->SetParent(m_apPart[g_anParts[nCntBst]]);
				m_pBoost[nCntBst]->SetPos(D3DXVECTOR3(fposX, 0.0f, 0.0f));
			}
		}
	}

	//HPQ[WÌ¶¬
	if (m_pGaugeBoost != nullptr)
	{
		m_pGaugeBoost->Uninit();
		m_pGaugeBoost = nullptr;
	}

	m_pGaugeBoost = CGauge::Create(D3DXVECTOR3(m_pos.x, m_pos.y + HP_HEIGHT, m_pos.z), m_apPart[0]->GetRot(), D3DXVECTOR3(60.0f, 10.0f, 0.0f));
	
	CInputMouse *pInputMouse = CManager::GetInstance()->GetInputMouse();

	//óÔÌ¶¬
	if (m_pStateLife != nullptr)
	{
		m_pStateLife->Uninit();
		m_pStateLife = nullptr;
	}

	m_pStateLife = CState_Life::Create();

	//^CvÝè
	SetType(TYPE_PLAYER);

	return S_OK;
}

//============================
// vC[ÌI¹
//============================
void CPlayer::Uninit(void)
{
	for (int nCntPrt = 0; nCntPrt < MAX_PLAYER_PARTS; nCntPrt++)
	{
		if (m_apPart[nCntPrt] != nullptr)
		{
			m_apPart[nCntPrt]->Uninit();
			//delete m_apPart[nCntPrt];
			m_apPart[nCntPrt] = nullptr;
		}
	}

	if (m_pMotion != nullptr)
	{
		m_pMotion->Uninit();
		delete m_pMotion;
		m_pMotion = nullptr;
	}

	for (int nCntBst = 0; nCntBst < sizeof(m_pBoost) / sizeof(m_pBoost[0]); nCntBst++)
	{
		if (m_pBoost[nCntBst] != nullptr)
		{
			m_pBoost[nCntBst]->Uninit();
			m_pBoost[nCntBst] = nullptr;
		}
	}

	if (m_pGaugeBoost != nullptr)
	{
		m_pGaugeBoost->Uninit();
		m_pGaugeBoost = nullptr;
	}
	
	if (m_pStateLife != nullptr)
	{
		m_pStateLife->Uninit();
		m_pStateLife = nullptr;
	}

	//I¹
	Release();
}

//============================
// vC[ÌXV
//============================
void CPlayer::Update(void)
{
	//ÀWæ¾
	float fRotMove = GetRot().y;	//»ÝÌü«
	float fRotDest = GetRot().y;	//ÚWÌü«
	float fRotDiff = 0.0f;			//·ª

	D3DXVECTOR3 pos = GetPos();
	m_posOld = pos;

	//L[{[hæ¾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputMouse *pInputMouse = CManager::GetInstance()->GetInputMouse();
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();

	//Ú®üÍ
	fRotDest = m_rotDest.y;

	MoveOperate2D(&fRotDest);
	RotOperate(&fRotDest);

	fRotDiff = fRotDest - fRotMove;
	RotAdj(fRotDiff);

	if (pInputKeyboard->GetTrigger(DIK_SPACE) ||
		pInputGamepad->GetPress(CInputGamepad::BUTTON_A,0))
	{//[ - ]L[ÅWv
		if (pInputKeyboard->GetPress(DIK_S))
		{
			if ((m_bJump == false) && m_pMotion->GetType() != MOTIONTYPE_SLIDING)
			{//ºL[ºWvµÄ¢È¢XCfBOÅÍÈ¢
				m_move.x += sinf(m_rot.y * D3DX_PI) * NUM_BOOST;		//x
				m_pMotion->Set(MOTIONTYPE_SLIDING);
			}
			else if (m_bBoost == false)
			{//WvgpÏÝ  orXCfBOÈç
			 //©Âu[XgQ[WªcÁÄ¢êÎ
			 //u[Xg
				m_bJump = true;
				m_bBoost = true;
				m_move.y = NUM_JUMP * 1.5f;
				m_pMotion->Set(MOTIONTYPE_BOOST);
			}
		}
		else if (((m_bJump == true) || m_pMotion->GetType() == MOTIONTYPE_SLIDING) && (m_bBoost == false))
		{//WvgpÏÝ  orXCfBOÈç
			//©Âu[XgQ[WªcÁÄ¢êÎ
			 //u[Xg
			m_bJump = true;
			m_bBoost = true;
			m_move.y = NUM_JUMP * 1.5f;
			m_pMotion->Set(MOTIONTYPE_BOOST);
		}
		else if (m_bJump == false)
		{//Wv¢gp
			m_bJump = true;
			m_move.y += NUM_JUMP;
			m_pMotion->Set(MOTIONTYPE_JUMP);
		}
	}
	
#if _DEBUG
	DebugKey(pInputKeyboard);
#endif

	//dÍ
	m_move.y -= NUM_GRAV;

	//Ú®ÊðKp
	pos += m_move;

	//³ðæ¾·é
	CollisionField(pos);

	//º~Ï
	if (pos.y <= -50.0f)
	{
		pos.y = -50.0f;
		m_move.y = 0.0f;
		m_bJump = false;
		m_bBoost = false;
		//static_assert(true, "À");
	}

	//íÌXV
	for (int nCntBst = 0; nCntBst < sizeof(m_pBoost) / sizeof(m_pBoost[0]); nCntBst++)
	{
		if (m_pBoost[nCntBst] != nullptr)
		{
			m_pBoost[nCntBst]->Update();
		}
	}

	//HPQ[WÌÀWXV
	if (m_pGaugeBoost != nullptr)
	{
		m_pGaugeBoost->SetPos(D3DXVECTOR3(pos.x, pos.y + HP_HEIGHT, pos.z));
	
		m_pGaugeBoost->Update();
	}
	
	if (m_pStateLife != nullptr)
	{
		CState_Life::STATE state = m_pStateLife->Get();
	
		m_pStateLife->Update();

		if (state == CState_Life::STATE_DAMAGE &&
			m_pStateLife->Get() == CState_Life::STATE_NORMAL)
		{//DAMAGE©çNORMALÉßÁ½ç

			D3DXMATERIAL mat;
			ZeroMemory(&mat, sizeof(D3DXMATERIAL));

			//p[cêÂ¸Âh·é
			for (int nCntPrt = 0; nCntPrt < MAX_PLAYER_PARTS; nCntPrt++)
			{
				if (m_apPart[nCntPrt] != nullptr)
				{
					m_apPart[nCntPrt]->SetMat(mat);
				}
			}
		}
	}
	
	//Ú®ÊðXV(¸³¹é)µ«
	m_move.x += (0 - m_move.x) * 0.1f;
	m_move.z += (0 - m_move.z) * 0.1f;

	if (m_move.x <= NUM_SPEED_STOP && m_move.x >= -NUM_SPEED_STOP)
	{//KèlÈºÅÚ®Êð0É
		m_move.x = 0.0f;
	}
	if (m_move.z <= NUM_SPEED_STOP && m_move.z >= -NUM_SPEED_STOP)
	{//KèlÈºÅÚ®Êð0É
		m_move.z = 0.0f;
	}

	if (!m_pMotion->IsFinish())
	{
		m_pMotion->Update();
	}
}

//============================
// vC[Ì`æ
//============================
void CPlayer::Draw(void)
{
	//`æ
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//foCXÌæ¾
	D3DXMATRIX mtxRot, mtxTrans;		//vZp}gbNX

	//[h}gbNXÌú»
	D3DXMatrixIdentity(&m_mtxWorld);

	//ü«ð½f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//Êuð½f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//[h}gbNXÌÝè
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//fobO
	CDebugProc *pDebug = CManager::GetInstance()->GetDebugProc();
	pDebug->Print("--- vC[îñ ---\n");
	pDebug->Print("»ÝÌûü:%f\n", m_rot.y);
	pDebug->Print("»ÝÌûü:%f %f %f\n", m_pos.x, m_pos.y, m_pos.z);
}

//============================
// vC[Ì¶¬
//============================
CPlayer * CPlayer::Create(const D3DXVECTOR3 pos, const D3DXVECTOR3 rot)
{
	CPlayer *pPlayer = nullptr;

	//IuWFNg¶¬&ú»
	pPlayer = new CPlayer;

	if (pPlayer != nullptr)
	{
		pPlayer->Init(pos, rot, 1);
	}
	else
	{
		return nullptr;
	}

	return pPlayer;
}

//============================
// Ú®ì
//============================
void CPlayer::MoveOperate(float *pRotDest)
{
	//L[{[hæ¾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();
	CCamera *pCamera= CManager::GetInstance()->GetCamera();
	bool bInput = false;

	D3DXVECTOR3 cameraRot = pCamera->GetRot();

	if (pInputKeyboard->GetPress(DIK_S) == true ||
		pInputGamepad->GetPress(CInputGamepad::BUTTON_DOWN, 0) || pInputGamepad->GetGameStickLYPress(0) < 0)
	{
		if (pInputKeyboard->GetPress(DIK_A) == true ||
			pInputGamepad->GetPress(CInputGamepad::BUTTON_LEFT, 0) || pInputGamepad->GetGameStickLXPress(0) < 0)
		{//ã©Â¶L[ðµ½Æ«
			m_move.x += sinf(cameraRot.y + -0.75f * D3DX_PI) * m_param.fSpeed;		//x
			m_move.z += cosf(cameraRot.y + -0.75f * D3DX_PI) * m_param.fSpeed;		//y
			*pRotDest = cameraRot.y + 0.25f * D3DX_PI;
			bInput = true;
		}
		else if (pInputKeyboard->GetPress(DIK_D) == true ||
			pInputGamepad->GetPress(CInputGamepad::BUTTON_RIGHT, 0) || pInputGamepad->GetGameStickLXPress(0) > 0)
		{//ã©ÂEL[ðµ½Æ«
			m_move.x += sinf(cameraRot.y + 0.75f * D3DX_PI) * m_param.fSpeed;		//x
			m_move.z += cosf(cameraRot.y + 0.75f * D3DX_PI) * m_param.fSpeed;		//y
			*pRotDest = cameraRot.y + -0.25f * D3DX_PI;
			bInput = true;
		}
		else
		{//ãL[ÌÝðµ½Æ«
			m_move.x += sinf(cameraRot.y + 1.0f * D3DX_PI) * m_param.fSpeed;		//x
			m_move.z += cosf(cameraRot.y + 1.0f * D3DX_PI) * m_param.fSpeed;		//y
			*pRotDest = cameraRot.y + 0.0f * D3DX_PI;
			bInput = true;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_W) == true ||
		pInputGamepad->GetPress(CInputGamepad::BUTTON_UP, 0) || pInputGamepad->GetGameStickLYPress(0) > 0)
	{
		if (pInputKeyboard->GetPress(DIK_A) == true ||
			pInputGamepad->GetPress(CInputGamepad::BUTTON_LEFT, 0) || pInputGamepad->GetGameStickLXPress(0) < 0)
		{//º©Â¶L[ðµ½Æ«
			m_move.x += sinf(cameraRot.y + -0.25f * D3DX_PI) * m_param.fSpeed;		//x
			m_move.z += cosf(cameraRot.y + -0.25f * D3DX_PI) * m_param.fSpeed;		//y
			*pRotDest = cameraRot.y + 0.75f * D3DX_PI;
			bInput = true;
		}
		else if (pInputKeyboard->GetPress(DIK_D) == true ||
			pInputGamepad->GetPress(CInputGamepad::BUTTON_RIGHT, 0) || pInputGamepad->GetGameStickLXPress(0) > 0)
		{//º©ÂEL[ðµ½Æ«
			m_move.x += sinf(cameraRot.y + 0.25f * D3DX_PI) * m_param.fSpeed;		//x
			m_move.z += cosf(cameraRot.y + 0.25f * D3DX_PI) * m_param.fSpeed;		//y
			*pRotDest = cameraRot.y + -0.75f * D3DX_PI;
			bInput = true;
		}
		else
		{//ºL[ÌÝðµ½Æ«
			m_move.x += sinf(cameraRot.y + 0.0f * D3DX_PI) * m_param.fSpeed;		//x
			m_move.z += cosf(cameraRot.y + 0.0f * D3DX_PI) * m_param.fSpeed;		//y
			*pRotDest = cameraRot.y + 1.0f * D3DX_PI;
			bInput = true;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_A) == true ||
		pInputGamepad->GetPress(CInputGamepad::BUTTON_LEFT, 0) || pInputGamepad->GetGameStickLXPress(0) < 0)
	{//¶L[ÌÝðµ½Æ«
		m_move.x += sinf(cameraRot.y + -0.5f * D3DX_PI) * m_param.fSpeed;
		m_move.z += cosf(cameraRot.y + -0.5f * D3DX_PI) * m_param.fSpeed;
		*pRotDest = cameraRot.y + 0.5f * D3DX_PI;
		bInput = true;
	}
	else if (pInputKeyboard->GetPress(DIK_D) == true ||
		pInputGamepad->GetPress(CInputGamepad::BUTTON_RIGHT, 0) || pInputGamepad->GetGameStickLXPress(0) > 0)
	{//EL[ÌÝðµ½Æ«
		m_move.x += sinf(cameraRot.y + 0.5f * D3DX_PI) * m_param.fSpeed;
		m_move.z += cosf(cameraRot.y + 0.5f * D3DX_PI) * m_param.fSpeed;
		*pRotDest = cameraRot.y + -0.5f * D3DX_PI;
		bInput = true;
	}

	if (bInput == true)
	{
		if (m_pMotion->IsFinish() ||
			m_pMotion->GetType() == MOTIONTYPE_NEUTRAL ||
			m_pMotion->GetType() == MOTIONTYPE_GROUND)
		{
			if (NUM_SPEED > m_param.fSpeed)
			{
				m_pMotion->Set(MOTIONTYPE_DASH);
			}
			else
			{
				m_pMotion->Set(MOTIONTYPE_WALK);
			}
		}
	}
	else
	{
		if (m_pMotion->IsFinish() ||
			m_pMotion->GetType() == MOTIONTYPE_DASH ||
			m_pMotion->GetType() == MOTIONTYPE_WALK)
		{
			m_pMotion->Set(MOTIONTYPE_NEUTRAL);
		}
	}
}

//============================
// 2DÚ®ì
//============================
void CPlayer::MoveOperate2D(float *pRotDest)
{
	//L[{[hæ¾
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();
	CCamera *pCamera = CManager::GetInstance()->GetCamera();
	bool bInput = false;

	D3DXVECTOR3 cameraRot = pCamera->GetRot();

	//if (pInputKeyboard->GetPress(DIK_S) == true ||
	//	pInputGamepad->GetPress(CInputGamepad::BUTTON_DOWN, 0) || pInputGamepad->GetGameStickLYPress(0) < 0)
	//{
	//	if (pInputKeyboard->GetPress(DIK_A) == true ||
	//		pInputGamepad->GetPress(CInputGamepad::BUTTON_LEFT, 0) || pInputGamepad->GetGameStickLXPress(0) < 0)
	//	{//º©Â¶L[ðµ½Æ«

	//	}
	//	else if (pInputKeyboard->GetPress(DIK_D) == true ||
	//		pInputGamepad->GetPress(CInputGamepad::BUTTON_RIGHT, 0) || pInputGamepad->GetGameStickLXPress(0) > 0)
	//	{//º©ÂEL[ðµ½Æ«

	//	}
	//	else
	//	{//ºL[ÌÝðµ½Æ«
	//		//µáªÝ½¢(è])
	//	}
	//}
	//else if (pInputKeyboard->GetPress(DIK_W) == true ||
	//	pInputGamepad->GetPress(CInputGamepad::BUTTON_UP, 0) || pInputGamepad->GetGameStickLYPress(0) > 0)
	//{
	//	if (pInputKeyboard->GetPress(DIK_A) == true ||
	//		pInputGamepad->GetPress(CInputGamepad::BUTTON_LEFT, 0) || pInputGamepad->GetGameStickLXPress(0) < 0)
	//	{//ã©Â¶L[ðµ½Æ«

	//	}
	//	else if (pInputKeyboard->GetPress(DIK_D) == true ||
	//		pInputGamepad->GetPress(CInputGamepad::BUTTON_RIGHT, 0) || pInputGamepad->GetGameStickLXPress(0) > 0)
	//	{//ã©ÂEL[ðµ½Æ«

	//	}
	//	else
	//	{//ãL[ÌÝðµ½Æ«

	//	}
	//}
	//else if (pInputKeyboard->GetPress(DIK_A) == true ||
	if (pInputKeyboard->GetPress(DIK_A) == true ||
		pInputGamepad->GetPress(CInputGamepad::BUTTON_LEFT, 0) || pInputGamepad->GetGameStickLXPress(0) < 0)
	{//¶L[ÌÝðµ½Æ«
		m_move.x += sinf(cameraRot.y + -0.5f * D3DX_PI) * m_param.fSpeed;
		m_move.z += cosf(cameraRot.y + -0.5f * D3DX_PI) * m_param.fSpeed;
		*pRotDest = cameraRot.y + 0.5f * D3DX_PI;
		bInput = true;
	}
	else if (pInputKeyboard->GetPress(DIK_D) == true ||
		pInputGamepad->GetPress(CInputGamepad::BUTTON_RIGHT, 0) || pInputGamepad->GetGameStickLXPress(0) > 0)
	{//EL[ÌÝðµ½Æ«
		m_move.x += sinf(cameraRot.y + 0.5f * D3DX_PI) * m_param.fSpeed;
		m_move.z += cosf(cameraRot.y + 0.5f * D3DX_PI) * m_param.fSpeed;
		*pRotDest = cameraRot.y + -0.5f * D3DX_PI;
		bInput = true;
	}

	if (bInput == true)
	{
		m_rotDest.y = *pRotDest;
		if (m_pMotion->IsFinish() ||
			m_pMotion->GetType() == MOTIONTYPE_NEUTRAL ||
			m_pMotion->GetType() == MOTIONTYPE_GROUND)
		{
			if (NUM_SPEED > m_param.fSpeed)
			{
				m_pMotion->Set(MOTIONTYPE_DASH);
			}
			else
			{
				m_pMotion->Set(MOTIONTYPE_WALK);
			}
		}
	}
	else
	{
		if (m_pMotion->IsFinish() ||
			m_pMotion->GetType() == MOTIONTYPE_DASH ||
			m_pMotion->GetType() == MOTIONTYPE_WALK)
		{
			m_pMotion->Set(MOTIONTYPE_NEUTRAL);
		}
	}
}

//============================
// Ú®ì
//============================
void CPlayer::RotOperate(float *pfRotDest)
{
	//L[{[hæ¾
	CInputMouse *pInputMouse = CManager::GetInstance()->GetInputMouse();
	CInputGamepad *pInputGamepad = CManager::GetInstance()->GetInputGamepad();
	bool bInput = false;
}

//============================
// ü«ÌC³
//============================
void CPlayer::RotAdj(float fRotDiff)
{
	//pxÌlðC³·é
	RotLimit(&fRotDiff);

	m_rot.y += fRotDiff * 0.1f;		//Ú®ûü(px)Ìâ³

	//pxÌlðC³·é
	RotLimit(&m_rot.y);
}

//============================
// t@CÇÝÝ
//============================
void CPlayer::ReadFile(void)
{
	char *pComp = new char[READ_PSIZE];				//S~
	char *pFilepass[MAX_PLAYER_PARTS] = {};		//t@CpX
	D3DXVECTOR3 pos[MAX_PLAYER_PARTS];			//vZbgÊu
	D3DXVECTOR3 rot[MAX_PLAYER_PARTS];			//vZbgü«
	int aParent[MAX_PLAYER_PARTS];				//efÌL³
	int nNumParts = 0;					//p[c
	D3DXVECTOR3 **ppPos = nullptr;		//Êu
	D3DXVECTOR3 **ppRot = nullptr;		//ü«
	int nNumKey = 0;					//L[
	int nFrame = 0;						//t[
	int nLoop = 0;						//[v [ 0:µÈ¢ / 1:·é ]

	int nKeyCtr = 0;			//[VÇÌL[JE^[
	int nKeySetCtr = 0;			//[VÇÌL[ZbgJE^[
	int nMotionCtr = 0;			//[V
	CMotion::INFO *info = new CMotion::INFO[16];		//[Vîñ

	for (int nCntNull = 0; nCntNull < MAX_PLAYER_PARTS; nCntNull++)
	{
		pos[nCntNull] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rot[nCntNull] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		aParent[nCntNull] = -1;
	}

	FILE *pFile;

	pFile = fopen(MOTION_FILE, "r");

	if (pFile != nullptr)
	{
		do
		{
			fscanf(pFile, "%s", pComp);

			if (strncmp(pComp, "#", 1) == 0)
			{// ±êÌ ÆRg
				fgets(pComp, READ_PSIZE, pFile);
				continue;
			}

			if (strcmp(pComp, "NUM_MODEL") == 0)
			{//æ¾
				fscanf(pFile, "%s %d", pComp, &nNumParts);
				m_nNumModel = nNumParts;
			}
			else if (strcmp(pComp, "MODEL_FILENAME") == 0)
			{//t@CÇ
				for (int nCntCrt = 0; nCntCrt < nNumParts; nCntCrt++)
				{
					if (pFilepass[nCntCrt] == nullptr)
					{
						pFilepass[nCntCrt] = new char[128];
						fscanf(pFile, "%s %s", pComp, pFilepass[nCntCrt]);
						break;
					}
				}
			}
			else if (strcmp(pComp, "CHARACTERSET") == 0)
			{//ItZbgîñæ¾Jn
				int nCntSet = 0;

				do
				{
					fscanf(pFile, "%s", pComp);

					if (strcmp(pComp, "PARTSSET") == 0)
					{//p[cîñæ¾Jn
						while (TRUE)
						{
							fscanf(pFile, "%s", pComp);

							if (strcmp(pComp, "END_PARTSSET") == 0)
							{
								break;
							}
							else if (strcmp(pComp, "PARENT") == 0)
							{
								fscanf(pFile, "%s %d", pComp, &aParent[nCntSet]);
							}
							else if (strcmp(pComp, "POS") == 0)
							{
								fscanf(pFile, "%s %f %f %f", pComp, &pos[nCntSet].x, &pos[nCntSet].y, &pos[nCntSet].z);
							}
							else if (strcmp(pComp, "ROT") == 0)
							{
								fscanf(pFile, "%s %f %f %f", pComp, &rot[nCntSet].x, &rot[nCntSet].y, &rot[nCntSet].z);
							}
						}

						//æ¾I¹ÅÁZ
						nCntSet++;
					}

				} while (strcmp(pComp, "END_CHARACTERSET") != 0);
			}
			else if (strcmp(pComp, "MOTIONSET") == 0)
			{
				do
				{//[VîñðÇÞ

					fscanf(pFile, "%s", pComp);

					if (strncmp(pComp, "#", 1) == 0)
					{// ±êÌ ÆRg
						fgets(pComp, READ_PSIZE, pFile);
						continue;
					}
					else if (strcmp(pComp, "END_MOTIONSET") == 0)
					{
						nMotionCtr++;
						nKeyCtr = 0;
						nKeySetCtr = 0;

						if (ppPos != nullptr)
						{
							for (int nCntMotKey = 0; nCntMotKey < nNumKey; nCntMotKey++)
							{
								delete[] ppPos[nCntMotKey];
							}

							delete[] ppPos;
						}

						if (ppRot != nullptr)
						{
							for (int nCntMotKey = 0; nCntMotKey < nNumKey; nCntMotKey++)
							{
								delete[] ppRot[nCntMotKey];
							}

							delete[] ppRot;
						}

						break;
					}
					else if (strcmp(pComp, "LOOP") == 0)
					{//[vÝèæ¾
						fscanf(pFile, "%s %d", pComp, &nLoop);

						info[nMotionCtr].bLoop = (nLoop == 0 ? false : true);
					}
					else if (strcmp(pComp, "NUM_KEY") == 0)
					{//L[æ¾
						fscanf(pFile, "%s %d", pComp, &nNumKey);

						info[nMotionCtr].nNumKey = nNumKey;

						//[VÉKvÈ¾¯Êuîñð¶¬
						//¶¬àe : ppPos[L[][p[c]
						//¶¬àe : ppRot[L[][p[c]
						ppPos = new D3DXVECTOR3*[nNumKey];
						ppRot = new D3DXVECTOR3*[nNumKey];

						for (int nCntMotKey = 0; nCntMotKey < nNumKey; nCntMotKey++)
						{
							ppPos[nCntMotKey] = new D3DXVECTOR3[nNumParts];
							ppRot[nCntMotKey] = new D3DXVECTOR3[nNumParts];
						}
					}
					else if (strcmp(pComp, "KEYSET") == 0)
					{//L[Zbgîñæ¾Jn
						do
						{
							fscanf(pFile, "%s", pComp);

							if (strncmp(pComp, "#", 1) == 0)
							{// ±êÌ ÆRg
								fgets(pComp, READ_PSIZE, pFile);
								continue;
							}
							else if (strcmp(pComp, "END_KEYSET") == 0)
							{
								//æ¾I¹ÅÁZ
								nKeySetCtr++;
								nKeyCtr = 0;

								break;
							}
							else if (strcmp(pComp, "FRAME") == 0)
							{//t[æ¾
								fscanf(pFile, "%s %d", pComp, &nFrame);

								info[nMotionCtr].aKeyInfo[nKeySetCtr].nFrame = nFrame;
							}
							else if (strcmp(pComp, "KEY") == 0)
							{//p[cîñæ¾Jn
								while (TRUE)
								{
									fscanf(pFile, "%s", pComp);

									if (strncmp(pComp, "#", 1) == 0)
									{// ±êÌ ÆRg
										fgets(pComp, READ_PSIZE, pFile);
										continue;
									}
									else if (strcmp(pComp, "END_KEY") == 0)
									{
										//æ¾I¹ÅÁZ
										nKeyCtr++;
										break;
									}
									else if (strcmp(pComp, "POS") == 0)
									{
										fscanf(pFile, "%s %f %f %f", pComp, &ppPos[nKeySetCtr][nKeyCtr].x, &ppPos[nKeySetCtr][nKeyCtr].y, &ppPos[nKeySetCtr][nKeyCtr].z);

										info[nMotionCtr].aKeyInfo[nKeySetCtr].aKey[nKeyCtr].fPosX = ppPos[nKeySetCtr][nKeyCtr].x;
										info[nMotionCtr].aKeyInfo[nKeySetCtr].aKey[nKeyCtr].fPosY = ppPos[nKeySetCtr][nKeyCtr].y;
										info[nMotionCtr].aKeyInfo[nKeySetCtr].aKey[nKeyCtr].fPosZ = ppPos[nKeySetCtr][nKeyCtr].z;
									}
									else if (strcmp(pComp, "ROT") == 0)
									{
										fscanf(pFile, "%s %f %f %f", pComp, &ppRot[nKeySetCtr][nKeyCtr].x, &ppRot[nKeySetCtr][nKeyCtr].y, &ppRot[nKeySetCtr][nKeyCtr].z);

										info[nMotionCtr].aKeyInfo[nKeySetCtr].aKey[nKeyCtr].fRotX = ppRot[nKeySetCtr][nKeyCtr].x;
										info[nMotionCtr].aKeyInfo[nKeySetCtr].aKey[nKeyCtr].fRotY = ppRot[nKeySetCtr][nKeyCtr].y;
										info[nMotionCtr].aKeyInfo[nKeySetCtr].aKey[nKeyCtr].fRotZ = ppRot[nKeySetCtr][nKeyCtr].z;
									}
								}

							}

						} while (strcmp(pComp, "END_KEYSET") != 0);
					}
				} while (strcmp(pComp, "END_MOTIONSET") != 0);
			}

		} while (strcmp(pComp, "END_SCRIPT") != 0);

		fclose(pFile);
	}
	else
	{//t@CÇÉ¸s
		return;
	}

	//fÌ¶¬(Sp[cª)
	for (int nCntCrt = 0; nCntCrt < nNumParts; nCntCrt++)
	{
		m_apPart[nCntCrt] = CParts::Create(pFilepass[nCntCrt], pos[nCntCrt], rot[nCntCrt]);
	}

	//efÌÝè(Sp[cª)
	for (int nCntPrt = 0; nCntPrt < nNumParts; nCntPrt++)
	{
		if (aParent[nCntPrt] <= -1)
		{
			m_apPart[nCntPrt]->SetParent(nullptr);
		}
		else
		{
			m_apPart[nCntPrt]->SetParent(m_apPart[aParent[nCntPrt]]);
		}
	}

	//[VîñÝè
	m_pMotion->SetInfo(info, nMotionCtr);

	delete[] pComp;		//S~
	delete[] info;

	for (int nCntPass = 0; nCntPass < 32; nCntPass++)
	{
		if (pFilepass[nCntPass] != nullptr)
		{
			delete pFilepass[nCntPass];
		}
	}
}

//============================
// _[W
//============================
void CPlayer::Damage(float fDamege)
{
	D3DXMATERIAL mat;
	ZeroMemory(&mat, sizeof(D3DXMATERIAL));

	if (m_pStateLife != nullptr)
	{
		if (m_pStateLife->Get() != CState_Life::STATE_NORMAL)
		{//_[Wðó¯çêÈ¢óÔÈç
			return;
		}
	}

	m_param.fLife -= fDamege;

	if (m_param.fLife > m_param.fLifeMax)
	{
		m_param.fLife = m_param.fLifeMax;
	}

	if (m_pStateLife != nullptr)
	{
		mat = m_pStateLife->GetMat();
	}

	//p[cêÂ¸Âh·é
	for (int nCntPrt = 0; nCntPrt < MAX_PLAYER_PARTS; nCntPrt++)
	{
		if (m_apPart[nCntPrt] != nullptr)
		{
			m_apPart[nCntPrt]->SetMat(mat);
		}
	}

	float fRatio = m_param.fLife / m_param.fLifeMax;

	m_pGaugeBoost->SetRatio(fRatio);

	if (m_param.fLife <= 0.0f)
	{
		//ñ¾çÇ¤µæ¤©
		CManager::GetInstance()->SetResult(CManager::RT_LOSE);
	}

	m_pStateLife->Set(CState_Life::STATE_DAMAGE, DAMAGE_CT);
}

//============================
// fobOL[
//============================
void CPlayer::DebugKey(CInputKeyboard *pInputKeyboard)
{
	//if (pInputKeyboard->GetPress(DIK_B) || (pInputKeyboard->GetTrigger(DIK_N)))
	//{//BL[ÅubN¶¬
	//	CBlock::Create(GetPos(), GetRot());
	//}

	if (pInputKeyboard->GetTrigger(DIK_K))
	{//KÅí`F
		int nType = (m_pBoost[0]->GetWpnType() + 1) % CBoost::WPNTYPE_MAX;
		m_pBoost[0]->SetWpnType(CWeapon::WPNTYPE(nType));
	}

	if (pInputKeyboard->GetTrigger(DIK_I))
	{//¶ShiftÅACe¶¬
		D3DXVECTOR3 pos = GetPos();
		pos.y += 50.0f;
	}

	if (pInputKeyboard->GetTrigger(DIK_E))
	{//¶ShiftÅHP¸­

		float fRatio = m_pGaugeBoost->GetRatio();

		fRatio -= 0.01f;

		m_pGaugeBoost->SetRatio(fRatio);
	}
}

//============================
// pxÌlðC³·é
//============================
void CPlayer::RotLimit(float *pRot)
{
	if (*pRot > D3DX_PI)
	{
		*pRot -= D3DX_PI * 2;
	}
	else if (*pRot < -D3DX_PI)
	{
		*pRot += D3DX_PI * 2;
	}
}

//============================
//ubNÆÌ½è»è(é`)
//============================
void CPlayer::CollisionField(D3DXVECTOR3 pos)
{
	float fHeight = 0.0f;

	for (int nCntPrt = 0; nCntPrt < PRIORITY_MAX; nCntPrt++)
	{
		CObject *pObject = CObject::GetTop(nCntPrt);

		while ((pObject != nullptr))
		{
			if (pObject != nullptr)
			{
				CObject::TYPE type = pObject->GetType();	//¡ñÌIuWFNgÌ^Cv

				if (type == CObject::TYPE_FIELD)
				{//ACe¾Á½ç

					CField *pField = (CField*)pObject;
					fHeight = pField->GetHeight(pos);
				}
				pObject = pObject->GetNext();
			}
			else
			{// (pObject == NULL) == EndÜÅsÁ½ÁÄ±ÆÅ±ÌDæxÍI¹
				break;
			}
		}
	}

	if (pos.y < fHeight && m_posOld.y >= fHeight)
	{
		pos.y = fHeight;
		m_move.y = 0.0f;
		m_bJump = false;
		m_bBoost = false;

		if (m_pMotion->GetType() == MOTIONTYPE_JUMP)
		{
			m_pMotion->Set(MOTIONTYPE_GROUND);
		}
	}

	//ÀWÝè(XV)
	SetPos(pos);
}
