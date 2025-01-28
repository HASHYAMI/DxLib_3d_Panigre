#pragma once

//#define CAMERA_H
#define CAMERA_H

#include "DxLib.h"

class Camera
{
private:
	VECTOR position;	//�|�W�V����
	VECTOR target;		//�^�[�Q�b�g
	VECTOR rotation;	//�J������]

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

