/********************************************************************************
** Form generated from reading UI file 'mainform.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFORM_H
#define UI_MAINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
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
    QAction *actionLE;
    QAction *actionWE;
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
            MainForm->setObjectName(QString::fromUtf8("MainForm"));
        MainForm->resize(1279, 781);
        actionOpen = new QAction(MainForm);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icons/open_file.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon);
        actionExit = new QAction(MainForm);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/icons/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon1);
        actionMBR = new QAction(MainForm);
        actionMBR->setObjectName(QString::fromUtf8("actionMBR"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/icons/maer.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMBR->setIcon(icon2);
        actionPCA = new QAction(MainForm);
        actionPCA->setObjectName(QString::fromUtf8("actionPCA"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/icons/wa.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPCA->setIcon(icon3);
        actionClear_results = new QAction(MainForm);
        actionClear_results->setObjectName(QString::fromUtf8("actionClear_results"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/icons/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClear_results->setIcon(icon4);
        actionClear_All = new QAction(MainForm);
        actionClear_All->setObjectName(QString::fromUtf8("actionClear_All"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/icons/clear_er.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClear_All->setIcon(icon5);
        actionLE = new QAction(MainForm);
        actionLE->setObjectName(QString::fromUtf8("actionLE"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/icons/longestedge.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLE->setIcon(icon6);
        actionWE = new QAction(MainForm);
        actionWE->setObjectName(QString::fromUtf8("actionWE"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/icons/weightedbisector.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionWE->setIcon(icon7);
        centralwidget = new QWidget(MainForm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Canvas = new Draw(centralwidget);
        Canvas->setObjectName(QString::fromUtf8("Canvas"));

        horizontalLayout->addWidget(Canvas);

        MainForm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainForm);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1279, 23));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuSimplify = new QMenu(menubar);
        menuSimplify->setObjectName(QString::fromUtf8("menuSimplify"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        MainForm->setMenuBar(menubar);
        statusbar = new QStatusBar(MainForm);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainForm->setStatusBar(statusbar);
        toolBar = new QToolBar(MainForm);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainForm->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuSimplify->menuAction());
        menubar->addAction(menuView->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuSimplify->addAction(actionMBR);
        menuSimplify->addAction(actionPCA);
        menuSimplify->addAction(actionLE);
        menuSimplify->addAction(actionWE);
        menuView->addAction(actionClear_results);
        menuView->addSeparator();
        menuView->addAction(actionClear_All);
        toolBar->addAction(actionOpen);
        toolBar->addSeparator();
        toolBar->addAction(actionMBR);
        toolBar->addAction(actionPCA);
        toolBar->addAction(actionLE);
        toolBar->addAction(actionWE);
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
        actionLE->setText(QCoreApplication::translate("MainForm", "LE", nullptr));
#if QT_CONFIG(tooltip)
        actionLE->setToolTip(QCoreApplication::translate("MainForm", "Longest Edge", nullptr));
#endif // QT_CONFIG(tooltip)
        actionWE->setText(QCoreApplication::translate("MainForm", "WE", nullptr));
#if QT_CONFIG(tooltip)
        actionWE->setToolTip(QCoreApplication::translate("MainForm", "Weighted Bisector", nullptr));
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
