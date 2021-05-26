
#include <DxLib.h>

static constexpr int SCREEN_SIZE_X = 800;
static constexpr int SCREEN_SIZE_Y = 800;

struct Vector2
{
	int x;
	int y;
};

void Draw(Vector2 pos);

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	SetWindowText(L"1916001_èHéRóT");
	SetDrawScreen(DX_SCREEN_BACK);
	SetGraphMode(500, 500, 32);
	ChangeWindowMode(true);
	
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	Vector2 pos = { 100,100 };
	int speed = 5;

	while (ProcessMessage() != -1 &&
		CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();

		if (CheckHitKey(KEY_INPUT_W))
		{
			pos.y -= speed;
		}
		if (CheckHitKey(KEY_INPUT_S))
		{
			pos.y += speed;
		}
		if (CheckHitKey(KEY_INPUT_A))
		{
			pos.x -= speed;
		}
		if (CheckHitKey(KEY_INPUT_D))
		{
			pos.x += speed;
		}

		Draw(pos);

		ScreenFlip();
	}
	DxLib_End();
	return 0;
}

void Draw(Vector2 pos)
{
	DrawBox(pos.x, pos.y, pos.x + 100, pos.y + 100, 0xffffff, true);

	DrawString(10, 10, L"HELLO_WORLD", 0xffffff, true);
	DrawFormatString(10, 30, 0xffffff, L"X : %d Y : %d", pos.x, pos.y, true);

}
