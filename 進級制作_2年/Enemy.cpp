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

	E_MHandle = MV1LoadModel("Assets/test/Crystale/crystal_spinner.mv1");	//MV1Data

	E_BHandle = MV1LoadModel("Assets/tset/BlookPanel.mv1");

	//if (E_MHandle == -1)
	//	printf("モデルの読込失敗");

	trans = VGet(320.f, 500.f, 10.f);
	rotation = VGet(0.0f, DX_PI, 0.f);
	scale = VGet(1.0f,1.0f,1.0f);
	name = "Enemy";

	//
	//コライダーの初期化
	//
	//敵の始点
	E_colStartPos = MV1GetFramePosition(E_MHandle,5);
	//敵の終点
	E_colEndPos = MV1GetFramePosition(E_MHandle, 6);
	//敵の半径
	E_radius = 80.0f;
	
	isSurvival = true;		//生存フラグ

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

	Hp = 100000;		//HPの初期化
}

//
Enemy::~Enemy()
{
	MV1DeleteModel(E_MHandle);	//敵モデルの消去
	delete animPtr;				//アニメーションの破棄

}

bool Enemy::CheckCapsuleCollision(VECTOR start1, VECTOR end1, float radius1,
	VECTOR start2, VECTOR end2, float radius2,
	float& penetrationDepth, VECTOR& collisionNormal) {
	// 線分間の最近接点を計算するヘルパー関数
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
	//アニメーション番号とplayerに攻撃動作





}

//遠距離攻撃用のvoid-後回し
void Enemy::RongLenght_Attack()
{
	//遠距離攻撃
	//地面から判定を出して攻撃


}

//攻撃を避ける方のBlook
void Enemy::Blook()
{
	//攻撃を避ける、防ぐ行動
	isBlockFlag = true;

	MV1DrawModel(E_BHandle);

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
		//近距離 enum
		//Attack;
		Run;
	}
	//
	else if (Hp <= 8499 && Hp > 8400)
	{
		//遠距離
		RongLengthttack;
	}
	//
	else if (Hp == 5000)
	{
		//一回目の必殺を有効化
		EX_Attack;
	}
	//
	else if (Hp <= 4999 && Hp > 2700)
	{
		//自分の前に盾を出して一定時間止まる
		Difiend;
	}
	//
	else if (Hp <= 2699 && Hp > 1)
	{
		//遠距離と近距離を連打
		RongLengthttack;
		/*Attack;*/

	}
	//
	else if (Hp == 50)
	{
		//必殺をオンに
		Ex_AttackFlga = true;
	}
	//もしフラグがtrueでHpが0なら
	if ((isSurvival == true) && Hp == 0)
	{
		//死亡として判定
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
	// コライダー描画
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

//playerを攻撃する際に使う当たり判定
void Enemy::OnCollisionHit_Player(Collider* ColliderPtr, GameObject* gobjPtr) 
{
	
}

void Enemy::OnCollisionHit(Collider* collidederPtr, GameObject* gobjPtr)
{
	
}


