#include <chrono>
#include "Timer.h"

std::chrono::system_clock::time_point g_LastTime;

void InitTimer()
{
	g_LastTime = std::chrono::system_clock::now();
}

float GetDeltaTime()
{
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

	std::chrono::duration<float, std::milli> elapsed = now - g_LastTime;

	float elapsedSec = elapsed.count() * 0.001f;

	g_LastTime = now;

	return elapsedSec;
}
