#pragma once
#include <DxLib.h>

//関数で使う型をここに定義して整理する


//void FPS(int fps);

//hellper関数
float GetDistance(VECTOR a, VECTOR b) 
{
	return sqrtf((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) + (b.z - a.z) * (b.z - a.z));
}


