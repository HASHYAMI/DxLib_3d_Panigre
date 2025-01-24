#include "Weapon.h"
#include "Define.h"

Weapon::Weapon() 
{

	MHandle = MV1LoadModel("Assets/Weapon's/CreataPoint_Middle_2nd_SAM_Blead.mv1");

    //コライダー定義
    W_colStartPos = 0;
    W_colEndPos = 0;
    W_radius = 0;

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
    int index = MV1SearchFrame(MHandle, "Top");
    orgStartPos = MV1GetFramePosition(MHandle, index);
    index = MV1SearchFrame(MHandle, "Midlle");
    int index_2 = MV1SearchFrame(MHandle, "Midlle");
    orgEndPos = MV1GetFramePosition(MHandle, index);


    ///*書き直し*/
    //int index_1 = MV1SearchFrame(MHandle, "Top");        //TOPのフレームインデックス
    //int index_2 = MV1SearchFrame(MHandle, "Middle");    //Middleのフレームインデックス
    //int index_3 = MV1SearchFrame(MHandle, "Middle_2");  //Middle_2ndのフレームインデックス
    //int index_4 = MV1SearchFrame(MHandle, "Under");     //Underのフレームインデックス

    //orgStartPos = MV1GetFramePosition(MHandle, index_1);//TopからMiddleまでのコライダー
    //EndPos = MV1GetFramePosition(MHandle, index_2);     //          "  "
    //orgStartPos = MV1GetFramePosition(MHandle, index_2);//MiddleからMiddle_2ndまでのコライダー
    //EndPos = MV1GetFramePosition(MHandle, index_3);     //          "  " 


#else
    int index = MV1SearchFrame(MHandle, "Top");
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

    //
    // コライダー描画
    //
    DrawCapsule3D(MV1GetFramePosition(MHandle, W_colStartPos), MV1GetFramePosition(MHandle, W_colEndPos), radius,
        6, GetColor(0, 255, 0), GetColor(255, 0, 0), FALSE);

    Draw();
}

void Weapon::Draw() 
{
	MV1DrawModel(MHandle);
}

void Weapon::OnCollisionHit(Collider* colliderPtr, GameObject* gobjPtr) 
{
    //
	if (gobjPtr ->tag_name.compare("Player"))
	{
		int a = 0;
		a += 1;
	}
}