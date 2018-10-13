/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QRadioButton *radioButton_disabled_mode;
    QRadioButton *radioButton_static_mode;
    QRadioButton *radioButton_sine_mode;
    QLabel *label;
    QSpinBox *spinBox_des_val;
    QLabel *label_2;
    QPushButton *pushButton_Set_angle;
    QSlider *horizontalSlider;
    QPushButton *pushButton_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QTextEdit *Kp_text;
    QPushButton *pushButton_Set_angle_2;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QTextEdit *Ki_text;
    QPushButton *write_Ki;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QTextEdit *Kd_text;
    QPushButton *write_Kd;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(780, 498);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        radioButton_disabled_mode = new QRadioButton(tab_2);
        radioButton_disabled_mode->setObjectName(QStringLiteral("radioButton_disabled_mode"));
        radioButton_disabled_mode->setGeometry(QRect(30, 50, 82, 17));
        radioButton_static_mode = new QRadioButton(tab_2);
        radioButton_static_mode->setObjectName(QStringLiteral("radioButton_static_mode"));
        radioButton_static_mode->setGeometry(QRect(30, 70, 141, 17));
        radioButton_sine_mode = new QRadioButton(tab_2);
        radioButton_sine_mode->setObjectName(QStringLiteral("radioButton_sine_mode"));
        radioButton_sine_mode->setGeometry(QRect(30, 90, 82, 17));
        label = new QLabel(tab_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 30, 47, 13));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        spinBox_des_val = new QSpinBox(tab_2);
        spinBox_des_val->setObjectName(QStringLiteral("spinBox_des_val"));
        spinBox_des_val->setGeometry(QRect(30, 150, 71, 22));
        spinBox_des_val->setMinimum(-1000);
        spinBox_des_val->setMaximum(1000);
        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 130, 121, 16));
        label_2->setFont(font);
        pushButton_Set_angle = new QPushButton(tab_2);
        pushButton_Set_angle->setObjectName(QStringLiteral("pushButton_Set_angle"));
        pushButton_Set_angle->setGeometry(QRect(110, 150, 31, 23));
        horizontalSlider = new QSlider(tab_2);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(30, 190, 221, 19));
        horizontalSlider->setMaximum(360);
        horizontalSlider->setOrientation(Qt::Horizontal);
        pushButton_2 = new QPushButton(tab_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(30, 240, 75, 23));
        layoutWidget = new QWidget(tab_2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(310, 40, 172, 73));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        Kp_text = new QTextEdit(layoutWidget);
        Kp_text->setObjectName(QStringLiteral("Kp_text"));

        horizontalLayout->addWidget(Kp_text);

        pushButton_Set_angle_2 = new QPushButton(layoutWidget);
        pushButton_Set_angle_2->setObjectName(QStringLiteral("pushButton_Set_angle_2"));

        horizontalLayout->addWidget(pushButton_Set_angle_2);

        layoutWidget1 = new QWidget(tab_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(310, 130, 171, 73));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        Ki_text = new QTextEdit(layoutWidget1);
        Ki_text->setObjectName(QStringLiteral("Ki_text"));

        horizontalLayout_3->addWidget(Ki_text);

        write_Ki = new QPushButton(layoutWidget1);
        write_Ki->setObjectName(QStringLiteral("write_Ki"));

        horizontalLayout_3->addWidget(write_Ki);

        layoutWidget2 = new QWidget(tab_2);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(310, 220, 172, 73));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(layoutWidget2);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_4->addWidget(label_5);

        Kd_text = new QTextEdit(layoutWidget2);
        Kd_text->setObjectName(QStringLiteral("Kd_text"));

        horizontalLayout_4->addWidget(Kd_text);

        write_Kd = new QPushButton(layoutWidget2);
        write_Kd->setObjectName(QStringLiteral("write_Kd"));

        horizontalLayout_4->addWidget(write_Kd);

        tabWidget->addTab(tab_2, QString());

        gridLayout->addWidget(tabWidget, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 780, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        radioButton_disabled_mode->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\272\320\273\321\216\321\207\320\265\320\275", nullptr));
        radioButton_static_mode->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 \320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\321\217", nullptr));
        radioButton_sine_mode->setText(QApplication::translate("MainWindow", "\320\241\320\270\320\275\321\203\321\201\320\276\320\270\320\264\320\260", nullptr));
        label->setText(QApplication::translate("MainWindow", "\320\240\320\265\320\266\320\270\320\274", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 \320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\321\217", nullptr));
        pushButton_Set_angle->setText(QApplication::translate("MainWindow", "W", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "\320\232\320\260\320\273\320\270\320\261\321\200\320\276\320\262\320\272\320\260", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Kp", nullptr));
        pushButton_Set_angle_2->setText(QApplication::translate("MainWindow", "W", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Ki", nullptr));
        write_Ki->setText(QApplication::translate("MainWindow", "W", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Kd", nullptr));
        write_Kd->setText(QApplication::translate("MainWindow", "W", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
