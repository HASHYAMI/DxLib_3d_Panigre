#pragma once

#include "GameObject.h"

class Collider
{
public:
	static const int SPEHERE_TYPE = 1;
	static const int BOX_TYPE = 2;
	static const int CAPSULE_TYPE = 3;

	int colliderID;
	int colliderType;

public:

	Collider();
	~Collider();

	void SetGameObject(GameObject* gobjPtr) 
	{
		gameObjectPtr = gobjPtr;
	}
	GameObject* GetGameObject() 
	{
		return gameObjectPtr;
	}

	virtual void OnCollisionHit(Collider* collidederPtr, GameObject* gobject) = 0;

private:
	GameObject* gameObjectPtr;

};

/*BOX_Colliderの定義*/
class BoxCollider : public Collider 
{
public:
	BoxCollider() 
	{
		minPos = VGet(0.f, 0.f, 0.f);
		maxPos = VGet(0.f, 0.f, 0.f);
	}

	~BoxCollider() 
	{

	}

	VECTOR minPos;
	VECTOR maxPos;
	VECTOR localBoxMaxPos;
	VECTOR localBoxMinPos;
};

/*Capsule_Colliderの定義*/
class CapsuleCollider : public Collider
{
public:
	CapsuleCollider() 
	{
		StartPos = VGet(0.f, 0.f, 0.f);
		EndPos = VGet(0.f, 0.f, 0.f);
		orgStartPos = VGet(0.f, 0.f, 0.f);
		orgEndPos = VGet(0.f, 0.f, 0.f);
		radius = 0.f;
	}

	~CapsuleCollider() 
	{
	}

	VECTOR orgStartPos;
	VECTOR orgEndPos;
	VECTOR StartPos;
	VECTOR EndPos;
	float radius;
};

/*Sphere_Colliderの定義*/
class SphereCollider : public Collider
{
public:
	SphereCollider() {
		offset = VGet(0.f,0.f,0.f);
		radius = 0.f;
	}
	~SphereCollider() 
	{	
	}

	VECTOR offset;
	float radius;
};