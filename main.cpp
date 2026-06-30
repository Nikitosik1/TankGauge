#include <iostream>
#include "currentloop.h"
#include "tankgauge.h"
#include <cmath>
#include <map>

// press = 17.776
// lvl = 4.0117035


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

    const double k_0 = 613.9723;
    const double alpha = 12.5 *  pow(10,-6);
    const float g_val = 9.815;

    double t_curr_val1, t_curr_val2, t_curr_val3, d_curr_val, fi_chlor_salt, w_water_cont, p_curr_val,
            v_val, h_curr_val, w_mech_impur;

    cout << "Enter temp 1(mA):    " << endl;
    cin >> t_curr_val1;
    double temp_calc_val1 = func_calc_temp(t_curr_val1);

    cout << "Enter temp 2(mA):    " << endl;
    cin >> t_curr_val2;
    double temp_calc_val2 = func_calc_temp(t_curr_val2);

    cout << "Enter temp 3(mA):    " << endl;
    cin >> t_curr_val3;
    double temp_calc_val3 = func_calc_temp(t_curr_val3);

    cout << "Enter pressure(mA):" << endl;
    cin >> p_curr_val;
    CurrentLoop calc_press(P_min, P_max, p_curr_val);
    double press_calc_val = calc_press.calc_x();

    cout << "Enter level(mA):   " << endl;
    cin >> h_curr_val;
    CurrentLoop calc_lvl(Y_min, Y_max, h_curr_val);
    double level_calc_val = calc_lvl.calc_x();

    cout << "Enter density(mA):   " << endl;
    cin >> d_curr_val;
    CurrentLoop calc_denst(d_min, d_max, d_curr_val);
    double denst_calc_val = calc_denst.calc_x();

    std::map<double, int> volume;
    volume[0.1] = 324; volume[0.2] = 892;
    volume[0.3] = 1678; volume[0.4] = 2634;
    volume[0.5] = 3712; volume[0.6] = 4889;
    volume[0.7] = 6123; volume[0.8] = 7412;
    volume[0.9] = 7856; volume[1] = 9425;
    volume[1.1] = 11032; volume[1.2] = 12650;
    volume[1.3] = 14256; volume[1.4] = 15823;
    volume[1.5] = 17234; volume[1.6] = 17896;
    volume[1.7] = 18234; volume[1.8] = 19876;
    volume[1.9] = 21345; volume[2] = 22678;
    volume[2.1] = 23812; volume[2.2] = 24598;
    volume[2.3] = 24892; volume[2.4] = 25000;
//    {
//        {0.1,324},{0.2,892},{0.3,1678},{0.4,2634},
//        {0.5,3712},{0.6,4889},{0.7,6123},{0.8,7412},
//        {0,9,7856},{1,9425},{1.1,11032},{1.2,12650},
//        {1.3,14256},{1.4,15823},{1.5,17234},{1.6 , 17896},
//        {1.7,18234},{1.8,19876},{1.9,21345},{2 , 22678},
//        {2.1,23812},{2.2,24598},{2.3,24892},{2.4 , 25000}
//    };

    double round_lvl_val = round(level_calc_val * 10)/10;
    v_val = volume[round_lvl_val];

    cout<< round_lvl_val << endl;

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

    cout << "\nTemp :  " << t_val << endl;
    cout << "Pressur :    " << press_calc_val << endl;
    cout << "Level :    " << level_calc_val << endl;
    cout << "Volume:       " << v_val << endl;
    cout << "Density:       " << d_curr_val << endl;
    cout << "Mass:       " << m_netto_val << endl;
}
