#include"Geometry.h"
#include<cmath>
#include <algorithm>


void
Rect::Draw() {
	DxLib::DrawBox(Left()*2, Top()*2, Right()*2, Bottom()*2, 0xffffffff, false);
}

void
Rect::Draw(Vector2& offset) {
	DxLib::DrawBox((Left()+offset.x)*2, (Top()+offset.y)*2, (Right()+offset.x)*2, (Bottom()+offset.y)*2, 0xffffffff, false);
}

void
Vector2::operator+=(const Vector2& vec) {
	x += vec.x;
	y += vec.y;
}
void
Vector2::operator-=(const Vector2& vec) {
	x -= vec.x;
	y -= vec.y;
}

void
Vector2::operator*=(float scale) {
	x *= scale;
	y *= scale;
}

void Vector2::operator/=(float div)
{
	x /= div;
	y /= div;
}

bool 
Vector2::operator==(const Vector2& vec)const
{
	return x == vec.x && y == vec.y;
}

float
Vector2::Magnitude()const {
	return std:: sqrt(SQMagnitude());
}

float
Vector2::SQMagnitude()const{
	return x * x + y * y;
}

void 
Vector2::Normalize() {
	float mag = Magnitude();
	x /= mag;
	y /= mag;
}

Vector2
Vector2::Normalized()const {
	float mag = Magnitude();
	return { x / mag,	y / mag };
}

void
Vector2::Rotate90() {
	std::swap(x, y);
	x = -x;
}

Vector2 Vector2::Rotated90() const{
	return { -y,x };
}

Vector2 operator + (const Vector2& lval, const Vector2& rval) {
	return { lval.x + rval.x,lval.y + rval.y };
}
Vector2 operator - (const Vector2& lval, const Vector2& rval) {
	return { lval.x - rval.x,lval.y - rval.y };
}
Vector2 operator * (const Vector2& lval, float scale) {
	return { lval.x * scale,lval.y * scale };
}
Vector2 operator / (const Vector2& lval, float div) {
	return { lval.x / div,lval.y / div };
}

///���ς�Ԃ�
float
Dot(const Vector2& va, const Vector2& vb) {
	return va.x*vb.x + va.y*vb.y;
}

///�O�ς�Ԃ�
float
Cross(const Vector2& va, const Vector2& vb) {
	return va.x*vb.y - vb.x*va.y;
}

///���ω��Z�q
float 
operator*(const Vector2& va, const Vector2& vb) {
	return Dot(va, vb);
}

///�O�ω��Z�q
float 
operator%(const Vector2& va, const Vector2& vb) {
	return Cross(va, vb);
}


//-------��������3D�̃^�[��------
void
Vector3::operator*=(float scale) {
	x *= scale;
	y *= scale;
	z *= scale;
}

Vector3
Vector3::operator*(float scale)const {
	return Vector3(x*scale, y*scale,z*scale);
}

//Vector3
//Vector3::operator*(const Vector3& v) const {
//	return Vector3(x * v.x, y * v.y, z * v.z);
//}

Vector3 
operator+(const Vector3& va, const Vector3 vb) {
	return Vector3(va.x + vb.x, va.y + vb.y,va.z+vb.z);
}

Vector3 
operator-(const Vector3& va, const Vector3 vb) {
	return Vector3(va.x - vb.x, va.y - vb.y,va.z-vb.z);
}

float
Vector3::Magnitude()const {
	return sqrt(x*x+y*y+z*z);
}

float 
Vector3::SQMagnitude() const
{
	return (x * x + y * y + z * z);
}

void
Vector3::Normalize() {
	float mag = Magnitude();
	x /= mag;
	y /= mag;
	z /= mag;
}


Vector3
Vector3::Normalized() const{
	float mag = Magnitude();
	return Vector3(x / mag, y / mag,z/mag);
}


///���ς�Ԃ�
float
Dot(const Vector3& va, const Vector3& vb) {
	return va.x*vb.x + va.y*vb.y+va.z*vb.z;
}

///�O�ς�Ԃ�
Vector3
Cross(const Vector3& va, const Vector3& vb) {
	return Vector3(va.z*vb.y-va.y*vb.z,va.z*vb.x-va.x*vb.z,va.x*vb.y - vb.x*va.y);
}

///���ω��Z�q
Vector3
operator*(const Vector3& va, const Vector3& vb) {
	return Vector3(va.x * vb.x, va.y * vb.y, va.z * vb.z);
}

Vector3 
operator*(float scale, const Vector3& vec) {
	return vec * scale;
}

///�O�ω��Z�q
Vector3
operator%(const Vector3& va, const Vector3& vb) {
	return Cross(va, vb);
}


void
Vector3::operator+=(const Vector3& v) {
	x += v.x;
	y += v.y;
	z += v.z;
}
void
Vector3::operator-=(const Vector3& v) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

