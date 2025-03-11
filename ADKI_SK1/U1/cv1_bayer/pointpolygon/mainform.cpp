#include "mainform.h"
#include "./ui_mainform.h"

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
    if(res == 1)
        setWindowTitle("Inside");
    else
        setWindowTitle("Outside");

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














