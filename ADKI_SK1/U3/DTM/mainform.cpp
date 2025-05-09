#include "mainform.h"
#include "ui_mainform.h"
#include "qpoint3df.h"
#include "algorithms.h"
#include "triangle.h"

MainForm::MainForm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainForm)
{
    ui->setupUi(this);

    //Initialize variables
    view_points = true;
    view_dt = true;
    view_contour_lines = true;
    view_slope = true;
    view_aspect = true;

    //Check/uncheck menu items
    ui->actionPoints->setChecked(view_points);
    ui->actionDT->setChecked(view_dt);
    ui->actionContour_Lines->setChecked(view_contour_lines);
    ui->actionSlope->setChecked(view_slope);
    ui->actionExposition->setChecked(view_aspect);
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::on_actionCreate_DT_triggered()
{
    //Perform Delaunay triangulation

    //Get data
    std::vector<QPoint3DF> points = ui -> Canvas -> getPoints();

    //Perform DT
    Algorithms a;
    std::vector<Edge> dt = a.DT(points);

    //Set results
    ui -> Canvas -> setDT(dt);

    //Repaint
    repaint();
}


void MainForm::on_actionCreate_Contour_lines_triggered()
{
    //Generate contour lines

    //Get Delauanay triangulation
    std::vector<Edge> dt = ui -> Canvas -> getDT();

    //Get parameters of contour lines
    double z_min = settings.getZMin();
    double z_max = settings.getZMax();
    double dz = settings.getDz();

    //Generate contour lines
    Algorithms a;
    std::vector<Edge> cl = a.createContourLines(dt, z_min, z_max, dz);

    //Set results
    ui -> Canvas -> setCL(cl);

    //Repaint
    repaint();
}


void MainForm::on_actionParameters_triggered()
{
    //Show window
    settings.exec();
}


void MainForm::on_actionAnalyze_slope_triggered()
{
    //Analyze slope
    std::vector<Triangle> triangles;

    //Get Delauanay triangulation
    std::vector<Edge> dt = ui -> Canvas -> getDT();

    //Compute slope
    Algorithms a;
    a.analyzeSlope(dt, triangles);

    //Set results
    ui->Canvas->setTR(triangles);

    //Repaint
    repaint();
}


void MainForm::on_actionPoints_changed()
{
    view_points = ui -> actionPoints -> isChecked();

    ui -> Canvas ->setViewPoints(view_points);

    ui->Canvas->repaint();
}


void MainForm::on_actionDT_changed()
{
    view_dt = ui -> actionDT -> isChecked();

    ui -> Canvas ->setViewDT(view_dt);

    ui->Canvas->repaint();
}


void MainForm::on_actionContour_Lines_changed()
{
    view_contour_lines = ui -> actionContour_Lines -> isChecked();

    ui -> Canvas ->setViewContourLines(view_contour_lines);

    ui->Canvas->repaint();
}


void MainForm::on_actionSlope_changed()
{
    view_slope = ui -> actionSlope -> isChecked();

    ui -> Canvas ->setViewSlope(view_slope);

    ui->Canvas->repaint();
}


void MainForm::on_actionExposition_changed()
{
    view_aspect = ui -> actionExposition -> isChecked();

    ui -> Canvas ->setViewAspect(view_aspect);

    ui->Canvas->repaint();
}

