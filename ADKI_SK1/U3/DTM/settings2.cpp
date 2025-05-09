#include "settings2.h"
#include "ui_settings2.h"

Settings2::Settings2(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Settings2)
{
    ui->setupUi(this);

    //Initializuj values
    z_min = 100;
    z_max = 1500;
    dz = 10;

    //Set values to spin boxes
    ui->spinBox->setValue(z_min);
    ui->spinBox_2->setValue(z_max);
    ui->spinBox_3->setValue(dz);

}

Settings2::~Settings2()
{
    delete ui;
}


void Settings2::on_spinBox_editingFinished()
{
    //Actualize zmin
    z_min = ui->spinBox->value();
}


void Settings2::on_spinBox_2_editingFinished()
{
    //Actualize zmax
    z_max = ui->spinBox_2->value();
}


void Settings2::on_spinBox_3_editingFinished()
{
    //Actualize dz
    z_max = ui->spinBox_3->value();
}

