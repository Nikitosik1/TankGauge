#ifndef CURRENTLOOP_H
#define CURRENTLOOP_H


class CurrentLoop
{
private:
    double min_val, max_val, current_val;
public:
    CurrentLoop(double min_val, double max_val, double current_val);
//перевод тока
    double calc_x();
};

#endif // CURRENTLOOP_H
