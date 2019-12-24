#include "MovingAverage.h"

MovingAverage::MovingAverage(const int& numSamples)
{
  this->numSamples = numSamples;
  this->samples = std::deque<double>();
  this->runningTotal = 0;
}

double MovingAverage::update(const double& sample)
{
  if (samples.size() > numSamples) {
    runningTotal -= samples.front();
    samples.pop_front();
  }
  samples.push_back(sample);
  runningTotal += sample;
  return getAverage();
}

double MovingAverage::getAverage() const
{
  return runningTotal / (double)samples.size();
}
