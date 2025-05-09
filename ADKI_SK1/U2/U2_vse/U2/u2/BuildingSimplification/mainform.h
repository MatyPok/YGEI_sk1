#ifndef MAINFORM_H
#define MAINFORM_H

#include <QMainWindow>
#include <QLabel>
#include <QVector>
#include <QPolygonF>


QT_BEGIN_NAMESPACE
namespace Ui { class MainForm; }
QT_END_NAMESPACE

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    MainForm(QWidget *parent = nullptr);
    ~MainForm();

private slots:
    void on_actionOpen_triggered();
    void on_actionOpen_SHP_triggered();
    void on_actionExit_triggered();

    void on_actionMBR_triggered();
    void on_actionPCA_triggered();
    void on_actionLE_triggered();
    void on_actionWE_triggered();
    void on_actionWA_triggered();
    void on_actionJarvis_Scan_triggered();
    void on_actionGraham_Scan_triggered();

    // U1
    void on_actionClear_results_triggered();
    void on_actionClear_All_triggered();

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    Ui::MainForm *ui;
    QLabel* iouLabel;

        void updateIoU(const QVector<QPolygonF>& originals, const QVector<QPolygonF>& generated);
    void testIoU();
};

#endif // MAINFORM_H
