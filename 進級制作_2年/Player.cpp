#include "Player.h"
#include "Camera.h"
#include "Collider.h"
#include <cstdio>

static vector <AnimationInfo> animInfo =
{
	{0,"Assets/Character/Idle.mv1",true},	//Idle
	{1,"Assets/Character/Running.mv1",false},	//Wallk_?
	{2,"Assets/Character/jumping.mv1",false},	//Dash
	//{3,"fillPath",false},	//Atack_1
	//{4,"fillPath",false},	//Attack_2
	//{5,"fillPath",false},	//Attack_3
	//{6,"",false},			//jump
	//{7,"",false},			//other_0
};

int playerModelHandle;
int weaponModelHandle;

const char* handFrameName = "Right wrist";//����̖ړI�̉E��̃t���[����

Player::Player() 
{
	MHandle = MV1LoadModel("Assets/test/PointBlack_human.mv1");

	int a = MHandle;

	//if (MHandle == -1)
	//	return;

	trans = VGet(320.f, 500.f, 0.f);
	rotation = VGet(0.f, DX_PI, 0.f);
	scale = VGet(1.f,1.f,1.f);
	name = "Player";
	
	anim_id = 0;		//�A�C�h��
	animatorPtr = new Animator();
	animatorPtr->Load(animInfo);

	forward = VGet(0.f,0.f,-1.f);

	//
	// �R���C�_�[���̏�����
	//
	colStartPos = MV1GetFramePosition(MHandle, 51);
	colEndPos = MV1GetFramePosition(MHandle, 53);
	radius = 50.0f;

	isWallHit = false;
	IsAttack = false;
	IsDash = false;
	IsRun = false;

	//���탂�f���̓ǂݍ���
	WPHandle = MV1LoadModel("Assets/Weapon's/CreataPoint_Middle_2nd_SAM_Blead.mv1");

	//��������������̃m�[�h���L�������f������T��
	MV1SearchFrame(MHandle,"28");
	
	//MPHandle = MV1LoadModel("fill_Name");	//MAP

	weaponPtr = new Weapon();

	camera = new Camera();

}

Player::~Player() 
{
	MV1DeleteModel(MHandle);
	MV1DeleteModel(WPHandle);	//����n���h��
	delete animatorPtr;

}

//�A���O�����쏈��
void Game_Init() 
{
	
}

void Player::move() 
{
	float speed = 5.0f;
	float diagonalSpeed = speed * 0.07f;
	float sideSpeed = 5.0f;

	float MoveX = 0;
	float MoveZ = 0;

	if (CheckHitKey(KEY_INPUT_W) && !isWallHit && !IsAttack && !IsRun) 
	{
		//IsRun = true;
		PlayerPos.x -= sinf(rotation.y) * speed;
		PlayerPos.z -= cosf(rotation.y) * speed;
		anim_id = 1;
		animatorPtr->Play(MHandle, anim_id);
		
		//IsRun = false;
	}

	else if (CheckHitKey(KEY_INPUT_S) && !isWallHit && !IsAttack)
	{
		PlayerPos.x += sinf(rotation.y) * speed;
		PlayerPos.z += cosf(rotation.y) * speed;
		anim_id = 0;
		animatorPtr->Play(MHandle, anim_id);
	}

	else if (CheckHitKey(KEY_INPUT_A) && !isWallHit && !IsAttack)
	{
		PlayerPos.x += cosf(rotation.y) * sideSpeed; // �������̌v�Z
		PlayerPos.z -= sinf(rotation.y) * sideSpeed;
		animatorPtr->Play(MHandle, anim_id);
	}

	else if (CheckHitKey(KEY_INPUT_D) && !isWallHit && !IsAttack)
	{
		PlayerPos.x -= cosf(rotation.y) * sideSpeed; // �E�����̌v�Z
		PlayerPos.z += sinf(rotation.y) * sideSpeed;
		animatorPtr->Play(MHandle, anim_id);
	}

	if (CheckHitKey(KEY_INPUT_SPACE) && !IsJump) 
	{
		//isJump��true��
		IsJump = true;
		jumpPower += 20;
		//void Player::Jump�ɔ��
		Player::jump();

	}

	//�΂ߓ��͂̍ۂ̏���
	if ((CheckHitKey(KEY_INPUT_W) && CheckHitKey(KEY_INPUT_A)) ||
		(CheckHitKey(KEY_INPUT_W) && CheckHitKey(KEY_INPUT_D)) ||
		(CheckHitKey(KEY_INPUT_S) && CheckHitKey(KEY_INPUT_A)) ||
		(CheckHitKey(KEY_INPUT_S) && CheckHitKey(KEY_INPUT_D))) 
	{
		MoveX *= diagonalSpeed;
		MoveZ *= diagonalSpeed;
	}

	PlayerPos.x += MoveX;
	PlayerPos.z += MoveZ;

}

void Player::jump() 
{
	if (IsJump == true) 
	{
		jumpPower -= GRAVITY;

		PlayerPos.y += jumpPower;

		if (PlayerPos.y <= GroundPos.y)
		{
			IsJump = false;
			PlayerPos.y = GroundPos.y;
			//IsGroundHit = true;
		}
	}

	else
	{
		// �W�����v���ł͂Ȃ�/_�d�͏���
		PlayerPos.y -= 0.f;
		if (PlayerPos.y <= GroundPos.y)
		{
			PlayerPos.y = GroundPos.y;

			IsJump = false;
			jumpPower = 0.f;
			IsGroundHit = true;
		}
	}

	DrawFormatString(10, 200, 32000, "trans.y=%f", PlayerPos.y);

	int a = IsJump;
}

