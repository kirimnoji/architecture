
#include <DxLib.h>

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	SetWindowText(L"1916001_èHéRóT_Test");
	SetDrawScreen(DX_SCREEN_BACK);
	SetGraphMode(500, 500, 32);
	ChangeWindowMode(true);
	
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();

		ScreenFlip();
	}

	DxLib_End();
}