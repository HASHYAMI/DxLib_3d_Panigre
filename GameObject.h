#pragma once

#include <string>
#include "DxLib.h"

using namespace std;

class GameObject
{
public:
	VECTOR trans;
	VECTOR rotation;
	VECTOR scale;
	bool visible;
	string name;
	string tag_name;

	GameObject() 
	{
		visible = true;
	}

	~GameObject() 
	{
	}
		void Transform(int handle);

		MATRIX GetMatrix() 
		{
			return matrix;
		}

		VECTOR Getforward()
		{
			return forward;
		}

		VECTOR GetLeft() {
			return Left;
		}
		
		VECTOR GetRight() 
		{
			return Right;
		}

		void SetVisible(bool flag) 
		{
			visible = flag;
		}

		virtual void Update() = 0;		//âºëzä÷êî
		virtual void Draw() = 0;

protected:
	MATRIX matrix;
	VECTOR forward;
	VECTOR Left;
	VECTOR Right;
};

