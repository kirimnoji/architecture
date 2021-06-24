#pragma once

#include<DxLib.h>

//�T�C�Y��\���\����
struct Size {
	float w;//��
	float h;//����
};

//2D���W�E�x�N�g����\���\����
struct Vector2 {
	float x, y;
	Vector2() :x(0.0f), y(0.0f) {};
	Vector2(float inx, float iny) :x(inx), y(iny) {};

	void operator += (const Vector2& vec);
	void operator -= (const Vector2& vec);
	void operator *= (float scale);
	void operator /= (float div);
	bool operator ==(const Vector2& vec)const;

	///�x�N�g���̑傫����Ԃ��܂�
	float Magnitude()const;

	float SQMagnitude()const;

	///���K��(�傫�����P��)���܂�
	void Normalize();

	///���K���x�N�g����Ԃ��܂�
	Vector2 Normalized()const;

	void Rotate90();
	Vector2 Rotated90()const;

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

///���ς�Ԃ�
float Dot(const Vector2& va, const Vector2& vb);

///�O�ς�Ԃ�
float Cross(const Vector2& va, const Vector2& vb);

///���ω��Z�q
float operator*(const Vector2& va, const Vector2& vb);

///�O�ω��Z�q
float operator%(const Vector2& va, const Vector2& vb);

//�Ƃ肠�����u���W�v���ĈӖ����ƃx�N�^���
//Position�̂ق����悭�ˁH���ė��R�ł��̖��O
using Position2 = Vector2;

//3D���W�E�x�N�g����\���\����
struct Vector3 {
	Vector3() :x(0), y(0), z(0) {}
	Vector3(float inx, float iny, float inz) :x(inx), y(iny), z(inz) {}
	float x, y, z;
	///�x�N�g���̑傫����Ԃ��܂�
	float Magnitude()const;

	float SQMagnitude()const;

	///���K��(�傫�����P��)���܂�
	void Normalize();

	///���K���x�N�g����Ԃ��܂�
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

///���ς�Ԃ�
float Dot(const Vector3& va, const Vector3& vb);

///�O�ς�Ԃ�
Vector3 Cross(const Vector3& va, const Vector3& vb);

///���ω��Z�q
Vector3 operator*(const Vector3& va, const Vector3& vb);
Vector3 operator*(float, const Vector3& vec);

///�O�ω��Z�q
Vector3 operator%(const Vector3& va, const Vector3& vb);
typedef Vector3 Position3;

///�~��\���\����
struct Circle {
	float radius;//���a
	Position2 pos; //���S���W
	Circle() :radius(0), pos(0, 0) {}
	Circle(float v, Position2& p) :radius(v), pos(p) {}
};

///��`��\���\����
struct Rect {
	Position2 pos; //���S���W
	int w, h;//��,����
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
	void Draw();//�����̋�`��`�悷��
	void Draw(Vector2& offset);//�����̋�`��`�悷��(�I�t�Z�b�g�t��)
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
