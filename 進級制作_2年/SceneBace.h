#pragma once

#include "Dxlib.h"
#include <math.h>

//#include "SceneManager.h"

enum class SceneTag
{
	Title,
	MainGame,
	Result,
	/*--*/

	/*--*/

	NotFound = -1,
};

enum class SceneLoadState 
{
	/*-�ҋ@��_0-*/
	Wait,
	/*-���[�h��_1-*/
	Loading,
	/*-���[�h����_2-*/
	Completed,
};

class SceneBace 
{
	friend class SceneManager;

protected:
	//�����o�ϐ�
	
	//SceneTag
	SceneTag sceneTag;
	//�J�ڐ�̃V�[���^�O
	SceneTag nextSceneTag;
	/*-�񓯊��œǂݍ��ރV�[���^�O-*/
	SceneTag nextSceneTagAsync;
	/*�R�[���o�b�N�p�̊֐�ID*/
	int callBackId;



	//Menber
	
	//�R���X�g���N�^
	SceneBace() : nextSceneTag(SceneTag::NotFound), nextSceneTagAsync(SceneTag::NotFound)
	{
	}

	//Scene�����ŃV�[���J�ڂ�����
	void SceneChange(const SceneTag _nextSceneTag)
	{
		nextSceneTag = _nextSceneTag;
	}

	void SceneChangeAsync(const SceneTag _nextSceneTag) 
	{
		nextSceneTagAsync = _nextSceneTag;
	}

public:
	//�f�X�g���N�^
	//���z�֐�
	virtual ~SceneBace() {};

	//��F�Ă΂�郁�\�b�h
	//���z�֐�
	virtual void Update() {};

};