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
	/*-メンバ変数-*/

	/*-実行中のシーンタグ-*/
	SceneTag crrSceneTag;
	/*-実行中のシーンのインスタンス-*/
	SceneBace* crrScene;

	/*-非同期処理を行うスレッド-*/
	std::thread sceneLoadThread;
	/*-ロードが完了しているか-*/
	std::atomic<SceneLoadState>atomicLoadState;
	/*-非同期で読み込んだシーンのインスタンス-*/
	SceneBace* loadScene;


public:

	//メンバ変数
	void FPS(int fps);

	//シングルトンインスタンスを取得する

	static SceneManager& Instance() 
	{
		static SceneManager* instance = new SceneManager();
		return *instance;
	}

	//実行中のシーンタグを取得
	const SceneTag& GetCrrSceneTag() const { return crrSceneTag; }

	/*--*/
	void Update();
	
	void SceneChangeSync(const SceneTag& _nextSceneTag);

	/*--*/
	void SceneChangeAsync(const SceneTag& _nextSceneTag);

private:
	/*-シーン読み込み-*/
	void SceneLoad(const SceneTag& _nextSceneTag);
	
	//明示的に消去
	SceneManager();
};

