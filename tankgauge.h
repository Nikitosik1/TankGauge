#ifndef TONKGAUGE_H
#define TONKGAUGE_H
#include <vector>

//Структура для входных данных
struct TGInput {
    std::vector<double> height;
    std::vector<double> volume;
    double t_curr_val1;
    double t_curr_val2;
    double t_curr_val3;
    int choice_15_20;
    double k_0;
    double denst_calc_val;
    double alpha;
    double level_calc_val;
    double g_val;
    double fi_chlor_salt;
    double w_water_cont;
    double w_mech_impur;
    double v_tabl_val;
    double p_max;
    double press_calc_val;
    int n_about_val;
    double R_water;
    double r_water;
    double R_mech;
    double r_mech;
    double R_cl;
    double r_cl;
};

// Структура для результатов
struct TGOutput {
    double v_val_interp;
    double t_val;
    double beta_val;
    double k_val;
    double ctl_val;
    double d_oil_val;
    double s_avg_val;
    double m_brutto_val;
    double w_salt_val;
    double m_ballast_val;
    double m_netto_val;
    double k_koef_val;
    double k_tab_val;
    double error_abs;
    double err_w_water;
    double err_w_mech;
    double err_w_cl;
    double err_m_netto;
};



class TankGauge
{
public:
    TGOutput calculate_all(TGInput& input);
private:
    //расчет температуры стенки резервуара
    double calc_t_v(double t_val_1, double t_val_2, double t_val_3);

    //расчет коэфицента расширения рабочей среды
    double calc_beta(double val_k_0, double p_val);

    //поправочный коэффицент на темп. расширения тепла для ареометров
    double calc_k_val(double t_val, int choice);

    //поправочный коэффицент учитывающий влияние темп. нефти на их объем
    double calc_CTL_val(double beta_val, double t_val, int choice);

    //плотность нефти в резервуаре
    double calc_d_oil(double d_val, double k_val, double ctl_val);

    //средняя площадь поперечного сечения наполненной части резервуара
    double calc_s_avg(double v_val, double alpha_val, double t_val, double h_val);

    //формула для расчета массы брутто
    double calc_m_brutto(float g_val, double d_val, double s_val);

    //расчет массовой доли хлористых солей в нефти
    double calc_w_salt(double fi_salt_val, double d_val, double ctl_val);

    //формула для расчета массы балласта
    double calc_m_ballast(double brutto_val, double w_water_val, double w_mech_val, double w_chlor_val);

    //расчет массы нетто
    double calc_m_netto(double brutto_val, double ballast_val);

    double calc_k_koef(double v_tabl_val, double h_val, double v_val);

    //расчет относительной погрешности измерения массы брутто
    double calc_error_abs(double p_err_val, double k_err_val, double k_geom_form, double h_err_val, double n_err_val);

    //абсолютная пошрешность массовой доли воды в нефти
    double calc_err_water(double R_w_val, double r_w_val);

    //абсолютная пошрешность массовой доли механической примеси в нефти
    double calc_err_mech(double R_mech_val, double r_mech_val);

    //абсолютная пошрешность массовой доли хлористых солей в нефти
    double calc_err_cl(double R_cl_val, double r_cl_val, double d_val);

    //относительная погрешность измерений массы нетто нефти
    double calc_netto_error(double brutto_err_val, double err_water_val, double err_mech_val,
                            double err_cl_val, double water_val, double mech_val, double cl_val);

    //расчет интерполяции для нахождения объема по высоте
    double calc_interpolate_volume(std::vector<double>&h_val, std::vector<double>&v_val, double find_v_val);
};

#endif // TANKGAUGE_H
