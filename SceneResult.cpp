#include "SceneResult.h"

SceneResult::SceneResult() 
{
	//���s���̃V�[���^�O
	sceneTag = SceneTag::Result;
}

SceneResult::~SceneResult() 
{

}

void SceneResult::Update() 
{
	//�f�o�b�N�m�F�p
	DrawFormatString(100, 200, GetColor(255, 255, 255), "SceeneResult");
	DrawFormatString(100, 250, GetColor(255, 255, 255), "Key to -E-");

	if (CheckHitKey(KEY_INPUT_E))
		SceneChange(SceneTag::Title);
}