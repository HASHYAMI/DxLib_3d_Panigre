#pragma once
#include <DxLib.h>

//ŠÖ”‚Åg‚¤Œ^‚ğ‚±‚±‚É’è‹`‚µ‚Ä®—‚·‚é

//void FPS(int fps);

//hellperŠÖ”
float GetDistance(VECTOR a, VECTOR b) 
{
	return sqrtf((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y) + (b.z - a.z) * (b.z - a.z));
}
