#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include "visual_data.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // инициализация COM порта
    serial_port_init();

   // добавление графика в Layout
    ui->Plot_Layout->addWidget(Plot_data.chartView);                // осциллограмма
    ui->real_time_plot_layout->addWidget(RT_Data.RTchartView);      //  real time plot

    // Установка значений окон параметров осцилограммы по умолчанию
    set_default_values();
}







MainWindow::~MainWindow()
{
    delete ui;
    port_test->close();
}

void MainWindow::build_static_plot()
{
       QVector<float> angle_L2GIS, angle_accel_MPU6000, angle_accel_LSM6DS33;

    bool data1_flag=0, data2_flag=0, data3_flag=0,data4_flag=0, data5_flag=0, data6_flag=0, data7_flag=0, data8_flag=0,  current_data_flag=0, current_des_data_flag=0 ;
    int maxX=0, minY1=0, minY2=0, minY3=0, minY4=0, minY5=0, minY6=0, minY7=0, minY8=0, maxY1=0, maxY2=0, maxY3=0, maxY4=0, maxY5=0, maxY6=0, maxY7=0, maxY8=0, minY=0, maxY=0, min_max_set=0;
    int minY_current=0, minY_current_des=0, maxY_current=0, maxY_current_des=0;
    int samples_num=0;
    uint8_t max_osc=0;;



// Очистка графиков перед созданием новых
Plot_data.series->clear();
Plot_data.series2->clear();
Plot_data.series3->clear();
Plot_data.series4->clear();
Plot_data.series5->clear();
Plot_data.series6->clear();
Plot_data.series7->clear();
Plot_data.series8->clear();
Plot_data.series_current->clear();
Plot_data.series_des_current->clear();

// Предварительное отключение маркировки
Plot_data.chart1->legend()->markers(Plot_data.series)[0]->setVisible(false);
Plot_data.chart1->legend()->markers(Plot_data.series2)[0]->setVisible(false);
Plot_data.chart1->legend()->markers(Plot_data.series3)[0]->setVisible(false);
Plot_data.chart1->legend()->markers(Plot_data.series4)[0]->setVisible(false);
Plot_data.chart1->legend()->markers(Plot_data.series5)[0]->setVisible(false);
Plot_data.chart1->legend()->markers(Plot_data.series6)[0]->setVisible(false);
Plot_data.chart1->legend()->markers(Plot_data.series7)[0]->setVisible(false);
Plot_data.chart1->legend()->markers(Plot_data.series8)[0]->setVisible(false);
Plot_data.chart1->legend()->markers(Plot_data.series_current)[0]->setVisible(false);
Plot_data.chart1->legend()->markers(Plot_data.series_des_current)[0]->setVisible(false);

























    if(data1_flag)
    {
        minY = *std::min_element(data1_v.begin(), data1_v.end()); // нахождение минимального значения
        maxY = *std::max_element(data1_v.begin(), data1_v.end()); // нахождение максимального значения
        maxX = data1_v.size(); // граница оси х - количество данных
        samples_num = data1_v.size();
        min_max_set=1;

    }

    if(data2_flag)
    {
        minY2 = *std::min_element(data2_v.begin(), data2_v.end()); // нахождение минимального значения
        maxY2 = *std::max_element(data2_v.begin(), data2_v.end()); // // нахождение максимального значения
        maxX = data2_v.size(); // граница оси х - количество данных


       if(min_max_set==0)
        {
            minY=minY2;
            maxY=maxY2;
            samples_num = data2_v.size();
            min_max_set=1;
        }
       else
       {
           minY = std::min(minY, minY2);
           maxY = std::max(maxY, maxY2);
           samples_num = std::min(samples_num, data2_v.size());

       }

    }

    if(data3_flag)
    {
        minY3 = *std::min_element(data3_v.begin(), data3_v.end()); // нахождение минимального значения
        maxY3 = *std::max_element(data3_v.begin(), data3_v.end()); // // нахождение максимального значения
        maxX = data3_v.size(); // граница оси х - количество данных

        if(min_max_set==0)
         {
             minY=minY3;
             maxY=maxY3;
             samples_num = data3_v.size();
             min_max_set=1;
         }
        else
        {
            minY = std::min(minY, minY3);
            maxY = std::max(maxY, maxY3);
            samples_num = std::min(samples_num, data3_v.size());

        }

    }


    if(data4_flag)
    {
        minY4 = *std::min_element(data4_v.begin(), data4_v.end()); // нахождение минимального значения
        maxY4 = *std::max_element(data4_v.begin(), data4_v.end()); // // нахождение максимального значения
        maxX = data4_v.size(); // граница оси х - количество данных

        if(min_max_set==0)
         {
             minY=minY4;
             maxY=maxY4;
             samples_num = data4_v.size();
             min_max_set=1;
         }
        else
        {
            minY = std::min(minY, minY4);
            maxY = std::max(maxY, maxY4);
            samples_num = std::min(samples_num, data4_v.size());

        }

    }





    if(data5_flag)
    {
        minY5 = *std::min_element(data5_v.begin(), data5_v.end()); // нахождение минимального значения
        maxY5 = *std::max_element(data5_v.begin(), data5_v.end()); // // нахождение максимального значения
        maxX = data5_v.size(); // граница оси х - количество данных

        if(min_max_set==0)
         {
             minY=minY5;
             maxY=maxY5;
             samples_num = data5_v.size();
             min_max_set=1;
         }
        else
        {
            minY = std::min(minY, minY5);
            maxY = std::max(maxY, maxY5);
            samples_num = std::min(samples_num, data5_v.size());

        }

    }





    if(data6_flag)
    {
        minY6 = *std::min_element(angle_accel_MPU6000.begin(), angle_accel_MPU6000.end()); // нахождение минимального значения
        maxY6 = *std::max_element(angle_accel_MPU6000.begin(), angle_accel_MPU6000.end()); // // нахождение максимального значения
        maxX = angle_accel_MPU6000.size();//Plot_data.chartView->chart()->axisX()->setMax(angle_accel_MPU6000.size()); // граница оси х - количество данных

        if(min_max_set==0)
         {
             minY=minY6;
             maxY=maxY6;
             samples_num = angle_accel_MPU6000.size();
             min_max_set=1;
         }
        else
        {
            minY = std::min(minY, minY6);
            maxY = std::max(maxY, maxY6);
            samples_num = std::min(samples_num, angle_accel_MPU6000.size());

        }

    }




    if(data7_flag)
    {
        minY7 = *std::min_element(angle_accel_LSM6DS33.begin(), angle_accel_LSM6DS33.end()); // нахождение минимального значения
        maxY7 = *std::max_element(angle_accel_LSM6DS33.begin(), angle_accel_LSM6DS33.end()); // // нахождение максимального значения
        maxX = angle_accel_LSM6DS33.size();//Plot_data.chartView->chart()->axisX()->setMax(angle_accel_LSM6DS33.size()); // граница оси х - количество данных

        if(min_max_set==0)
         {
             minY=minY7;
             maxY=maxY7;
             samples_num = angle_accel_LSM6DS33.size();
             min_max_set=1;
         }
        else
        {
            minY = std::min(minY, minY7);
            maxY = std::max(maxY, maxY7);
            samples_num = std::min(samples_num, angle_accel_LSM6DS33.size());

        }

    }







    if(data8_flag)
    {
        minY8 = *std::min_element(angle_L2GIS.begin(), angle_L2GIS.end()); // нахождение минимального значения
        maxY8 = *std::max_element(angle_L2GIS.begin(), angle_L2GIS.end()); // // нахождение максимального значения
        maxX = angle_L2GIS.size();//Plot_data.chartView->chart()->axisX()->setMax(angle_L2GIS.size()); // граница оси х - количество данных

        if(min_max_set==0)
         {
             minY=minY8;
             maxY=maxY8;
             samples_num = angle_L2GIS.size();
             min_max_set=1;
         }
        else
        {
            minY = std::min(minY, minY8);
            maxY = std::max(maxY, maxY8);
            samples_num = std::min(samples_num, angle_L2GIS.size());

        }

    }




    if(current_data_flag)
    {
        minY_current = *std::min_element(current_v.begin(), current_v.end()); // нахождение минимального значения
        maxY_current = *std::max_element(current_v.begin(), current_v.end()); // // нахождение максимального значения
        maxX = current_v.size();//Plot_data.chartView->chart()->axisX()->setMax(angle_L2GIS.size()); // граница оси х - количество данных

        if(min_max_set==0)
         {
             minY=minY_current;
             maxY=maxY_current;
             samples_num = current_v.size();
             min_max_set=1;
         }
        else
        {
            minY = std::min(minY, minY_current);
            maxY = std::max(maxY, maxY_current);
            samples_num = std::min(samples_num, current_v.size());

        }

    }







    if(current_des_data_flag)
    {
        minY_current_des = *std::min_element(current_des_v.begin(), current_des_v.end()); // нахождение минимального значения
        maxY_current_des = *std::max_element(current_des_v.begin(), current_des_v.end()); // // нахождение максимального значения
        maxX = current_v.size();//Plot_data.chartView->chart()->axisX()->setMax(angle_L2GIS.size()); // граница оси х - количество данных

        if(min_max_set==0)
         {
             minY=minY_current_des;
             maxY=maxY_current_des;
             samples_num = current_des_v.size();
             min_max_set=1;
         }
        else
        {
            minY = std::min(minY, minY_current_des);
            maxY = std::max(maxY, maxY_current_des);
            samples_num = std::min(samples_num, current_des_v.size());

        }

    }













    qDebug() << "Размер выборки: " << samples_num;



// Построение графика

    for(int i=0; i< samples_num-1 ; i++) // строится график по наименьшему количеству точек для предотвращения выхода за пределы массива
    {

        if(data1_flag)
        {
            Plot_data.series->append(i, data1_v[i]);

        }

        if(data2_flag)
        {
            Plot_data.series2->append(i, data2_v[i]);
          //  qDebug() << "Plotting value" << data2_v[i];


        }

        if(data3_flag)
        {
          Plot_data.series3->append(i, data3_v[i]);

        }


        if(data4_flag)
        {
          Plot_data.series4->append(i, data4_v[i]);

        }




        if(data5_flag)
        {
          Plot_data.series5->append(i, data5_v[i]);

        }


        if(data6_flag)
        {
          Plot_data.series6->append(i, angle_accel_MPU6000[i]);

        }


        if(data7_flag)
        {
          Plot_data.series7->append(i, angle_accel_LSM6DS33[i]);

        }



        if(data8_flag)
        {
          Plot_data.series8->append(i, angle_L2GIS[i]);
          //qDebug() << "Строю angle_L2GIS[i] = " << angle_L2GIS[i];

        }


        if(current_data_flag)
        {
          Plot_data.series_current->append(i, current_v[i]);
          //qDebug() << "Строю angle_L2GIS[i] = " << angle_L2GIS[i];

        }

        if(current_des_data_flag)
        {
          Plot_data.series_des_current->append(i, current_des_v[i]);
          //qDebug() << "Строю angle_L2GIS[i] = " << angle_L2GIS[i];

        }




    }












    // установка соответствующих границ
    /*Plot_data.chartView->chart()->axisY()->setMin(minY - 100);
    Plot_data.chartView->chart()->axisY()->setMax(maxY + 100);
    Plot_data.chartView->chart()->axisX()->setMin(0);*/

  // Установка шкалы по осям графика (перенести в конструктор)
    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;
    axisX->setRange(0, maxX);
    axisX->setTickCount(20);
    axisX->setLabelFormat("%d");
    Plot_data.chartView->chart()->setAxisX(axisX, Plot_data.series);
    Plot_data.chartView->chart()->setAxisX(axisX, Plot_data.series2);
    Plot_data.chartView->chart()->setAxisX(axisX, Plot_data.series3);
    Plot_data.chartView->chart()->setAxisX(axisX, Plot_data.series4);
    Plot_data.chartView->chart()->setAxisX(axisX, Plot_data.series5);
    Plot_data.chartView->chart()->setAxisX(axisX, Plot_data.series6);
    Plot_data.chartView->chart()->setAxisX(axisX, Plot_data.series7);
    Plot_data.chartView->chart()->setAxisX(axisX, Plot_data.series8);
    Plot_data.chartView->chart()->setAxisX(axisX, Plot_data.series_current);
    Plot_data.chartView->chart()->setAxisX(axisX, Plot_data.series_des_current);
    axisY->setRange(minY-abs(((float)minY))*0.1, maxY+((float)maxY)*0.1);
    //qDebug() << "minY, maxY, abs(((float)minY))*0.1, maxY+((float)maxY)*0.1 " << minY << " " << maxY << " " << abs(((float)minY))*0.1 << " " << maxY+((float)maxY)*0.1;
    axisY->setTickCount(10);
    axisY->setLabelFormat("%d");
    Plot_data.chartView->chart()->setAxisY(axisY, Plot_data.series);
    Plot_data.chartView->chart()->setAxisY(axisY, Plot_data.series2);
    Plot_data.chartView->chart()->setAxisY(axisY, Plot_data.series3);
    Plot_data.chartView->chart()->setAxisY(axisY, Plot_data.series4);
    Plot_data.chartView->chart()->setAxisY(axisY, Plot_data.series5);
    Plot_data.chartView->chart()->setAxisY(axisY, Plot_data.series6);
    Plot_data.chartView->chart()->setAxisY(axisY, Plot_data.series7);
    Plot_data.chartView->chart()->setAxisY(axisY, Plot_data.series8);
    Plot_data.chartView->chart()->setAxisY(axisY, Plot_data.series_current);
    Plot_data.chartView->chart()->setAxisY(axisY, Plot_data.series_des_current);

    //Plot_data.chartView->chart()->setAxisX(axisX, Plot_data.series2);



    // очищение векторов данных для следующей осциллограмы
    data1_v.clear();
    data2_v.clear();
    data3_v.clear();
    data4_v.clear();
    data5_v.clear();
    data8_v.clear();
    current_v.clear();
    current_des_v.clear();

    qDebug() <<  "График построен";

   // accel_angle_v.clear();
    //gyroL2GID_angle_v.clear();




}

