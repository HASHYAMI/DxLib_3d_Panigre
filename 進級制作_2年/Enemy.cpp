#include "Enemy.h"
#include "Collider.h"
#include "Camera.h"
#include <vector>
#include <cmath>

template<typename T>
T clamp(const T& value, const T& min, const T& max) {
	if (value < min) return min;
	if (value > max) return max;
	return value;
}

static vector <AnimationInfo> animInfo_E =
{
	{0,"FaillPath", true},		//Enemy�̊�{�A�C�h��
	{0,"FaillPath", false},		//�ړ�
	{0,"FaillPath", false},		//�U��1
	{0,"FaillPath", false},		//�U��2
	{0,"FaillPath", false},		//�U��3
	{0,"FaillPath", false},		//�������p
	{0,"FaillPath", false},		//�u���b�N(���)
	{0,"FaillPath", false},		//���j�p
};

//
Enemy::Enemy() 
{

	E_MHandle = MV1LoadModel("Assets/test/Crystale/crystal_spinner.mv1");	//MV1Data

	E_BHandle = MV1LoadModel("Assets/tset/BlookPanel.mv1");

	//if (E_MHandle == -1)
	//	printf("���f���̓Ǎ����s");

	trans = VGet(320.f, 500.f, 10.f);
	rotation = VGet(0.0f, DX_PI, 0.f);
	scale = VGet(1.0f,1.0f,1.0f);
	name = "Enemy";

	//
	//�R���C�_�[�̏�����
	//
	//�G�̎n�_
	E_colStartPos = MV1GetFramePosition(E_MHandle,5);
	//�G�̏I�_
	E_colEndPos = MV1GetFramePosition(E_MHandle, 6);
	//�G�̔��a
	E_radius = 80.0f;
	
	isSurvival = true;		//�����t���O

	anim_id_E = 0;
	animPtr = new Animator();
	animPtr->Load(animInfo_E);

	forward = VGet(0.f,0.f,-1.f);
	
	isAttackFlag = false;		//�ʏ�U��
	isBlockFlag = false;		//�u���b�N
	isDashFlag = false;			//�����l��
	isRongDistance = false;		//�������U��
	isDestructionFlag = false;	//���j
	isWallHit = false;			//�ǂ̓����蔻��p
	Ex_AttackFlga= false;		//�K�E�p

	isUnder_Attack_WepHandle = false;

	Hp = 100000;		//HP�̏�����
}

//
Enemy::~Enemy()
{
	MV1DeleteModel(E_MHandle);	//�G���f���̏���
	delete animPtr;				//�A�j���[�V�����̔j��

}

bool Enemy::CheckCapsuleCollision(VECTOR start1, VECTOR end1, float radius1,
	VECTOR start2, VECTOR end2, float radius2,
	float& penetrationDepth, VECTOR& collisionNormal) {
	// �����Ԃ̍ŋߐړ_���v�Z����w���p�[�֐�
	auto ClosestPointOnSegment = [](VECTOR point, VECTOR segStart, VECTOR segEnd) {
		VECTOR segVec = VSub(segEnd, segStart);
		float segLength = VSize(segVec);
		VECTOR segDir = VNorm(segVec);

		float t = VDot(VSub(point, segStart), segDir);
		t = clamp(t, 0.0f, segLength);

		return VAdd(segStart, VScale(segDir, t));
	};

	VECTOR closestPoint1 = ClosestPointOnSegment(start2, start1, end1);
	VECTOR closestPoint2 = ClosestPointOnSegment(closestPoint1, start2, end2);

	VECTOR difference = VSub(closestPoint2, closestPoint1);
	float distance = VSize(difference);

	if (distance < radius1 + radius2) {
		penetrationDepth = radius1 + radius2 - distance;
		collisionNormal = VNorm(difference);
		return true;
	}

	return false;
}

//��{�ړ����W�b�N
void Enemy::Move() 
{
	//���ł͈ړ��͖���

}

//�������l�߂�p��void-���
void Enemy::Dash()
{
	//���l�ɂ��������ł͖���

}

void Enemy::Attack() 
{
	//��{�U��

	//Player�Ɍ������čU���A�j���[�V�����ƍU��
	//�A�j���[�V�����ԍ���player�ɍU������





}

//�������U���p��void-���
void Enemy::RongLenght_Attack()
{
	//�������U��
	//�n�ʂ��画����o���čU��


}

//�U������������Blook
void Enemy::Blook()
{
	//�U���������A�h���s��
	isBlockFlag = true;

	MV1DrawModel(E_BHandle);

}

//AI�̎v�l����
void Enemy::Tink()
{
	//HP10000�ȉ�HP300�ȏ�
	if (Hp <= 100000 && Hp > 300)
	{
		//�ʏ�U���@enum
		RongLengthttack;

	}
	//
	else if (Hp <= 9999 && Hp > 8500)
	{
		//�ߋ��� enum
		//Attack;
		Run;
	}
	//
	else if (Hp <= 8499 && Hp > 8400)
	{
		//������
		RongLengthttack;
	}
	//
	else if (Hp == 5000)
	{
		//���ڂ̕K�E��L����
		EX_Attack;
	}
	//
	else if (Hp <= 4999 && Hp > 2700)
	{
		//�����̑O�ɏ����o���Ĉ�莞�Ԏ~�܂�
		Difiend;
	}
	//
	else if (Hp <= 2699 && Hp > 1)
	{
		//�������Ƌߋ�����A��
		RongLengthttack;
		/*Attack;*/

	}
	//
	else if (Hp == 50)
	{
		//�K�E���I����
		Ex_AttackFlga = true;
	}
	//�����t���O��true��Hp��0�Ȃ�
	if ((isSurvival == true) && Hp == 0)
	{
		//���S�Ƃ��Ĕ���
		isSurvival = false;

	}

}

void Enemy::Update()
{
	animPtr->Play(E_MHandle, anim_id_E);

	Tink();
	//Move();
	Draw();

	//HitCheck_Capsule_Capsule(player->colStartPos, player->colEndPos, player->radius, E_colStartPos, E_colEndPos, E_radius);

	animPtr->Update();

	//
	// �R���C�_�[�`��
	//
	DrawCapsule3D(E_colStartPos, E_colEndPos, E_radius,
		6, GetColor(0, 255, 0), GetColor(0, 255, 0), FALSE);

	E_colStartPos = MV1GetFramePosition(E_MHandle, 5);

	E_colEndPos = MV1GetFramePosition(E_MHandle, 6);
}

void Enemy::Draw() 
{
	MV1SetPosition(E_MHandle, EnemyPos);
	
	MV1DrawModel(E_MHandle);

	if (Hp <= 4999 && Hp > 2700)
	{

		MV1DrawModel(E_BHandle);
	}
	
}

//player���U������ۂɎg�������蔻��
void Enemy::OnCollisionHit_Player(Collider* ColliderPtr, GameObject* gobjPtr) 
{
	
}

void Enemy::OnCollisionHit(Collider* collidederPtr, GameObject* gobjPtr)
{
	
}


