#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QWidget>
#include <QtCharts/QChart>
#include <QtCharts/QtCharts>
#include "visual_data.h"
#include "defines.h"
#include <cmath>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    MyChart Plot_data; // oscillogram
    RealTimePlot RT_Data; // real time data plot class
    uint8_t MEMS_state;// выбранные источники сигнала



    void build_static_plot();
    void serial_port_init(void);
    void set_default_values(void);

private slots:

    void serial_recieved();
   // void build_plot();




    void on_Get_oscillogram_pressed();


    void on_radioButton_disabled_mode_clicked();

    void on_radioButton_static_mode_clicked();

    void on_radioButton_sine_mode_clicked();

    void on_pushButton_Set_angle_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void on_pushButton_2_clicked();

    void on_pushButton_Set_angle_2_clicked();

    void on_write_Ki_clicked();

    void on_write_Kd_clicked();

private:

    Ui::MainWindow *ui;

    //COM ===
    QSerialPort *port_test;
    QString serial_buffer;
    QByteArray data_buffer; // буффер для приема данных
    QVector<int16_t> data1_v; // контейнер для первой переменной
    QVector<int16_t> data2_v; // контейнер для второй переменной
    QVector <int16_t> data3_v; // контейнер для третьего параметра
    QVector <int16_t> data4_v; // акселерометр MPU6000
    QVector <int16_t> data5_v; // акселерометр DA2

    QVector <int16_t> data8_v; //  угол по гироскопу L2GIS

    QVector<uint16_t> current_v;
    QVector<uint16_t> current_des_v;


    bool oscillogramm_EN;

    //============





};

#endif // MAINWINDOW_H
