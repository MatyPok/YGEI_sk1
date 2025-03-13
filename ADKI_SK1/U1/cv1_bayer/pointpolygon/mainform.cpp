#include "mainform.h"
#include "./ui_mainform.h"

#include "algorithms.h"
#include "gdal_priv.h"


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

void MainForm::on_actionPoint_Polygon_triggered()
{
    //change input: point q or polygon P
    ui->Canvas->switch_source();
}



void MainForm::on_actionRay_Crossing_triggered()
{
    //RUN RAY CROSSING ALGORITHM

    //get data
    QPointF q = ui->Canvas->getQ();
    QPolygonF pol = ui->Canvas->getPol();

    short res = 0;

    if (algorithms::isPointInMinMaxBoxOfPolygon(q,pol)){
        //run algorithm
        res = algorithms::analyzePointndPolPosition(q,pol);
        }

    //show results
    if(res == 1){
        setWindowTitle("Inside");
        ui->Canvas->highlightPolygon(0);
    } else {
        setWindowTitle("Outside");
    }
}


void MainForm::on_actionWinding_Number_triggered()
{
    //RUN WINDING NUMBER ALGORITHM

    //get data
    QPointF q = ui->Canvas->getQ();
    QPolygonF pol = ui->Canvas->getPol();

    short res = 0;

    if (algorithms::isPointInMinMaxBoxOfPolygon(q,pol)){
        //run algorithm
        res = algorithms::WindingNumber(q,pol);
    }

    //show results
    if(res==1){
        setWindowTitle("Inside");
        ui->Canvas->highlightPolygon(0);
    }else if(res==0){
        setWindowTitle("Outside");
    }else if (res == -2){
        setWindowTitle("Vertex");
    }else if (res == -3){
        setWindowTitle("Edges");
    }

}



void MainForm::on_actionOpen_triggered(){

    //input polygons from txt
    ui->Canvas->openFile();
    //ui->Canvas->repaint();

}



void MainForm::on_actionOpen_SHP_triggered()
{
    //load shp with gdal
    ui->Canvas->openSHP();
}



void MainForm::on_actionHighlight_Polygon_triggered()
{
    // Highlight the first polygon (index 0) - or prompt for user input to choose which one
    if (!ui->Canvas->getPol().isEmpty()) {
        ui->Canvas->highlightPolygon(0);  // Pass index of the polygon you want to highlight
    }
    else {
        qDebug() << "No polygons available to highlight!";
    }
}












