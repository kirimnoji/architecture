
#include <DxLib.h>
#include <cmath>
#include <assert.h>

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

		tmp();

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
	SetWindowText(L"1916001_HŽR—T");
	SetDrawScreen(DX_SCREEN_BACK);
	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 32);
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)
	{
		return -1;
	}

	mCat = LoadGraph(L"../image/arrowcat.png", true);
	groundH = LoadGraph(L"../img/ground.png", true);
	assert(groundH >= 0);

	assetsH = LoadGraph(L"../image/Assets.png", true);
	assert(assetsH >= 0);

	rcA = { {200,200},50,50 };
	KeyState[256];

	pos = { 100,100 };

	center = { 320,240 };
	angle = 0;

	speed = 5;
}

void tmp()
{
	constexpr size_t block_size = 32;
	const auto count = 1080 / block_size;
	int x = 0;
	int y = 500 + 100 * sinf(0.5f * (float)(frameForAngle) * DX_PI_F / 180.f);
	Vector2 p0{ x,y };

	for (int i = 1; i <= count ; ++i)
	{
		auto nextX = block_size * i;
		auto nextY = 500 + 100 * sinf(0.5f *(float)(nextX + frameForAngle) * DX_PI_F / 180.f);
		
		DrawModiGraph(
			x, y,
			nextX, nextY,
			nextX, nextY + block_size,
			x, y + block_size,
			groundH, true);

			constexpr int offsetY = 100;
			DrawRectModiGraph(
				x, y + 100,
				nextX, nextY + 100,
				nextX, nextY + block_size + 100,
				x, y + block_size + 100,
				48,0,
				16,16,
				assetsH, true);

		/*// 4•Ó‚ðƒ‰ƒCƒ“‚Å•\Ž¦
			// ã•Ó
			DrawLineAA(
				x, y,
				nextX, nextY,
				0xffffff, 3.0f);
			// ‰E•Ó
			DrawLineAA(
				nextX, nextY,
				nextX, nextY + block_size,
				0xffffff, 3.0f);
			// ‰º•Ó
			DrawLineAA(
				nextX, nextY + block_size,
				x, y + block_size,
				0xffffff, 3.0f);
			// ¶•Ó
			DrawLineAA(
				x, y + block_size,
				x, y,
				0xffffff, 3.0f);*/

		/*DrawLineAA(
			x, y,
			nextX, nextY,
			0xffffff,
			3.f);*/

		x = nextX;
		y = nextY;
	}
	frameForAngle = (frameForAngle + 1) % 720;
}

void Draw(Vector2 pos)
{
	/*int mx, my;
	GetMousePoint(&mx, &my);

	auto currentMouseInput = GetMouseInput();
	if ((currentMouseInput & MOUSE_INPUT_LEFT) &&
		!(lastMouseInput & MOUSE_INPUT_LEFT))
	{
		flipFlag = !flipFlag;
	}
	lastMouseInput = currentMouseInput;

	Vector2 dir = GetCurrentMousePosition2() - rcA.center;

	float angle = atan2(dir.y, dir.x);

	int cx = 32;
	int gw, gh;
	GetGraphSize(mCat, &gw, &gh);
	if (flipFlag)
	{
		cx = gw - cx;
	}
	DrawRotaGraph2(rcA.center.x, rcA.center.y,
		cx, 35,
		5.f, angle, mCat, true, flipFlag);
	DrawCircleAA(rcA.center.x, rcA.center.y, 5, 16, 0xff4444);*/

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

