#include"Geometry.h"
#include<DxLib.h>
#include<cmath>
#include <algorithm>


void
Rect::Draw() {
	DxLib::DrawBox((int)Left()*2, (int)Top()*2, (int)Right()*2, (int)Bottom()*2, 0xffffffff, false);
}

void
Rect::Draw(Vector2& offset) {
	DxLib::DrawBox((int)(Left() + offset.x) * 2, (int)(Top() + offset.y) * 2, (int)(Right() + offset.x) * 2, (int)(Bottom() + offset.y) * 2, 0xffffffff, false);
}

Vector2
Vector2::operator*(float scale) {
	return { x * scale,y * scale };
}

Vector2
operator+(const Vector2& va, const Vector2 vb) {
	return { va.x + vb.x,va.y + vb.y };
}

Vector2 
operator-(const Vector2& va, const Vector2 vb){
	return { va.x - vb.x,va.y - vb.y };
}

Vector2
operator * (const Vector2& lval, float scale) {
	return { lval.x * scale,lval.y * scale };
}
Vector2 
operator / (const Vector2& lval, float div) {
	return { lval.x / div,lval.y / div };
}

float
Vector2::Magnitude()const {
	return hypot(x, y);
}

float
Vector2::SQMagnitude()const {
	return x * x + y * y;
}

void 
Vector2::Normalize() {
	float mag = Magnitude();
	x /= mag;
	y /= mag;
}

Vector2
Vector2::Normalized() {
	float mag = Magnitude();
	return Vector2(x / mag,	y /mag);
}

void
Vector2::Rotate90() {
	std::swap(x, y);
	x = -x;
}

Vector2 Vector2::Rotated90() const {
	return { -y,x };
}

///内積を返す
float
Dot(const Vector2& va, const Vector2& vb) {
	return va.x*vb.x + va.y*vb.y;
}

///外積を返す
float
Cross(const Vector2& va, const Vector2& vb) {
	return va.x*vb.y - vb.x*va.y;
}

///内積演算子
float 
operator*(const Vector2& va, const Vector2& vb) {
	return Dot(va, vb);
}

///外積演算子
float 
operator%(const Vector2& va, const Vector2& vb) {
	return Cross(va, vb);
}

void 
Vector2::operator+=(const Vector2& v) {
	x += v.x;
	y += v.y;
}
void 
Vector2::operator-=(const Vector2& v) {
	x -= v.x;
	y -= v.y;
}
void
Vector2::operator*=(float scale) {
	x *= scale;
	y *= scale;
}
void 
Vector2::operator/=(float div)
{
	x /= div;
	y /= div;
}

bool Vector2::operator==(const Vector2& val)
{
	return x == val.x && y == val.y;
}

bool Vector2::operator!=(const Vector2 & val)
{
	return x != val.x && y != val.y;
}
