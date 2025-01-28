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
	/*-待機中_0-*/
	Wait,
	/*-ロード中_1-*/
	Loading,
	/*-ロード完了_2-*/
	Completed,
};

class SceneBace 
{
	friend class SceneManager;

protected:
	//メンバ変数
	
	//SceneTag
	SceneTag sceneTag;
	//遷移先のシーンタグ
	SceneTag nextSceneTag;
	/*-非同期で読み込むシーンタグ-*/
	SceneTag nextSceneTagAsync;
	/*コールバック用の関数ID*/
	int callBackId;



	//Menber
	
	//コンストラクタ
	SceneBace() : nextSceneTag(SceneTag::NotFound), nextSceneTagAsync(SceneTag::NotFound)
	{
	}

	//Scene内部でシーン遷移をする
	void SceneChange(const SceneTag _nextSceneTag)
	{
		nextSceneTag = _nextSceneTag;
	}

	void SceneChangeAsync(const SceneTag _nextSceneTag) 
	{
		nextSceneTagAsync = _nextSceneTag;
	}

public:
	//デストラクタ
	//仮想関数
	virtual ~SceneBace() {};

	//毎F呼ばれるメソッド
	//仮想関数
	virtual void Update() {};

};