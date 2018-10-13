#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // инициализация COM порта
    serial_port_init();


}







MainWindow::~MainWindow()
{
    delete ui;
    port_test->close();
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
    //connect(port_test, SIGNAL(readyRead()), this, SLOT(serial_recieved()));
}

void MainWindow::set_default_values()
{


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
