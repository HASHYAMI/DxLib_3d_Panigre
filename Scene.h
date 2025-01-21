#pragma once

#include <vector>
#include <string>

#include "Dxlib.h"

using namespace std;

class Scene
{
private :
	string scene_change_name;
public:
	int scene_id;
	string scene_name;
	int frame_counter;

	Scene();
	virtual ~Scene() = 0;
	virtual void Update() = 0;

	string sceneSruveillance();
	void SceneChange(string scene_name);
};

