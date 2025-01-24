#include "Dxlib.h"
#include "SceneManager.h"
//#include "Define.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(true);		//Windowモード
	SetGraphMode(1200, 800, 32);//画面サイズ設定
	/*SetUseDirect3DVersion(DX_DIRECT3D_11);*/

	SetUseZBuffer3D(TRUE);     // デプスバッファ（Zバッファ）を有効にする
	SetWriteZBuffer3D(TRUE);   // Zバッファへの書き込みを有効にする

	if (DxLib_Init() == -1) 
		return 0;	//エラーで抜ける
		//WaitKey();
		//DxLib_End();	//Dx終了の処理
		//return 0;	//ソフト終了

	SceneManager& sceneManager = SceneManager::Instance();

	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		if (ProcessMessage() == -1)
			break;
		ClearDrawScreen();
		sceneManager.Update();
		//FPS(60);
		ScreenFlip();
		
	}

	DxLib_End();	//Dx終了の処理

	return 0;	//ソフト終了
}