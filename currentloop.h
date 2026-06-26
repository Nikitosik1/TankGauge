#ifndef CURRENTLOOP_H
#define CURRENTLOOP_H


class CurrentLoop
{
private:
    double minVal, maxVal, current;
public:
    CurrentLoop(double minVal, double maxVal, double current);

    double calc_x();
};

#endif // CURRENTLOOP_H
