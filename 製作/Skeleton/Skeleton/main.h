#pragma once

static constexpr int SCREEN_SIZE_X = 900;
static constexpr int SCREEN_SIZE_Y = 900;

int Init();
void Draw(Vector2 pos);
void BoxCtl();
void tmp();

Vector2 pos = { 100,100 };

Vector2 target;
Vector2 center;

Rect rcA;
char KeyState[];

float angle;

int speed;

int frameForAngle = 0;

int mCat;
int groundH;
int assetsH;
