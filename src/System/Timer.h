#pragma once
#include <functional>

class Timer
{
public:
	Timer() = default;

	void update(const double delta);
	void start(const double duration);

	void setCallback(std::function<void()> callback);
private:
	std::function<void()> m_callback;
	double m_timeLeft{ 0 };
	bool m_isRunning{ false };
};