#include "GameObject.h"

void GameObject::Transform(int handle) 
{
	MATRIX matRotX = MGetRotX(rotation.x);  //Xñ]sñðìé
	MATRIX matRorY = MGetRotY(rotation.y);  //yñ]sñðìé
	MATRIX matRotZ = MGetRotZ(rotation.z);  //zñ]sñðìé

	//@Z²ñ]sñ~Y²ñ]sñ
	matrix = MMult(matRotZ, matRorY);

	//AZYñ]sñ~X²ñ]sñ
	matrix = MMult(matrix, matRotX);

	//BgkÌsñðìé
	MATRIX matScl = MGetScale(VGet(scale.x, scale.y, scale.z));

	//Cgksñ~XYZñ]sñ
	matrix = MMult(matScl, matrix);

	//DXYZñ]sñ~½sÚ®sñ
	MATRIX matTrans = MGetTranslate(trans);
	matrix = MMult(matrix, matTrans);

	//ÅIIÈÀWÏXsñðfÉK
	MV1SetMatrix(handle, matrix);

	//»ÝÌñ]}gNXðgÁÄOü«xNgðìé
	MATRIX rotMatrix = MGetIdent();
	rotMatrix.m[0][0] = matrix.m[0][0]; rotMatrix.m[0][1] = matrix.m[0][1]; rotMatrix.m[0][2] = matrix.m[0][2];
	rotMatrix.m[1][0] = matrix.m[1][0]; rotMatrix.m[1][1] = matrix.m[1][1]; rotMatrix.m[1][2] = matrix.m[1][2];
	rotMatrix.m[2][0] = matrix.m[2][0]; rotMatrix.m[2][1] = matrix.m[2][1]; rotMatrix.m[2][2] = matrix.m[2][2];
	forward = VNorm(VTransform(VGet(0.f, 0.f, -1.f), rotMatrix));
}

