#include <iostream>
#include "currentloop.h"
#include "tankgauge.h"
#include <cmath>
#include <map>

/*
 case TypeK: // Термопара типа K
        if (Value < -5.891) // <-200 C
        {
            uint8_t belowIndex = 0, aboveIndex = 1;
            for (belowIndex; belowIndex< 60; belowIndex++,aboveIndex++)
                if (Value < K_B0[belowIndex] && Value >= K_B0[aboveIndex])
                    break;
            
            if (belowIndex == 60)
                Temp = -270;
            else
            {
                Temp = -200 - belowIndex;
                Temp-= abs((K_B0[belowIndex] - Value)/(K_B0[belowIndex] - K_B0[aboveIndex]));
                if (Temp < -250)
                    Temp = -250.0 + (Temp + 250.0)/10.0; // -250 - max 1.0C;
            }
        }
        else if (Value <= 0)                                 // <= 0 C
            Temp = PolynomCorrection (K_B1, 9, Value);
        else if (Value <= 20.644)				        // <= 500 C
            Temp = PolynomCorrection (K_B2, 10, Value);
        else                                            // <= 1372 C
            Temp = PolynomCorrection (K_B3, 7, Value);
        break;

float K_B0[61] = {-5.891, -5.907, -5.922, -5.936, -5.951, -5.965, -5.980, -5.994, -6.007, -6.021, \
                  -6.035, -6.048, -6.061, -6.074, -6.087, -6.099, -6.111, -6.123, -6.135, -6.147, \
                  -6.158, -6.170, -6.181, -6.192, -6.202, -6.213, -6.223, -6.233, -6.243, -6.252, \
                  -6.262, -6.271, -6.280, -6.289, -6.297, -6.306, -6.314, -6.322, -6.329, -6.337, \
                  -6.344, -6.351, -6.358, -6.364, -6.370, -6.377, -6.382, -6.388, -6.393, -6.399, \
                  -6.404, -6.408, -6.413, -6.417, -6.421, -6.425, -6.429, -6.432, -6.435, -6.438, -6.441}; //<= -200 C

        
    */

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

    const double T_min = 0;
    const double T_max = 100;

    CurrentLoop calc_temp_1(T_min, T_max, t_val);
    double tempr_calc_val1 = calc_temp_1.calc_x();

    return tempr_calc_val1;
}

