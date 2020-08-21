#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "util/MovingAverage.h"

class SimpleTimer {
 private:
	bool started = false;
	double lastTime = 0;
	double deltaTime = 0;
	double currentTime = 0;
	MovingAverage movingAverage;

 public:
	explicit SimpleTimer(int samples = 0) : movingAverage(samples) {};
	double mark();
	double getDelta();
	double getMovingAverage();
	double getLastMarkTime() const;
};