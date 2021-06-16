#pragma once

static constexpr int SCREEN_SIZE_X = 900;
static constexpr int SCREEN_SIZE_Y = 900;

struct Vector2
{
	int x;
	int y;
};

int Init();
void Draw(Vector2 pos);
void BoxCtl();
void tmp();

Vector2 pos = { 100,100 };

Vector2 target;
Vector2 center;
float angle;

int speed;

int frameForAngle;


int mCat;
int groundH;
int assetH;
