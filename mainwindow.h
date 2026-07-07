#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "tankgauge.h"
#include "calibrationdialog.h"
#include <vector>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_caliborationButton_clicked();

    void on_Calculate_clicked();

    void on_T1doubleSpinBox_valueChanged(double arg1);

    void on_T2doubleSpinBox_2_valueChanged(double arg1);

    void on_T3doubleSpinBox_3_valueChanged(double arg1);

    void on_PdoubleSpinBox_4_valueChanged(double arg1);

    void on_HdoubleSpinBox_5_valueChanged(double arg1);

    void on_D_doubleSpinBox_6_valueChanged(double arg1);

    void on_w_cldoubleSpinBox_7_valueChanged(double arg1);

    void on_w_mech_doubleSpinBox_8_valueChanged(double arg1);

    void on_w_water_doubleSpinBox_9_valueChanged(double arg1);

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;

    TankGauge TG;

    std::vector<double> hight;
    std::vector<double> volume;

    double t_val_1;
    double t_val_2;
    double t_val_3;
    double p_val;
    double h_val;
    double d_val;
    double w_cl_val;
    double w_mech_val;
    double w_water_val;
    int choice_val;

    void updateResults(const TGOutput& result);

    QPushButton *pushButton();

};

#endif // MAINWINDOW_H
