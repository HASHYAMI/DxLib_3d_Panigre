#include "Enemy.h"

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
	E_MHandle = MV1LoadModel("Assets/test/Crystale/crystale_spinner.mv1");	//MV1Data

	if (E_MHandle == -1)
		NULL;

	trans = VGet(100.f, 500.f, 0.f);
	rotation = VGet(0.0f, DX_PI, 0.f);
	scale = VGet(1.0f,1.0f,1.0f);
	name = "Enemy";

	//
	//�R���C�_�[�̏�����
	//

	//�G�̎n�_
	E_colStartPos = 5;
	//�G�̏I�_
	E_colEndPos = 6;
	//�G�̔��a
	E_radius = 0;

	/**/
	//�m�F�p
	int a = E_colEndPos;
	int b = E_colEndPos;
	int c = E_radius;
	/**/
	//�q�b�g�|�C���g
	Hp = 100000;

	/**/
	int d = Hp;
	/**/
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

	//�f��悤��
	E_camera = new Camera();

}

//
Enemy::~Enemy()
{
	MV1DeleteModel(E_MHandle);	//�G���f���̏���
	delete animPtr;				//�A�j���[�V�����̔j��

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

}
//�������U���p��void-���
void Enemy::RongLenght_Attack() 
{
	//�������U��
}

//�U������������Blook
void Enemy::Blook() 
{
	//�U���������A�h���s��


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
		//�ߋ���
		//Attack;
		//Run;
	}
	//
	else if (Hp <= 8499 && Hp > 8400) 
	{
		//������

	}
	//
	else if (Hp == 5000) 
	{
		//���ڂ̕K�E��L����

	}
	//
	else if (Hp <= 4999 && 2700) 
	{
		//�����̑O�ɏ����o���Ĉ�莞�Ԏ~�܂�

	}
	//
	else if (Hp <=  2699 && Hp > 1) 
	{
		//�������Ƌߋ�����A��
		RongLengthttack;
		//Attack;

	}
	//
	else if (Hp == 50) 
	{
		//�K�E���I����
		Ex_AttackFlga = true;
	}

}

void Enemy::Update() 
{
	animPtr->Play(E_MHandle, anim_id_E);

	Tink();
	//Move();
	Draw();

	//
	// �R���C�_�[�`��
	//
	DrawCapsule3D(MV1GetFramePosition(E_MHandle, E_colStartPos), MV1GetFramePosition(E_MHandle, E_colEndPos), radius,
		6, GetColor(0, 255, 0), GetColor(0, 255, 0), FALSE);
}

void Enemy::Draw() 
{
	MV1SetPosition(E_MHandle, EnemyPos);
	MV1DrawModel(E_MHandle);
}

//player���U������ۂɎg�������蔻��
void Enemy::OnCollisionHit_Player(Collider* ColliderPtr, GameObject* gobjPtr) 
{



}



/*Enemy_�����蔻��p�̘g_Collider*/

