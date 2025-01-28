#include "Camera.h"
#include "Player.h"

Camera::Camera() :position(VGet(0.0f, 0.0f, 0.0f)),
target(VGet(0.0f, 0.0f, 0.0f)),
rotation(VGet(0.0f, 0.0f, 0.0f))
{
}

Camera::~Camera() {}
void Camera::Initalize(VECTOR initTarget, float initLenght)
{
	target = initTarget;
}

void Camera::Update(VECTOR playerPosition)
{
	target = playerPosition;
	Apply();
}

void Camera::ProcessInput()
{
	if (CheckHitKey(KEY_INPUT_LEFT) == 1)
		rotation.y -= DX_PI / 180;

	if (CheckHitKey(KEY_INPUT_RIGHT) == 1)
	{
		//1度->(π / 180)ラジアン
		//1ラジアン-> (180 / π)度
		rotation.y += DX_PI / 180;
	}

	if (CheckHitKey(KEY_INPUT_UP) == 1)
		rotation.x -= DX_PI / 180;

	if (CheckHitKey(KEY_INPUT_DOWN) == 1)
		rotation.x += DX_PI / 180;
}

void Camera::Apply() 
{
	position = VAdd(target, VGet(0, 500, -700));

	SetCameraPositionAndAngle(position, rotation.x, rotation.y, 0.0f);
}

VECTOR Camera::GetPosition() const 
{
	return position;
}

VECTOR Camera::GetTarget() const 
{
	return target;
}