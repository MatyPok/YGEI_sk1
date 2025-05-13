/********************************************************************************
** Form generated from reading UI file 'settings2.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS2_H
#define UI_SETTINGS2_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Settings2
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Settings2)
    {
        if (Settings2->objectName().isEmpty())
            Settings2->setObjectName("Settings2");
        Settings2->resize(314, 227);
        verticalLayout = new QVBoxLayout(Settings2);
        verticalLayout->setObjectName("verticalLayout");
        groupBox = new QGroupBox(Settings2);
        groupBox->setObjectName("groupBox");
        label_7 = new QLabel(groupBox);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(20, 40, 171, 16));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(270, 40, 49, 16));
        label_9 = new QLabel(groupBox);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(270, 80, 49, 16));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(20, 80, 171, 16));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(270, 120, 49, 16));
        label_12 = new QLabel(groupBox);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(20, 120, 171, 16));
        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName("spinBox");
        spinBox->setGeometry(QRect(200, 40, 51, 22));
        spinBox->setMaximum(1500);
        spinBox_2 = new QSpinBox(groupBox);
        spinBox_2->setObjectName("spinBox_2");
        spinBox_2->setGeometry(QRect(200, 80, 51, 22));
        spinBox_2->setMaximum(1500);
        spinBox_3 = new QSpinBox(groupBox);
        spinBox_3->setObjectName("spinBox_3");
        spinBox_3->setGeometry(QRect(200, 120, 51, 22));
        spinBox_3->setMaximum(500);

        verticalLayout->addWidget(groupBox);

        buttonBox = new QDialogButtonBox(Settings2);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(Settings2);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, Settings2, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, Settings2, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Settings2);
    } // setupUi

    void retranslateUi(QDialog *Settings2)
    {
        Settings2->setWindowTitle(QCoreApplication::translate("Settings2", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Settings2", "Contour line properties", nullptr));
        label_7->setText(QCoreApplication::translate("Settings2", "Minimum contour line height", nullptr));
        label_8->setText(QCoreApplication::translate("Settings2", "m", nullptr));
        label_9->setText(QCoreApplication::translate("Settings2", "m", nullptr));
        label_10->setText(QCoreApplication::translate("Settings2", "Maximum contour line height", nullptr));
        label_11->setText(QCoreApplication::translate("Settings2", "m", nullptr));
        label_12->setText(QCoreApplication::translate("Settings2", "Contour line interval", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Settings2: public Ui_Settings2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS2_H
