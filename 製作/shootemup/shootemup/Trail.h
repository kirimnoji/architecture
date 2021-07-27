#pragma once

#include <list>
#include "Geometry.h"

class HomingShot;

// �O��
class Trail
{
private:
	HomingShot& owner_;
	std::list<Position2> history_;

public:
	Trail(HomingShot& owner);
	void Update();
	void Draw();
	void Clear();

};

