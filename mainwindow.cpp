#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "currentloop.h"
#include "tankgauge.h"
#include <QMessageBox>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    hight = {0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0,
                    1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0,
                    2.1, 2.2, 2.3, 2.4};

    volume = {324, 892, 1678, 2634, 3712, 4889, 6123, 7412, 7856, 9425,
                    11032, 12650, 14256, 15823, 17234, 17896, 18234, 19876,
                    21345, 22678, 23812, 24598, 24892, 25000};

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Calculate_clicked()
{
    TankGauge TG;
    try {
        TGInput input;

        input.height = hight;
        input.volume = volume;

        // Читаем значения из полей
        input.t_curr_val1 = ui->T1doubleSpinBox->value();
        input.t_curr_val2 = ui->T2doubleSpinBox_2->value();
        input.t_curr_val3 = ui->T3doubleSpinBox_3->value();
        input.level_calc_val = ui->HdoubleSpinBox_5->value();
        input.press_calc_val = ui->PdoubleSpinBox_4->value();
        input.denst_calc_val = ui->D_doubleSpinBox_6->value();
        input.fi_chlor_salt = ui->w_cldoubleSpinBox_7->value();
        input.w_mech_impur = ui->w_mech_doubleSpinBox_8->value();
        input.w_water_cont = ui->w_water_doubleSpinBox_9->value();
        input.choice_15_20 = ui->spinBox->value();

        input.k_0 = 613.9723; //из таблицы госта
        input.alpha = 12.5 *  pow(10,-6); //из госта
        input.g_val = 9.815; //ускорение свободного падения
        input.v_tabl_val = 9425; //из градуировочной таблицы для 1м.
        input.p_max = 15000;
        input.n_about_val = 0.05; //из госта
        input.R_water = 0.11; // из госта 2477
        input.r_water = 0.08; // из госта 2477
        input.R_mech = 0.02; // из госта 6370
        input.r_mech = 0.01; // из госта 6370
        input.R_cl = 4.2; // из госта 21534
        input.r_cl = 1.5; // из госта 21534

        TGOutput result = TG.calculate_all(input);

        QString message = QString(
            "====================================\n"
            "     РЕЗУЛЬТАТЫ РАСЧЕТА\n"
            "====================================\n\n"
            "────────────────────────────────────\n"
            "   Масса нетто             = %1 кг\n\n"
            "   ПОГРЕШНОСТИ:                %2\n"
            "────────────────────────────────────\n"
            " ДОПОЛНИТЕЛЬНЫЕ ПАРАМЕТРЫ:\n"
            "────────────────────────────────────\n"
            "  Плотность нефти         = %3 кг/м³\n"
            "  Температура               = %4 °C\n"
            "  Давление                  =%5  Па\n"
            "  Высота                    =%6   М\n"
            "  Объем                     =%7   м³\n"
            "===================================="
        )
        .arg(result.m_netto_val, 0, 'f', 4)
        .arg(result.err_m_netto, 0, 'f', 6)
        .arg(result.d_oil_val, 0, 'f', 4)
        .arg(result.t_val, 0, 'f', 2)
        .arg(input.press_calc_val, 0, 'f', 2)
        .arg(input.level_calc_val, 0, 'f', 2)
        .arg(result.v_val_interp, 0, 'f', 1);

        // Показываем диалоговое окно
        QMessageBox msgBox;
        msgBox.setWindowTitle("Результаты расчета");
        msgBox.setText(message);
        msgBox.setStyleSheet(
            "QMessageBox {"
            "    background-color: #f0f0f0;"
            "    font-family: 'Courier New', monospace;"
            "    font-size: 11pt;"
            "}"
            "QLabel {"
            "    min-width: 400px;"
            "    white-space: pre-wrap;"
            "}"
        );
        msgBox.exec();

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Ошибка",
                             QString("Произошла ошибка:\n%1").arg(e.what()));
    }
}

void MainWindow::on_caliborationButton_clicked(){
    CalibrationDialog dlg(this);
    dlg.setData(hight, volume);
    if(dlg.exec()==QDialog::Accepted){
        hight = dlg.get_hight();
        volume = dlg.get_volume();
    }
}
