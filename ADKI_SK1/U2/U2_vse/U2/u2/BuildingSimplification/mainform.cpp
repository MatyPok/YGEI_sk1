#include "mainform.h"
#include "ui_mainform.h"
#include "algorithms.h"

// U1
#include "gdal_priv.h"

#include "QApplication"

#include <iostream>


MainForm::MainForm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainForm)
{
    ui->setupUi(this);
}

MainForm::~MainForm()
{
    delete ui;
}


void MainForm::on_actionOpen_triggered()
{
    // U1
    //input polygons from txt
    ui->Canvas->openFile();
}


void MainForm::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainForm::on_actionMBR_triggered()
{
    //create minimum bounding rectangle
    QVector<QPolygonF> polygons = ui->Canvas->getPolygons();
    QVector<QPolygonF> maer;

    // run function
    for (int i = 0; i < polygons.size(); ++i) {

        if (maer.isEmpty()) {
            maer.append(QPolygonF());
        }
        maer.append(Algorithms::createMAER(polygons[i]));

    }
    //set results
    ui->Canvas->setMAER(maer);
    //repaint
    repaint();
}


void MainForm::on_actionPCA_triggered()
{
    //create minimum bounding rectangle

    //get data
    QVector<QPolygonF> polygons = ui->Canvas->getPolygons();
    QVector<QPolygonF> erpca;


    // run function
    for (int i = 0; i < polygons.size(); ++i) {

        if (erpca.isEmpty()) {
            erpca.append(QPolygonF());
        }
        erpca.append(Algorithms::createERPCA(polygons[i]));

    }
    //set results
    ui->Canvas->setERPCA(erpca);

    //repaint
    repaint();
}



void MainForm::on_actionLE_triggered()
{
    //get data
    QVector<QPolygonF> polygons = ui->Canvas->getPolygons();
    QVector<QPolygonF> le;


    //run function
    for (int i = 0; i < polygons.size(); ++i) {

        if (le.isEmpty()) {
            le.append(QPolygonF());
        }
        le.append(Algorithms::createLongesEdge(polygons[i]));

    }
    ui->Canvas->setLE(le);

    //repaint
    repaint();

}



void MainForm::on_actionWE_triggered()
{
    //get data
    QVector<QPolygonF> polygons = ui->Canvas->getPolygons();
    QVector<QPolygonF> we;

    // run function
    for (int i = 0; i < polygons.size(); ++i) {

        if (we.isEmpty()) {
            we.append(QPolygonF());
        }
        we.append(Algorithms::createWE(polygons[i]));

    }

    //set results
    //ui->Canvas->setCH(ch);
    ui->Canvas->setWE(we);

    //repaint
    repaint();
}

void MainForm::on_actionWA_triggered()
{

    //get data
    QVector<QPolygonF> polygons = ui->Canvas->getPolygons();
    QVector<QPolygonF> wa;

    // run function
    for (int i = 0; i < polygons.size(); ++i) {

        if (wa.isEmpty()) {
            wa.append(QPolygonF());
        }
        wa.append(Algorithms::createWA(polygons[i]));

    }

    //set results
    //ui->Canvas->setCH(ch);
    ui->Canvas->setWA(wa);

    //repaint
    repaint();
}


void MainForm::on_actionJarvis_Scan_triggered()
{
    //get data
    QVector<QPolygonF> polygons = ui->Canvas->getPolygons();
    QVector<QPolygonF> ch;


    // run function
    for (int i = 0; i < polygons.size(); ++i) {

        if (ch.isEmpty()) {
            ch.append(QPolygonF());
        }
        ch.append(Algorithms::createCH(polygons[i]));

    }
    //set results
    ui->Canvas->setCH(ch);

    //repaint
    repaint();
}


void MainForm::on_actionGraham_Scan_triggered()
{
    //get data
    QVector<QPolygonF> polygons = ui->Canvas->getPolygons();
    QVector<QPolygonF> chGraham;


    // run function
    for (int i = 0; i < polygons.size(); ++i) {

        if (chGraham.isEmpty()) {
            chGraham.append(QPolygonF());
        }
        chGraham.append(Algorithms::createCH_Graham(polygons[i]));

    }
    //set results
    ui->Canvas->setCH(chGraham);

    //repaint
    repaint();
}

// U1


void MainForm::on_actionOpen_SHP_triggered()
{
    //load shp with gdal
    ui->Canvas->openSHP();
}


void MainForm::on_actionClear_results_triggered()
{
    ui->Canvas->clearResults();
    repaint();
}


void MainForm::on_actionClear_All_triggered()
{
    ui->Canvas->clear();
    repaint();
}






