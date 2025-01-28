#pragma once

#include <vector>
#include "GameObject.h"
#include "Collider.h"

using namespace std;

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	void Update();
	void Add(Collider* colliderPtr);
	void Remoce(Collider* colliderPtr);
private:
	int colliderID;
	vector<Collider*> colliderVec;
};

