#ifndef TONKGAUGE_H
#define TONKGAUGE_H


class TankGauge
{
public:

    double calc_s_area(double v_Val, double h_Val);
    double calc_s_mid(double v_Val, double v_Val_2,double h_Val, double h_Val_2);
    double calc_press_air(double p_Val, double p_Val_2, double h_Val, double h_Val_2);
    double calc_mass_val(double s_Val, double s_Val_2, double p_Val, double p_Val_2);
};

#endif // TANKGAUGE_H
