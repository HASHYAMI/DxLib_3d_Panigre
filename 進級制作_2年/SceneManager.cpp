#include <vector>

#include "SceneManager.h"	//シーン切り替え

#include "Title.h"			//タイトル
#include "MainGame.h"		//メインゲーム

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
		//シーンの上書き
		std::swap(crrScene, loadScene);
		//タグも変更
		crrSceneTag = loadScene->sceneTag;
		crrScene->nextSceneTagAsync = SceneTag::NotFound;
		//読込データを消去
		delete loadScene;
		//スレッドの開放
		sceneLoadThread.detach();
		//読込ステータスを変更
		atomicLoadState.store(SceneLoadState::Wait);
	}

		//シーン内で遷移指示が来た場合
		if (!(crrScene->nextSceneTag == SceneTag::NotFound ||
			crrScene->nextSceneTag == crrSceneTag))
			SceneChangeSync(crrScene->nextSceneTag);

		//シーン内で非同期を行う指示が来た場合
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

			/*型を元に複製用*/
		//case SceneTag::SceneTag:
		//	delete(crrScene);
		//	crrScene = new SceneNamae();
		//	break;
		}

		//シーンタグを更新
		//crrSceneTag = nextSceneTag;
	}

void SceneManager::SceneChangeAsync(const SceneTag& _nextSceneTag)
{
	if (sceneLoadThread.joinable() || atomicLoadState.load() != SceneLoadState::Wait) return;
	if (_nextSceneTag == crrSceneTag || _nextSceneTag == SceneTag::NotFound) return;
	
	/*-シーン読み込み開始-*/
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