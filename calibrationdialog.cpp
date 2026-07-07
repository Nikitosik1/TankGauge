#include "calibrationdialog.h"
#include "ui_calibrationdialog.h"

CalibrationDialog::CalibrationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CalibrationDialog)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(2);

    QStringList headers;
    headers << "Высота" << "Объем";
    ui->tableWidget->setHorizontalHeaderLabels(headers);
}

CalibrationDialog::~CalibrationDialog()
{
    delete ui;
}

void CalibrationDialog::on_addButton_clicked(){
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
}

void CalibrationDialog::on_deleteButton_clicked(){
    int row = ui->tableWidget->currentRow();

    if(row >= 0)
        ui->tableWidget->removeRow(row);
}

std::vector<double>CalibrationDialog::get_hight(){
    std::vector<double> result;

    for(int i=0; i<ui->tableWidget->rowCount();i++){
        if(ui->tableWidget->item(i,0))
            result.push_back(ui->tableWidget->item(i,0)->text().toDouble());
    }
    return result;
}

std::vector<double>CalibrationDialog::get_volume(){
    std::vector<double> result;

    for(int i=0;i<ui->tableWidget->rowCount();i++){
        if(ui->tableWidget->item(i,1))
            result.push_back(ui->tableWidget->item(i,1)->text().toDouble());
    }
    return result;
}

void CalibrationDialog::setData(const std::vector<double>& heights,
                                 const std::vector<double>& volumes){
    ui->tableWidget->setRowCount(heights.size());

    for (size_t i = 0; i < heights.size(); ++i) {
        QTableWidgetItem *heightItem = new QTableWidgetItem(QString::number(heights[i], 'f', 2));
        QTableWidgetItem *volumeItem = new QTableWidgetItem(QString::number(volumes[i]));

        ui->tableWidget->setItem(i, 0, heightItem);
        ui->tableWidget->setItem(i, 1, volumeItem);
    }
}

void CalibrationDialog::on_buttonBox_accepted()
{
    accept();
}

void CalibrationDialog::on_buttonBox_rejected()
{
    reject();
}
