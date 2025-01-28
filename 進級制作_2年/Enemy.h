#pragma once

#include "DxLib.h"

#include <math.h>

#include "GameObject.h"
#include "Animator.h"
#include "Collider.h"
#include "Collision.h"


#define JUMP_POWER_ENEMY  30.0f;
#define GRAVITY 1.0f;

//#define D2R(deg) ((deg)* DX_PI_F / 180.0f)		//�x�����W�A���p�ɕϊ�

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

class Enemy : public GameObject, public CapsuleCollider
{
public:
	
	Enemy();
	~Enemy();

	//! �R���C�_�[�̎n�_
	VECTOR E_colStartPos;
	//! �R���C�_�[�̏I�_
	VECTOR E_colEndPos;
	//! �R���C�_�[�̔��a
	float E_radius = 0;

	VECTOR EnemyPos;

	void Update()override;
	void Draw()override;
	void OnCollisionHit_Player(Collider* ColliderPtr, GameObject* gobjPtr);
	void OnCollisionHit(Collider* collidederPtr, GameObject* gobject)override;
	void Tink();

	/**/
	// �J�v�Z�����m�̏Փ˔���֐�
	bool CheckCapsuleCollision(VECTOR start1, VECTOR end1, float radius1,
		VECTOR start2, VECTOR end2, float radius2,
		float& penetrationDepth, VECTOR& collisionNormal);
	/**/

private:

	//Eenemy�̃��f���n���h��
	int E_MHandle;		//�G�̃��f���n���h��
	int E_BHandle;		//�K�[�h�p�̃��f���n���h��

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

	bool isSurvival;		//�����t���O

};