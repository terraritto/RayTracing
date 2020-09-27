#include "Utility/World.h"
#include "DxLib.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	World world;
	world.Build();
	world.mCameraPtr->RenderScene(world);

	// mmd‚ÅmResult‚É‘‚«‚Ş‚Æ‚«‚Ì‚İ“K—p
	for (int r = 0; r < world.mViewPlane.mHRes; r++)
	{
		for (int c = 0; c < world.mViewPlane.mVRes; c++)
		{
			RGBColor mappedColor = world.mResult[r][c];
			DrawPixel(r, c, GetColor(mappedColor.mRed * 255, mappedColor.mGreen * 255, mappedColor.mBlue * 255));
		}
	}
	

	DrawString(0,0,"finish render", GetColor(255,255,255));
	ScreenFlip();
	while (true)
	{
		if (CheckHitKey(KEY_INPUT_1) && CheckHitKey(KEY_INPUT_2) && CheckHitKey(KEY_INPUT_3))
		{
			break;
		}
	}

	DxLib_End();
	return 0;
}