void MainWindow::serial_port_init()
{
    port_test = new QSerialPort();
    port_test->setPortName("com4");

    port_test->open(QIODevice::ReadWrite);
    port_test->setBaudRate(QSerialPort::Baud115200);
    port_test->setDataBits(QSerialPort::Data8);
    port_test->setParity(QSerialPort::NoParity);
    port_test->setStopBits(QSerialPort::OneStop);
    port_test->setFlowControl(QSerialPort::NoFlowControl);
    connect(port_test, SIGNAL(readyRead()), this, SLOT(serial_recieved()));
}

void MainWindow::set_default_values()
{


}

void MainWindow::serial_recieved()
{

    int16_t data1, data2, data3, data4, data_full, data1_2, data_L, data_H,  data1_L, data1_H, data2_L, data2_H, data3_L, data3_H, data4_L, data4_H;
    bool data1_ready =0, data2_ready=0, data3_ready=0, data4_ready=0;

    QByteArray ba; // массив для приема данных


    //QVector<QByteArray> vector_ba; // альтернатива накопления значений
    // ba = port_test->readAll();

        ba = port_test->readAll();
        qDebug() <<  "  data recieved " << ba.toHex();


    if(ba=="finished") // при приеме последовательности "finished"
    {
        qDebug() << "FINISHED SEQUENSE GOTTEN";
        qDebug() << "Vector size1: " << data1_v.size();
        qDebug() << "Vector size2: " << data2_v.size();
        qDebug() << "Vector size3: " << data3_v.size();
        qDebug() << "Vector size4: " << data4_v.size();
        qDebug() << "Vector size5: " << data5_v.size();
        qDebug() << "Vector size8: " << data8_v.size();

        qDebug() << "Current vector: " << current_v.size();
        qDebug() << "Current_des vector:" << current_des_v.size();
        oscillogramm_EN=0;
        build_static_plot();
    }

    else
     {
        qDebug() <<  " new data recieved ";

        data_buffer += ba;

        for(int i = 0; i<ba.size(); i++) // цикл по полученным данным
         {
          if(ba.size() > (i+3)) // (+3) -> i - байт разделения, i+1 - байт индекса параметра, i+2 - нижний байт параметра, i+3 - верхний байт, проверка для исключения ситуации выхода за рамки массива
           {

             if(ba.at(i)=='\n')
             {

                 if(ba.at(i+1)=='a')
                 {
                     //i++;i++;

                     data1_L = ((int16_t)ba.at(i+2))&0xFF;
                     data1_H = ((int16_t)ba.at(i+3))<<8;
                     data1 = data1_L|data1_H;
                     data1_ready = true;
                     if(oscillogramm_EN) data1_v.push_back(data1);
                     RT_Data.gyro_L2GIS = data1;

                 }

                 if(ba.at(i+1)=='b')
                 {
                     data2_L = ((int16_t)ba.at(i+2))&0xFF;
                     data2_H = ((int16_t)ba.at(i+3))<<8;
                     data2 = data2_L|data2_H;
                     data2_ready = true;
                     if(oscillogramm_EN) data2_v.push_back(data2);
                     RT_Data.gyro_mpu6000 = data2;

                 }

                 if(ba.at(i+1)=='c')
                 {

                     data3_L = ((int16_t)ba.at(i+2))&0xFF;
                     data3_H = ((int16_t)ba.at(i+3))<<8;
                     data3 = data3_L|data3_H;
                     data3_ready = true;
                     if(oscillogramm_EN) data3_v.push_back(data3);
                     RT_Data.gyro_LSM6DS33 = data3;
                     qDebug() << "гироскоп LSM6DS33: " << data3;

                 }

                 if(ba.at(i+1)=='d')
                 {

                     data4_L = ((int16_t)ba.at(i+2))&0xFF;
                     data4_H = ((int16_t)ba.at(i+3))<<8;
                     data4 = data4_L|data4_H;
                     data4_ready = true;
                     if(oscillogramm_EN) data4_v.push_back(data4);
                     RT_Data.accel_mpu6000 = data4;

                  }





                 if(ba.at(i+1)=='e')
                 {

                     data_L = ((int16_t)ba.at(i+2))&0xFF;
                     data_H = ((int16_t)ba.at(i+3))<<8;
                     data_full = data_L|data_H;
                     if(oscillogramm_EN) data5_v.push_back(data_full);
                     RT_Data.accel_LSM6DS33 = data_full;

                  }







                  if(ba.at(i+1)=='h')
                  {

                     data_L = ((int16_t)ba.at(i+2))&0xFF;
                     data_H = ((int16_t)ba.at(i+3))<<8;
                     data_full = data_L|data_H;
                     //data8_ready = true;
                     if(oscillogramm_EN) data8_v.push_back(data_full);
                     RT_Data.angle_from_L2GIS_raw = data_full;
                    //qDebug() << "data_full" << data_full;
                   }




                  if(ba.at(i+1)=='f')
                  {

                  uint16_t udata_L = ((uint16_t)ba.at(i+2))&0xFF;
                  uint16_t udata_H = ((uint16_t)ba.at(i+3))<<8;
                  uint16_t udata_full = udata_L|udata_H;
                     //data8_ready = true;
                   if(oscillogramm_EN) current_v.push_back(udata_full);

                    //qDebug() << "data_full" << data_full;
                   }




                  if(ba.at(i+1)=='g')
                  {

                  uint16_t udata_L2 = ((uint16_t)ba.at(i+2))&0xFF;
                  uint16_t udata_H2 = ((uint16_t)ba.at(i+3))<<8;
                  uint16_t udata_full2 = udata_L2|udata_H2;
                     //data8_ready = true;
                 if(oscillogramm_EN) current_des_v.push_back(udata_full2);

                    //qDebug() << "data_full" << data_full;
                   }

             }

            } // if ba.size > i+3

            if(RT_Data.state_of_plot) RT_Data.update();

         } // for



    } // else (!finished)








}





