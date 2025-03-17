#include "mainform.h"
#include "./ui_mainform.h"

#include "algorithms.h"
#include "gdal_priv.h"

#include "QApplication"

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

    ui->Canvas->clearHighlighted();
    QVector<int> indices;
    short res = 0;

    bool isInside = false;
    bool isInVertex = false;
    bool isOnEdge = false;

    for (int i = 0; i < polygons.size(); ++i) {
        if (algorithms::isPointInMinMaxBoxOfPolygon(q, polygons[i])) {
            res = algorithms::analyzePointndPolPosition(q, polygons[i]);

            if (res == 1) {
                indices.push_back(i);
                isInside = true;
            } else if (res == -2) {
                indices.push_back(i);
                isInVertex = true;
            } else if (res == -1) {
                isOnEdge = true;
                indices.push_back(i);
            }

        }
    }

    ui->Canvas->highlightPolygon(indices);

    if (isInside) {
        setWindowTitle("Inside");
    } else if (isInVertex) {
        setWindowTitle("Vertex");
    } else if (isOnEdge) {
        setWindowTitle("Edge");
    } else setWindowTitle("Outside");
}

void MainForm::on_actionWinding_Number_triggered()
{
    //RUN WINDING NUMBER ALGORITHM

    //get data
    QPointF q = ui->Canvas->getQ();
    QVector<QPolygonF> polygons = ui->Canvas->getPolygons();

    ui->Canvas->clearHighlighted();
    QVector<int> indices;
    short res = 0;

    bool isInside = false;
    bool isInVertex = false;
    bool isOnEdge = false;

    for (int i = 0; i < polygons.size(); ++i) {
        if (algorithms::isPointInMinMaxBoxOfPolygon(q, polygons[i])) {
            res = algorithms::WindingNumber(q, polygons[i]);

            if (res == 1) {
                indices.push_back(i);
                isInside = true;
            } else if (res == -2) {
                indices.push_back(i);
                isInVertex = true;
            } else if (res == -1) {
                isOnEdge = true;
                indices.push_back(i);
            }

        }
    }

    ui->Canvas->highlightPolygon(indices);

    if (isInside) {
        setWindowTitle("Inside");
    } else if (isInVertex) {
        setWindowTitle("Vertex");
    } else if (isOnEdge) {
        setWindowTitle("Edge");
    } else setWindowTitle("Outside");
}

void MainForm::on_actionOpen_triggered()
{
    //input polygons from txt
    ui->Canvas->openFile();
}

void MainForm::on_actionOpen_SHP_triggered()
{
    //load shp with gdal
    ui->Canvas->openSHP();
}

void MainForm::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainForm::on_actionClear_data_triggered()
{
    ui->Canvas->clearPolygons();
    repaint();
}

void MainForm::on_actionClear_all_triggered()
{
    ui->Canvas->clear();
    repaint();
}

