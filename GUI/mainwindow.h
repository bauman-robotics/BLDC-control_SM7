#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QWidget>


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

    void serial_port_init(void);
    void set_default_values(void);

private slots:




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


    //============





};

#endif // MAINWINDOW_H
