#include "MainGame.h"

MainGame::MainGame()
{
	sceneTag = SceneTag::MainGame;
	
	collsionManagerPtr = new CollisionManager();

	//Player�̃C���X�^���X����
	Player* playerPtr = new Player();

	//Enemy�̃C���X�^���X
	enemyPtr = new Enemy();
	
	//enemyPtr->player = playerPtr;		//_?
	Weapon* weapPtr = new Weapon();

	/*collider�ݒ�*/
	CapsuleCollider* colliderPtr = (CapsuleCollider*)playerPtr;
	colliderPtr->SetGameObject(playerPtr);
	collsionManagerPtr->Add(colliderPtr);
	
	/*GameObject��o�^*/
	GameObject* P_gobjPtr = playerPtr;
	P_gobjPtr->tag_name = "Player";
	gameObjectVec.push_back(P_gobjPtr);

	/*-����R���C�_�[���̐ݒ�-*/
	GameObject* P_wepjPtr = weapPtr;
	P_wepjPtr->tag_name = "Weapon";
	gameObjectVec.push_back(weapPtr);
	CapsuleCollider* colliderPtr3 = (CapsuleCollider*)weapPtr;
	colliderPtr3->SetGameObject(weapPtr);
	collsionManagerPtr->Add(colliderPtr3);
	//
	/*-Enemy�̃R���C�_�[����-*/
	//
	GameObject* E_gobjPtr = enemyPtr;
	E_gobjPtr->tag_name = "Enemy";
	gameObjectVec.push_back(E_gobjPtr);

	CapsuleCollider* colliderPtr2 = (CapsuleCollider*)enemyPtr;
	colliderPtr2->SetGameObject(enemyPtr);
	collsionManagerPtr->Add(colliderPtr2);
	//mapModelRoad
	//mapHnadle = MV1LoadModel("faillPath");

	//�n�ʂƃR���W��������̃��f�����Z�b�g
	//collision.setModelHandle(mapHandle);

	//�f�o�b�N�p(�ҋ@����)
	//Sleep(1500);
}

MainGame::~MainGame() 
{

}

void MainGame::Update() 
{
	//�f�o�b�N�p
	DrawFormatString(100,200, GetColor(255,255,255),"Scene MainGame");
	DrawFormatString(100, 230, GetColor(255, 255, 255), "Key to -R-");
	if (CheckHitKey(KEY_INPUT_T))
		SceneBace::SceneChange(SceneTag::Result);

	collsionManagerPtr->Update();
	for (int i = 0; i < gameObjectVec.size(); i++)
	{
		gameObjectVec[i]->Update();
	}

	//MV1SetPosition(mapHandle, VGet(1200.f, 890.f, 0.f));
	chk_collision();

	//MV1DrawModel(mapHandle);
}

void MainGame::chk_collision() 
{
	//Player�̐ݒ蓙
	Player* playerPtr = (Player*)gameObjectVec[0];
	VECTOR hitPos;
	VECTOR playerPos = playerPtr->GetPos();
	playerPos.y += 50.0f;

	if (collision.CheckRaycast(playerPos, playerPtr->Getforward(), 40.f, &hitPos)) 
	{
		DrawFormatString(10, 10, 32000, "Hit");
		playerPtr->SetWallHit(true);
	}
	else 
	{
		playerPtr->SetWallHit(false);

		VECTOR playerPos = playerPtr->GetPos();
		playerPos.y += 100.f;
		hitPos = VGet(0.f, 240.f, 0.f);
		if (collision.CheckRaycast(playerPos, VGet(0.f, -1.f, 0.f),110.f, &hitPos)) 
		{
			DrawFormatString(10, 60, 32000, "Ground Hit %f", hitPos.y);
			playerPtr->SetGroundHit(true, hitPos);
		}
		else 
		{
			hitPos = VGet(0.0f, 0.f, 0.f);
			playerPtr->SetGroundHit(false, hitPos);
		}
	}
}