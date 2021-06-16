#pragma once

#include<DxLib.h>

//サイズを表す構造体
struct Size {
	float w;//幅
	float h;//高さ
};

//2D座標・ベクトルを表す構造体
struct Vector2 {
	float x, y;
	Vector2() :x(0.0f), y(0.0f) {};
	Vector2(float inx, float iny) :x(inx), y(iny) {};

	///ベクトルの大きさを返します
	float Magnitude()const;

	float SQMagnitude()const;

	///正規化(大きさを１に)します
	void Normalize();

	///正規化ベクトルを返します
	Vector2 Normalized()const;

	void Rotate90();

	void operator += (const Vector2& vec);
	void operator -= (const Vector2& vec);
	void operator *= (float scale);
	void operator /= (float div);
	bool operator ==(const Vector2& vec)const;

	Vector2 operator*(float scale) {
		return { x * scale, y * scale };
	}
	Vector2 operator-() {
		return Vector2(-x, -y);
	}
};
Vector2 operator + (const Vector2& lval, const Vector2& rval);
Vector2 operator - (const Vector2& lval, const Vector2& rval);
Vector2 operator * (const Vector2& lval, float scale);
Vector2 operator / (const Vector2& lval, float div);

///内積を返す
float Dot(const Vector2& va, const Vector2& vb);

///外積を返す
float Cross(const Vector2& va, const Vector2& vb);

///内積演算子
float operator*(const Vector2& va, const Vector2& vb);

///外積演算子
float operator%(const Vector2& va, const Vector2& vb);

//とりあえず「座標」って意味だとベクタより
//Positionのほうがよくね？って理由でこの名前
typedef Vector2 Position2;

//3D座標・ベクトルを表す構造体
struct Vector3 {
	Vector3() :x(0), y(0), z(0) {}
	Vector3(float inx, float iny, float inz) :x(inx), y(iny), z(inz) {}
	float x, y, z;
	///ベクトルの大きさを返します
	float Magnitude()const;

	float SQMagnitude()const;

	///正規化(大きさを１に)します
	void Normalize();

	///正規化ベクトルを返します
	Vector3 Normalized()const;

	void operator+=(const Vector3& v);
	void operator-=(const Vector3& v);
	void operator*=(float scale);
	Vector3 operator*(float scale)const;
	//Vector3 operator*(const Vector3& v)const;
	Vector3 operator-()const {
		return Vector3(-x, -y, -z);
	}
};

using  Color_ = Vector3;

Vector3 operator+(const Vector3& va, const Vector3 vb);
Vector3 operator-(const Vector3& va, const Vector3 vb);

///内積を返す
float Dot(const Vector3& va, const Vector3& vb);

///外積を返す
Vector3 Cross(const Vector3& va, const Vector3& vb);

///内積演算子
Vector3 operator*(const Vector3& va, const Vector3& vb);
Vector3 operator*(float, const Vector3& vec);

///外積演算子
Vector3 operator%(const Vector3& va, const Vector3& vb);
typedef Vector3 Position3;

///円を表す構造体
struct Circle {
	float radius;//半径
	Position2 pos; //中心座標
	Circle() :radius(0), pos(0, 0) {}
	Circle(float v, Position2& p) :radius(v), pos(p) {}
};

///矩形を表す構造体
struct Rect {
	Position2 pos; //中心座標
	int w, h;//幅,高さ
	Rect() : pos(0, 0), w(0), h(0) {}
	Rect(float x, float y, int inw, int inh) :
		pos(x, y), w(inw), h(inh) {}
	Rect(Position2& inpos, int inw, int inh) :
		pos(inpos), w(inw), h(inh)
	{}
	void SetCenter(float x, float y) {
		pos.x = x;
		pos.y = y;
	}
	void SetCenter(const Position2& inpos) {
		pos.x = inpos.x;
		pos.y = inpos.y;
	}
	Vector2 Center() {
		return pos;
	}
	float Left() { return pos.x - w / 2; }
	float Top() { return pos.y - h / 2; }
	float Right() { return pos.x + w / 2; }
	float Bottom() { return pos.y + h / 2; }
	void Draw();//自分の矩形を描画する
	void Draw(Vector2& offset);//自分の矩形を描画する(オフセット付き)
};

struct Color {
	float r;
	float g;
	float b;

	Color() :r(0), g(0), b(0) {}
	Color(float v) :r(v), g(v), b(v) {}
	Color(float inr, float ing, float inb) :r(inr), g(ing), b(inb) {}
	void operator=(float val) {
		r = g = b = val;
	}
	void operator*=(float val) {
		r *= val;
		g *= val;
		b *= val;
	}
	void operator/=(float val) {
		r /= val;
		g /= val;
		b /= val;
	}
	void operator+=(float val) {
		r += val;
		g += val;
		b += val;
	}
	void operator+=(Color c) {
		r += c.r;
		g += c.g;
		b += c.b;
	}

	unsigned int GetDxLibColor() {
		return GetColor(r * 255, g * 255, b * 255);
	}
};
