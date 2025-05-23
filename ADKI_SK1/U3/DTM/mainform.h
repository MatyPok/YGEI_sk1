#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include "settings2.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainForm;
}
QT_END_NAMESPACE

class MainForm : public QMainWindow
{
    Q_OBJECT

private:
    bool view_points, view_dt, view_contour_lines, view_aspect, view_slope;

public:
    MainForm(QWidget *parent = nullptr);
    ~MainForm();
    Settings2 settings;

private slots:
    void on_actionCreate_DT_triggered();

    void on_actionCreate_Contour_lines_triggered();

    void on_actionParameters_triggered();

    void on_actionAnalyze_slope_triggered();


    void on_actionPoints_changed();
    void on_actionDT_changed();
    void on_actionContour_Lines_changed();
    void on_actionSlope_changed();
    void on_actionExposition_changed();

    void on_actionAnalyze_exposition_triggered();

    void on_actionOpen_triggered();
    void on_actionExit_triggered();

    void on_actionClear_Results_triggered();
    void on_actionClear_All_triggered();


private:
    Ui::MainForm *ui;
};
#endif // MAINFORM_H
