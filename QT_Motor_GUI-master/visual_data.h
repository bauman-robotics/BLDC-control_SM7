#ifndef VISUAL_H
#define VISUAL_H

#include <QMainWindow>
#include <QThread>
#include <QtCharts>
#include <QObject>
//#include "mainwindow.h"


class MyChart : public QObject
{

   Q_OBJECT


public:
QChart* chart1;
QChartView *chartView;
QLineSeries *series;

QLineSeries* series_accel_angle_mpu6000;
QLineSeries* series_accel_angle_da2;

//Current data
QLineSeries* series_current;
QLineSeries* series_des_current;


MyChart();
    ~MyChart();

 //   void change();
};


class RealTimePlot: public QObject
{
    Q_OBJECT

public:
    bool state_of_plot;
    QLineSeries* RTseries;

    QChart* RTchart;
    QChartView *RTchartView;
    QVector<QPointF> data_plot_points1;
    QVector<QPointF> data_plot_points2;
    QVector<QPointF> data_plot_points3;
    QVector<QPointF> data_plot_points4;
    QVector<QPointF> data_plot_points5;
    QVector<QPointF> data_plot_points6;
    QVector<QPointF> data_plot_points7;
    QVector<QPointF> data_plot_points8;



    void update();

    void zero_init_vector(QVector<QPointF>& vector_of_points);



    RealTimePlot();
    ~RealTimePlot();

    //режимы построения графиков углов
    bool gyro_L2GIS_EN;
    bool gyro_LSM6DS33_EN;
    bool gyro_mpu6000_EN;
    bool accel_mpu6000_EN;
    bool accel_LSM6DS33_EN;
    bool angle_acc_mpu6000;
    bool angle_acc_LSM6DS33;
    bool angle_gyro_L2GIS;


    //отображаемые параметры
    qreal angle_from_L2GIS;

    qreal angle_from_acc6000;
    qreal angle_from_accLSM6DS33;
    int16_t accel_mpu6000;
    int16_t accel_LSM6DS33;
    int16_t gyro_L2GIS;
    int16_t gyro_mpu6000;
    int16_t gyro_LSM6DS33;
    int16_t angle_from_L2GIS_raw;

};








#endif // VISUAL_H
