#include "mainform.h"
#include "ui_mainform.h"
#include "algorithms.h"

// U1
#include "gdal_priv.h"

#include "QApplication"

#include <iostream>

#include <QResizeEvent>
#include <QPainterPath>
#include <QPolygonF>


MainForm::MainForm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainForm)
{
    ui->setupUi(this);  // Load the UI

    // Create QLabel
    iouLabel = new QLabel(this);
    iouLabel->setAlignment(Qt::AlignRight);  // Align to the right
    QString text = "<b>Intersection over union</b>";
    QFont font = iouLabel->font();
    QFontMetrics fm(font);

    // Get the width of the text with added padding
    int width = fm.horizontalAdvance(text) + 10;  // Add padding for better appearance

    // Set the minimum width of the label according to the text width
    iouLabel->setMinimumWidth(width);
    iouLabel->setText(text);  // Set the text
    iouLabel->adjustSize();   // Adjust size according to the text
    iouLabel->setStyleSheet("background-color: white; color: black; border: 1px solid black;");
    iouLabel->setTextFormat(Qt::RichText);  // Enable HTML formatting

    // Show the window
    this->show();
}

MainForm::~MainForm()
{
    delete ui;
}

void MainForm::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event);

    // Keep the label in the bottom right corner when the window is resized
    if (iouLabel) {
        int labelWidth = iouLabel->width();  // Get the current width of the label
        iouLabel->move(width() - labelWidth - 10, height() - iouLabel->height() - 10);
    }
}

void MainForm::updateIoU(const QVector<QPolygonF>& originals, const QVector<QPolygonF>& generated)
{
    if (originals.size() != generated.size() || originals.isEmpty()) {
        qDebug() << "IoU: size mismatch or empty input";
        if (iouLabel) {    iouLabel->setText("<html><b>Accuracy Evaluation</b><br>IoU: -</html>");}
        return;
    }

    double totalIoU = 0.0;
    int validPairs = 0;

    for (int i = 0; i < originals.size(); ++i) {
        double iou = Algorithms::computeIoU(originals[i], generated[i]);

        if (iou > 0.0) {
            totalIoU += iou;
            ++validPairs;
        }
    }

    if (validPairs > 0 && iouLabel) {
        double averageIoU = totalIoU / validPairs;
        qDebug() << "Average IoU: " << averageIoU;
        iouLabel->setText(QString("IoU: %1").arg(averageIoU, 0, 'f', 2));
    } else if (iouLabel) {
        qDebug() << "No valid pairs -> IoU: -";
        iouLabel->setText("IoU: -");
    }
}





void MainForm::on_actionOpen_triggered()
{
    // U1
    // Input polygons from txt
    ui->Canvas->drawPolygonsFromTXT();
}

void MainForm::on_actionOpen_SHP_triggered()
{
    // Load SHP with GDAL
    ui->Canvas->drawPolygonsFromSHP();
}



void MainForm::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainForm::on_actionMBR_triggered()
{
    QVector<QPolygonF> originals = ui->Canvas->getPolygons();
    QVector<QPolygonF> maer;

    for (const QPolygonF& poly : originals) {
        maer.append(Algorithms::createMAER(poly));
    }

    ui->Canvas->setMAER(maer);

    updateIoU(originals, maer);
    repaint();
}




void MainForm::on_actionPCA_triggered()
{
    // Get data
    QVector<QPolygonF> polygons = ui->Canvas->getPolygons();
    QVector<QPolygonF> erpca;

    // Perform the algorithm
    for (int i = 0; i < polygons.size(); ++i) {
        erpca.append(Algorithms::createERPCA(polygons[i]));  // Add actual results
    }

    // Set results
    ui->Canvas->setERPCA(erpca);

    // Update IoU
    updateIoU(polygons, erpca);

    // Repaint
    repaint();
}

void MainForm::on_actionLE_triggered()
{
    // Get data
    QVector<QPolygonF> polygons = ui->Canvas->getPolygons();
    QVector<QPolygonF> le;

    // Perform the algorithm
    for (int i = 0; i < polygons.size(); ++i) {
        le.append(Algorithms::createLongesEdge(polygons[i]));  // Add actual results
    }

    // Set results
    ui->Canvas->setLE(le);

    // Update IoU
    updateIoU(polygons, le);

    // Repaint
    repaint();
}

void MainForm::on_actionWE_triggered()
{
    // Get data
    QVector<QPolygonF> polygons = ui->Canvas->getPolygons();
    QVector<QPolygonF> we;

    // Perform the algorithm
    for (int i = 0; i < polygons.size(); ++i) {
        we.append(Algorithms::createWE(polygons[i]));  // Add actual results
    }

    // Set results
    ui->Canvas->setWE(we);

    // Update IoU
    updateIoU(polygons, we);

    // Repaint
    repaint();
}

void MainForm::on_actionWA_triggered()
{
    // Get data
    QVector<QPolygonF> polygons = ui->Canvas->getPolygons();
    QVector<QPolygonF> wa;

    // Perform the algorithm
    for (int i = 0; i < polygons.size(); ++i) {
        wa.append(Algorithms::createWA(polygons[i]));  // Add actual results
    }

    // Set results
    ui->Canvas->setWA(wa);

    // Update IoU
    updateIoU(polygons, wa);

    // Repaint
    repaint();
}



void MainForm::on_actionJarvis_Scan_triggered()
{
    // Get data
    QVector<QPolygonF> polygons = ui->Canvas->getPolygons();
    QVector<QPolygonF> ch;

    // Run the function
    for (int i = 0; i < polygons.size(); ++i) {

        if (ch.isEmpty()) {
            ch.append(QPolygonF());
        }
        ch.append(Algorithms::createCH(polygons[i]));
    }
    // Set results
    ui->Canvas->setCH(ch);

    // Repaint
    repaint();
}


void MainForm::on_actionGraham_Scan_triggered()
{
    // Get data
    QVector<QPolygonF> polygons = ui->Canvas->getPolygons();
    QVector<QPolygonF> chGraham;

    // Run the function
    for (int i = 0; i < polygons.size(); ++i) {

        if (chGraham.isEmpty()) {
            chGraham.append(QPolygonF());
        }
        chGraham.append(Algorithms::createCH_Graham(polygons[i]));
    }
    // Set results
    ui->Canvas->setCH(chGraham);

    // Repaint
    repaint();
}

// U1


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
