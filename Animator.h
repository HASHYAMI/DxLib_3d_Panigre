#pragma once
#include <vector>
#include "AnimationClip.h"
#include "DxLib.h"

#define ANIM_PLAY_START (1)
#define ANIM_PLAY (2)
#define ANIM_PLAY_NEUTRAL (3)
#define ANIM_MOTION_BLEND_START (4)
#define ANIM_MOTION_BLEND_PLAY (5)

class Animator
{
public:
	Animator();
	~Animator();

	void Load(vector <AnimationInfo> animInfo);
	void Play(int MHandle, int anim_id);
	bool Update();

	float GetPlayTime();
	void SetPlaySpeed(float speed);

	void SetAnimationClip(AnimationClip* clip_ptr) 
	{
		animClipVec.push_back(clip_ptr);
	}

	vector<AnimationClip*> GetAnimationClips() 
	{
		return animClipVec;
	}

	void CreateAnimInstance(Animator* scrAnimator);

private:
	vector <AnimationClip*> animClipVec;

	float playTime;
	float playSpeed;
	float totalTime;
	bool loopFlag;
	int attachIndex;
	int attachIndex2;
	int platAnimId;
	int modelHandle;
	int playAnimHandle;

	float blendRate;
	int playStatus;		//çƒê∂èÛë‘
	bool playloop;

	bool blendleAnim;
};

