#include "Title.h"

Title::Title() 
{

	sceneTag = SceneTag::Title;

	//デバック用動画Handle
	//PlayMovieToGraph(videoHandle);

	M_Handlel = MV1LoadModel("Assets/test/human.mv1");//ロード

}

Title::~Title() 
{
	/*----------------*/

}

//int Title::UserLocader() 
//{
//	//メモリ開放
//	return 0;
//}

void Title::Update() 
{
	//DrawGraph(0, 0, videoHandle, FALSE);

	int a = MV1DrawModel(M_Handlel);	//モデル描画

	//collisionMgr_Ptr->Update();		//一応

	//確認用
	DrawFormatString(100, 200, GetColor(255, 255, 255), "Scene-Title");
	DrawFormatString(100, 230, GetColor(255, 255, 255), "Key to -R-");
	if (CheckHitKey(KEY_INPUT_R))
		SceneChange(SceneTag::MainGame);

	//chk_Collision_t();		//要らない

}

void Title::chk_Collision_t() 
{

	Player* player_ptr = (Player*)gameobjectVec[0];
	//VECTOR hitPos;
	VECTOR playerPos = player_Ptr->GetPos();
	playerPos.y += 50.f;

	/*if (collision.CheckRaycast(playerPos, player_ptr->GetFoward(), 40.f, &hitPos))
	{

	}*/


}


