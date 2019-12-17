/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QtCharts"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_3;
    QToolBox *toolBox;
    QWidget *page;
    QGridLayout *gridLayout_49;
    QComboBox *ListInfoPortsBox;
    QPushButton *ConnectBtn;
    QWidget *page_2;
    QGridLayout *gridLayout_50;
    QLineEdit *udpIpEdit;
    QPushButton *udpConnectButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout_2;
    QSlider *horizontalSlider;
    QHBoxLayout *horizontalLayout_4;
    QDoubleSpinBox *spinBox_des_val;
    QPushButton *pushButton_Set_angle;
    QSpacerItem *horizontalSpacer;
    QWidget *sin_button_widget;
    QGridLayout *gridLayout_7;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *button_sin_025;
    QPushButton *button_sin_05;
    QPushButton *button_sin_1;
    QPushButton *button_sin_2;
    QPushButton *button_sin_3;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QRadioButton *radioButton_disabled_mode;
    QRadioButton *radioButton_static_mode;
    QRadioButton *radioButton_speed_mode;
    QRadioButton *radioButton_path_mode;
    QRadioButton *radioButton_sine_mode;
    QGridLayout *gridLayout_4;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QTextEdit *Kp_text;
    QPushButton *write_Kp;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QTextEdit *Ki_text;
    QPushButton *write_Ki;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QTextEdit *Kd_text;
    QPushButton *write_Kd;
    QSpacerItem *verticalSpacer;
    QLabel *label_6;
    QSpacerItem *verticalSpacer_2;
    QWidget *tab_graph;
    QWidget *widget;
    QGridLayout *gridLayout;
    QChartView *graphicsView;
    QCheckBox *plot_graphic;
    QPushButton *pushButtonResetPlot;
    QPushButton *pushButtonStartSaveToFile;
    QPushButton *savePlotToFile;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(814, 704);
        MainWindow->setUnifiedTitleAndToolBarOnMac(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 799, 629));
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout_6 = new QGridLayout(tab_2);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setSpacing(6);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(50, 20, 20, 20);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        toolBox = new QToolBox(tab_2);
        toolBox->setObjectName(QString::fromUtf8("toolBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(toolBox->sizePolicy().hasHeightForWidth());
        toolBox->setSizePolicy(sizePolicy);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setGeometry(QRect(0, 0, 169, 85));
        gridLayout_49 = new QGridLayout(page);
        gridLayout_49->setSpacing(6);
        gridLayout_49->setContentsMargins(11, 11, 11, 11);
        gridLayout_49->setObjectName(QString::fromUtf8("gridLayout_49"));
        ListInfoPortsBox = new QComboBox(page);
        ListInfoPortsBox->setObjectName(QString::fromUtf8("ListInfoPortsBox"));

        gridLayout_49->addWidget(ListInfoPortsBox, 0, 0, 1, 1);

        ConnectBtn = new QPushButton(page);
        ConnectBtn->setObjectName(QString::fromUtf8("ConnectBtn"));

        gridLayout_49->addWidget(ConnectBtn, 1, 0, 1, 1);

        toolBox->addItem(page, QString::fromUtf8("Serial Connection"));
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        page_2->setGeometry(QRect(0, 0, 115, 79));
        gridLayout_50 = new QGridLayout(page_2);
        gridLayout_50->setSpacing(6);
        gridLayout_50->setContentsMargins(11, 11, 11, 11);
        gridLayout_50->setObjectName(QString::fromUtf8("gridLayout_50"));
        udpIpEdit = new QLineEdit(page_2);
        udpIpEdit->setObjectName(QString::fromUtf8("udpIpEdit"));
        udpIpEdit->setEnabled(false);

        gridLayout_50->addWidget(udpIpEdit, 1, 0, 1, 1);

        udpConnectButton = new QPushButton(page_2);
        udpConnectButton->setObjectName(QString::fromUtf8("udpConnectButton"));
        udpConnectButton->setEnabled(false);

        gridLayout_50->addWidget(udpConnectButton, 0, 0, 1, 1);

        toolBox->addItem(page_2, QString::fromUtf8("UDP Connection"));

        gridLayout_3->addWidget(toolBox, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(tab_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setEnabled(false);

        gridLayout_3->addWidget(pushButton_2, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_2, 0, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_3, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSlider = new QSlider(tab_2);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setEnabled(true);
        horizontalSlider->setMinimum(-360);
        horizontalSlider->setMaximum(360);
        horizontalSlider->setPageStep(20);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setTickPosition(QSlider::TicksBelow);

        gridLayout_2->addWidget(horizontalSlider, 2, 0, 1, 2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        spinBox_des_val = new QDoubleSpinBox(tab_2);
        spinBox_des_val->setObjectName(QString::fromUtf8("spinBox_des_val"));
        spinBox_des_val->setMinimumSize(QSize(100, 0));
        spinBox_des_val->setDecimals(4);
        spinBox_des_val->setSingleStep(0.1);

        horizontalLayout_4->addWidget(spinBox_des_val);

        pushButton_Set_angle = new QPushButton(tab_2);
        pushButton_Set_angle->setObjectName(QString::fromUtf8("pushButton_Set_angle"));

        horizontalLayout_4->addWidget(pushButton_Set_angle);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        gridLayout_2->addLayout(horizontalLayout_4, 1, 0, 1, 1);

        sin_button_widget = new QWidget(tab_2);
        sin_button_widget->setObjectName(QString::fromUtf8("sin_button_widget"));
        sin_button_widget->setEnabled(true);
        gridLayout_7 = new QGridLayout(sin_button_widget);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        button_sin_025 = new QPushButton(sin_button_widget);
        button_sin_025->setObjectName(QString::fromUtf8("button_sin_025"));
        button_sin_025->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_5->addWidget(button_sin_025);

        button_sin_05 = new QPushButton(sin_button_widget);
        button_sin_05->setObjectName(QString::fromUtf8("button_sin_05"));

        horizontalLayout_5->addWidget(button_sin_05);

        button_sin_1 = new QPushButton(sin_button_widget);
        button_sin_1->setObjectName(QString::fromUtf8("button_sin_1"));

        horizontalLayout_5->addWidget(button_sin_1);

        button_sin_2 = new QPushButton(sin_button_widget);
        button_sin_2->setObjectName(QString::fromUtf8("button_sin_2"));

        horizontalLayout_5->addWidget(button_sin_2);

        button_sin_3 = new QPushButton(sin_button_widget);
        button_sin_3->setObjectName(QString::fromUtf8("button_sin_3"));

        horizontalLayout_5->addWidget(button_sin_3);


        gridLayout_7->addLayout(horizontalLayout_5, 0, 0, 1, 1);


        gridLayout_2->addWidget(sin_button_widget, 3, 0, 1, 1);

        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout_2, 2, 0, 1, 2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(tab_2);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Comic Sans MS"));
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);

        verticalLayout_2->addWidget(label);

        radioButton_disabled_mode = new QRadioButton(tab_2);
        radioButton_disabled_mode->setObjectName(QString::fromUtf8("radioButton_disabled_mode"));

        verticalLayout_2->addWidget(radioButton_disabled_mode);

        radioButton_static_mode = new QRadioButton(tab_2);
        radioButton_static_mode->setObjectName(QString::fromUtf8("radioButton_static_mode"));

        verticalLayout_2->addWidget(radioButton_static_mode);

        radioButton_speed_mode = new QRadioButton(tab_2);
        radioButton_speed_mode->setObjectName(QString::fromUtf8("radioButton_speed_mode"));

        verticalLayout_2->addWidget(radioButton_speed_mode);

        radioButton_path_mode = new QRadioButton(tab_2);
        radioButton_path_mode->setObjectName(QString::fromUtf8("radioButton_path_mode"));
        radioButton_path_mode->setEnabled(false);

        verticalLayout_2->addWidget(radioButton_path_mode);

        radioButton_sine_mode = new QRadioButton(tab_2);
        radioButton_sine_mode->setObjectName(QString::fromUtf8("radioButton_sine_mode"));

        verticalLayout_2->addWidget(radioButton_sine_mode);


        gridLayout_5->addLayout(verticalLayout_2, 1, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_3, 1, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        Kp_text = new QTextEdit(tab_2);
        Kp_text->setObjectName(QString::fromUtf8("Kp_text"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Kp_text->sizePolicy().hasHeightForWidth());
        Kp_text->setSizePolicy(sizePolicy1);
        Kp_text->setMaximumSize(QSize(71, 29));

        horizontalLayout->addWidget(Kp_text);

        write_Kp = new QPushButton(tab_2);
        write_Kp->setObjectName(QString::fromUtf8("write_Kp"));

        horizontalLayout->addWidget(write_Kp);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_3->addWidget(label_4);

        Ki_text = new QTextEdit(tab_2);
        Ki_text->setObjectName(QString::fromUtf8("Ki_text"));
        sizePolicy1.setHeightForWidth(Ki_text->sizePolicy().hasHeightForWidth());
        Ki_text->setSizePolicy(sizePolicy1);
        Ki_text->setMaximumSize(QSize(71, 29));

        horizontalLayout_3->addWidget(Ki_text);

        write_Ki = new QPushButton(tab_2);
        write_Ki->setObjectName(QString::fromUtf8("write_Ki"));

        horizontalLayout_3->addWidget(write_Ki);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_2->addWidget(label_5);

        Kd_text = new QTextEdit(tab_2);
        Kd_text->setObjectName(QString::fromUtf8("Kd_text"));
        sizePolicy1.setHeightForWidth(Kd_text->sizePolicy().hasHeightForWidth());
        Kd_text->setSizePolicy(sizePolicy1);
        Kd_text->setMaximumSize(QSize(71, 29));

        horizontalLayout_2->addWidget(Kd_text);

        write_Kd = new QPushButton(tab_2);
        write_Kd->setObjectName(QString::fromUtf8("write_Kd"));

        horizontalLayout_2->addWidget(write_Kd);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout_4->addLayout(verticalLayout, 2, 0, 1, 1);

        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font1);

        gridLayout_4->addWidget(label_6, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_2, 0, 0, 1, 1);


        gridLayout_5->addLayout(gridLayout_4, 0, 1, 2, 1);


        gridLayout_6->addLayout(gridLayout_5, 0, 0, 1, 1);

        tabWidget->addTab(tab_2, QString());
        tab_graph = new QWidget();
        tab_graph->setObjectName(QString::fromUtf8("tab_graph"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tab_graph->sizePolicy().hasHeightForWidth());
        tab_graph->setSizePolicy(sizePolicy2);
        widget = new QWidget(tab_graph);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 10, 771, 581));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        graphicsView = new QChartView(widget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        gridLayout->addWidget(graphicsView, 0, 0, 1, 4);

        plot_graphic = new QCheckBox(widget);
        plot_graphic->setObjectName(QString::fromUtf8("plot_graphic"));

        gridLayout->addWidget(plot_graphic, 1, 0, 1, 1);

        pushButtonResetPlot = new QPushButton(widget);
        pushButtonResetPlot->setObjectName(QString::fromUtf8("pushButtonResetPlot"));
        pushButtonResetPlot->setMaximumSize(QSize(150, 16777215));

        gridLayout->addWidget(pushButtonResetPlot, 1, 1, 1, 1);

        pushButtonStartSaveToFile = new QPushButton(widget);
        pushButtonStartSaveToFile->setObjectName(QString::fromUtf8("pushButtonStartSaveToFile"));

        gridLayout->addWidget(pushButtonStartSaveToFile, 1, 2, 1, 1);

        savePlotToFile = new QPushButton(widget);
        savePlotToFile->setObjectName(QString::fromUtf8("savePlotToFile"));
        savePlotToFile->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(savePlotToFile, 1, 3, 1, 1);

        tabWidget->addTab(tab_graph, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 814, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);
        toolBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        ConnectBtn->setText(QApplication::translate("MainWindow", "Connect", nullptr));
        toolBox->setItemText(toolBox->indexOf(page), QApplication::translate("MainWindow", "Serial Connection", nullptr));
        udpConnectButton->setText(QApplication::translate("MainWindow", "Connect", nullptr));
        toolBox->setItemText(toolBox->indexOf(page_2), QApplication::translate("MainWindow", "UDP Connection", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "\320\232\320\260\320\273\320\270\320\261\321\200\320\276\320\262\320\272\320\260", nullptr));
        pushButton_Set_angle->setText(QApplication::translate("MainWindow", "Send", nullptr));
        button_sin_025->setText(QApplication::translate("MainWindow", "0.25 \320\223\321\206", nullptr));
        button_sin_05->setText(QApplication::translate("MainWindow", "0.5 \320\223\321\206", nullptr));
        button_sin_1->setText(QApplication::translate("MainWindow", "1 \320\223\321\206", nullptr));
        button_sin_2->setText(QApplication::translate("MainWindow", "2\320\223\321\206", nullptr));
        button_sin_3->setText(QApplication::translate("MainWindow", "3\320\223\321\206", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 \320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\321\217/\321\201\320\272\320\276\321\200\320\276\321\201\321\202\320\270", nullptr));
        label->setText(QApplication::translate("MainWindow", "\320\240\320\265\320\266\320\270\320\274", nullptr));
        radioButton_disabled_mode->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\272\320\273\321\216\321\207\320\265\320\275", nullptr));
        radioButton_static_mode->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 \320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\321\217", nullptr));
        radioButton_speed_mode->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 \321\201\320\272\320\276\321\200\320\276\321\201\321\202\320\270", nullptr));
        radioButton_path_mode->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\320\275\320\270\320\265 \320\277\321\203\321\202\320\270", nullptr));
        radioButton_sine_mode->setText(QApplication::translate("MainWindow", "\320\241\320\270\320\275\321\203\321\201\320\276\320\270\320\264\320\260", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Kp", nullptr));
        Kp_text->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0.3</p></body></html>", nullptr));
        write_Kp->setText(QApplication::translate("MainWindow", "W", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "Ki", nullptr));
        Ki_text->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0.0002</p></body></html>", nullptr));
        write_Ki->setText(QApplication::translate("MainWindow", "W", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "Kd", nullptr));
        Kd_text->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">50</p></body></html>", nullptr));
        write_Kd->setText(QApplication::translate("MainWindow", "W", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "\320\237\320\230\320\224 \321\200\320\265\320\263\321\203\320\273\321\217\321\202\320\276\321\200 \320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\321\217", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265", nullptr));
        plot_graphic->setText(QApplication::translate("MainWindow", "\320\237\320\276\321\201\321\202\321\200\320\276\320\265\320\275\320\270\320\265 \320\263\321\200\320\260\321\204\320\270\320\272\320\260", nullptr));
        pushButtonResetPlot->setText(QApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\263\321\200\320\260\321\204\320\270\320\272", nullptr));
        pushButtonStartSaveToFile->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\277\320\270\321\201\321\214 \320\262 \321\204\320\260\320\271\320\273", nullptr));
        savePlotToFile->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_graph), QApplication::translate("MainWindow", "\320\223\321\200\320\260\321\204\320\270\320\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
