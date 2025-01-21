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

	// �n�ʂ̓����蔻��p��z��
	int root_index = MV1SearchFrame(modeleHandle, "map_root");
	traverse(root_index, "map_root");

	// �ǂȂǂ̉����瓖���锻��p��z��
	MV1SetupReferenceMesh(handle, 0, TRUE);
	root_index = MV1SearchFrame(modeleHandle, "map");
	traverse(root_index, "map");
}

/**
* @brief �}�b�v�m�[�h�̊K�w��H��A�R���W��������p�̃m�[�h�𔻕ʂ���
* @param[in] parent_index�i�R���W�������肷�郋�[�g�m�[�h�j
* @param[out] �Ȃ�
* @return �Ȃ�
* @details Player�̃t���[���������X�V����
*/
void Collision::traverse(int parent_index, string root_name)
{
	// parent_index�Ŏw�肳�ꂽ�m�[�h�����q�m�[�h�����擾
	int num_of_child = MV1GetFrameChildNum(modeleHandle, parent_index);
	for (int i = 0; i < num_of_child; i++) {
		int index = MV1GetFrameChild(modeleHandle, parent_index, i);

		// ���b�V������0�ȏ�Ȃ�A���_�����݂���m�[�h�Ȃ̂ŁA�����蔻��m�[�h�Ƃ���vector�z��ɓo�^
		if (MV1GetFrameMeshNum(modeleHandle, index) > 0) {
			if (MV1SetupReferenceMesh(modeleHandle, index, TRUE) == 0) {	// DX���C�u�����Ƀ��b�V���Q�Ɨp�m�[�h�Ƃ��Ďw�����Ă���
				// �����Ńt���[���i�m�[�h�jindex���L�^���Ă���
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

		// �q�m�[�h�����擾
		int num_of_child = MV1GetFrameChildNum(modeleHandle, index);

		// �ċA�R�[���ŊK�w��H��
		traverse(index, root_name);
	}
}

bool Collision::CheckRaycast(VECTOR pos, VECTOR forward, float ray_cast_length, VECTOR* hitPos)
{
	bool result = false;
	bool hit = false;

	// ���C�L���X�g�p�̎n�_�ƏI�_��ݒ�
	VECTOR RayStart = pos;

	// �O�����x�N�g���̕����փ��C���΂�
	pos.x = pos.x + forward.x * ray_cast_length;
	pos.y = pos.y + forward.y * ray_cast_length;
	pos.z = pos.z + forward.z * ray_cast_length;
	VECTOR RayEnd = VGet(pos.x, pos.y, pos.z);
	DrawLine3D(RayStart, RayEnd, GetColor(255, 0, 0));

	// �}�b�v�̃}�g���N�X���擾
	MATRIX matrix = MV1GetMatrix(modeleHandle);

	// ������̂���|���S����T��
	for (int i = 0; i < colWallFrameVec.size(); i++) {
		MV1_REF_POLYGONLIST  RefPoly = MV1GetReferenceMesh(modeleHandle, colWallFrameVec[i]->frameIndex, TRUE);

		for (int j = 0; j < RefPoly.PolygonNum; j++) {
			// �|���S���̒��_���W���擾
			VECTOR tri_v0 = RefPoly.Vertexs[RefPoly.Polygons[j].VIndex[0]].Position;
			VECTOR tri_v1 = RefPoly.Vertexs[RefPoly.Polygons[j].VIndex[1]].Position;
			VECTOR tri_v2 = RefPoly.Vertexs[RefPoly.Polygons[j].VIndex[2]].Position;
			tri_v0 = VTransform(tri_v0, matrix);
			tri_v1 = VTransform(tri_v1, matrix);
			tri_v2 = VTransform(tri_v2, matrix);

			// �����ƎO�p�`�̓����蔻������{
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