#pragma once

#include "DxLib.h"
#include "GameObject.h"
#include "Collider.h"

class Weapon : public GameObject, CapsuleCollider
{
public:

	Weapon();
	~Weapon();

	void Update();
	void Draw();
	void OnCollisionHit(Collider* colliderPtr, GameObject* gobjPtr);

	void SetMatrix(MATRIX matrix) 
	{
		MV1SetMatrix(MHandle, matrix);
	}

	int GetHandle() { return MHandle; }

private:

	int MHandle;
};

