#ifndef CALIBRATIONDIALOG_H
#define CALIBRATIONDIALOG_H

#include <QDialog>
#include <vector>

namespace Ui {
class CalibrationDialog;
}

class CalibrationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CalibrationDialog(QWidget *parent = 0);
    ~CalibrationDialog();
    std::vector<double> get_hight();
    std::vector<double> get_volume();
    void setData(const std::vector<double>& hights,
                                     const std::vector<double>& volumes);

private slots:
    void on_addButton_clicked();
    void on_deleteButton_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::CalibrationDialog *ui;
};

#endif // CALIBRATIONDIALOG_H
