#include "Title.h"

Title::Title() 
{
	
	sceneTag = SceneTag::Title;

	//デバック用動画Handle
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

	//確認用
	DrawFormatString(100, 200, GetColor(255, 255, 255), "Scene-Title");
	DrawFormatString(100, 230, GetColor(255, 255, 255), "Key to -R-");
	if (CheckHitKey(KEY_INPUT_R))
		SceneChange(SceneTag::MainGame);

	if ((CheckHitKey(KEY_INPUT_F9)) && CheckHitKey(KEY_INPUT_F10)) 
	{
		isDebugger = true;

		if ((isDebugger == true)) 
		{
			DrawString(100,100,"この入力は開発者の権限を有します", GetColor(255, 0, 0),FALSE);
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


