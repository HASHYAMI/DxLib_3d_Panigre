#include "Animator.h"

Animator::Animator() 
{
	playTime = 0.f;
	playSpeed = 1.0f;
	totalTime = 0.f;
	attachIndex = 0;
	platAnimId = -1;
}

Animator::~Animator()
{
	animClipVec.clear();
	animClipVec.shrink_to_fit();
}

void Animator::CreateAnimInstance(Animator* scrAnimetor) 
{
	vector<AnimationClip*>scrAnimClip = scrAnimetor->GetAnimationClips();

	vector<AnimationClip*>::iterator it = scrAnimClip.begin();
	while (it != scrAnimClip.end())
	{	
		AnimationClip* clipPtr = *it;

		AnimationClip* instanceClipPtr = new AnimationClip();
		int AnimHandle = MV1DuplicateModel(clipPtr->GetAnimHandle());
		instanceClipPtr->SetAnimHandle(AnimHandle);
		instanceClipPtr->SetLoopFlag(clipPtr->GetLoopFlag());

		animClipVec.push_back(instanceClipPtr);
		++it;

	}
}

void Animator::Load(vector <AnimationInfo> animInfo) 
{
	for (int i = 0; i < animInfo.size(); i++) 
	{
		AnimationClip* animClipPtr = new AnimationClip();
		animClipPtr->SetLoopFlag(animInfo[i].llopFlag);
		animClipPtr->Load(animInfo[i].fileName);
		animClipVec.push_back(animClipPtr);
	}	
}

void Animator::Play(int Mhandle, int anim_id) 
{
	if (platAnimId != anim_id)
	{
		modelHandle = Mhandle;

		if (playStatus == ANIM_PLAY || playStatus == ANIM_PLAY_NEUTRAL)
		{
			playStatus = ANIM_PLAY_START;
			MV1DetachAnim(modelHandle, attachIndex2);

			if (!blendleAnim) 
			{
				//アニメーションファイルが分割ロードされて場合のアニメーションアタッチ
				attachIndex = MV1AttachAnim(modelHandle, 0, animClipVec[anim_id]->GetAnimHandle());
			}
			totalTime = MV1GetAttachAnimTotalTime(modelHandle, attachIndex);
			playStatus = ANIM_PLAY;
			playTime;

			MV1DetachAnim(modelHandle, attachIndex);
			attachIndex = MV1AttachAnim(modelHandle, 0, animClipVec[anim_id]->GetAnimHandle());
		}
	}
	else
	{
		playStatus = ANIM_PLAY_START;
	}

	playAnimHandle = animClipVec[anim_id]->GetAnimHandle();
	platAnimId = anim_id;
	playloop = animClipVec[anim_id]->GetLoopFlag();
}

bool Animator::Update() 
{
	bool result = true;
	switch (playStatus)
	{
	case ANIM_MOTION_BLEND_START:
		attachIndex2 = MV1AttachAnim(modelHandle, 0, playAnimHandle);
		blendRate = 0.0f;
		playStatus = 0.0f;
		playStatus = ANIM_MOTION_BLEND_PLAY;
		MV1SetAttachAnimBlendRate(modelHandle, attachIndex, 1.0f - blendRate);
		MV1SetAttachAnimBlendRate(modelHandle, attachIndex2, blendRate);
		break;

	case ANIM_MOTION_BLEND_PLAY:
		blendRate += 0.1f;
		if (blendRate >= 1.0f) {
			MV1SetAttachAnimBlendRate(modelHandle, attachIndex, 1.0f - blendRate);
			MV1SetAttachAnimBlendRate(modelHandle, attachIndex2, blendRate);
			MV1DetachAnim(modelHandle, attachIndex);
			playStatus = ANIM_PLAY;
			playTime = 0.0f;
			attachIndex = attachIndex2;
			totalTime = MV1GetAttachAnimTotalTime(modelHandle, attachIndex);
			break;

		}

		MV1SetAttachAnimBlendRate(modelHandle, attachIndex, 1.0f - blendRate);
		MV1SetAttachAnimBlendRate(modelHandle, attachIndex2, blendRate);
		break;

	case ANIM_PLAY_START:
		MV1DetachAnim(modelHandle, attachIndex);
		attachIndex = MV1AttachAnim(modelHandle, 0, playAnimHandle);
		totalTime = MV1GetAttachAnimTotalTime(modelHandle, attachIndex);
		playStatus = ANIM_PLAY;
		playTime = 0.0f;
		break;

	case ANIM_PLAY:
		if (playTime >= totalTime) {
			if (playloop == false) {
				playStatus = ANIM_PLAY_NEUTRAL;
				break;
			}
		}
		playTime += 1.0f;
		if (playTime > totalTime) {
			playTime = 0.0f;
		}

		MV1SetAttachAnimTime(modelHandle, attachIndex, playTime);
		break;

	case ANIM_PLAY_NEUTRAL:
		Play(modelHandle, 0);
		result = false;
		break;
	}

	return result;

}

float Animator::GetPlayTime() 
{
	return playTime;
}

void Animator::SetPlaySpeed(float speed) 
{
	playSpeed = speed;
}