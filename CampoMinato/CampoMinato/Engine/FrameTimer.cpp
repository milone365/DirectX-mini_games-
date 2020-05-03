#include "FrameTimer.h"

using namespace std::chrono;

Timer::Timer()
{
	last = steady_clock::now();
}

float Timer::Mark()
{
	auto old = last;
	last = steady_clock::now();
	const duration<float>frametime = last - old;
	return frametime.count();
}
