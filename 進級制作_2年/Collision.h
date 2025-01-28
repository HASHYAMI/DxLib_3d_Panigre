#pragma once

#include "Dxlib.h"
#include <string>
#include <vector>

using namespace std;

typedef struct _CollisionRect 
{
	VECTOR min_pos;
	VECTOR max_pos;
} CollisioRect;

typedef struct _CollisionNode 
{
	int frameIndex;		//�t���[���C���f�b�N�X
	string name;		//�m�[�h��
	bool visible;		//�q���W������������邩�ǂ���
	bool static_node;	//���W�ϊ��𖈃t���[�����{���邩�ǂ���
} CollisionNode;

class Collision
{
private:
	string nodeName;
	int modeleHandle;
	vector<CollisionNode*> colFrameVec;
	vector<CollisionNode*> colWallFrameVec;

	void traverse(int parent_index, string root_name);

public:

	Collision();
	~Collision();

	void SetName(string node_name) 
	{
		nodeName = node_name;
	}

	bool CheckAABB_AABB(_CollisionRect rect1, CollisioRect rect2);
	bool CheckRectPoint(_CollisionRect rect, VECTOR pos);
	bool CheckRaycast(VECTOR startPos, VECTOR foward, const float ray_cast_lenght, VECTOR* hitpos);

	void SetModeHandle(int handle);

	static void DrawRect(_CollisionRect rect1) 
	{
		float X = rect1.max_pos.x - rect1.min_pos.x;
		float Y = rect1.max_pos.y - rect1.min_pos.y;
		float Z = rect1.max_pos.z - rect1.min_pos.z;

		VECTOR pos1 = VGet(rect1.min_pos.x + X, rect1.min_pos.y, rect1.min_pos.z);
		VECTOR Pos2 = VGet(rect1.min_pos.x, rect1.min_pos.y, rect1.min_pos.z);

		DrawLine3D(rect1.min_pos, rect1.max_pos, GetColor(255, 0, 0));
		DrawLine3D(rect1.min_pos, pos1, (255, 0, 0));
		DrawLine3D(Pos2, rect1.max_pos, GetColor(255, 0, 0));

		pos1 = VGet(rect1.min_pos.x, rect1.min_pos.y, rect1.min_pos.z);
		DrawLine3D(rect1.min_pos, pos1, GetColor(255, 0, 0));

		Pos2 = VGet(rect1.max_pos.x, rect1.max_pos.y, rect1.max_pos.z);
		DrawLine3D(Pos2, rect1.max_pos, GetColor(255, 0, 0));
	}

};

