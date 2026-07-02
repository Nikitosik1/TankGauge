#include <iostream>
#include "currentloop.h"
#include "tankgauge.h"
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>


using namespace std;

int func_chs(){
    int chs_15_20;
    cout << "Enter CTL(15 or 20):   " << endl;
    cin >> chs_15_20;

    if(chs_15_20 != 15 && chs_15_20 != 20){
        cout << "Error! Invalid CTL value!" << endl;
        func_chs();
    }
    else{
        return chs_15_20;
    }
}

double func_calc_temp(double t_val){
//функция для нахождения средней температуры в резервуаре
    const double t_min = 0;
    const double t_max = 100;

    CurrentLoop calc_temp_1(t_min, t_max, t_val);
    double tempr_calc_val1 = calc_temp_1.calc_x();

    return tempr_calc_val1;
}

int main()
{
    TankGauge TG;

    const double p_min = 0;
    const double p_max = 15000;

    const double h_min = 0;
    const double h_max = 2.4;

    float d_min = 0;
    float d_max = 1500;

    const double k_0 = 613.9723; //из таблицы госта
    const double alpha = 12.5 *  pow(10,-6); //из госта
    const float g_val = 9.815; //ускорение свободного падения
    const double n_about_val = 0.05; //из госта
    const double v_tabl_val = 9425; //из градуировочной таблицы для 1м.
    const double R_water = 0.11; // из госта 2477
    const double r_water = 0.08; // из госта 2477
    const double R_mech = 0.02; // из госта 6370
    const double r_mech = 0.01; // из госта 6370
    const double R_cl = 4.2; // из госта 21534
    const double r_cl = 1.5; // из госта 21534

    double t_curr_val1, t_curr_val2, t_curr_val3, d_curr_val, fi_chlor_salt, w_water_cont, p_curr_val,
            v_val, h_curr_val, w_mech_impur;

    cout << "Enter temp 1(mA):    " << endl;
    cin >> t_curr_val1;//температура 1
//    double temp_calc_val1 = func_calc_temp(t_curr_val1);
    double temp_calc_val1 = t_curr_val1;
    cout << "Enter temp 2(mA):    " << endl;
    cin >> t_curr_val2;//температура 2
//    double temp_calc_val2 = func_calc_temp(t_curr_val2);
    double temp_calc_val2 = t_curr_val2;
    cout << "Enter temp 3(mA):    " << endl;
    cin >> t_curr_val3;//температура 2
//    double temp_calc_val3 = func_calc_temp(t_curr_val3);
    double temp_calc_val3 = t_curr_val3;
    cout << "Enter pressure(mA):" << endl;
    cin >> p_curr_val;//давление
    CurrentLoop calc_press(p_min, p_max, p_curr_val);
//    double press_calc_val = calc_press.calc_x();
    double press_calc_val = p_curr_val;
    cout << "Enter level(mA):   " << endl;
    cin >> h_curr_val;//высота
    CurrentLoop calc_lvl(h_min, h_max, h_curr_val);
//    double level_calc_val = calc_lvl.calc_x();
    double level_calc_val = h_curr_val;
    cout << "Enter density(mA):   " << endl;
    cin >> d_curr_val;//плотность
    CurrentLoop calc_denst(d_min, d_max, d_curr_val);
//    double denst_calc_val = calc_denst.calc_x();
    double denst_calc_val = d_curr_val;
//градуировочная таблица
    vector<double>hight = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0,
                                 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0,
                                 2.1, 2.2, 2.3, 2.4};

        vector<int>volume = {324, 892, 1678, 2634, 3712, 4889, 6123, 7412, 7856, 9425,
                              11032, 12650, 14256, 15823, 17234, 17896, 18234, 19876,
                              21345, 22678, 23812, 24598, 24892, 25000};

    v_val = TG.calc_interpolate_volume(hight,volume,level_calc_val);
    //расчет для градуировочноый таблицы

    cout << "Enter chloride salts:   " << endl;
    cin >> fi_chlor_salt;//массовая доля хлористых солей в нефти

    cout << "Enter mechanical impurities:   " << endl;
    cin >> w_mech_impur;//массовая доля механических примесей в нефти

    cout << "Enter water content:   " << endl;
    cin >> w_water_cont;//массовая доля воды

    double t_val = TG.calc_t_v(t_curr_val1, t_curr_val2, t_curr_val3);

    double beta_val = TG.calc_beta(k_0, denst_calc_val);

    int choice_15_20 = func_chs();

    double k_val = TG.calc_k_val(t_val, choice_15_20);
    double ctl_val = TG.calc_CTL_val(beta_val, t_val, choice_15_20);

    double d_oil_val = TG.calc_d_oil(denst_calc_val, k_val, ctl_val);

    double s_avg_val = TG.calc_s_avg(v_val, alpha, t_val, level_calc_val);

    double m_brutto_val = TG.calc_m_brutto(g_val, denst_calc_val, s_avg_val);

    double w_salt_val = TG.calc_w_salt(fi_chlor_salt, denst_calc_val, ctl_val);

    double m_ballast_val = TG.calc_m_ballast(m_brutto_val, w_water_cont, w_mech_impur, w_salt_val);
    double m_netto_val = TG.calc_m_netto(m_brutto_val, m_ballast_val);

    double k_koef_val = TG.calc_k_koef(v_tabl_val, level_calc_val, v_val);

    double k_tab_val = level_calc_val/3; //3м диаметр бака
    double error_abs = TG.calc_error_abs(0.075*(p_max/press_calc_val), k_tab_val,
                                         k_koef_val, 0.003/level_calc_val, n_about_val);

    double err_w_water = TG.calc_err_water(R_water,r_water);
    double err_w_mech = TG.calc_err_mech(R_mech,r_mech);
    double err_w_cl = TG.calc_err_cl(R_cl,r_cl,d_oil_val);

    double err_m_netto = TG.calc_netto_error(error_abs,err_w_water,err_w_mech,
                                             err_w_cl,w_water_cont,w_mech_impur,w_salt_val);

    cout << "\nTemp :  " << t_val << endl;
    cout << "Pressur :    " << press_calc_val << endl;
    cout << "Level :    " << level_calc_val << endl;
    cout << "Volume:       " << v_val << endl;
    cout << "Density:       " << d_curr_val << endl;
    cout << "Mass:       " << m_netto_val << endl;
    cout << "Relative measurement error: " << err_m_netto << endl;
}
