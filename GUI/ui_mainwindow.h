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
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout_2;
    QVBoxLayout *Plot_Layout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *Get_oscillogram;
    QPushButton *motor_on_off_button;
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
    QWidget *tab_4;
    QGridLayout *gridLayout_4;
    QGridLayout *real_time_plot_layout;
    QPushButton *pushButton;
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
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout_2 = new QGridLayout(tab);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        Plot_Layout = new QVBoxLayout();
        Plot_Layout->setSpacing(6);
        Plot_Layout->setObjectName(QStringLiteral("Plot_Layout"));

        gridLayout_2->addLayout(Plot_Layout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        Get_oscillogram = new QPushButton(tab);
        Get_oscillogram->setObjectName(QStringLiteral("Get_oscillogram"));

        horizontalLayout_2->addWidget(Get_oscillogram);

        motor_on_off_button = new QPushButton(tab);
        motor_on_off_button->setObjectName(QStringLiteral("motor_on_off_button"));

        horizontalLayout_2->addWidget(motor_on_off_button);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        tabWidget->addTab(tab, QString());
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
        tabWidget->addTab(tab_2, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        tab_4->setEnabled(true);
        gridLayout_4 = new QGridLayout(tab_4);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        real_time_plot_layout = new QGridLayout();
        real_time_plot_layout->setSpacing(6);
        real_time_plot_layout->setObjectName(QStringLiteral("real_time_plot_layout"));

        gridLayout_4->addLayout(real_time_plot_layout, 0, 0, 1, 1);

        pushButton = new QPushButton(tab_4);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout_4->addWidget(pushButton, 1, 0, 1, 1);

        tabWidget->addTab(tab_4, QString());

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

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        Get_oscillogram->setText(QApplication::translate("MainWindow", "\320\241\320\275\321\217\321\202\321\214 \320\276\321\206\320\270\320\273\320\273\320\276\320\263\321\200\320\260\320\274\320\274\321\203", nullptr));
        motor_on_off_button->setText(QApplication::translate("MainWindow", "\320\222\320\272\320\273/\320\262\321\213\320\272\320\273 \320\274\320\276\321\202\320\276\321\200", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "\320\236\321\201\321\206\320\270\320\273\320\273\320\276\320\263\321\200\320\260\320\274\320\260 ", nullptr));
        radioButton_disabled_mode->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\272\320\273\321\216\321\207\320\265\320\275", nullptr));
        radioButton_static_mode->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 \320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\321\217", nullptr));
        radioButton_sine_mode->setText(QApplication::translate("MainWindow", "\320\241\320\270\320\275\321\203\321\201\320\276\320\270\320\264\320\260", nullptr));
        label->setText(QApplication::translate("MainWindow", "\320\240\320\265\320\266\320\270\320\274", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 \320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\321\217", nullptr));
        pushButton_Set_angle->setText(QApplication::translate("MainWindow", "W", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "\320\232\320\260\320\273\320\270\320\261\321\200\320\276\320\262\320\272\320\260", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "\320\222\320\272\320\273\321\216\321\207\320\270\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "\320\223\321\200\320\260\321\204\320\270\320\272 \320\262 \321\200\320\265\320\260\320\273\321\214\320\275\320\276\320\274 \320\262\321\200\320\265\320\274\320\265\320\275\320\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
