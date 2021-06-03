
#include <DxLib.h>

#include "Singleton.h"

void Singleton::Out()
{
	int line = 50;
	DrawFormatString(10, line, 0xffffff, L"Cnt : %d", counter, true);
	counter++;
}
