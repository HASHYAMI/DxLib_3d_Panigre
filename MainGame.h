#pragma once

#include "SceneBace.h"
#include "Scene.h"
#include "Player.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "GameObject.h"

class MainGame : public SceneBace
{
	VECTOR cameraPos;
	VECTOR lookAtPos;

	vector<GameObject*> gameObjectVec;
	int mapMHandle;
	vector<int>mapCubeFrameIndexVec;
	Collision collision;

	CollisionManager* collsionManagerPtr;

private:
	/*�����o�ϐ�*/

public:
	MainGame();
	~MainGame() override;

	//��F�Ă΂��֐�
	//�I�[�o�[���C�h���\�b�h
	void Update() override;

	void Add(Collider* colliderPtr);
	void Remove(Collider* colliderPtr);

	Player* playerPtr;

public:
	int ShadowMapHandle;	//����t�@�C���n���h��

	void chk_collision();
};

