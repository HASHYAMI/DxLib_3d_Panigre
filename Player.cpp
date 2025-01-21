#include "Player.h"
#include "Camera.h"
static vector <AnimationInfo> animInfo =
{
	{0,"fillPath",true},	//Idle
	{1,"fillPath",false},	//Wallk_?
	{2,"fillPath",false},	//Dash
	//{3,"fillPath",false},	//Atack_1
	//{4,"fillPath",false},	//Attack_2
	//{5,"fillPath",false},	//Attack_3
	//{6,"",false},			//jump
	//{7,"",false},			//other_00
};

Player::Player() 
{
	MHandle = MV1LoadModel("Assets/test/human.mv1");

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

	isWallHit = false;
	IsAttack = false;
	IsDash = false;
	IsRun = false;

	//武器モデルの読み込み
	WPHandle = MV1LoadModel("Assets/Weapon's/SAM_Blead.mv1");

	//武器を持たせる手のノードをキャラモデルから探す
	handFrameIndex = MV1SearchFrame(MHandle, "Assets/Character/ModelFrameName");
	
	//MPHandle = MV1LoadModel("fill_Name");	//MAP

	//handFrameIndex = MV1SearchFrame(MHandle, "Model_Rig or ModeleFrameName_Node");

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
	if (CheckHitKey(KEY_INPUT_W)) 
	{
		PlayerPos.x -= sinf(rotation.y) * 10.f;
		PlayerPos.z -= cosf(rotation.y) * 10.f;
		anim_id = 0;
		animatorPtr->Play(MHandle, anim_id);
	}

	else if (CheckHitKey(KEY_INPUT_S) && !isWallHit && !IsAttack)
	{
		PlayerPos.x += sinf(rotation.y) * 10.f;
		PlayerPos.z += cosf(rotation.y) * 10.f;
		anim_id = 0;
		animatorPtr->Play(MHandle, anim_id);
	}

	else if (CheckHitKey(KEY_INPUT_A) && !isWallHit && !IsAttack)
	{
		rotation.y -= 0.0f;
		PlayerPos.x -= cosf(DX_PI * rotation.z) * 5.0f;
		PlayerPos.z += sinf(DX_PI * rotation.x) * 5.0f;
		anim_id = 0;
	}

	else if (CheckHitKey(KEY_INPUT_D) && !isWallHit && !IsAttack)
	{
		rotation.y += 0.0f;
		PlayerPos.x += cosf(DX_PI * rotation.z) * 5.0f;
		PlayerPos.z -= sinf(DX_PI * rotation.x) * 5.0f;
		//anim_id = 00;
	}

	//斜め入力の際の処理
	if (CheckHitKey(KEY_INPUT_W) == 1 || CheckHitKey(KEY_INPUT_A) == 1)
	{
		if (CheckHitKey(KEY_INPUT_S) == 1 && CheckHitKey(KEY_INPUT_D) == 1) 
		{
			//float型の数値で減らす
			//speed = 0.707f;
			//playerの向く方向にモデルを回転する処理
		}
		else 
		{
			//数値のクリア
			//speed = 10.0f;	
		}
	}
	else 
	{
		//float クリア
		//speed = 10.0f;
	}
	

	if (CheckHitKey(KEY_INPUT_A) && CheckHitKey(KEY_INPUT_W)) 
	{
		PlayerPos.x -= sinf(rotation.y) * 5.0f;
		PlayerPos.z -= cosf(rotation.y) * 5.0f;
		//trans.x += cosf(DX_PI * rotation.z) * 1.0f;
		//trans.z -= sinf(DX_PI * rotation.x) * 1.0f;
		//anim_id = 00;
	}

	else if (CheckHitKey(KEY_INPUT_W) && CheckHitKey(KEY_INPUT_D))
	{
		PlayerPos.x -= sinf(rotation.y) * 5.f;
		PlayerPos.z -= cosf(rotation.y) * 5.f;
		//trans.x += cosf(DX_PI * rotation.z) * 1.0f;
		//trans.z -= sinf(DX_PI * rotation.x) * 1.0f;
		anim_id = 2;
	}

	else if (CheckHitKey(KEY_INPUT_S) && CheckHitKey(KEY_INPUT_D))
	{
		//残りは余った時間に
	}

	else if (CheckHitKey(KEY_INPUT_S) && CheckHitKey(KEY_INPUT_A))
	{
		//残りは余った時間に
	}

	//else 
	//{
	//	if (!IsAttack && IsJump) 
	//	{
	//		//
	//		//
	//	}
	//}
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
			//IsGroundHit  true;
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

}

void Player::Update() 
{
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

	//アニメーションの再生更新
	animatorPtr->Update();

	MV1SetPosition(MHandle, PlayerPos);		//playerとカメラ
	MV1DrawModel(MHandle);

	//MATRIX wpMatrix = MV1GetFrameLocalMatrix(MHandle, handFrameIndex);

	//武器のマトリクスとして適用
	//weaponPtr->SetMatrix(WPMatrix);

	//武器描画
	weaponPtr->Update();

	// カメラの更新
	camera->Update(PlayerPos);
}

void Player::Draw() 
{
	MV1SetPosition(PlayerHandle, PlayerPos);					//PlayerModelの座標をセット

	SetCameraPositionAndTarget_UpVecY(CameraPos, CameraTarget);	//カメラの位置と注視点をセット

	MV1DrawModel(MHandle);										//PlayerModelの描画

	MV1DrawModel(WPHandle);										//WPHandleの描画

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