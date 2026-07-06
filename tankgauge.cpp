#include "tankgauge.h"
#include <cmath>
#include <vector>
#include <algorithm>

//расчет температуры стенки резервуара
double TankGauge::calc_t_v(double t_val_1, double t_val_2, double t_val_3){
    return (t_val_1+t_val_2+t_val_3)/3;
}

//расчет коэфицента расширения рабочей среды
double TankGauge::calc_beta(double val_k_0, double p_val){
    return (val_k_0 * p_val)/(p_val * p_val);
}

//поправочный коэффицент на темп. расширения тепла для ареометров
double TankGauge::calc_k_val(double t_val, int choice){

    if(choice == 15){
        return 1 - 0.000023 * (t_val - 15) - 0.00000002 * ((t_val - 15)*(t_val - 15));
    }
    else {
        return 1 - 0.000025 * (t_val - 20);
    }
}

//поправочный коэффицент учитывающий влияние темп. нефти на их объем
double TankGauge::calc_CTL_val(double beta_val, double t_val, int choice) {

    if(choice == 15){
        return exp(- beta_val * (t_val - 15)*(1 + 0.8 * beta_val * (t_val - 15)));
    }
    else {
        return exp(- beta_val * (t_val - 20)*(1 + 0.8 * beta_val * (t_val - 20)));
    }
}

//плотность нефти в резервуаре
double TankGauge::calc_d_oil(double d_val, double k_val, double ctl_val){
    return (d_val * k_val)/ctl_val;
}

//средняя площадь поперечного сечения наполненной части резервуара
double TankGauge::calc_s_avg(double v_val, double alpha_val, double t_val, double h_val){
    return (v_val*(1+2*alpha_val*(t_val-20)))/h_val;
}

//формула для расчета массы брутто
double TankGauge::calc_m_brutto(float g_val, double d_val, double s_val){
    return 1/g_val * d_val * s_val * pow(10, -3);
}

//расчет массовой доли хлористых солей в нефти
double TankGauge::calc_w_salt(double fi_salt_val, double d_val, double ctl_val){
    return (0.1 * fi_salt_val)/(d_val * ctl_val);
}

//формула для расчета массы балласта
double TankGauge::calc_m_ballast(double brutto_val, double w_water_val, double w_mech_val, double w_chlor_val){
    return (brutto_val * w_water_val * w_mech_val * w_chlor_val) / 100;
}

//расчет массы нетто
double TankGauge::calc_m_netto(double brutto_val, double ballast_val){
    return brutto_val - ballast_val;
}

//
double TankGauge::calc_k_koef(double v_tabl_val, double h_val, double v_val){
    return v_tabl_val * h_val / v_val;
}

//расчет относительной погрешности измерения массы брутто
double TankGauge::calc_error_abs(double p_err_val, double k_err_val, double k_geom_form, double h_err_val, double n_err_val){
    double square_root = (p_err_val * p_err_val) + (k_err_val * k_err_val) + (k_geom_form - 1)
            * (k_geom_form - 1) * (h_err_val * h_err_val) + (n_err_val * n_err_val);
    return 1.1 * pow(square_root, 0.5);
}

//абсолютная пошрешность массовой доли воды в нефти
double TankGauge::calc_err_water(double R_val, double r_val){
    double square_root = R_val * R_val - 0.5 * r_val * r_val;
    return pow(square_root, 0.5)/pow(2,0.5);
}

//абсолютная пошрешность массовой доли механической примеси в нефти
double TankGauge::calc_err_mech(double R_val, double r_val){
    double square_root = R_val * R_val * 0.5 * r_val * r_val;
    return pow(square_root, 0.5)/pow(2,0.5);
}

//абсолютная пошрешность массовой доли хлористых солей в нефти
double TankGauge::calc_err_cl(double R_val, double r_val, double d_val){
    double square_root = R_val * R_val - 0.5 * r_val * r_val;
    return 0.1 * pow(square_root, 0.5)/ d_val *pow(2,0.5);
}

//относительная погрешность измерений массы нетто нефти
double TankGauge::calc_netto_error(double brutto_err_val, double err_water_val, double err_mech_val, double err_cl_val, double water_val, double mech_val, double cl_val){
    double square_root = (brutto_err_val/1.1) * (brutto_err_val/1.1) +
            err_water_val * err_water_val + err_mech_val * err_mech_val + err_cl_val * err_cl_val /
            (1 - (water_val + mech_val + cl_val)/100) * (1 - (water_val + mech_val + cl_val)/100);
    return 1.1 * pow(square_root, 0.5);
}

//расчет интерполяции для нахождения объема по высоте
double TankGauge::calc_interpolate_volume(std::vector<double>& h_val, std::vector<int>& v_val, double find_v_val){

    auto it = std::find_if(h_val.begin(), h_val.end(),
                           [find_v_val](double value){return value >= find_v_val;});//поиск элемента
    if(it == h_val.end()){ //если совпадает с последним элементом
        return v_val.back();
    }

    size_t index = std::distance(h_val.begin(), it);

    if(std::abs(*it - find_v_val)<1e-9){ //совпадает со значением высоты
        return v_val[index];
    }

    if(index = 0){ //если это первый элемент
        return v_val.front();
    }

    double x1 = h_val[index + 1];
    double x2 = h_val[index];
    double y1 = v_val[index + 1];
    double y2 = v_val[index];

    return y1 + (y2 - y1) * (find_v_val - x1) / (x2 - x1);
}


TGOutput TG::calculateAll(const TGInput& input) {
    TGOutput result;
    
    result.v_val_interp = calc_interpolate_volume(input.height, input.volume, input.level_calc_val);
    result.t_val = calc_t_v(input.t_curr_val1, input.t_curr_val2, input.t_curr_val3);
    result.beta_val = calc_beta(input.k_0, input.denst_calc_val);
    result.choice_15_20 = func_chs();
    result.k_val = calc_k_val(result.t_val, result.choice_15_20);
    result.ctl_val = calc_CTL_val(result.beta_val, result.t_val, result.choice_15_20);
    result.d_oil_val = calc_d_oil(input.denst_calc_val, result.k_val, result.ctl_val);
    result.s_avg_val = calc_s_avg(input.v_val, input.alpha, result.t_val, input.level_calc_val);
    result.m_brutto_val = calc_m_brutto(input.g_val, input.denst_calc_val, result.s_avg_val);
    result.w_salt_val = calc_w_salt(input.fi_chlor_salt, input.denst_calc_val, result.ctl_val);
    result.m_ballast_val = calc_m_ballast(result.m_brutto_val, input.w_water_cont, 
                                         input.w_mech_impur, result.w_salt_val);
    result.m_netto_val = calc_m_netto(result.m_brutto_val, result.m_ballast_val);
    result.k_koef_val = calc_k_koef(input.v_tabl_val, input.level_calc_val, input.v_val);
    result.k_tab_val = input.level_calc_val / 3.0;
    result.error_abs = calc_error_abs(0.075 * (input.p_max / input.press_calc_val), 
                                      result.k_tab_val,
                                      result.k_koef_val, 
                                      0.003 / input.level_calc_val, 
                                      input.n_about_val);
    result.err_w_water = calc_err_water(input.R_water, input.r_water);
    result.err_w_mech = calc_err_mech(input.R_mech, input.r_mech);
    result.err_w_cl = calc_err_cl(input.R_cl, input.r_cl, result.d_oil_val);
    result.err_m_netto = calc_netto_error(result.error_abs, result.err_w_water, result.err_w_mech,
                                         result.err_w_cl, input.w_water_cont, 
                                         input.w_mech_impur, result.w_salt_val);
    
    return result;
}
