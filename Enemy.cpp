#include "Enemy.h"

static vector <AnimationInfo> animInfo_E =
{
	{0,"FaillPath", true},		//Enemyの基本アイドル
	{0,"FaillPath", false},		//移動
	{0,"FaillPath", false},		//攻撃1
	{0,"FaillPath", false},		//攻撃2
	{0,"FaillPath", false},		//攻撃3
	{0,"FaillPath", false},		//遠距離用
	{0,"FaillPath", false},		//ブロック(回避)
	{0,"FaillPath", false},		//撃破用
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
	//コライダーの初期化
	//

	//敵の始点
	E_colStartPos = 5;
	//敵の終点
	E_colEndPos = 6;
	//敵の半径
	E_radius = 0;

	/**/
	//確認用
	int a = E_colEndPos;
	int b = E_colEndPos;
	int c = E_radius;
	/**/
	//ヒットポイント
	Hp = 100000;

	/**/
	int d = Hp;
	/**/
	anim_id_E = 0;
	animPtr = new Animator();
	animPtr->Load(animInfo_E);

	forward = VGet(0.f,0.f,-1.f);
	
	isAttackFlag = false;		//通常攻撃
	isBlockFlag = false;		//ブロック
	isDashFlag = false;			//距離詰め
	isRongDistance = false;		//遠距離攻撃
	isDestructionFlag = false;	//撃破
	isWallHit = false;			//壁の当たり判定用
	Ex_AttackFlga= false;		//必殺用

	isUnder_Attack_WepHandle = false;

	//映るように
	E_camera = new Camera();

}

//
Enemy::~Enemy()
{
	MV1DeleteModel(E_MHandle);	//敵モデルの消去
	delete animPtr;				//アニメーションの破棄

}

//基本移動ロジック
void Enemy::Move() 
{
	//αでは移動は無し

}

//距離を詰める用のvoid-後回し
void Enemy::Dash()
{
	//同様にここもαでは無し

}

void Enemy::Attack() 
{
	//基本攻撃

	//Playerに向かって攻撃アニメーションと攻撃

}
//遠距離攻撃用のvoid-後回し
void Enemy::RongLenght_Attack() 
{
	//遠距離攻撃
}

//攻撃を避ける方のBlook
void Enemy::Blook() 
{
	//攻撃を避ける、防ぐ行動


}

//AIの思考部分
void Enemy::Tink()
{
	//HP10000以下HP300以上
	if (Hp <= 100000 && Hp > 300)
	{
		//通常攻撃　enum
		RongLengthttack;

	}
	//
	else if (Hp <= 9999 && Hp > 8500)
	{
		//近距離
		//Attack;
		//Run;
	}
	//
	else if (Hp <= 8499 && Hp > 8400) 
	{
		//遠距離

	}
	//
	else if (Hp == 5000) 
	{
		//一回目の必殺を有効化

	}
	//
	else if (Hp <= 4999 && 2700) 
	{
		//自分の前に盾を出して一定時間止まる

	}
	//
	else if (Hp <=  2699 && Hp > 1) 
	{
		//遠距離と近距離を連打
		RongLengthttack;
		//Attack;

	}
	//
	else if (Hp == 50) 
	{
		//必殺をオンに
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
	// コライダー描画
	//
	DrawCapsule3D(MV1GetFramePosition(E_MHandle, E_colStartPos), MV1GetFramePosition(E_MHandle, E_colEndPos), radius,
		6, GetColor(0, 255, 0), GetColor(0, 255, 0), FALSE);
}

void Enemy::Draw() 
{
	MV1SetPosition(E_MHandle, EnemyPos);
	MV1DrawModel(E_MHandle);
}

//playerを攻撃する際に使う当たり判定
void Enemy::OnCollisionHit_Player(Collider* ColliderPtr, GameObject* gobjPtr) 
{



}



/*Enemy_当たり判定用の枠_Collider*/

