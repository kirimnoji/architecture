#include "Trail.h"
#include "HomingShot.h"

#include <DxLib.h>

constexpr size_t history_limit = 20;
void Trail::SetHandle(int handle)
{
	handle_ = handle;
}

Trail::Trail(HomingShot& owner) :owner_(owner)
{

}

void Trail::Update()// �����X�V
{
	history_.push_front(owner_.pos);
	if (history_.size() > history_limit)
	{
		history_.pop_back();
	}
}

void Trail::Draw()	// ����`��
{
	float thickness = 5.0f;
	auto lastPos = owner_.pos;
	if (history_.empty())return;
	float div = 1.f / static_cast<float>(history_.size());
	float u = 0.f;
	for (const auto& pos : history_)
	{
		if ((pos.x == lastPos.x) && (pos.y == lastPos.y))continue;
		/*DrawLineAA(lastPos.x, lastPos.y,
			pos.x, pos.y, 0xffffff, thickness);
		thickness *= 0.9f;*/

		auto v = pos - lastPos;
		v.Magnitude();
		v = Vector2(-v.y, v.x);
		auto p1 = lastPos + v * 2;
		auto p2 = pos + v * 2;
		auto p3 = pos - v * 2;
		auto p4 = lastPos - v * 2;
		DrawRectModiGraph(
			p1.x, p1.y,
			p2.x, p2.y,
			p3.x, p3.y,
			p4.x, p4.y,
			u * 256, 0,
			div * 256, 64, handle_, true);
		u += div;
		lastPos = pos;
	}
}

void Trail::Clear()
{
	history_.clear();
}
