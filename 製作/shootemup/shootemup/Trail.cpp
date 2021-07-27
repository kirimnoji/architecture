#include "Trail.h"
#include "HomingShot.h"

#include <DxLib.h>

constexpr size_t history_limit = 20;

Trail::Trail(HomingShot& owner) :owner_(owner)
{

}

void Trail::Update()// —š—ðXV
{
	history_.push_front(owner_.pos);
	if (history_.size() > history_limit)
	{
		history_.pop_back();
	}
}

void Trail::Draw()	// —š—ð•`‰æ
{
	float thickness = 20.0f;
	auto lastPos = owner_.pos;
	for (const auto& pos : history_)
	{
		DrawLineAA(lastPos.x, lastPos.y,
			pos.x, pos.y, 0xffffff, thickness);
		thickness *= 0.9f;
		lastPos = pos;
	}
}

void Trail::Clear()
{
	history_.clear();
}
