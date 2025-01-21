#pragma once

#include "SceneBace.h"
#include "Player.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "GameObject.h"

class Title : public SceneBace
{
	VECTOR cameraPos;
	VECTOR LookAtPos;

	vector<GameObject*> gameobjectVec;
	

	int M_Handlel;
	Collision collision;
	CollisionManager* collisionMgr_Ptr;

public:

	Title();
	~Title() override;
	
	//int UserLocader();	//Scene�̃������J���p�֐�
	void Update() override;
	void Add(Collider* colliderPtr);
	void Remove(Collider* colliderPtr);

	//void Draw();		//���f���`��p

	int PlayerHandle;

	VECTOR camera_Pos;
	VECTOR player_pos;
	Player* player_Ptr;

private:
	int res_Handle;

	int videoHandle = LoadGraph("Assets/.mp4/Zilaffe25fps.mp4");		//�m�F�p

	void chk_Collision_t();
};

