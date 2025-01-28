#pragma once

#include "DxLib.h"

#include <math.h>

#include "GameObject.h"
#include "Animator.h"
#include "Collider.h"
#include "Collision.h"


#define JUMP_POWER_ENEMY  30.0f;
#define GRAVITY 1.0f;

//#define D2R(deg) ((deg)* DX_PI_F / 180.0f)		//度をラジアン角に変換

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

class Enemy : public GameObject, public CapsuleCollider
{
public:
	
	Enemy();
	~Enemy();

	//! コライダーの始点
	VECTOR E_colStartPos;
	//! コライダーの終点
	VECTOR E_colEndPos;
	//! コライダーの半径
	float E_radius = 0;

	VECTOR EnemyPos;

	void Update()override;
	void Draw()override;
	void OnCollisionHit_Player(Collider* ColliderPtr, GameObject* gobjPtr);
	void OnCollisionHit(Collider* collidederPtr, GameObject* gobject)override;
	void Tink();

	/**/
	// カプセル同士の衝突判定関数
	bool CheckCapsuleCollision(VECTOR start1, VECTOR end1, float radius1,
		VECTOR start2, VECTOR end2, float radius2,
		float& penetrationDepth, VECTOR& collisionNormal);
	/**/

private:

	//Eenemyのモデルハンドル
	int E_MHandle;		//敵のモデルハンドル
	int E_BHandle;		//ガード用のモデルハンドル

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

	VECTOR E_cameraPosition;
	float cameraHAngle_E;
	float cameraVAngle_E;

	void Move();
	void Attack();
	void Dash();
	void RongLenght_Attack();
	void Blook();

protected:
	
	int Hp = 100000;

	bool isSurvival;		//生存フラグ

};