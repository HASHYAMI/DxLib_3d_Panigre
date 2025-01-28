#pragma once

#include "SceneBace.h"

class SceneResult : public SceneBace
{
private :
	//メンバ変数
public:
	//メソッド

	//コンストラクタ
	SceneResult();
	//デストラクタ
	~SceneResult() override;

	//毎フレーム呼ばれる関数
	//オーバーライドメソッド
	void Update() override;
};

