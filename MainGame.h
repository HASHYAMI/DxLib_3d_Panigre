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
	/*メンバ変数*/

public:
	MainGame();
	~MainGame() override;

	//毎F呼ばれる関数
	//オーバーライドメソッド
	void Update() override;

	void Add(Collider* colliderPtr);
	void Remove(Collider* colliderPtr);

	Player* playerPtr;

public:
	int ShadowMapHandle;	//動画ファイルハンドル

	void chk_collision();
};