void Player::Update() 
{
	
	colStartPos = MV1GetFramePosition(MHandle, 5);
	colEndPos = MV1GetFramePosition(MHandle, 0);

	animatorPtr->Play(MHandle, anim_id);

	while (ProcessMessage == 0)
	{
		Input = GetJoypadInputState(DX_INPUT_PAD1);

		MoveFlag == false;
		//�ŏ��Ɏ΂ߓ��͂̔�����m�F���A���̂��ƍ��E�P�̓��͂̔��������
		if ((Input & PAD_INPUT_LEFT) != 0 && (Input & PAD_INPUT_UP) != 0) {
			Angle = 135.0f;
			MoveFlag = true;
		}
		else if ((Input & PAD_INPUT_UP) != 0 && (Input & PAD_INPUT_RIGHT) != 0) {
			Angle = -135.0f;
			MoveFlag = true;
		}
		else if ((Input & PAD_INPUT_RIGHT) != 0 && (Input & PAD_INPUT_RIGHT) != 0) {
			Angle = -45.0f;
			MoveFlag = true;
		}
		else if ((Input & PAD_INPUT_DOWN) != 0 && (Input & PAD_INPUT_LEFT) != 0) {
			Angle = 45.0;
			MoveFlag = true;
		}
		else if ((Input & PAD_INPUT_LEFT) != 0) {
			Angle = 90.0;
			MoveFlag = true;
		}
		else if (Input & PAD_INPUT_RIGHT) {
			Angle = -90.0;
			MoveFlag = true;
		}
		else if ((Input & PAD_INPUT_DOWN != 0)) 
		{
			Angle = 180.0;
			MoveFlag = true;
		}

	}

	//Player�ړ�
	move();
	jump();

	CameraTarget = PlayerPos;		//PlayerPos->trans

	//
	VECTOR Direction = VGet(0.0f, 0.0f, CameraLenght);
	
	//VECTOR Direction = VGet(0.f, 0.f, 0.f);
	Direction = VNorm(Direction);
	Direction = VScale(Direction,CameraLenght);
	CameraPos = VAdd(CameraTarget, Direction);
	animatorPtr->Update();

	/*-MainGame���Ɉړ� -v -*/
	// �L�����̈ʒu�֌W��������悤�ɒn�ʂɃ��C����`�悷��i�f�o�b�O�\���j
	{
		VECTOR pos1;
		VECTOR pos2;

		pos1 = VGet(-10000.f / 2.0f, 0.0f, -10000.f / 2.0f);
		pos2 = VGet(-10000.f / 2.0f, 0.0f, 10000.f / 2.0f);
		for (int i = 0; i <= 50; i++)
		{
			DrawLine3D(pos1, pos2, GetColor(255, 255, 255));
			pos1.x += 10000.f / 50.f;
			pos2.x += 10000.f / 50.f;
		}

		pos1 = VGet(-10000.f / 2.0f, 0.0f, -10000.f / 2.0f);
		pos2 = VGet(10000.f / 2.0f, 0.0f, -10000.f / 2.0f);
		for (int i = 0; i < 50; i++)
		{
			DrawLine3D(pos1, pos2, GetColor(255, 255, 255));
			pos1.z += 10000.f / 50.f;
			pos2.z += 10000.f / 50.f;
		}
	}
	/**/

	MV1GetFramePosition(MHandle, 51);
	MV1GetFramePosition(MHandle, 53);

	//�A�j���[�V�����̍Đ��X�V
	animatorPtr->Update();

	////����`��
	weaponPtr->Update();

	MV1SetPosition(MHandle, PlayerPos);		//player�ƃJ����
	MV1DrawModel(MHandle);
	MV1DrawModel(WPHandle);

	//
	// �R���C�_�[�`��
	//
	DrawCapsule3D(colStartPos, colEndPos, radius,
		6, GetColor(0, 255, 0), GetColor(0, 255, 0),FALSE);

	MATRIX WPMatrix = MV1GetFrameLocalMatrix(MHandle, handFrameIndex);

	//����̃}�g���N�X�Ƃ��ēK�p
	//weaponPtr->SetMatrix(WPMatrix);
	//
	// 
	// �J�����̍X�V
	camera->Update(PlayerPos);

}

void Player::Draw() 
{
	MV1SetPosition(PlayerHandle, PlayerPos);					//PlayerModel�̍��W���Z�b�g

	SetCameraPositionAndTarget_UpVecY(CameraPos, CameraTarget);	//�J�����̈ʒu�ƒ����_���Z�b�g

}

//���픻��
void Player::OnCollisionHit(Collider* colliderPth, GameObject* gobjPtr) 
{

	//�R���W��������Ńq�b�g�������ɌĂяo�����R�[���o�b�N�֐�
	//if (gobjPtr->tag_name.compare("Weapon"))
	//{
	//	VECTOR pos = VGet(-forward.x * 10.f, 0.f, -forward.z* 10.f);
	//	trans = VAdd(trans, pos);
	//}
	
	//Attack�`�F�b�N����p�R���C�_�[
	//isAttack?
	/***/

	//�H�炤����p�̃R���C�_�[
	//isHit?
	/***/

}
