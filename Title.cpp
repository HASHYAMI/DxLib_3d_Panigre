#include "Title.h"

Title::Title() 
{

	sceneTag = SceneTag::Title;

	//�f�o�b�N�p����Handle
	//PlayMovieToGraph(videoHandle);

	M_Handlel = MV1LoadModel("Assets/test/human.mv1");//���[�h

}

Title::~Title() 
{
	/*----------------*/

}

//int Title::UserLocader() 
//{
//	//�������J��
//	return 0;
//}

void Title::Update() 
{
	//DrawGraph(0, 0, videoHandle, FALSE);

	int a = MV1DrawModel(M_Handlel);	//���f���`��

	//collisionMgr_Ptr->Update();		//�ꉞ

	//�m�F�p
	DrawFormatString(100, 200, GetColor(255, 255, 255), "Scene-Title");
	DrawFormatString(100, 230, GetColor(255, 255, 255), "Key to -R-");
	if (CheckHitKey(KEY_INPUT_R))
		SceneChange(SceneTag::MainGame);

	//chk_Collision_t();		//�v��Ȃ�

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


