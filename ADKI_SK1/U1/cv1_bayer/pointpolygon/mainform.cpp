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
    QVector<QPolygonF> polygons = ui->Canvas->getPolygons();

    short res = 0;
    int index= -1;

    for (int i = 0; i < polygons.size(); ++i) {
        if (algorithms::isPointInMinMaxBoxOfPolygon(q, polygons[i])) {
            res = algorithms::analyzePointndPolPosition(q, polygons[i]);
            if (res == 1) {
                index = i;
                break;
            }
        }
    }

    //show results
    if (index != -1) {
        setWindowTitle("Inside");
        ui->Canvas->highlightPolygon(index);
    } else {
        setWindowTitle("Outside");
    }
}


void MainForm::on_actionWinding_Number_triggered()
{
    //RUN WINDING NUMBER ALGORITHM

    //get data
    QPointF q = ui->Canvas->getQ();
    QVector<QPolygonF> polygons = ui->Canvas->getPolygons();

    short res = 0;
    int highlightedIndex = -1;

    for (int i = 0; i < polygons.size(); ++i) {
        if (algorithms::isPointInMinMaxBoxOfPolygon(q, polygons[i])) {
            res = algorithms::WindingNumber(q, polygons[i]);
            if (res == 1 || res == -2 || res == -3) {
                highlightedIndex = i;
                break;
            }
        }
    }


    //show results
    if (highlightedIndex != -1) {
        if (res == 1) setWindowTitle("Inside");
        else if (res == -2) setWindowTitle("Vertex");
        else if (res == -3) setWindowTitle("Edges");
        ui->Canvas->highlightPolygon(highlightedIndex);
    } else {
        setWindowTitle("Outside");
    }

}



void MainForm::on_actionOpen_triggered(){

    //input polygons from txt
    ui->Canvas->openFile();

}



void MainForm::on_actionOpen_SHP_triggered()
{
    //load shp with gdal
    ui->Canvas->openSHP();
}



void MainForm::on_actionHighlight_Polygon_triggered()
{
    // Highlight the first polygon (index 0) - or prompt for user input to choose which one
    QVector<QPolygonF> polygons = ui->Canvas->getPolygons();
    if (!polygons.isEmpty()) {
        ui->Canvas->highlightPolygon(0);
    } else {
        qDebug() << "No polygons available to highlight!";
    }
}












