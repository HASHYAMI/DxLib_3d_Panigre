#pragma once
#include <DxLib.h>

//�֐��Ŏg���^�������ɒ�`���Đ�������

//void FPS(int fps);

//hellper�֐�
float GetDistance(VECTOR a, VECTOR b) 
{
	return sqrtf((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) + (b.z - a.z) * (b.z - a.z));
}
