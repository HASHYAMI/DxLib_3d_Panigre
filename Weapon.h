#pragma once

#include "DxLib.h"
#include "GameObject.h"
#include "Collider.h"

class Weapon : public GameObject, CapsuleCollider
{
public:

	Weapon();
	~Weapon();

	//! �R���C�_�[�̎n�_
	int W_colStartPos;
	//! �R���C�_�[�̏I�_
	int W_colEndPos;
	//! �R���C�_�[�̔��a
	float W_radius;

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

