#include "currentloop.h"

CurrentLoop::CurrentLoop(double minVal, double maxVal, double current)
{
    this->min_val = min_val;
    this->max_val = max_val;
    this->current_val = current_val;
}

double CurrentLoop::calc_x()
{
    return min_val + (max_val - min_val) * (current_val - 4) / 16;
}
