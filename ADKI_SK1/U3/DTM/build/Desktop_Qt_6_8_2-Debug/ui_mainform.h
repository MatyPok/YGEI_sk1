/********************************************************************************
** Form generated from reading UI file 'mainform.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "draw.h"

QT_BEGIN_NAMESPACE

class Ui_MainForm
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionCreate_DT;
    QAction *actionCreate_Contour_lines;
    QAction *actionAnalyze_slope;
    QAction *actionAnalyze_exposition;
    QAction *actionPoints;
    QAction *actionDT;
    QAction *actionContour_Lines;
    QAction *actionSlope;
    QAction *actionExposition;
    QAction *actionClear_Results;
    QAction *actionClear_All;
    QAction *actionParameters;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    Draw *Canvas;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuAnalysis;
    QMenu *menuView;
    QMenu *menuClear;
    QMenu *menuSettings;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName("MainForm");
        MainForm->resize(1232, 710);
        actionOpen = new QAction(MainForm);
        actionOpen->setObjectName("actionOpen");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icons/open_file.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionOpen->setIcon(icon);
        actionExit = new QAction(MainForm);
        actionExit->setObjectName("actionExit");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/icons/exit.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionExit->setIcon(icon1);
        actionCreate_DT = new QAction(MainForm);
        actionCreate_DT->setObjectName("actionCreate_DT");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/icons/triangles2.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionCreate_DT->setIcon(icon2);
        actionCreate_Contour_lines = new QAction(MainForm);
        actionCreate_Contour_lines->setObjectName("actionCreate_Contour_lines");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/icons/contours2.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionCreate_Contour_lines->setIcon(icon3);
        actionAnalyze_slope = new QAction(MainForm);
        actionAnalyze_slope->setObjectName("actionAnalyze_slope");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/icons/slope2.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionAnalyze_slope->setIcon(icon4);
        actionAnalyze_exposition = new QAction(MainForm);
        actionAnalyze_exposition->setObjectName("actionAnalyze_exposition");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/icons/orientation2.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionAnalyze_exposition->setIcon(icon5);
        actionPoints = new QAction(MainForm);
        actionPoints->setObjectName("actionPoints");
        actionPoints->setCheckable(true);
        actionDT = new QAction(MainForm);
        actionDT->setObjectName("actionDT");
        actionDT->setCheckable(true);
        actionContour_Lines = new QAction(MainForm);
        actionContour_Lines->setObjectName("actionContour_Lines");
        actionContour_Lines->setCheckable(true);
        actionSlope = new QAction(MainForm);
        actionSlope->setObjectName("actionSlope");
        actionSlope->setCheckable(true);
        actionExposition = new QAction(MainForm);
        actionExposition->setObjectName("actionExposition");
        actionExposition->setCheckable(true);
        actionClear_Results = new QAction(MainForm);
        actionClear_Results->setObjectName("actionClear_Results");
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/icons/clear.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionClear_Results->setIcon(icon6);
        actionClear_All = new QAction(MainForm);
        actionClear_All->setObjectName("actionClear_All");
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/icons/clear_er.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionClear_All->setIcon(icon7);
        actionParameters = new QAction(MainForm);
        actionParameters->setObjectName("actionParameters");
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/images/icons/settings.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actionParameters->setIcon(icon8);
        centralwidget = new QWidget(MainForm);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        Canvas = new Draw(centralwidget);
        Canvas->setObjectName("Canvas");

        horizontalLayout->addWidget(Canvas);

        MainForm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainForm);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1232, 22));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuAnalysis = new QMenu(menubar);
        menuAnalysis->setObjectName("menuAnalysis");
        menuView = new QMenu(menubar);
        menuView->setObjectName("menuView");
        menuClear = new QMenu(menubar);
        menuClear->setObjectName("menuClear");
        menuSettings = new QMenu(menubar);
        menuSettings->setObjectName("menuSettings");
        MainForm->setMenuBar(menubar);
        statusbar = new QStatusBar(MainForm);
        statusbar->setObjectName("statusbar");
        MainForm->setStatusBar(statusbar);
        toolBar = new QToolBar(MainForm);
        toolBar->setObjectName("toolBar");
        MainForm->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuAnalysis->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuClear->menuAction());
        menubar->addAction(menuSettings->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuAnalysis->addAction(actionCreate_DT);
        menuAnalysis->addSeparator();
        menuAnalysis->addAction(actionCreate_Contour_lines);
        menuAnalysis->addAction(actionAnalyze_slope);
        menuAnalysis->addAction(actionAnalyze_exposition);
        menuView->addAction(actionPoints);
        menuView->addAction(actionDT);
        menuView->addAction(actionContour_Lines);
        menuView->addAction(actionSlope);
        menuView->addAction(actionExposition);
        menuClear->addAction(actionClear_Results);
        menuClear->addSeparator();
        menuClear->addAction(actionClear_All);
        menuSettings->addAction(actionParameters);
        toolBar->addAction(actionOpen);
        toolBar->addSeparator();
        toolBar->addAction(actionCreate_DT);
        toolBar->addSeparator();
        toolBar->addAction(actionCreate_Contour_lines);
        toolBar->addAction(actionAnalyze_slope);
        toolBar->addAction(actionAnalyze_exposition);
        toolBar->addSeparator();
        toolBar->addAction(actionClear_Results);
        toolBar->addAction(actionClear_All);
        toolBar->addSeparator();
        toolBar->addAction(actionParameters);
        toolBar->addSeparator();
        toolBar->addAction(actionExit);

        retranslateUi(MainForm);

        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(QMainWindow *MainForm)
    {
        MainForm->setWindowTitle(QCoreApplication::translate("MainForm", "MainForm", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainForm", "Open", nullptr));
#if QT_CONFIG(tooltip)
        actionOpen->setToolTip(QCoreApplication::translate("MainForm", "Open a File", nullptr));
#endif // QT_CONFIG(tooltip)
        actionExit->setText(QCoreApplication::translate("MainForm", "Exit", nullptr));
#if QT_CONFIG(tooltip)
        actionExit->setToolTip(QCoreApplication::translate("MainForm", "Close Application", nullptr));
#endif // QT_CONFIG(tooltip)
        actionCreate_DT->setText(QCoreApplication::translate("MainForm", "Create DT", nullptr));
        actionCreate_Contour_lines->setText(QCoreApplication::translate("MainForm", "Create Contour lines", nullptr));
        actionAnalyze_slope->setText(QCoreApplication::translate("MainForm", "Analyze Slope", nullptr));
#if QT_CONFIG(tooltip)
        actionAnalyze_slope->setToolTip(QCoreApplication::translate("MainForm", "Analyze DTM Slope", nullptr));
#endif // QT_CONFIG(tooltip)
        actionAnalyze_exposition->setText(QCoreApplication::translate("MainForm", "Analyze Exposition", nullptr));
#if QT_CONFIG(tooltip)
        actionAnalyze_exposition->setToolTip(QCoreApplication::translate("MainForm", "Analyze DTM Exposition", nullptr));
#endif // QT_CONFIG(tooltip)
        actionPoints->setText(QCoreApplication::translate("MainForm", "Points", nullptr));
        actionDT->setText(QCoreApplication::translate("MainForm", "DT", nullptr));
        actionContour_Lines->setText(QCoreApplication::translate("MainForm", "Contour Lines", nullptr));
        actionSlope->setText(QCoreApplication::translate("MainForm", "Slope", nullptr));
        actionExposition->setText(QCoreApplication::translate("MainForm", "Exposition", nullptr));
        actionClear_Results->setText(QCoreApplication::translate("MainForm", "Clear Results", nullptr));
        actionClear_All->setText(QCoreApplication::translate("MainForm", "Clear All", nullptr));
#if QT_CONFIG(tooltip)
        actionClear_All->setToolTip(QCoreApplication::translate("MainForm", "Clear All Data", nullptr));
#endif // QT_CONFIG(tooltip)
        actionParameters->setText(QCoreApplication::translate("MainForm", "Parameters", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainForm", "File", nullptr));
        menuAnalysis->setTitle(QCoreApplication::translate("MainForm", "Analysis", nullptr));
        menuView->setTitle(QCoreApplication::translate("MainForm", "View", nullptr));
        menuClear->setTitle(QCoreApplication::translate("MainForm", "Clear", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("MainForm", "Settings", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainForm", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainForm: public Ui_MainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
