#pragma once

//#define CAMERA_H
#define CAMERA_H

#include "DxLib.h"

class Camera
{
private:
	VECTOR position;	//ポジション
	VECTOR target;		//ターゲット
	VECTOR rotation;	//カメラ回転

public:
	Camera();
	~Camera();

	void Initalize(VECTOR initTarget, float initLenght);
	void Update(VECTOR playerPosition);
	void ProcessInput();
	void Apply();

	VECTOR GetPosition() const;
	VECTOR GetTarget() const;

};

