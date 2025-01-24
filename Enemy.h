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

#define D2R(deg) ((deg)* DX_PI_F / 180.0f)		//�x�����W�A���p�ɕϊ�

//�e�X�e�[�^�X
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

	//! �R���C�_�[�̎n�_
	int E_colStartPos;
	//! �R���C�_�[�̏I�_
	int E_colEndPos;
	//! �R���C�_�[�̔��a
	float E_radius;

	VECTOR EnemyPos;

	Camera* E_camera;

	void Update();
	void Draw();
	void OnCollisionHit_Player(Collider* ColliderPtr, GameObject* gobjPtr);
	void Tink();
	/**/
	//�v�l�̉�H��������

	/**/
private:

	//Eenemy�̃��f���n���h��
	int E_MHandle;		//�G�̃��f���n���h��

	bool isAttackFlag;	 //�U���p
	bool isBlockFlag;		 //�U��������邽�߂ɃK�[�h����Ӗ�
	bool isWallkFlag;		 //�ړ��p
	bool isDashFlag;		 //�߂Â��p
	bool isRongDistance;	 //�������U���p
	bool isDestructionFlag;//���j���ꂽ�p
	bool isEx_A;
	bool isWallHit;			//�ǂ̓����蔻��p

	/*--------------------------------------------------*/
	bool Ex_AttackFlga;	//���܂����x.�����͌�����
	/*--------------------------------------------------*/

	bool isUnder_Attack_WepHandle;		//������̍U���p
	int anim_id_E;
	Animator* animPtr;

	float jumpPower = 0.0f;			//�������܂ł�����

	int Hp;

	void Move();
	void Attack();
	void Dash();
	void RongLenght_Attack();
	void Blook();
};