
#include <DxLib.h>
#include <cmath>

#include "main.h"
#include "Singleton.h"

int WINAPI WinMain(_In_ HINSTANCE, 
	_In_opt_ HINSTANCE,
	_In_ LPSTR, _In_ int)
{
	Init();

	while (ProcessMessage() != -1 &&
		CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();

		GetMousePoint(&target.x, &target.y);

		angle = atan2(target.y - center.y, target.x - center.x);

		BoxCtl();

		Draw(pos);

		/*Singleton& singleton = Singleton::Instanse();
		singleton.Out();
		Singleton& singleton2 = Singleton::Instanse();
		singleton2.Out();
		singleton2.Out();
		singleton2.Out();
		singleton2.Out();
		singleton2.Out();*/

		ScreenFlip();
	}

	DxLib_End();
	return 0;
}

int Init()
{
	SetWindowText(L"1916001_èHéRóT");
	SetDrawScreen(DX_SCREEN_BACK);
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	mCat = LoadGraph(L"../image/arrowcat.png", true);
	groundH = LoadGraph(L"../img/ground.png", true);
	/*LoadDivGraph("../image/Assets.png");*/

	pos = { 100,100 };

	center = { 320,240 };
	angle = 0;

	speed = 5;

	frameForAngle = 0;

}

void tmp()
{
	constexpr size_t block_size = 32;
	const auto a = 0;
	int x = 0;
	int y = 240;
	Vector2 p0{ x,y };

	for (int i = 0; i < 16 ; i++)
	{
		auto nextX = block_size;
		auto nextY = 240 + 100 * sinf(0.5f *(float)(nextX + frameForAngle) * DX_PI_F);

		/*	DrawModiGraph(x, y, 
			nextX, nextY,
			nextX, nextY + block_size,
			x, y + block_size, 
			groundH, true);*/

		/*constexpr int offsetY = 100;
		DrawModiGraph(
			x, y + 100,
			nextX, nextY + 100,
			nextX, nextY + block_size + 100,
			x, y + block_size + 100,
			48,0,
			16,16,
			groundH, true);*/

		/*DrawLineAA(x, y,
			nextX, nextY,
			0xffffff, 3.0f);
		DrawLineAA(nextX, nextY,
			nextX, nextY + block_size,
			0xffffff, 3.0f);
		DrawLineAA(nextX, nextY + block_size,
			x, y + block_size,
			0xffffff, 3.0f);
		DrawLineAA(x, y + block_size,
			x, y,
			0xffffff, 3.0f);*/

		x = nextX;
		y = nextY;

	}
	frameForAngle = (frameForAngle);
}


void Draw(Vector2 pos)
{
	DrawRotaGraph(center.x, center.y, 1, angle, mCat, true);
	DrawBox(pos.x, pos.y, pos.x + 100, pos.y + 100, 0xffffff, true);

	DrawString(10, 10, L"HELLO_WORLD", 0xffffff, true);
	DrawFormatString(10, 30, 0xffffff, L"X : %d Y : %d", pos.x, pos.y, true);
}

void BoxCtl()
{
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
}

