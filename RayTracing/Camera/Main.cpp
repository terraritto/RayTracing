#include "Utility/World.h"
#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	World world;
	world.Build();
	world.mCameraPtr->RenderScene(world);

	DrawString(0,0,"finish render", GetColor(255,255,255));
	WaitTimer(10000);

	DxLib_End();
	return 0;
}