int main()
{
    TankGauge TG;

    const double P_min = 0;
    const double P_max = 100000;

    const double Y_min = 0;
    const double Y_max = 2.4;

    float d_min = 0;
    float d_max = 1500;

    const double k_0 = 613.9723; //из таблицы госта
    const double alpha = 12.5 *  pow(10,-6); //из госта
    const float g_val = 9.815;
    const double n_about_val = 0.05; //из госта
    const double v_tabl_val = 9425; //из градуировочной таблицы для 1м.
    const double R_water = 0.11; //
    const double r_water = 0.08;
    const double R_mech = 0.02;
    const double r_mech = 0.01;
    const double R_cl = 4.2;
    const double r_cl = 1.5;

    double t_curr_val1, t_curr_val2, t_curr_val3, d_curr_val, fi_chlor_salt, w_water_cont, p_curr_val,
            v_val, h_curr_val, w_mech_impur;

    cout << "Enter temp 1(mA):    " << endl;
    cin >> t_curr_val1;
//    double temp_calc_val1 = func_calc_temp(t_curr_val1);
    double temp_calc_val1 = t_curr_val1;
    cout << "Enter temp 2(mA):    " << endl;
    cin >> t_curr_val2;
//    double temp_calc_val2 = func_calc_temp(t_curr_val2);
    double temp_calc_val2 = t_curr_val2;
    cout << "Enter temp 3(mA):    " << endl;
    cin >> t_curr_val3;
//    double temp_calc_val3 = func_calc_temp(t_curr_val3);
    double temp_calc_val3 = t_curr_val3;
    cout << "Enter pressure(mA):" << endl;
    cin >> p_curr_val;
    CurrentLoop calc_press(P_min, P_max, p_curr_val);
//    double press_calc_val = calc_press.calc_x();
    double press_calc_val = p_curr_val;
    cout << "Enter level(mA):   " << endl;
    cin >> h_curr_val;
    CurrentLoop calc_lvl(Y_min, Y_max, h_curr_val);
//    double level_calc_val = calc_lvl.calc_x();
    double level_calc_val = h_curr_val;
    cout << "Enter density(mA):   " << endl;
    cin >> d_curr_val;
    CurrentLoop calc_denst(d_min, d_max, d_curr_val);
//    double denst_calc_val = calc_denst.calc_x();
    double denst_calc_val = d_curr_val;
//    std::map<double, int> volume;
//    volume[0.1] = 324; volume[0.2] = 892;
//    volume[0.3] = 1678; volume[0.4] = 2634;
//    volume[0.5] = 3712; volume[0.6] = 4889;
//    volume[0.7] = 6123; volume[0.8] = 7412;
//    volume[0.9] = 7856; volume[1] = 9425;
//    volume[1.1] = 11032; volume[1.2] = 12650;
//    volume[1.3] = 14256; volume[1.4] = 15823;
//    volume[1.5] = 17234; volume[1.6] = 17896;
//    volume[1.7] = 18234; volume[1.8] = 19876;
//    volume[1.9] = 21345; volume[2] = 22678;
//    volume[2.1] = 23812; volume[2.2] = 24598;
//    volume[2.3] = 24892; volume[2.4] = 25000;

//    double round_lvl_val = round(level_calc_val * 10)/10;
//    v_val = volume[round_lvl_val];

    v_val = -2209.8730 * level_calc_val * level_calc_val * level_calc_val
            + 7974.5161 * level_calc_val * level_calc_val + 4234.7677 * level_calc_val - 193.1146;

    cout << "Enter chloride salts:   " << endl;
    cin >> fi_chlor_salt;

    cout << "Enter mechanical impurities:   " << endl;
    cin >> w_mech_impur;

    cout << "Enter water content:   " << endl;
    cin >> w_water_cont;

    double t_val = TG.calc_t_v(t_curr_val1, t_curr_val2, t_curr_val3);

    double beta_val = TG.calc_beta(k_0, denst_calc_val);

    int choice_15_20 = func_chs();

    double k_val = TG.calc_k_val(t_val, choice_15_20);
    double ctl_val = TG.calc_CTL_val(beta_val, t_val, choice_15_20);

    double d_oil = TG.calc_d_oil(denst_calc_val, k_val, ctl_val);

    double s_avg_val = TG.calc_s_avg(v_val, alpha, t_val, level_calc_val);

    double m_brutto_val = TG.calc_m_brutto(g_val, denst_calc_val, s_avg_val);

    double w_salt_val = TG.calc_w_salt(fi_chlor_salt, denst_calc_val, ctl_val);

    double m_ballast_val = TG.calc_m_ballast(m_brutto_val, w_water_cont, w_mech_impur, w_salt_val);
    double m_netto_val = TG.calc_m_netto(m_brutto_val, m_ballast_val);

    double k_koef_val = TG.calc_k_koef(v_tabl_val, level_calc_val, v_val);

    double k_tab_val = level_calc_val/3; //3м диаметр
    float x_n = 15000;
    double error_abs = TG.calc_error_abs(0.075*(x_n/press_calc_val),k_tab_val,k_koef_val,0.003/level_calc_val,n_about_val);

    double err_w_water = TG.calc_err_water(R_water,r_water);
    double err_w_mech = TG.calc_err_mech(R_mech,r_mech);
    double err_w_cl = TG.calc_err_cl(R_cl,r_cl,d_oil);

    double err_m_netto = TG.calc_netto_error(error_abs,err_w_water,err_w_mech,err_w_cl,w_water_cont,w_mech_impur,w_salt_val);

    cout << "\nTemp :  " << t_val << endl;
    cout << "Pressur :    " << press_calc_val << endl;
    cout << "Level :    " << level_calc_val << endl;
    cout << "Volume:       " << v_val << endl;
    cout << "Density:       " << d_curr_val << endl;
    cout << "Mass:       " << m_netto_val << endl;
    cout << "relative measurement error: " << err_m_netto << endl;
}
