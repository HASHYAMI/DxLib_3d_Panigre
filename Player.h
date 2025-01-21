#pragma once

#include "Dxlib.h"

#include <math.h>

#include "GameObject.h"
#include "Animator.h"
#include "Collision.h"
#include "Collider.h"
#include "Weapon.h"
#include "Camera.h"

#define JUMPOWER 16.0f;
#define GRAVITY 1.0f;

#define D2R(deg) ((deg)*DX_PI_F/180.f)	//?

class Player :public GameObject, CapsuleCollider
{
public:
	Player();
	~Player();

	int Angle;
	int MoveFlag;
	int JumpFlag;
	int Input;

	int PlayerHandle;

	VECTOR Position;
	VECTOR CameraPos;
	VECTOR CameraAngle;

	VECTOR CameraTarget;
	VECTOR PlayerPos;

	void Update();
	void Draw();
	void OnCollisionHit(Collider* colliderPtr, GameObject* gobjPtr);	//コリジョン判定でヒットした時のコールバック関数

	_CollisionRect GetCollisionRect() 
	{
		MATRIX matrix = MV1GetMatrix(MHandle);
		_CollisionRect rect;
		rect.min_pos = VGet(-120.f, -150.f, 40.f);
		rect.max_pos = VGet(50.f, 150.f, -40.f);
		rect.min_pos = VTransform(rect.min_pos, matrix);
		rect.max_pos = VTransform(rect.max_pos, matrix);
		DrawLine3D(rect.min_pos, rect.max_pos, GetColor(255, 0, 0));
		return rect;
	}

	VECTOR GetPos() 
	{
		return trans;
	}

	VECTOR GetFoward() 
	{
		return forward;
	}

	VECTOR GetLeft() 
	{
		return Left;
	}
	VECTOR GEtRight() 
	{
		return Right;
	}

	bool GetJump() 
	{
		return IsJump;
	}
	bool GetDash() 
	{
		return IsDash;
	}

	void SetWallHit(bool flag) 
	{
		isWallHit = flag;
	}

	void SetGroundHit(bool flag, VECTOR pos) 
	{
		GroundPos = pos;
		//IsGoundHit = flag;
	}

	//Weapom* GetWeapon() { return WeaponPtr; }

private:
	int MHandle;
	int WPHandle;
	int anim_id;
	Animator* animatorPtr;

	Weapon* weaponPtr;


	int handFrameIndex;

	float CameraLenght = 0.0f;

	float jumpPower = 0.0f;

	bool isWallHit;
	bool IsGroundHit;
	bool IsUpHit;

	bool IsJump;
	bool IsAttack;
	bool IsRun;
	bool IsDash;

	Camera* camera;

	//bool m_isRockOn = false;	//チャレンジ用

	VECTOR GroundPos;


	void move();
	void jump();
	void Dash();
	void Attack();
};

