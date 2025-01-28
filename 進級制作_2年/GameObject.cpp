#include "GameObject.h"

void GameObject::Transform(int handle) 
{
	MATRIX matRotX = MGetRotX(rotation.x);  //X回転行列を作る
	MATRIX matRorY = MGetRotY(rotation.y);  //y回転行列を作る
	MATRIX matRotZ = MGetRotZ(rotation.z);  //z回転行列を作る

	//①Z軸回転行列×Y軸回転行列
	matrix = MMult(matRotZ, matRorY);

	//②ZY回転行列×X軸回転行列
	matrix = MMult(matrix, matRotX);

	//③拡縮の行列を作る
	MATRIX matScl = MGetScale(VGet(scale.x, scale.y, scale.z));

	//④拡縮行列×XYZ回転行列
	matrix = MMult(matScl, matrix);

	//⑤XYZ回転行列×平行移動行列
	MATRIX matTrans = MGetTranslate(trans);
	matrix = MMult(matrix, matTrans);

	//最終的な座標変更行列をモデルに適応
	MV1SetMatrix(handle, matrix);

	//現在の回転マトリクスを使って前向きベクトルを作る
	MATRIX rotMatrix = MGetIdent();
	rotMatrix.m[0][0] = matrix.m[0][0]; rotMatrix.m[0][1] = matrix.m[0][1]; rotMatrix.m[0][2] = matrix.m[0][2];
	rotMatrix.m[1][0] = matrix.m[1][0]; rotMatrix.m[1][1] = matrix.m[1][1]; rotMatrix.m[1][2] = matrix.m[1][2];
	rotMatrix.m[2][0] = matrix.m[2][0]; rotMatrix.m[2][1] = matrix.m[2][1]; rotMatrix.m[2][2] = matrix.m[2][2];
	forward = VNorm(VTransform(VGet(0.f, 0.f, -1.f), rotMatrix));
}

