#include "GameObject.h"

void GameObject::Transform(int handle) 
{
	MATRIX matRotX = MGetRotX(rotation.x);  //X��]�s������
	MATRIX matRorY = MGetRotY(rotation.y);  //y��]�s������
	MATRIX matRotZ = MGetRotZ(rotation.z);  //z��]�s������

	//�@Z����]�s��~Y����]�s��
	matrix = MMult(matRotZ, matRorY);

	//�AZY��]�s��~X����]�s��
	matrix = MMult(matrix, matRotX);

	//�B�g�k�̍s������
	MATRIX matScl = MGetScale(VGet(scale.x, scale.y, scale.z));

	//�C�g�k�s��~XYZ��]�s��
	matrix = MMult(matScl, matrix);

	//�DXYZ��]�s��~���s�ړ��s��
	MATRIX matTrans = MGetTranslate(trans);
	matrix = MMult(matrix, matTrans);

	//�ŏI�I�ȍ��W�ύX�s������f���ɓK��
	MV1SetMatrix(handle, matrix);

	//���݂̉�]�}�g���N�X���g���đO�����x�N�g�������
	MATRIX rotMatrix = MGetIdent();
	rotMatrix.m[0][0] = matrix.m[0][0]; rotMatrix.m[0][1] = matrix.m[0][1]; rotMatrix.m[0][2] = matrix.m[0][2];
	rotMatrix.m[1][0] = matrix.m[1][0]; rotMatrix.m[1][1] = matrix.m[1][1]; rotMatrix.m[1][2] = matrix.m[1][2];
	rotMatrix.m[2][0] = matrix.m[2][0]; rotMatrix.m[2][1] = matrix.m[2][1]; rotMatrix.m[2][2] = matrix.m[2][2];
	forward = VNorm(VTransform(VGet(0.f, 0.f, -1.f), rotMatrix));
}

