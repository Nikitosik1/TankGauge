#include "tankgauge.h"
#include <cmath>

double TankGauge::calc_t_v(double t_val_1, double t_val_2, double t_val_3){
    return (t_val_1+t_val_2+t_val_3)/3;
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

double TankGauge::calc_k_koef(double v_tabl_val, double h_val, double v_val){
    return v_tabl_val * h_val / v_val;
}

double TankGauge::calc_error_abs(double p_err_val, double k_err_val, double k_geom_form, double h_err_val, double n_err_val){
    double square_root = (p_err_val * p_err_val) + (k_err_val * k_err_val) + (k_geom_form - 1)
            * (k_geom_form - 1) * (h_err_val * h_err_val) + (n_err_val * n_err_val);
    return 1.1 * pow(square_root, 0.5);
}

double TankGauge::calc_err_water(double R_val, double r_val){
    double square_root = R_val * R_val - 0.5 * r_val * r_val;
    return pow(square_root, 0.5)/pow(2,0.5);
}

double TankGauge::calc_err_mech(double R_val, double r_val){
    double square_root = R_val * R_val * 0.5 * r_val * r_val;
    return pow(square_root, 0.5)/pow(2,0.5);
}

double TankGauge::calc_err_cl(double R_val, double r_val, double d_val){
    double square_root = R_val * R_val - 0.5 * r_val * r_val;
    return 0.1 * pow(square_root, 0.5)/ d_val *pow(2,0.5);
}

double TankGauge::calc_netto_error(double brutto_err_val, double err_water_val, double err_mech_val, double err_cl_val, double water_val, double mech_val, double cl_val){
    double square_root = (brutto_err_val/1.1) * (brutto_err_val/1.1) +
            err_water_val * err_water_val + err_mech_val * err_mech_val + err_cl_val * err_cl_val /
            (1 - (water_val + mech_val + cl_val)/100) * (1 - (water_val + mech_val + cl_val)/100);
    return 1.1 * pow(square_root, 0.5);
}
