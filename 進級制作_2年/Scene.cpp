#include "Scene.h"
#include "SceneManager.h"

Scene::Scene() 
{
	scene_id = 0;
	scene_name = "";
	scene_change_name = "";

	frame_counter = 0;

}

Scene::~Scene() 
{
	//-�����͎̂Ă�G�t�F�N�g���L�����肷��ꍇ�ɋL��-
}
void Scene::SceneChange(string name) 
{
	//scene_change_name = name;
}

string Scene::sceneSruveillance() 
{
	//if (scene_change_name != "")
	//{
	//	if (scene_name != scene_name) {
	//		string name = scene_change_name;
	//		scene_change_name = "";
	//		return name;
	//	}
	//}
	return scene_change_name;

}