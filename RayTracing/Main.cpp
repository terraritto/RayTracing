#include "World.h"
#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	World w;
	w.Build();
	w.RenderScene();

	DxLib_End();
	return 0;
}