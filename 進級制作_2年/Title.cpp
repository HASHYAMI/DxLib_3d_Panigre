#include "Title.h"

Title::Title() 
{
	
	sceneTag = SceneTag::Title;

	//�f�o�b�N�p����Handle
	PlayMovieToGraph(videoHandle);

	isDebugger = false;

}

Title::~Title() 
{
	/*----------------*/

	/*----------------*/

}

void Title::Update() 
{	

	//�m�F�p
	DrawFormatString(100, 200, GetColor(255, 255, 255), "Scene-Title");
	DrawFormatString(100, 230, GetColor(255, 255, 255), "Key to -R-");
	if (CheckHitKey(KEY_INPUT_R))
		SceneChange(SceneTag::MainGame);

	if ((CheckHitKey(KEY_INPUT_F9)) && CheckHitKey(KEY_INPUT_F10)) 
	{
		isDebugger = true;

		if ((isDebugger == true)) 
		{
			DrawString(100,100,"���̓��͂͊J���҂̌�����L���܂�", GetColor(255, 0, 0),FALSE);
		}
		else if (CheckHitKey(KEY_INPUT_F9) && CheckHitKey(KEY_INPUT_F10)) 
		{
			isDebugger = false;
		}
	}

	if (CheckHitKey(KEY_INPUT_SPACE) && 1) 
	{
		SetMouseDispFlag(FALSE);
	}
	else if (CheckHitKey(KEY_INPUT_SPACE) && 0) 
	{
		SetMouseDispFlag(TRUE);
	}
}


