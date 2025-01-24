#pragma once

#include "DxLib.h"

#include <math.h>

#include "GameObject.h"
#include "Animator.h"
#include "Collider.h"
#include "Collision.h"
#include "Camera.h"

#define JUMP_POWER_ENEMY  30.0f;
#define GRAVITY 1.0f;

#define D2R(deg) ((deg)* DX_PI_F / 180.0f)		//度をラジアン角に変換

//各ステータス
enum Enemy_State 
{
	Attack,
	Difiend,
	Esxape,
	EX_Attack,
	Run,
	None,
	Blook,
	RongLengthttack
};

class Enemy : public GameObject, CapsuleCollider 
{
public:

	Enemy();
	~Enemy();

	//! コライダーの始点
	int E_colStartPos;
	//! コライダーの終点
	int E_colEndPos;
	//! コライダーの半径
	float E_radius;

	VECTOR EnemyPos;

	Camera* E_camera;

	void Update();
	void Draw();
	void OnCollisionHit_Player(Collider* ColliderPtr, GameObject* gobjPtr);
	void Tink();
	/**/
	//思考の回路をここに

	/**/
private:

	//Eenemyのモデルハンドル
	int E_MHandle;		//敵のモデルハンドル

	bool isAttackFlag;	 //攻撃用
	bool isBlockFlag;		 //攻撃を避けるためにガードする意味
	bool isWallkFlag;		 //移動用
	bool isDashFlag;		 //近づく用
	bool isRongDistance;	 //遠距離攻撃用
	bool isDestructionFlag;//撃破された用
	bool isEx_A;
	bool isWallHit;			//壁の当たり判定用

	/*--------------------------------------------------*/
	bool Ex_AttackFlga;	//おまけ程度.導入は検討中
	/*--------------------------------------------------*/

	bool isUnder_Attack_WepHandle;		//下からの攻撃用
	int anim_id_E;
	Animator* animPtr;

	float jumpPower = 0.0f;			//初期化までここで

	int Hp;

	void Move();
	void Attack();
	void Dash();
	void RongLenght_Attack();
	void Blook();
};