#ifndef TONKGAUGE_H
#define TONKGAUGE_H


class TankGauge
{
public:

    double calc_t_v(double t_val_1, double t_val_2, double t_val_3);
    double calc_beta(double val_k_0, double p_val);
    double calc_k_val(double t_Val, int choice);
    double calc_CTL_val(double beta_val, double t_val, int choice);
    double calc_d_oil(double d_val, double k_val, double ctl_val);
    double calc_s_avg(double v_val, double alpha_val, double t_val, double h_val);
    double calc_m_brutto(float g_val, double d_val, double s_val);
    double calc_w_salt(double fi_salt_val, double d_val, double ctl_val);
    double calc_m_ballast(double brutto_val, double w_water_val, double w_mech_val, double w_chlor_val);
    double calc_m_netto(double brutto_val, double ballast_val);
    double calc_k_koef(double v_tabl_val, double h_val, double v_val);
    double calc_error_abs(double p_err_val, double k_err_val, double k_geom_form, double h_err_val, double n_err_val);
    double calc_err_water(double R_val, double r_val);
    double calc_err_mech(double R_val, double r_val);
    double calc_err_cl(double R_val, double r_val, double d_val);
    double calc_netto_error(double brutto_err_val, double err_water_val, double err_mech_val, double err_cl_val, double water_val, double mech_val, double cl_val);
};

#endif // TANKGAUGE_H
