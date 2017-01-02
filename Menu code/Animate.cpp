#include "Animate.h"
#include <time.h>

Animate gAnimate;

float Animate::easeOut(float start, float end, float speed)
{
	if (start > end || speed <= 1)
		return end;

	if (timer())
	{
		if (start < end)
			return start * speed;
		return end;
	}
	return start;
}

float Animate::easeIn(float start, float end, float speed)
{
	if (start < end || speed >= 1)
		return end;

	if (timer())
	{
		if (start > end)
			return start * speed;
		return end;
	}
	return start;
}

float Animate::linear(float start, float end, float speed)
{
	if (start < end)
		return start + speed;
	return end;
}

bool Animate::timer()
{
	int t = clock();
	static int i = 0;

	if (t > i)
	{
		i += 1;
		return true;
	}
	return false;
}