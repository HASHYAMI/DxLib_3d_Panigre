#pragma once

#include "Scene.h"			// -No Make-

#include "MainGame.h"
#include "Title.h"
#include "SceneResult.h"

#include <atomic>
#include <thread>

class SceneManager
{
private:
	/*-�����o�ϐ�-*/

	/*-���s���̃V�[���^�O-*/
	SceneTag crrSceneTag;
	/*-���s���̃V�[���̃C���X�^���X-*/
	SceneBace* crrScene;

	/*-�񓯊��������s���X���b�h-*/
	std::thread sceneLoadThread;
	/*-���[�h���������Ă��邩-*/
	std::atomic<SceneLoadState>atomicLoadState;
	/*-�񓯊��œǂݍ��񂾃V�[���̃C���X�^���X-*/
	SceneBace* loadScene;


public:

	//�����o�ϐ�
	void FPS(int fps);

	//�V���O���g���C���X�^���X���擾����

	static SceneManager& Instance() 
	{
		static SceneManager* instance = new SceneManager();
		return *instance;
	}

	//���s���̃V�[���^�O���擾
	const SceneTag& GetCrrSceneTag() const { return crrSceneTag; }

	/*--*/
	void Update();
	
	void SceneChangeSync(const SceneTag& _nextSceneTag);

	/*--*/
	void SceneChangeAsync(const SceneTag& _nextSceneTag);

private:
	/*-�V�[���ǂݍ���-*/
	void SceneLoad(const SceneTag& _nextSceneTag);
	
	//�����I�ɏ���
	SceneManager();
};

