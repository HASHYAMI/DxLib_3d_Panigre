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

const char* handFrameName = "Right wrist";//今回の目的の右手のフレーム名

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
	
	anim_id = 0;		//アイドル
	animatorPtr = new Animator();
	animatorPtr->Load(animInfo);

	forward = VGet(0.f,0.f,-1.f);

	//
	// コライダー情報の初期化
	//
	colStartPos = MV1GetFramePosition(MHandle, 51);
	colEndPos = MV1GetFramePosition(MHandle, 53);
	radius = 50.0f;

	isWallHit = false;
	IsAttack = false;
	IsDash = false;
	IsRun = false;

	//武器モデルの読み込み
	WPHandle = MV1LoadModel("Assets/Weapon's/CreataPoint_Middle_2nd_SAM_Blead.mv1");

	//武器を持たせる手のノードをキャラモデルから探す
	MV1SearchFrame(MHandle,"28");
	
	//MPHandle = MV1LoadModel("fill_Name");	//MAP

	weaponPtr = new Weapon();

	camera = new Camera();

}

Player::~Player() 
{
	MV1DeleteModel(MHandle);
	MV1DeleteModel(WPHandle);	//武器ハンドル
	delete animatorPtr;

}

//アングル操作処理
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
		PlayerPos.x += cosf(rotation.y) * sideSpeed; // 左方向の計算
		PlayerPos.z -= sinf(rotation.y) * sideSpeed;
		animatorPtr->Play(MHandle, anim_id);
	}

	else if (CheckHitKey(KEY_INPUT_D) && !isWallHit && !IsAttack)
	{
		PlayerPos.x -= cosf(rotation.y) * sideSpeed; // 右方向の計算
		PlayerPos.z += sinf(rotation.y) * sideSpeed;
		animatorPtr->Play(MHandle, anim_id);
	}

	if (CheckHitKey(KEY_INPUT_SPACE) && !IsJump) 
	{
		//isJumpをtrueに
		IsJump = true;
		jumpPower += 20;
		//void Player::Jumpに飛ぶ
		Player::jump();

	}

	//斜め入力の際の処理
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
		// ジャンプ中ではない/_重力処理
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
		//最初に斜め入力の判定を確認し、そのあと左右単体入力の判定をする
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

	//Player移動
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

	/*-MainGame内に移動 -v -*/
	// キャラの位置関係が分かるように地面にラインを描画する（デバッグ表示）
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

	//アニメーションの再生更新
	animatorPtr->Update();

	////武器描画
	weaponPtr->Update();

	MV1SetPosition(MHandle, PlayerPos);		//playerとカメラ
	MV1DrawModel(MHandle);
	MV1DrawModel(WPHandle);

	//
	// コライダー描画
	//
	DrawCapsule3D(colStartPos, colEndPos, radius,
		6, GetColor(0, 255, 0), GetColor(0, 255, 0),FALSE);

	MATRIX WPMatrix = MV1GetFrameLocalMatrix(MHandle, handFrameIndex);

	//武器のマトリクスとして適用
	//weaponPtr->SetMatrix(WPMatrix);
	//
	// 
	// カメラの更新
	camera->Update(PlayerPos);

}

void Player::Draw() 
{
	MV1SetPosition(PlayerHandle, PlayerPos);					//PlayerModelの座標をセット

	SetCameraPositionAndTarget_UpVecY(CameraPos, CameraTarget);	//カメラの位置と注視点をセット

}

//武器判定
void Player::OnCollisionHit(Collider* colliderPth, GameObject* gobjPtr) 
{

	//コリジョン判定でヒットした時に呼び出されるコールバック関数
	//if (gobjPtr->tag_name.compare("Weapon"))
	//{
	//	VECTOR pos = VGet(-forward.x * 10.f, 0.f, -forward.z* 10.f);
	//	trans = VAdd(trans, pos);
	//}
	
	//Attackチェック判定用コライダー
	//isAttack?
	/***/

	//食らう判定用のコライダー
	//isHit?
	/***/

}
