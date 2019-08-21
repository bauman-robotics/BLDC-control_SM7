#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QWidget>
#include <QQueue>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include "visual_data.h"

QT_CHARTS_USE_NAMESPACE

size_t encode(const uint8_t *ptr, size_t length, uint8_t *dst);
size_t cobs_decode(const uint8_t * input, size_t length, uint8_t * output);

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void build_static_plot();
    void serial_port_init(void);
    void set_default_values(void);

private slots:
    void openConnection();
    void on_radioButton_disabled_mode_clicked();
    void on_radioButton_static_mode_clicked();
    void on_radioButton_sine_mode_clicked();
    void on_radioButton_speed_mode_clicked();
    void on_pushButton_Set_angle_clicked();
    void on_horizontalSlider_valueChanged(int value);
    void on_pushButton_2_clicked();
    void on_write_Kp_clicked();
    void on_write_Ki_clicked();
    void on_write_Kd_clicked();
    void on_spinBox_des_val_valueChanged(double arg1);
    void on_button_sin_3_clicked();
    void on_button_sin_2_clicked();
    void on_button_sin_1_clicked();
    void on_button_sin_05_clicked();
    void on_button_sin_025_clicked();
    void SendBytesFloat(char command_code, float data);
    void SendByte(char command_code);
    void serialDataReceived();
    void on_pushButtonResetPlot_clicked();
    void on_savePlotToFile_clicked();

    void on_pushButtonStartSaveToFile_clicked();

    void on_plot_graphic_stateChanged(int arg1);

private:
    QSerialPortInfo* portInfo;
    uint8_t MEMS_state;// выбранные источники сигнала
    Ui::MainWindow *ui;
    QLineSeries *encoderPosPointsArr;
    QChart *encoderPosChart;
    QChartView *encoderChartView;
    bool plot_enabled = false;              // enable graphics plot
    bool save_to_file_enabled = false;              // enable graphics plot

    QQueue<uint8_t>* serialDataQueue;

    //COM ===
    QSerialPort *port_test;
    QString serial_buffer;
    QByteArray data_buffer; // буфер для приема данных

    //============
    QVector<int16_t> data1_v; // контейнер для первой переменной
    QVector<int16_t> data2_v; // контейнер для второй переменной
    QVector<int16_t> data3_v; // контейнер для третьего параметра
    QVector<int16_t> data4_v; // акселерометр MPU6000
    QVector<int16_t> data5_v; // акселерометр DA2
    QVector<int16_t> data8_v; // угол по гироскопу L2GIS
    QVector<uint16_t> current_v;
    QVector<uint16_t> current_des_v;
    bool oscillogramm_EN;
    QVector<float> series_vec;
};

#endif // MAINWINDOW_H
