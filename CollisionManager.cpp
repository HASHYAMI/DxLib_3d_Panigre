#include "CollisionManager.h"
#include "Collision.h"

CollisionManager::CollisionManager() 
{

}

CollisionManager::~CollisionManager() 
{

}

void CollisionManager::Add(Collider* colliderPtr) 
{
	vector<Collider*>::iterator it = colliderVec.begin();
	while (it != colliderVec.end())
	{
		Collider* colPtr = *it;
		if (colPtr->colliderID == colliderPtr->colliderID) 
		{
			colliderVec.erase(it);
			break;
		}
		++it;
	}
	
}

void CollisionManager::Update() 
{
	for (int i = 0; i < colliderVec.size(); i++) {
		// 球と球で当たり判定する
		if (colliderVec[i]->colliderType == Collider::SPEHERE_TYPE) {
			SphereCollider* colliderPtr = (SphereCollider*)colliderVec[i];
			VECTOR center1 = VAdd(colliderPtr->GetGameObject()->trans, colliderPtr->offset);
			DrawSphere3D(center1, colliderPtr->radius, 32, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);

			for (int j = i + 1; j < colliderVec.size(); j++) {
				SphereCollider* colliderPtr2 = (SphereCollider*)colliderVec[j];
				VECTOR center2 = VAdd(colliderVec[j]->GetGameObject()->trans, colliderPtr2->offset);
				DrawSphere3D(center2, colliderPtr2->radius, 32, GetColor(255, 0, 0), GetColor(255, 0, 0), FALSE);

				if (HitCheck_Sphere_Sphere(center1, colliderPtr->radius, center2, colliderPtr2->radius)) {
					// ヒット時のコールバック関数呼び出し
					// ヒットしたオブジェクトのGameObjectとColliderを渡す
					colliderPtr->OnCollisionHit(colliderVec[j], colliderVec[j]->GetGameObject());
					colliderVec[j]->OnCollisionHit(colliderPtr, colliderPtr->GetGameObject());
				}
			}
		}

		// カプセルとカプセルで当たり判定する
		if (colliderVec[i]->colliderType == Collider::CAPSULE_TYPE) {
			CapsuleCollider* colliderPtr = (CapsuleCollider*)colliderVec[i];
			DrawCapsule3D(colliderPtr->StartPos, colliderPtr->EndPos, colliderPtr->radius, 32, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);

			for (int j = i + 1; j < colliderVec.size(); j++) {
				CapsuleCollider* colliderPtr2 = (CapsuleCollider*)colliderVec[j];
				DrawCapsule3D(colliderPtr2->StartPos, colliderPtr2->EndPos, colliderPtr2->radius, 32, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);

				if (HitCheck_Capsule_Capsule(colliderPtr->StartPos, colliderPtr->EndPos, colliderPtr->radius,
					colliderPtr2->StartPos, colliderPtr2->EndPos, colliderPtr2->radius)) {
					// ヒット時のコールバック関数呼び出し
					// ヒットしたオブジェクトのGameObjectとColliderを渡す
					colliderPtr->OnCollisionHit(colliderVec[j], colliderVec[j]->GetGameObject());
					colliderVec[j]->OnCollisionHit(colliderPtr, colliderPtr->GetGameObject());
				}
			}
		}

		// 箱と箱で当たり判定する
		if (colliderVec[i]->colliderType == Collider::BOX_TYPE) {
			Collision collision;
			_CollisionRect rect1, rect2;
			BoxCollider* colliderPtr = (BoxCollider*)colliderVec[i];
			rect1.min_pos = colliderPtr->minPos;
			rect1.max_pos = colliderPtr->maxPos;

			for (int j = i + 1; j < colliderVec.size(); j++) {
				BoxCollider* colliderPtr2 = (BoxCollider*)colliderVec[j];
				rect2.min_pos = colliderPtr2->minPos;
				rect2.max_pos = colliderPtr2->maxPos;
				DrawLine3D(rect2.min_pos, rect2.max_pos, GetColor(255, 255, 0));

				if (collision.CheckAABB_AABB(rect1, rect2)) {
					// ヒット時のコールバック関数呼び出し
					// ヒットしたオブジェクトのGameObjectとColliderを渡す
					colliderPtr->OnCollisionHit(colliderVec[j], colliderVec[j]->GetGameObject());
					colliderVec[j]->OnCollisionHit(colliderPtr, colliderPtr->GetGameObject());
				}
			}
		}
	}
}