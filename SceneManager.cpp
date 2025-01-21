#include <vector>

#include "SceneManager.h"	//�V�[���؂�ւ�

#include "Title.h"			//�^�C�g��
#include "MainGame.h"		//���C���Q�[��

SceneManager::SceneManager() 
{
	crrSceneTag = SceneTag::NotFound;
	atomicLoadState = SceneLoadState::Wait;

	SceneChangeSync(SceneTag::Title);
}

void SceneManager::Update()
{
	crrScene->Update();

	if (atomicLoadState.load() == SceneLoadState::Loading)
	{
		DrawFormatString(100, 300, GetColor(0, 255, 0), "Loading...");
	}

	if (atomicLoadState.load() == SceneLoadState::Completed)
	{
		//�V�[���̏㏑��
		std::swap(crrScene, loadScene);
		//�^�O���ύX
		crrSceneTag = loadScene->sceneTag;
		crrScene->nextSceneTagAsync = SceneTag::NotFound;
		//�Ǎ��f�[�^������
		delete loadScene;
		//�X���b�h�̊J��
		sceneLoadThread.detach();
		//�Ǎ��X�e�[�^�X��ύX
		atomicLoadState.store(SceneLoadState::Wait);
	}

		//�V�[�����őJ�ڎw���������ꍇ
		if (!(crrScene->nextSceneTag == SceneTag::NotFound ||
			crrScene->nextSceneTag == crrSceneTag))
			SceneChangeSync(crrScene->nextSceneTag);

		//�V�[�����Ŕ񓯊����s���w���������ꍇ
		if (!(crrScene->nextSceneTagAsync == SceneTag::NotFound ||
			crrScene->nextSceneTagAsync == crrSceneTag))
			SceneChangeAsync(crrScene->nextSceneTagAsync);
}

void SceneManager::SceneChangeSync(const SceneTag& _nextSceneTag)
{
	if (_nextSceneTag == crrSceneTag || _nextSceneTag == SceneTag::NotFound)
		return;

	const SceneTag nextSceneTag = _nextSceneTag;

	if (crrScene != nullptr)
		delete (crrScene);

		switch (nextSceneTag)
		{
		case SceneTag::Title:
			crrScene = new Title();
			break;
		case SceneTag::MainGame:
			crrScene = new MainGame();
			break;
		case SceneTag::Result:
			crrScene = new SceneResult();
			break;

			/*�^�����ɕ����p*/
		//case SceneTag::SceneTag:
		//	delete(crrScene);
		//	crrScene = new SceneNamae();
		//	break;
		}

		//�V�[���^�O���X�V
		//crrSceneTag = nextSceneTag;
	}

void SceneManager::SceneChangeAsync(const SceneTag& _nextSceneTag)
{
	if (sceneLoadThread.joinable() || atomicLoadState.load() != SceneLoadState::Wait) return;
	if (_nextSceneTag == crrSceneTag || _nextSceneTag == SceneTag::NotFound) return;
	
	/*-�V�[���ǂݍ��݊J�n-*/
	sceneLoadThread = std::thread(&SceneManager::SceneLoad, this, _nextSceneTag);
}

void SceneManager::SceneLoad(const SceneTag& _nextSceneTag) 
{
	atomicLoadState.store(SceneLoadState::Loading);

	const SceneTag nextSceneTag = _nextSceneTag;

	switch (nextSceneTag)
	{
	case SceneTag::Title:
		loadScene = new Title();
		break;
	case SceneTag::MainGame:
		loadScene = new MainGame();
		break;
	case SceneTag::Result:
		loadScene = new SceneResult();
		break;
	}

	atomicLoadState.store(SceneLoadState::Completed);
}