void MainWindow::on_Get_oscillogram_pressed()
{
    uint8_t max_osc;
    QByteArray data_to_send;
    uint8_t data=0, data2=0;
    data_to_send[0] = 'f'; // команда записи осциллограмы







    oscillogramm_EN=true;

    data_to_send[1] = data;
    data_to_send[2] = data2;

    port_test->write(data_to_send);

}







void MainWindow::on_radioButton_disabled_mode_clicked()
{
    QByteArray data_to_send;
    data_to_send[0] = 'a';
    data_to_send[1] = 0x00;
    data_to_send[2] = 0x00;
    port_test->write(data_to_send);

}

void MainWindow::on_radioButton_static_mode_clicked()
{
    QByteArray data_to_send;
    data_to_send[0] = 'a';
    data_to_send[1] = 0x02;
    data_to_send[2] = 0x00;
    port_test->write(data_to_send);
}

void MainWindow::on_radioButton_sine_mode_clicked()
{
    QByteArray data_to_send;
    data_to_send[0] = 'a';
    data_to_send[1] = 0x01;
    data_to_send[2] = 0x00;
    port_test->write(data_to_send);
}

void MainWindow::on_pushButton_Set_angle_clicked()
{
    QByteArray data_to_send;
    data_to_send[0] = 'd';
    int16_t angle = ui->spinBox_des_val->value();
    data_to_send[1] = int16_t(angle)&0xFF;
    data_to_send[2] = (int16_t(angle)&0xFF00)>>8;
    port_test->write(data_to_send);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    QByteArray data_to_send;
    data_to_send[0] = 'd';
    int16_t angle = ui->horizontalSlider->value();
    data_to_send[1] = int16_t(angle)&0xFF;
    data_to_send[2] = (int16_t(angle)&0xFF00)>>8;
    port_test->write(data_to_send);
}

