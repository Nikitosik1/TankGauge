#include "tankgauge.h"

double TankGauge::calc_s_area(double v_Val, double h_Val){
    return (v_Val / h_Val);
}

double TankGauge::calc_s_mid(double v_Val, double v_Val_2,double h_Val, double h_Val_2){
    return ((v_Val - v_Val_2) / (h_Val - h_Val_2));
}

double TankGauge::calc_press_air(double p_Val, double p_Val_2, double h_Val, double h_Val_2){
    return p_Val - p_Val_2 - 1.3 * (h_Val - h_Val_2);
}

double TankGauge::calc_mass_val(double s_Val, double s_Val_2, double p_Val, double p_Val_2){
    return (s_Val * p_Val / 9.815 - s_Val_2 * p_Val_2 / 9.815);
}
