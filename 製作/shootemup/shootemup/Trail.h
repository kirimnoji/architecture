#pragma once

#include <list>
#include "Geometry.h"

struct HomingShot;

// ãOê’
class Trail
{
private:
	int handle_;
	HomingShot& owner_;
	std::list<Position2> history_;

public:
	Trail(HomingShot& owner);
	void SetHandle(int handle);
	void Update();
	void Draw();
	void Clear();

};