void MainWindow::on_pushButton_2_clicked()
{
    QByteArray data_to_send;// калибровка энкодера
    data_to_send[0] = 'b';
    data_to_send[1] = 0x00;
    data_to_send[2] = 0x00;
    port_test->write(data_to_send);
}

void MainWindow::on_pushButton_Set_angle_2_clicked()
{
    QByteArray data_to_send;//
    data_to_send[0] = 'e'; // Коэффициент
    QString raw_string_val = ui->Kp_text->toPlainText();
    float float_val  = raw_string_val.toFloat();
    int16_t encoded_float_val = (int16_t)(float_val*100);

    data_to_send[1] = (encoded_float_val & 0xFF); // Значение int16 (float*100)
    data_to_send[2] = (encoded_float_val & 0xFF00)>>8;
    port_test->write(data_to_send);
}

void MainWindow::on_write_Ki_clicked()
{
    QByteArray data_to_send;//
    data_to_send[0] = 'g'; // Коэффициент
    QString raw_string_val = ui->Ki_text->toPlainText();
    qDebug() << raw_string_val;
    float float_val  = raw_string_val.toFloat();
    qDebug() << float_val;
    float test2  = (float_val*10000);
    qDebug() << test2;
    int16_t encoded_float_val = (int16_t)test2;
     qDebug() << encoded_float_val;

    data_to_send[1] = (encoded_float_val & 0xFF); // Значение int16 (float*100)
    data_to_send[2] = (encoded_float_val & 0xFF00)>>8;
    port_test->write(data_to_send);
}

void MainWindow::on_write_Kd_clicked()
{
    QByteArray data_to_send;//
    data_to_send[0] = 'h'; // Коэффициент
    QString raw_string_val = ui->Kd_text->toPlainText();
    qDebug() << raw_string_val;
    uint16_t Kd  = raw_string_val.toUShort();
    //qDebug() << float_val;
    //float test2  = (float_val*10000);
    //qDebug() << test2;
    //int16_t encoded_float_val = (int16_t)test2;
    // qDebug() << encoded_float_val;

    data_to_send[1] = (Kd & 0xFF); // Значение int16 (float*100)
    data_to_send[2] = (Kd & 0xFF00)>>8;
    port_test->write(data_to_send);
}
