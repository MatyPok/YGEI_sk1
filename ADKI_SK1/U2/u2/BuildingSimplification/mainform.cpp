#include "mainform.h"
#include "ui_mainform.h"
#include "algorithms.h"

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

}


void MainForm::on_actionMBR_triggered()
{
    //create minimum bounding rectangle

    //get data
    QPolygonF building = ui->Canvas->getBuilding();

    // run function
    //QPolygonF ch = Algorithms::createCH(building);
    QPolygonF maer = Algorithms::createMAER(building);

    //set results
    //ui->Canvas->setCH(ch);
    ui->Canvas->setMAER(maer);

    //repaint
    repaint();
}


void MainForm::on_actionPCA_triggered()
{
    //create minimum bounding rectangle

    //get data
    QPolygonF building = ui->Canvas->getBuilding();

    // run function
    //QPolygonF ch = Algorithms::createCH(building);
    QPolygonF erpca = Algorithms::createERPCA(building);

    //set results
    //ui->Canvas->setCH(ch);
    ui->Canvas->setERPCA(erpca);

    //repaint
    repaint();
}



void MainForm::on_actionLE_triggered()
{
    //get data
    QPolygonF building = ui->Canvas->getBuilding();

    //run function
    QPolygonF le = Algorithms::createLongesEdge(building);

    //ui->Canvas->setCH(ch);
    ui->Canvas->setLE(le);

    //repaint
    repaint();

}

