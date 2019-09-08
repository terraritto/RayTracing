#include "Utility/World.h"
#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	World world;
	world.Build();
	world.mCameraPtr->RenderScene(world);

	DxLib_End();
	return 0;
}