#include "Collision.h"

Collision::Collision() 
{
	
}

Collision::~Collision() 
{

}

bool Collision::CheckAABB_AABB(_CollisionRect rect1, _CollisionRect rect2) 
{
	if ((rect1.min_pos.x <= rect2.max_pos.x && rect1.max_pos.x >= rect2.min_pos.x) &&
		(rect1.min_pos.y <= rect2.max_pos.y && rect1.max_pos.y >= rect2.min_pos.y) &&
		(rect1.min_pos.z <= rect2.max_pos.z && rect1.max_pos.z >= rect2.min_pos.z))
		return true;{

	}
	return false;
}

void Collision::SetModeHandle(int handle)
{
	modeleHandle = handle;

	// 地面の当たり判定用を想定
	int root_index = MV1SearchFrame(modeleHandle, "map_root");
	traverse(root_index, "map_root");

	// 壁などの横から当たる判定用を想定
	MV1SetupReferenceMesh(handle, 0, TRUE);
	root_index = MV1SearchFrame(modeleHandle, "map");
	traverse(root_index, "map");
}

/**
* @brief マップノードの階層を辿り、コリジョン判定用のノードを判別する
* @param[in] parent_index（コリジョン判定するルートノード）
* @param[out] なし
* @return なし
* @details Playerのフレーム毎処理更新処理
*/
void Collision::traverse(int parent_index, string root_name)
{
	// parent_indexで指定されたノードが持つ子ノード数を取得
	int num_of_child = MV1GetFrameChildNum(modeleHandle, parent_index);
	for (int i = 0; i < num_of_child; i++) {
		int index = MV1GetFrameChild(modeleHandle, parent_index, i);

		// メッシュ数が0以上なら、頂点が存在するノードなので、当たり判定ノードとしてvector配列に登録
		if (MV1GetFrameMeshNum(modeleHandle, index) > 0) {
			if (MV1SetupReferenceMesh(modeleHandle, index, TRUE) == 0) {	// DXライブラリにメッシュ参照用ノードとして指示しておく
				// ここでフレーム（ノード）indexを記録しておく
				if (root_name == "map_root") {
					CollisionNode* colNodePtr = new CollisionNode();
					colNodePtr->frameIndex = index;
					colNodePtr->name = MV1GetFrameName(modeleHandle, index);
					colNodePtr->visible = true;
					if (colNodePtr->name.find("Static_") != std::string::npos) {
						colNodePtr->static_node = true;
					}

					colFrameVec.push_back(colNodePtr);
				}
				else if (root_name == "map") {
					CollisionNode* colNodePtr = new CollisionNode();
					colNodePtr->frameIndex = index;
					colNodePtr->name = MV1GetFrameName(modeleHandle, index);
					colNodePtr->visible = true;
					if (colNodePtr->name.find("Static_") != std::string::npos) {
						colNodePtr->static_node = true;
					}

					colWallFrameVec.push_back(colNodePtr);
				}
			}
		}

		// 子ノード数を取得
		int num_of_child = MV1GetFrameChildNum(modeleHandle, index);

		// 再帰コールで階層を辿る
		traverse(index, root_name);
	}
}

bool Collision::CheckRaycast(VECTOR pos, VECTOR forward, float ray_cast_length, VECTOR* hitPos)
{
	bool result = false;
	bool hit = false;

	// レイキャスト用の始点と終点を設定
	VECTOR RayStart = pos;

	// 前向きベクトルの方向へレイを飛ばす
	pos.x = pos.x + forward.x * ray_cast_length;
	pos.y = pos.y + forward.y * ray_cast_length;
	pos.z = pos.z + forward.z * ray_cast_length;
	VECTOR RayEnd = VGet(pos.x, pos.y, pos.z);
	DrawLine3D(RayStart, RayEnd, GetColor(255, 0, 0));

	// マップのマトリクスを取得
	MATRIX matrix = MV1GetMatrix(modeleHandle);

	// 当たりのあるポリゴンを探す
	for (int i = 0; i < colWallFrameVec.size(); i++) {
		MV1_REF_POLYGONLIST  RefPoly = MV1GetReferenceMesh(modeleHandle, colWallFrameVec[i]->frameIndex, TRUE);

		for (int j = 0; j < RefPoly.PolygonNum; j++) {
			// ポリゴンの頂点座標を取得
			VECTOR tri_v0 = RefPoly.Vertexs[RefPoly.Polygons[j].VIndex[0]].Position;
			VECTOR tri_v1 = RefPoly.Vertexs[RefPoly.Polygons[j].VIndex[1]].Position;
			VECTOR tri_v2 = RefPoly.Vertexs[RefPoly.Polygons[j].VIndex[2]].Position;
			tri_v0 = VTransform(tri_v0, matrix);
			tri_v1 = VTransform(tri_v1, matrix);
			tri_v2 = VTransform(tri_v2, matrix);

			// 線分と三角形の当たり判定を実施
			HITRESULT_LINE Result = HitCheck_Line_Triangle(RayStart, RayEnd, tri_v0, tri_v1, tri_v2);
			if (Result.HitFlag) {
				result = TRUE;
				hitPos->x = Result.Position.x;
				hitPos->y = Result.Position.y;
				hitPos->z = Result.Position.z;
				DrawFormatString(10, 80, 32000, "Ray Hit");
				break;
			}
		}

		if (result) break;
	}

	return result;

}