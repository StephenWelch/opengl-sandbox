#pragma once

#include <deque>

class MovingAverage {
 private:
	int numSamples;
	double runningTotal;
	std::deque<double> samples;

 public:
	MovingAverage(int numSamples);
	double update(double sample);
	double getAverage() const;
};