#pragma once

#include <chrono>

unsigned long long
GetTickCount()
{
	using namespace std::chrono;
	return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}

// Clock built upon Windows GetTickCount()
struct TickCountClock
{
	typedef unsigned long long                       rep;
	typedef std::milli                               period;
	typedef std::chrono::duration<rep, period>       duration;
	typedef std::chrono::time_point<TickCountClock>  time_point;
	static const bool is_steady = true;

	static time_point now() noexcept
	{
		return time_point(duration(GetTickCount()));
	}
};