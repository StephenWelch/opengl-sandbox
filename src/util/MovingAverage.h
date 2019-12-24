#pragma once

#include <deque>

class MovingAverage {
private:
  int numSamples;
  double runningTotal;
  std::deque<double> samples;
public:
  MovingAverage(const int& numSamples);
  double update(const double& sample);
  double getAverage() const;
};