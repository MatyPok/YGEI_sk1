/********************************************************************************
** Form generated from reading UI file 'mainform.ui'
**
** Created by: Qt User Interface Compiler version 6.6.2
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
    QAction *actionMBR;
    QAction *actionPCA;
    QAction *actionClear_results;
    QAction *actionClear_All;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    Draw *Canvas;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuSimplify;
    QMenu *menuView;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainForm)
    {
        if (MainForm->objectName().isEmpty())
            MainForm->setObjectName("MainForm");
        MainForm->resize(1279, 781);
        actionOpen = new QAction(MainForm);
        actionOpen->setObjectName("actionOpen");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icons/open_file.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionExit = new QAction(MainForm);
        actionExit->setObjectName("actionExit");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/icons/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon1);
        actionMBR = new QAction(MainForm);
        actionMBR->setObjectName("actionMBR");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/icons/maer.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMBR->setIcon(icon2);
        actionPCA = new QAction(MainForm);
        actionPCA->setObjectName("actionPCA");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/icons/wa.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPCA->setIcon(icon3);
        actionClear_results = new QAction(MainForm);
        actionClear_results->setObjectName("actionClear_results");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/icons/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClear_results->setIcon(icon4);
        actionClear_All = new QAction(MainForm);
        actionClear_All->setObjectName("actionClear_All");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/icons/clear_er.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClear_All->setIcon(icon5);
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
        menubar->setGeometry(QRect(0, 0, 1279, 26));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuSimplify = new QMenu(menubar);
        menuSimplify->setObjectName("menuSimplify");
        menuView = new QMenu(menubar);
        menuView->setObjectName("menuView");
        MainForm->setMenuBar(menubar);
        statusbar = new QStatusBar(MainForm);
        statusbar->setObjectName("statusbar");
        MainForm->setStatusBar(statusbar);
        toolBar = new QToolBar(MainForm);
        toolBar->setObjectName("toolBar");
        MainForm->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuSimplify->menuAction());
        menubar->addAction(menuView->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuSimplify->addAction(actionMBR);
        menuSimplify->addAction(actionPCA);
        menuView->addAction(actionClear_results);
        menuView->addSeparator();
        menuView->addAction(actionClear_All);
        toolBar->addAction(actionOpen);
        toolBar->addSeparator();
        toolBar->addAction(actionMBR);
        toolBar->addAction(actionPCA);
        toolBar->addSeparator();
        toolBar->addAction(actionClear_results);
        toolBar->addAction(actionClear_All);
        toolBar->addSeparator();
        toolBar->addAction(actionExit);

        retranslateUi(MainForm);

        QMetaObject::connectSlotsByName(MainForm);
    } // setupUi

    void retranslateUi(QMainWindow *MainForm)
    {
        MainForm->setWindowTitle(QCoreApplication::translate("MainForm", "Building Simplify", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainForm", "Open", nullptr));
#if QT_CONFIG(tooltip)
        actionOpen->setToolTip(QCoreApplication::translate("MainForm", "Open file", nullptr));
#endif // QT_CONFIG(tooltip)
        actionExit->setText(QCoreApplication::translate("MainForm", "Exit", nullptr));
#if QT_CONFIG(tooltip)
        actionExit->setToolTip(QCoreApplication::translate("MainForm", "Close application", nullptr));
#endif // QT_CONFIG(tooltip)
        actionMBR->setText(QCoreApplication::translate("MainForm", "MBR", nullptr));
#if QT_CONFIG(tooltip)
        actionMBR->setToolTip(QCoreApplication::translate("MainForm", "SImpligy building using MBR", nullptr));
#endif // QT_CONFIG(tooltip)
        actionPCA->setText(QCoreApplication::translate("MainForm", "PCA", nullptr));
#if QT_CONFIG(tooltip)
        actionPCA->setToolTip(QCoreApplication::translate("MainForm", "SImpligy building using PCA", nullptr));
#endif // QT_CONFIG(tooltip)
        actionClear_results->setText(QCoreApplication::translate("MainForm", "Clear Results", nullptr));
        actionClear_All->setText(QCoreApplication::translate("MainForm", "Clear All", nullptr));
#if QT_CONFIG(tooltip)
        actionClear_All->setToolTip(QCoreApplication::translate("MainForm", "Clear all data", nullptr));
#endif // QT_CONFIG(tooltip)
        menuFile->setTitle(QCoreApplication::translate("MainForm", "File", nullptr));
        menuSimplify->setTitle(QCoreApplication::translate("MainForm", "Simplify", nullptr));
        menuView->setTitle(QCoreApplication::translate("MainForm", "View", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainForm", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainForm: public Ui_MainForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFORM_H
