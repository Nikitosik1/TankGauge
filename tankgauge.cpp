#include "tankgauge.h"
#include <cmath>

double TankGauge::calc_t_v(double t_val_1, double t_val_2, double t_val_3){
    return (t_val_1,t_val_2,t_val_3)/3;
}

double TankGauge::calc_beta(double val_k_0, double p_val){
    return (val_k_0 * p_val)/(p_val * p_val);
}

double TankGauge::calc_k_val(double t_Val, int choice){

    if(choice == 15){
        return 1 - 0.000023 * (t_Val - 15) - 0.00000002 * ((t_Val - 15)*(t_Val - 15));
    }
    else {
        return 1 - 0.000025 * (t_Val - 20);
    }
}

double TankGauge::calc_CTL_val(double beta_val, double t_val, int choice) {

    if(choice == 15){
        return exp(- beta_val * (t_val - 15)*(1 + 0.8 * beta_val * (t_val - 15)));
    }
    else {
        return exp(- beta_val * (t_val - 20)*(1 + 0.8 * beta_val * (t_val - 20)));
    }
}

double TankGauge::calc_d_oil(double d_val, double k_val, double ctl_val){
    return (d_val * k_val)/ctl_val;
}

double TankGauge::calc_s_avg(double v_val, double alpha_val, double t_val, double h_val){
    return (v_val*(1+2*alpha_val*(t_val-20)))/h_val;
}

double TankGauge::calc_m_brutto(float g_val, double d_val, double s_val){
    return 1/g_val * d_val * s_val * pow(10, -3);
}

double TankGauge::calc_w_salt(double fi_salt_val, double d_val, double ctl_val){
    return (0.1 * fi_salt_val)/(d_val * ctl_val);
}

double TankGauge::calc_m_ballast(double brutto_val, double w_water_val, double w_mech_val, double w_chlor_val){
    return (brutto_val * w_water_val * w_mech_val * w_chlor_val) / 100;
}

double TankGauge::calc_m_netto(double brutto_val, double ballast_val){
    return brutto_val - ballast_val;
}
