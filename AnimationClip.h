#pragma once

#include <string>
#include "DxLib.h"

using namespace std;

typedef struct _AnimationInfo 
{
	int id;
	string fileName;
	bool llopFlag;
}AnimationInfo;

class AnimationClip
{
public:
	AnimationClip();
	~AnimationClip();

	void Load(string filmeName);

	int GetAnimHandle() 
	{
		return animHandle;
	}

	void SetAnimHandle(int handle) 
	{
		animHandle = handle;
	}

	bool GetLoopFlag() 
	{
		return loopFlag;
	}

	void SetLoopFlag(bool flag) 
	{
		loopFlag = flag;
	}

private:
	int animHandle;
	bool loopFlag;

};

