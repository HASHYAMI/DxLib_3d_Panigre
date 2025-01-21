#include "Weapon.h"
#include "Define.h"

Weapon::Weapon() 
{

	MHandle = MV1LoadModel("Assets/Weapon's/SAM_Blead.mv1");
    int a = MHandle;

#if 1
	colliderType = Collider::CAPSULE_TYPE;
	radius = 10.f;
	tag_name = "Weapon";
	name = "weapon";

#else
    int frameIndex = MV1SearchFrame(MHandxle, "Sword");
    int meshIndex = MV1GetFrameMesh(MHandle, frameIndex, 0);
    localBoxMaxPos = MV1GetMeshMaxPosition(MHandle, meshIndex);
    localBoxMinPos = MV1GetMeshMinPosition(MHandle, meshIndex);

    int ColliderMHandle = MV1LoadModel("Assets/Collider/Weapon_BoxCollider.mv1");
    frameIndex = MV1SearchFrame(ColliderMHandle, "Weapn_BoxCollider");
    meshIndex = MV1GetFrameMesh(ColliderMHandle, frameIndex, 0);
    localBoxMaxPos = MV1GetMeshMaxPosition(ColliderMHandle, meshIndex);
    localBoxMinPos = MV1GetMeshMinPosition(ColliderMHandle, meshIndex);
    localBoxMinPos.x *= 150.f;
    localBoxMinPos.y *= 150.f;
    localBoxMinPos.z *= 150.f;
    minPos.x = localBoxMinPos.x;
    minPos.z = localBoxMinPos.y;
    minPos.y = localBoxMinPos.z;

    localBoxMaxPos.x *= 150.f;
    localBoxMaxPos.y *= 150.f;
    localBoxMaxPos.z *= 150.f;
    maxPos.x = localBoxMaxPos.x;
    maxPos.z = localBoxMaxPos.y;
    maxPos.y = localBoxMaxPos.z;
    localBoxMinPos = minPos;
    localBoxMaxPos = maxPos;

#endif

#if 1
    int index = MV1SearchFrame(MHandle, "sword_top");
    orgStartPos = MV1GetFramePosition(MHandle, index);
    index = MV1SearchFrame(MHandle, "sowrd_midlle");
    orgEndPos = MV1GetFramePosition(MHandle, index);
#else
    int index = MV1SearchFrame(MHandle, "sword_top");
    colliderType = Collider::BOX_TYPE;
    tag_name = "weapon";

#endif
}

Weapon::~Weapon() 
{
	
}

void Weapon::Update() 
{
    MATRIX matrix = MV1GetMatrix(MHandle);
#if 1
    StartPos = VTransform(orgStartPos, matrix);
    EndPos = VTransform(orgEndPos, matrix);
    DrawCapsule3D(StartPos, EndPos, 10.f, 32, GetColor(0, 0, 255), GetColor(0, 0, 255), FALSE);

    MV1DrawModel(MHandle);
#else
    minPos = localBoxMinPos;
    minPos.x += 50.f;
    maxPos = localBoxMaxPos;
    maxPos.x += 50.f;

    minPos = VTransform(minPos, matrix);
    maxPos = VTransform(maxPos, matrix);
    DrawLine3D(minPos, maxPos, GetColor(255, 255, 0));
#endif
    Draw();
}

void Weapon::Draw() 
{
	MV1DrawModel(MHandle);
}

void Weapon::OnCollisionHit(Collider* colliderPtr, GameObject* gobjPtr) 
{
	if (gobjPtr ->tag_name.compare("Player"))
	{
		int a = 0;
		a += 1;
	}
}