#include "visual_data.h"
#include <QApplication>
#include "defines.h"
#include "mainwindow.h"
#include <math.h>

static int randomBetween(int low, int high, int seed)
{
    qsrand(seed); // Установка базового числа для отсчёта рандома в qrand
    return (qrand() % ((high + 1) - low) + low);
}

MyChart::MyChart()
{
   chart1 = new QChart();
   series = new QLineSeries();

   series_current = new QLineSeries();
   series_des_current = new QLineSeries();

    series->setName(QString("L2GIS_GYRO"));
    series_current->setName(QString("Current"));
    series_des_current->setName(QString("Current_des"));

    chartView = new QChartView();

    //---------------------
    // Создаём случайную синусоиду
    int seed =0;
    seed = randomBetween(0, 100, seed);
    QLineSeries *series = new QLineSeries();
    int k = 0;
    while (k <= 100)
    {
        *series << QPointF(sin((seed+ k)*0.1), k);
        //data1_v.append(sin((seed+ k)*0.1);
        ++k;
    }

    // Создаём график и добавляем в него синусоиду
    //QChart *chart = new QChart();
    //chart->addSeries(series);
    //chart->legend()->hide();
    //chart->setTitle("Graphic");
    //------------------------



    chart1->addSeries(series);
    chart1->addSeries(series_current);
    chart1->addSeries(series_des_current);

    chart1->setTitle("Inertial measurements");

    chart1->createDefaultAxes();

    chart1->axisX()->setTitleText("Discretes");
    chart1->axisY()->setTitleText("Value");

    chart1->axisY()->setMin(-25);
    chart1->axisY()->setMax(25);

    chart1->legend()->setVisible(true);
    chart1->legend()->setAlignment(Qt::AlignBottom);

    chart1->setAnimationOptions(QChart::AllAnimations);

    QPen pen;
    pen.setWidth(2);
    //pen.setColor(Qt::red);
    series->setPen(pen);
    series->setColor(Qt::red);

    series->setUseOpenGL(true);

    series_current->setUseOpenGL(true);
    series_des_current->setUseOpenGL(true);

    chartView->setRubberBand(QChartView::RectangleRubberBand);

    chartView->setChart(chart1);

   chartView->chart()->axisX()->setMin(0);
   chartView->chart()->axisX()->setMax(9);
}

MyChart::~MyChart()
{

}



void RealTimePlot::update()
{
    static bool filled;
    static uint16_t fill_cnt=0;
    QPointF newPoint;
    qreal index_mem;


        for(int i=1; i<RT_SAMPLES; i++)
        {
            if(gyro_L2GIS_EN)
            {
                index_mem = data_plot_points1[i].y();
                data_plot_points1[i-1].setY(index_mem);

            }

        } // for


        if(gyro_L2GIS_EN)
            {
                data_plot_points1[RT_SAMPLES-1].setY(qreal(gyro_L2GIS));
            }


       if(gyro_L2GIS_EN) RTseries->replace(data_plot_points1);
}



void RealTimePlot::zero_init_vector(QVector<QPointF>& vector_of_points)
{
    QPointF newPoint;
    vector_of_points.clear();          // очистка вектора
    for(int i=0; i<RT_SAMPLES; i++)    //
    {
        newPoint.setX(qreal(i));
        newPoint.setY(qreal(0));
        vector_of_points.push_back(newPoint);
    }

}

RealTimePlot::RealTimePlot()
{
    gyro_L2GIS_EN=0;
    gyro_LSM6DS33_EN=0;
    gyro_mpu6000_EN=0;
    accel_mpu6000_EN=0;
    accel_LSM6DS33_EN=0;
    angle_acc_mpu6000=0;
    angle_acc_LSM6DS33=0;
    angle_gyro_L2GIS=0;

    state_of_plot=false;
    RTchart = new QChart();

    RTseries = new QLineSeries();
//   RTseries6 = new QLineSeries();

    RTchartView = new QChartView();

    RTseries->setName(QString("gyro_L2GIS"));

    RTchart->addSeries(RTseries);

    RTchart->setTitle("Real Time Plot");

    RTchart->createDefaultAxes();

    RTchart->axisX()->setTitleText("Discretes");
    RTchart->axisY()->setTitleText("Value");


   RTchart->axisY()->setMin(-17000);
   RTchart->axisY()->setMax(17000);



    RTchart->legend()->setVisible(true);
    RTchart->legend()->setAlignment(Qt::AlignBottom);



    RTchart->setAnimationOptions(QChart::NoAnimation); // NoAnimation

    QPen pen;
    pen.setWidth(1);
    RTseries->setPen(pen);
    RTseries->setColor(Qt::red);
    RTseries->setUseOpenGL(true);

    RTchartView->setRubberBand(QChartView::RectangleRubberBand);

    RTchartView->setChart(RTchart);

    RTchartView->chart()->axisX()->setMin(0);
    RTchartView->chart()->axisX()->setMax(1000);

}

RealTimePlot::~RealTimePlot()
{

}
