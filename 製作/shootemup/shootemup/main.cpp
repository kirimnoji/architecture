
#include <vector>

#include <DxLib.h>
#include <cmath>
#include <memory>
#include "HomingShot.h"

///当たり判定関数
///@param posA Aの座標
///@param radiusA Aの半径
///@param posB Bの座標
///@param radiusB Bの半径
bool IsHit(const Position2& posA, float radiusA, const Position2& posB,  float radiusB) {
	//当たり判定を実装してください
	return (posA - posB).Magnitude() < (radiusA + radiusB);
}

using namespace std;

int WINAPI WinMain(
	_In_ HINSTANCE,
	_In_opt_  HINSTANCE,
	_In_ LPSTR, 
	_In_ int) {
	ChangeWindowMode(true);
	SetMainWindowText("1916001_秋山裕");
	if (DxLib_Init() != 0) {
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);

	//背景用
	int bgH[4];
	LoadDivGraph("img/bganim.png", 4, 4, 1, 256, 192, bgH);

	int skyH = LoadGraph("img/sky.png");
	int sky2H = LoadGraph("img/sky2.png");

	auto bulletH=LoadGraph("img/bullet.png");
	int playerH[10];
	LoadDivGraph("img/player.png", 10, 5, 2, 16, 24,playerH );

	int enemyH[2];
	LoadDivGraph("img/enemy.png", 2, 2, 1, 32, 32, enemyH);

	//
	auto arrowH = LoadGraph("img/arrow.png");

	//弾の半径
	float bulletRadius = 5.0f;

	//自機の半径
	float playerRadius = 10.0f;

	//適当に256個くらい作っとく
	Bullet bullets[256];

	Position2 enemypos(320,25);//敵座標
	Position2 playerpos(320, 400);//自機座標

	// 自機の弾
	HomingShot shots[16] = {};
	for (auto& shot : shots)
	{
		shot.trail.SetHandle(arrowH);
	}

	unsigned int frame = 0;//フレーム管理用

	char keystate[256] = {};
	char lastKeyState[256] = {};
	bool isDebugMode = false;
	int skyy = 0;
	int skyy2 = 0;
	int bgidx = 0;
	constexpr float player_shot_speed = 8.f;

	while ((ProcessMessage() == 0) && 
		(CheckHitKey(KEY_INPUT_ESCAPE) == 0)) 
	{
		ClearDrawScreen();

		GetHitKeyStateAll(keystate);

		isDebugMode = keystate[KEY_INPUT_P];

		//背景
		DrawExtendGraph(0, 0, 640, 480, bgH[bgidx / 8], false);
		bgidx = (bgidx + 1) % 32;

		//SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
		skyy = (skyy + 1) % 480;
		skyy2 = (skyy2 + 2) % 480;
		DrawExtendGraph(0, skyy, 640, skyy + 480, skyH, true);
		DrawExtendGraph(0, skyy - 480, 640, skyy, skyH, true);
		DrawExtendGraph(0, skyy2, 640, skyy2 + 480, sky2H, true);
		DrawExtendGraph(0, skyy2 - 480, 640, skyy2, sky2H, true);

		//プレイヤー
		if (keystate[KEY_INPUT_RIGHT]) {
			playerpos.x = min(640,playerpos.x+4);
		}
		else if (keystate[KEY_INPUT_LEFT]) {
			playerpos.x = max(0,playerpos.x-4);
		}
		if (keystate[KEY_INPUT_UP]) {
			playerpos.y = max(0,playerpos.y-4);
		}else if (keystate[KEY_INPUT_DOWN]) {
			playerpos.y = min(480,playerpos.y+4);
		}

		int pidx = (frame/4 % 2)*5+3;
		
		if (isDebugMode) {
			//自機の本体(当たり判定)
			DrawCircle(playerpos.x, playerpos.y, playerRadius, 0xffaaaa, false, 3);
		}

		// 弾発射
		if (keystate[KEY_INPUT_Z] && !lastKeyState[KEY_INPUT_Z])
		{
			int cnt = 0;
			for (auto& shot : shots)
			{
				if (!shot.isActive)
				{
					shot.isActive = true;
					shot.pos = playerpos;
					shot.vel = Vector2({ cnt == 0 ? 1.f : -1.f,1.f }).Normalized() * player_shot_speed;
					shot.trail.Clear();
					if (++cnt > 1)
					{
						break;
					}
				}
			}
		}

		// 弾の更新・描画
		for (auto& shot : shots)
		{
			if (!shot.isActive)continue;

			if (frame % 2 == 0)
			{
				shot.trail.Update();
			}
			shot.pos += shot.vel;
			shot.trail.Draw();

			shot.vel = (shot.vel +(enemypos - shot.pos).Normalized()).Normalized() *player_shot_speed;

				//// 敵狙い弾にする
				constexpr bool isSimple = false;
				if (isSimple)
				{
					shot.vel = shot.vel + (enemypos - shot.pos).Normalized() * 0.5;
					shot.vel = shot.vel.Normalized() * player_shot_speed;
				}
				else
				{
					auto nShotVel = shot.vel.Normalized();
					auto nToEnemyVec = (enemypos - shot.pos).Normalized();
					float dot = Dot(nShotVel, nToEnemyVec);
					float c = acos(dot);
					// マイナスだと右回り、プラスだと左回り
					float sross = Cross(nShotVel, nToEnemyVec);
				}
		
				DrawCircleAA(shot.pos.x, shot.pos.y,
					5.f, 16, 0xff0000);

				// 画面外に弾が出たら消す
				/*if (shot.pos.x < -10 || 650 < shot.pos.x ||
					shot.pos.y < -10 || 490 < shot.pos.y)
				{
					shot.isActive = false;
				}*/
				// 敵に当たっても消える
				if (IsHit(shot.pos, 16, enemypos, 16))
				{
					shot.isActive = false;
				}
		}
		DrawCircleAA(enemypos.x, enemypos.y, 30.f, 16, 0x0000ff, false, 3.0);

		DxLib::DrawRotaGraph(playerpos.x, playerpos.y, 2.0f, 0.0f, playerH[pidx], true);

		//弾発射
		if (frame % 12 == 0) {
			for (auto& b : bullets) {
				if (!b.isActive) {
					//b.pos = enemypos;
					//b.vel = Vector2(0, 5);
					//b.isActive = true;
					break;
				}
			}
		}

		//弾の更新および表示
		for (auto& b : bullets) {
			if (!b.isActive) {
				continue;
			}

			//弾の現在座標に弾の現在速度を加算してください
			
			float angle = 0.0f;
			//弾の角度をatan2で計算してください。angleに値を入れるんだよオゥ
			
			DxLib::DrawRotaGraph(b.pos.x, b.pos.y,1.0f,angle, bulletH, true);
			
			if (isDebugMode) {
				//弾の本体(当たり判定)
				DrawCircle(b.pos.x, b.pos.y, bulletRadius, 0x0000ff, false, 3);
			}
			//弾を殺す
			if (b.pos.x + 16 < 0 || b.pos.x - 16 > 640 ||
				b.pos.y + 24 < 0 || b.pos.y - 24 > 480) {
				b.isActive = false;
			}

			//あたり！
			//↓のIsHitは実装を書いてません。自分で書いてください。
			if (IsHit(b.pos, bulletRadius, playerpos, playerRadius)) {
				//当たった反応を書いてください。
			}
		}

		//敵の表示
		enemypos.x = (float)abs((int)((frame+320) % 1280) - 640);
		int eidx = (frame / 4 % 2);
		DxLib::DrawRotaGraph(enemypos.x, enemypos.y, 2.0f, 0.0f, enemyH[eidx],true);

		if (isDebugMode) {
			//敵の本体(当たり判定)
			DrawCircle(enemypos.x, enemypos.y, 5, 0xffffff, false, 3);
		}
		++frame;
		DxLib::ScreenFlip();

		// stdのbeginとend、その後に配列書くと、丸ごとコピーできる
		std::copy(begin(keystate),end(keystate),begin(lastKeyState));
	}

	DxLib::DxLib_End();

	return 0;
}