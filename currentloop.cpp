#include "currentloop.h"

CurrentLoop::CurrentLoop(double minVal, double maxVal, double current)
{
    this->minVal = minVal;
    this->maxVal = maxVal;
    this->current = current;
}

double CurrentLoop::calc_x()
{
    return minVal + (maxVal - minVal) * (current - 4) / 16;
}
