#include <iostream>
#include "currentloop.h"
#include "tankgauge.h"

// press = 17.776
// lvl = 4.0117035


using namespace std;

int main()
{  
    const double T_min = 0;
    const double T_max = 100;

    const double P_min = 0;
    const double P_max = 100000;

    const double Y_min = 0;
    const double Y_max = 15000;

    double t_curr_val, p_curr_val, l_curr_val, t_phys_val, p_phys_val, l_phys_val;

    cout << "Enter temp(mA):    " << endl;
    cin >> t_curr_val;
    CurrentLoop calc_temp(T_min, T_max, t_curr_val);
    double tempr_calc_val = calc_temp.calc_x();

    cout << "Enter pressure(mA):" << endl;
    cin >> p_curr_val;
    CurrentLoop calc_press(P_min, P_max, p_curr_val);
    double press_calc_val = calc_press.calc_x();

    cout << "Enter level(mA):   " << endl;
    cin >> l_curr_val;
    CurrentLoop calc_lvl(Y_min, Y_max, l_curr_val);
    double level_calc_val = calc_lvl.calc_x();

    cout << "\nEnter temp:    " << endl;
    cin >> t_phys_val;

    cout << "Enter pressure:" << endl;
    cin >> p_phys_val;

    cout << "Enter level:   " << endl;
    cin >> l_phys_val;

    cout << "Enter volume before:  " << endl;
    cin >> v_curr_val;

    cout << "Enter volume after:  " << endl;
    cin >> v_phys_val;

    TankGauge TG;

    float s_curr_val = TG.calc_s_area(v_curr_val, level_calc_val);
    float s_phys_val = TG.calc_s_area(v_phys_val, l_phys_val);

    double s_calc_val = TG.calc_s_mid(v_curr_val, v_phys_val, level_calc_val, l_phys_val);

    double press_air_val = TG.calc_press_air(press_calc_val, p_phys_val, level_calc_val, l_phys_val);

    double mass_calc_val = TG.calc_mass_val(s_curr_val, s_phys_val, press_calc_val, p_phys_val);

    cout << "\nTemp(mA) :  " << tempr_calc_val << endl;
    cout << "Pres(mA) :  " << press_calc_val << endl;
    cout << "Levl(mA) :  " << level_calc_val << endl;
    cout << "Temp phys:  " << t_phys_val << endl;
    cout << "Pres phys:  " << p_phys_val << endl;
    cout << "Levl phys:  " << l_phys_val << '\n' << endl;
    cout << "Volm_After:       " << s_curr_val << endl;
    cout << "Volm_Before:      " << s_phys_val << endl;
    cout << "s mid value:       " << s_calc_val << endl;
    cout << "Pressure air:    " << press_air_val << endl;
    cout << "Mass:       " << mass_calc_val << endl;
}
