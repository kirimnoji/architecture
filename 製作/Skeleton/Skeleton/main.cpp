
#include <DxLib.h>
#include <cmath>
#include <assert.h>

#include "Geometry.h"
#include "Singleton.h"
#include "main.h"


int WINAPI WinMain(_In_ HINSTANCE, 
	_In_opt_ HINSTANCE,
	_In_ LPSTR, _In_ int)
{
	Init();

	while (ProcessMessage() != -1 &&
		CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();

		int mx, my;
		GetMousePoint(&mx, &my);

		angle = atan2(my - center.y, mx - center.x);

		BoxCtl();

		Draw(pos);

		DrawSinLine();

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

	rcA = { 200,200,50,50 };
	KeyState[256];

	pos = { 100,100 };

	center = { 320,240 };
	angle = 0;

	frameForAngle = 0;

	speed = 5;
}

void DrawSinLine()
{
	constexpr size_t block_size = 32;
	const auto count = 720 / block_size;
	float theta = (float)(frameForAngle)*DX_PI_F / 180.f;
	int x = 0;
	int y = 350;
	Position2 p0(x, y);
	Position2 lastPos(x, y);
	Vector2 lastDelta90Vectors[2] = { {0.f,0.f} ,{0.f,0.f} };
	/*Vector2 lastDeltaVec90 = { 0,0 };*/

	for (int i = 1; i < count ; ++i)
	{
		theta += 0.1f;
		/*Vector2 deltaVec = { block_size,100 * sinf(0.5f * (float)(nextX + frameForAngle) * DX_PI_F / 180.f) };
		Position2 nextPos = currentPos + deltaVec;*/
		/*auto nextX = block_size * i;
		auto nextY = 500 + 100 * sinf(0.5f *(float)(nextX + frameForAngle) * DX_PI_F / 180.f);*/
		
		auto p1 = p0;

		auto deltaVec = Vector2(block_size,50.f *
			sinf(0.5f * (float)(frameForAngle + block_size * i) * DX_PI_F / 180.f)
		);

		deltaVec = deltaVec.Normalized() * block_size;
		p1 = p0 + deltaVec;

		auto delta90Vec = deltaVec.Rotated90();

		auto middleVecR = delta90Vec;
		auto middleVecL = delta90Vec;
		if (!(lastDelta90Vectors[0] == Vector2(0.f, 0.f))) {
			middleVecR = (middleVecR + lastDelta90Vectors[0]).Normalized()* block_size;
			middleVecL = lastDelta90Vectors[0];
		}
		if (!(lastDelta90Vectors[1] == Vector2(0.f, 0.f))) {
			middleVecL = (lastDelta90Vectors[0] + lastDelta90Vectors[1]).Normalized() * block_size;
		}
		lastDelta90Vectors[1] = lastDelta90Vectors[0];
		lastDelta90Vectors[0] = deltaVec.Rotated90();

		auto rightPos = p0 + middleVecR;
		auto leftPos = lastPos + middleVecL;
		/*auto middlePos = p0 + middleVec;*/
		if (i == count)
		{
			auto rightPos = p0 + middleVecR;
			auto leftPos = p1 + delta90Vec;
			DrawModiGraph(
				lastPos.x, lastPos.y,
				p0.x, p0.y,
				rightPos.x, rightPos.y,
				leftPos.x, leftPos.y,
				groundH, true);
		}
		else
		{
			leftPos = p0 + middleVecR;
			auto rightPos2 = p1 + delta90Vec;
			DrawModiGraph(
				p0.x, p0.y,
				p1.x, p1.y,
				rightPos2.x, rightPos2.y,
				leftPos.x, leftPos.y,
				groundH, true);
		}


		/*DrawModiGraph(
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
				assetsH, true);*/

		/// 4•Ó‚ðƒ‰ƒCƒ“‚Å•\Ž¦
		// ã•Ó
		DrawLineAA(
			p0.x, p0.y,
			p1.x, p1.y,
			0xffffff, 5.f);
		DrawCircle(p0.x, p0.y,5, 0xffaaaa);

		/*auto lPos = p0 + deltaVec.Rotated90();
		auto middlePos = lPos;
		if (!(lastDeltaVec90 == Vector2{ 0,0 })) {
			auto halfVec = deltaVec.Rotated90() + lastDeltaVec90;
			middlePos = p0 + halfVec.Rotated90();
		}
		lastDeltaVec90 = deltaVec.Normalized();
		auto rPos = p1 + deltaVec.Rotated90();*/
		

		// ‰E•Ó
		/*DrawLineAA(
			p1.x, p1.y,
			rPos.x, rPos.y,
			0xaaffaa, 3.0f);
		
		// ¶•Ó
		DrawLineAA(
			p0.x, p0.y,
			leftPos.x, leftPos.y,
			0xaaaaff, 3.0f);
		// ’†‰›
		DrawLineAA(
			p0.x, p0.y,
			middlePos.x, middlePos.y,
			0xffaaaa, 3.0f);*/

		/*DrawModiGraph(
			p0.x, p0.y,
			p1.x, p1.y,
			rPos.x, rPos.y,
			middlePos.x, middlePos.y,
			groundH, true);*/
		
		// ’†‰›•Ó
		/*DrawLineAA(
			middlePos.x, middlePos.y + block_size,
			x, y,
			0xff0000, 3.0f);*/

		// ‰º•Ó
		/*DrawLineAA(
			nextX, nextY + block_size,
			leftPos.x, leftPos.y + block_size,
			0x0000ff, 3.0f);*/
		/*DrawLineAA(
			x, y,
			nextX, nextY,
			0xffffff,
			3.f);*/

		//x = nextX;
		//y = nextY;
		p0 = p1;
		lastPos = p0;
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
	DxLib::DrawBox(pos.x, pos.y, pos.x + 100, pos.y + 100, 0xffffff, true);

	DxLib::DrawString(10, 10, L"HELLO_WORLD", 0xffffff, true);
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

