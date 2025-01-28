#pragma once

#include "SceneBace.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "GameObject.h"
#include "Player.h"
#include "Animator.h"

class Title : public SceneBace
{
	VECTOR cameraPos;
	VECTOR LookAtPos;

	vector<GameObject*> gameobjectVec;
	
	Player player;
	
	int T_Handle;

public:

	Title();
	~Title() override;
	
	void Update() override;

	int PlayerHandle;

	VECTOR camera_Pos;

private:

	int res_Handle;

	int videoHandle = LoadGraph("Assets/mp4/Zilaffe25fps.mp4");		//Šm”F—p

	bool isDebugger;

};

