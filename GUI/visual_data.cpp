#include "visual_data.h"
#include <QApplication>
#include "defines.h"
#include "mainwindow.h"
MyChart::MyChart()
{



   chart1 = new QChart();
   series = new QLineSeries();
   series2 = new QLineSeries();
   series3 = new QLineSeries();
   series4 = new QLineSeries();
   series5 = new QLineSeries();
   series6 = new QLineSeries();
   series7 = new QLineSeries();
   series8 = new QLineSeries();
   series_current = new QLineSeries();
   series_des_current = new QLineSeries();





    series->setName(QString("L2GIS_GYRO"));
    series2->setName(QString("MPU6000_GYRO"));
    series3->setName(QString("LSM6DS33_GYRO"));
    series4->setName(QString("MPU_6000_ACCEL"));
    series5->setName(QString("ACCEL_LSM6DS33"));
    series6->setName(QString("ANGLE_ACCEL_MPU6000"));
    series7->setName(QString("ANGLE_ACCEL_LSM6DS33"));
    series8->setName(QString("ANGLE_L2GIS"));
    series_current->setName(QString("Current"));
    series_des_current->setName(QString("Current_des"));



    chartView = new QChartView();




    chart1->addSeries(series);
    chart1->addSeries(series2);
    chart1->addSeries(series3);
    chart1->addSeries(series4);
    chart1->addSeries(series5);
    chart1->addSeries(series6);
    chart1->addSeries(series7);
    chart1->addSeries(series8);
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
    series2->setPen(pen);
    series2->setColor(Qt::darkGreen);
    series3->setPen(pen);
    series3->setColor(Qt::blue);
    series4->setPen(pen);
    series4->setColor(Qt::darkMagenta);

    series->setUseOpenGL(true);
    series2->setUseOpenGL(true);
    series3->setUseOpenGL(true);
    series4->setUseOpenGL(true);
    series5->setUseOpenGL(true);
    series6->setUseOpenGL(true);
    series7->setUseOpenGL(true);
    series8->setUseOpenGL(true);
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

            if(gyro_mpu6000_EN)
            {
                index_mem = data_plot_points2[i].y();
                data_plot_points2[i-1].setY(index_mem);
            }


            if(gyro_LSM6DS33_EN)
            {
                index_mem = data_plot_points3[i].y();
                data_plot_points3[i-1].setY(index_mem);
            }


            if(accel_mpu6000_EN)
            {
                index_mem = data_plot_points4[i].y();
                data_plot_points4[i-1].setY(index_mem);
            }


            if(accel_LSM6DS33_EN)
            {
                index_mem = data_plot_points5[i].y();
                data_plot_points5[i-1].setY(index_mem);
            }



            if(angle_acc_mpu6000)
            {
                index_mem = data_plot_points6[i].y();
                data_plot_points6[i-1].setY(index_mem);
            }


            if(angle_acc_LSM6DS33)
            {
                index_mem = data_plot_points7[i].y();
                data_plot_points7[i-1].setY(index_mem);
            }


            if(angle_gyro_L2GIS)
            {
                index_mem = data_plot_points8[i].y();
                data_plot_points8[i-1].setY(index_mem);
            }




        } // for


        if(gyro_L2GIS_EN)
            {
                data_plot_points1[RT_SAMPLES-1].setY(qreal(gyro_L2GIS));
            }
        if(gyro_mpu6000_EN)
            {
                data_plot_points2[RT_SAMPLES-1].setY(qreal(gyro_mpu6000));
            }
        if(gyro_LSM6DS33_EN)
            {
                data_plot_points3[RT_SAMPLES-1].setY(qreal(gyro_LSM6DS33));

            }
        if(accel_mpu6000_EN)
            {
                data_plot_points4[RT_SAMPLES-1].setY(qreal(accel_mpu6000));
            }
        if(accel_LSM6DS33_EN)
            {
                data_plot_points5[RT_SAMPLES-1].setY(qreal(accel_LSM6DS33));
            }

        if(angle_acc_mpu6000)
            {
                angle_from_acc6000 = ((qreal)accel_mpu6000/2048)*90;
                data_plot_points6[RT_SAMPLES-1].setY(qreal(angle_from_acc6000));
            }

        if(angle_acc_LSM6DS33)
            {
                angle_from_accLSM6DS33 = ((qreal)accel_LSM6DS33/2048)*90;
                data_plot_points7[RT_SAMPLES-1].setY(qreal(angle_from_accLSM6DS33));
            }

        if(angle_gyro_L2GIS)
            {
                angle_from_L2GIS = ((qreal)angle_from_L2GIS_raw)/100;
                data_plot_points8[RT_SAMPLES-1].setY(qreal(angle_from_L2GIS));
            }




       if(gyro_L2GIS_EN) RTseries->replace(data_plot_points1);
       if(gyro_mpu6000_EN) RTseries2->replace(data_plot_points2);
       if(gyro_LSM6DS33_EN) RTseries3->replace(data_plot_points3);
       if(accel_mpu6000_EN) RTseries4->replace(data_plot_points4);
       if(accel_LSM6DS33_EN) RTseries5->replace(data_plot_points5);
       if(angle_acc_mpu6000) RTseries6->replace(data_plot_points6);
       if(angle_acc_LSM6DS33) RTseries7->replace(data_plot_points7);
       if(angle_gyro_L2GIS) RTseries8->replace(data_plot_points8);
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
    RTseries2 = new QLineSeries();
    RTseries3 = new QLineSeries();
    RTseries4 = new QLineSeries();
    RTseries5 = new QLineSeries();
    RTseries6 = new QLineSeries();
    RTseries7 = new QLineSeries();
    RTseries8 = new QLineSeries();
 //   RTseries6 = new QLineSeries();



    RTchartView = new QChartView();

    RTseries->setName(QString("gyro_L2GIS"));
    RTseries2->setName(QString("gyro_mpu"));
    RTseries3->setName(QString("gyro_LSM6DS33"));
    RTseries4->setName(QString("accel_mpu"));
    RTseries5->setName(QString("accel_LSM6DS33"));
    RTseries6->setName(QString("angle_accel_mpu6000"));
    RTseries7->setName(QString("angle_LSM6DS33"));
    RTseries8->setName(QString("angle_L2GIS"));
    //RTseries2->setName(QString("gyro_mpu"));

    RTchart->addSeries(RTseries);
    RTchart->addSeries(RTseries2);
    RTchart->addSeries(RTseries3);
    RTchart->addSeries(RTseries4);
    RTchart->addSeries(RTseries5);
    RTchart->addSeries(RTseries6);
    RTchart->addSeries(RTseries7);
    RTchart->addSeries(RTseries8);

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

    RTseries2->setPen(pen);
    RTseries2->setColor(Qt::blue);
    RTseries2->setUseOpenGL(true);


    RTseries3->setPen(pen);
    RTseries3->setColor(Qt::green);
    RTseries3->setUseOpenGL(true);

    RTseries4->setPen(pen);
    RTseries4->setColor(Qt::darkMagenta);
    RTseries4->setUseOpenGL(true);

    RTseries5->setPen(pen);
    RTseries5->setColor(Qt::darkYellow);
    RTseries5->setUseOpenGL(true);

    RTseries6->setPen(pen);
    RTseries6->setColor(Qt::darkRed);
    RTseries6->setUseOpenGL(true);

    RTseries7->setPen(pen);
    RTseries7->setColor(Qt::darkBlue);
    RTseries7->setUseOpenGL(true);

    RTseries8->setPen(pen);
    RTseries8->setColor(Qt::darkGreen);
    RTseries8->setUseOpenGL(true);





    RTchartView->setRubberBand(QChartView::RectangleRubberBand);

    RTchartView->setChart(RTchart);


    RTchartView->chart()->axisX()->setMin(0);
    RTchartView->chart()->axisX()->setMax(1000);




}

RealTimePlot::~RealTimePlot()
{

}
