#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <stdint.h>
#include <stddef.h>
#include <math.h>
#include <QFile>

#define StartBlock()	(code_ptr = dst++, code = 1)
#define FinishBlock()	(*code_ptr = code)

int last_position = 0;
int last_speed = 0;
int flag_show_plot = 1;

enum State {disabled, position_control, speed_control, sinus};
State state = disabled;

int max_speed = 10; // Гц
int max_position = 360; // Градусов

size_t cobs_decode(const uint8_t * input, size_t length, uint8_t * output);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    portInfo(new QSerialPortInfo),
    ui(new Ui::MainWindow),
    port_test(new QSerialPort)
{
    ui->setupUi(this);
    connect(ui->ConnectBtn, SIGNAL(clicked()), this, SLOT(openConnection()));
    encoderPosPointsArr = new QLineSeries();
//    encoderPosPointsArr->append(0, 255);
//    encoderPosPointsArr->append(2, 4);
//    encoderPosPointsArr->append(3, 8);
//    encoderPosPointsArr->append(7, 4);
//    encoderPosPointsArr->append(255, 5);

    encoderPosChart = new QChart();
    encoderPosChart->legend()->hide();
    encoderPosChart->addSeries(encoderPosPointsArr);
    encoderPosChart->createDefaultAxes();
    encoderPosChart->setTitle("Simple line chart example");
    //encoderPosChart->axisY()->setRange(-185, 185); //need
        encoderPosChart->axisY()->setRange(0, 10000);
    encoderPosChart->axisX()->setRange(0, 10000);

    ui->graphicsView->setChart(encoderPosChart);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    QList<QSerialPortInfo>listOfPorts = portInfo->availablePorts();

    for (const QSerialPortInfo &info : listOfPorts)
    {
        QStringList list;
        list << info.portName();
        ui->ListInfoPortsBox->addItem(list.first(), list);
    }

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    connect(port_test, SIGNAL(readyRead()), this, SLOT(serialDataReceived()));
    set_default_values();
}

void MainWindow::update_speed_pos_visualisation(double pos)
{
    double delta = 0;
    current_pos = pos;
    if (current_pos < 0 && prev_pos > 0)
        delta = current_pos + 360 - prev_pos;
    else
        delta = current_pos - prev_pos;
    acc -= acc / acc_size;
    acc += delta;
    if (iteration_num < acc_size)
    {
        speed = (delta)*(4/6.28);         // дельта угол * (1/6.28)радианы * 200 (частота обновления 200 Герц)
        iteration_num++;
    }
    else
    {
        speed = (acc / acc_size) * (4/6.28);
    }

    ui->pos_output->display(floor(pos*10)/10);
    ui->speed_output->display(floor(speed*10000)/10000);
    prev_pos = pos;
}

MainWindow::~MainWindow()
{
    delete ui;
    port_test->close();
}

double plot_count;

double d_data_buf, yMin, yMax;
uint8_t angle_to_decode[6];
uint8_t angle_decoded[6];
uint8_t data_size;
uint8_t replace;


QQueue<uint8_t> quekap;
uint8_t kapla[254];
uint8_t kap = 0;
float fbuf;
uint8_t decoded[254];
uint8_t decodedhigh = 0;
uint8_t a, c;

void MainWindow::serialDataReceived()
{
    data_buffer = port_test->readAll();
    data_size = data_buffer.size();
   //  replace = ];
     //qDebug() << data_buffer.size();
     uint8_t tmp_mass[254];
     for (int i = 0; i < data_buffer.size(); i++){
         quekap.enqueue((uint8_t)data_buffer[i]);
         //qDebug() << (uint8_t)data_buffer[i];
         if ((uint8_t)data_buffer[i] == 0){
             kap = 0;
             kapla[kap++] = quekap.dequeue();
             while (kapla[kap-1] != 0){
                  kapla[kap++] = quekap.dequeue();
             }
             kap--;// ноль который был в конце выкинули
         }
     }data_buffer.clear();
  //   qDebug() << "kapla";
  //   qDebug() << kapla[0];
  //   qDebug() << kapla[1];
  //   qDebug() << kapla[2];
  //   qDebug() << kapla[3];
  //   qDebug() << kapla[4];
  //   qDebug() << kapla[5];
  //   qDebug() << " ";
     if (kap != 0){
         a = 1;
         decodedhigh = 0;
         c = kapla[0];
         while (a <= kap) {
             decoded[decodedhigh++]=kapla[a++];
             if (--c == 0){
                 c = decoded[decodedhigh];
                 decoded[decodedhigh] = 0;
             }
         }
         kap = 0;
     }
     decodedhigh--;
  //   qDebug() << "kapla";
  //      qDebug() << decoded[0];
  //      qDebug() << decoded[1];
  //      qDebug() << decoded[2];
  //      qDebug() << decoded[3];
  //      qDebug() << decoded[4];
  //      qDebug() << decoded[5];
  //      qDebug() << " ";
  // теперь любой пакет зашифрованный по тому самому алгоритму расшифрован
   memcpy(&(fbuf), &decoded[0], 4);




   d_data_buf = fbuf;

   //   for (uint8_t i = 1; i < data_size; i++)
//   {
//       if (i == replace) {
//       		if (data_buffer[replace] == 0x00) {
//        		break;
//       		}
//            tmp_mass[i-1] = 0x00;
//            replace = i + receive_buffer[i];
//       } else {
//       		tmp_mass[i-1] = receive_buffer[i];
//       }
//   }
  //  serialDataQueue->enqueue(data_buffer[0]);
  //d_data_buf = double(data_buffer[0]+127);
  //d_data_buf = double(data_buffer[0]);//////////////////////
//  qDebug() << data_buffer;
//  qDebug() << " ";
//  qDebug() << data_buffer[2];
//  qDebug() << data_buffer[3];
//  qDebug() << data_buffer[4];
//  qDebug() << data_buffer[5];
//  qDebug() << data_buffer[6];
 // cobs_decode(angle_to_decode, 5, angle_decoded); //???

  if (plot_enabled){

      encoderPosPointsArr->append(plot_count, d_data_buf); // need

      // encoderPosPointsArr->append(plot_count, plot_count);
      //QLineSeries encoderSubPosPointsArr();
      /*if (plot_count > 1000)
      {
         encoderPosChart->axisX()->setRange(plot_count - 1000, plot_count);
         //encoderPosChart->axisX()->setMin(100);
      }
      else{*/
          encoderPosChart->axisX()->setRange(0, plot_count); //need
      //}

      if(d_data_buf< yMin || d_data_buf > yMax){
          if(d_data_buf < yMin)
              yMin = d_data_buf;
          if(d_data_buf> yMax)
              yMax = d_data_buf;

           encoderPosChart->axisY()->setRange(yMin-1, yMax+1); //need
        }
    //  if (plot_count > 1000)
     //   encoderPosChart->axisX()->setRange(plot_count - 1000, plot_count);
     // else

      encoderPosChart->axisX()->setRange(0, plot_count);  //was

        plot_count++;

        //series_vec.push_back(plot_count); //was
        //series_vec.push_back(d_data_buf);
   }
  else
  {
      plot_count = 0;
      update_speed_pos_visualisation(d_data_buf); // обновление информации на первой вкладке, label Скорость и Положение
  }

  if (save_to_file_enabled)
  {
     series_vec.push_back(d_data_buf);
  }
 // else
  //    series_vec.clear();
}

void MainWindow::openConnection(){

    if(not port_test->isOpen()){
        QMessageBox *warn = new QMessageBox();
        warn->setIcon(QMessageBox::Warning);

        if (ui->ListInfoPortsBox->currentText() != ""){
            port_test->setPortName(ui->ListInfoPortsBox->currentText());
        } else {
            warn->setText("Нет доступных портов");
            warn->show();
        }

        port_test->setBaudRate(QSerialPort::Baud115200);
        port_test->setDataBits(QSerialPort::Data8);
        port_test->setParity(QSerialPort::NoParity);
        port_test->setStopBits(QSerialPort::OneStop);
        port_test->setFlowControl(QSerialPort::NoFlowControl);
        port_test->open(QIODevice::ReadWrite);

        if (port_test->isOpen()){
            ui->ConnectBtn->setText("Connected");
            ui->ConnectBtn->update();
            //warn->setText("Cоединение установлено");
            //warn->show();
        }else {
            warn->setText("Не удалось установить соединение, возможно порт занят другим процессом");
            warn->show();
        }
    }
    else{
        port_test->close();
        qDebug() << port_test->isOpen();
        ui->ConnectBtn->setText("Disconnected");
        ui->ConnectBtn->update();
    }
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
    ui->radioButton_disabled_mode->click();
}

void MainWindow::on_radioButton_disabled_mode_clicked()
{
    state = disabled;
    QByteArray data_to_send;
    data_to_send[0] = 'a';
    data_to_send[1] = 0x00;
    data_to_send[2] = 0x00;
    data_to_send[3] = 0x00;
    data_to_send[4] = 0x00;
    port_test->write(data_to_send);
    ui->horizontalSlider->setDisabled(true);
    ui->spinBox_des_val->setDisabled(true);
    ui->sin_button_widget->setDisabled(true);
}

void MainWindow::on_radioButton_static_mode_clicked()
{
    state = position_control;
    last_speed = ui->horizontalSlider->value();
    // ui->horizontalSlider->setEnabled(true);
    ui->spinBox_des_val->setEnabled(true);
    ui->sin_button_widget->setDisabled(true);
    ui->horizontalSlider->setRange(-max_position*10000,max_position*10000);
    ui->horizontalSlider->setPageStep(ceil(ceil((double)(max_position*10000)/20)));
    ui->horizontalSlider->setValue(last_position);
    ui->horizontalSlider->update();    
    ui->spinBox_des_val->setRange((double)(-max_position),(double)(max_position));
}

void MainWindow::on_radioButton_sine_mode_clicked()
{
    state = sinus;

    ui->horizontalSlider->setDisabled(true);
    ui->spinBox_des_val->setDisabled(true);
    ui->sin_button_widget->setEnabled(true);
}

void MainWindow::on_radioButton_speed_mode_clicked()
{
    state = speed_control;
    last_position = ui->horizontalSlider->value();
    // ui->horizontalSlider->setEnabled(true);
    ui->spinBox_des_val->setEnabled(true);
    ui->sin_button_widget->setDisabled(true);
    ui->horizontalSlider->setRange(-max_speed*10000, max_speed*10000);
    ui->horizontalSlider->setPageStep(ceil(ceil((double)(max_speed*10000)/20)));
    ui->horizontalSlider->setValue(last_speed);
    ui->horizontalSlider->update();
    ui->spinBox_des_val->setRange((double)(-max_speed), (double)(max_speed));
}

void MainWindow::on_pushButton_Set_angle_clicked()
{
    char command_code = 0;
    float data = ui->spinBox_des_val->value();
    ui->horizontalSlider->setValue((int)(data*10000));      //да да, это делается через signal

    switch (state) {
    case position_control:
        command_code = 'p';
        break;
    case speed_control:
        command_code = 'v';
        break;
    default:
        command_code = 'e';
        qDebug() << "error";
        break;
    }
    SendBytesFloat(command_code, data);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
//    char command_code = '\0';
//    float data = (float)(value);
//    ui->spinBox_des_val->setValue(((double)data)/10000);
//    switch (state) {
//    case position_control:
//        command_code = 'p';
//        break;
//    case speed_control:
//        command_code = 'v';
//        break;
//    default:
//        qDebug() << "error";
//        break;
//    }
//    SendBytesFloat(command_code, data/10000);
}

void MainWindow::on_pushButton_2_clicked()
{                                                   // калибровка энкодера
    char command_code = 'b';
    SendByte(command_code);
}

void MainWindow::on_write_Kp_clicked()
{
    QString raw_string_val = ui->Ki_text->toPlainText();
    float data  = raw_string_val.toFloat();
    char command_code = '1';
    SendBytesFloat(command_code, data);
}

void MainWindow::on_write_Ki_clicked()
{
    QString raw_string_val = ui->Ki_text->toPlainText();
    float data  = raw_string_val.toFloat();
    char command_code = '2';
    SendBytesFloat(command_code, data);
}

void MainWindow::on_write_Kd_clicked()
{
    QString raw_string_val = ui->Ki_text->toPlainText();
    float data  = raw_string_val.toFloat();
    char command_code = '3';
    SendBytesFloat(command_code, data);
}

void MainWindow::on_spinBox_des_val_valueChanged(double arg1)
{
    ui->horizontalSlider->setValue((int)(arg1*10000));
}

void MainWindow::on_button_sin_3_clicked()
{
    char command_code = 's';
    float data = 3.0;
    SendBytesFloat(command_code, data);
}

void MainWindow::on_button_sin_2_clicked()
{
    char command_code = 's';
    float data = 2.0;
    SendBytesFloat(command_code, data);
}

void MainWindow::on_button_sin_1_clicked()
{
    char command_code = 's';
    float data = 1.0;
    SendBytesFloat(command_code, data);
}

void MainWindow::on_button_sin_05_clicked()
{
    char command_code = 's';
    float data = 0.5;
    SendBytesFloat(command_code, data);
}

void MainWindow::on_button_sin_025_clicked()
{
    char command_code = 's';
    float data = 0.25;
    SendBytesFloat(command_code, data);
}

void MainWindow::SendBytesFloat(char command_code, float data)
{   // как-то можно было делать функцию с одним названием, но разной реализацией для разных типов
                                                                    //отправка команды "код команды + число"
    qDebug() << state;
    uint8_t data_to_send[5] = {};
    data_to_send[0] = command_code;           // стартовый бит
    memcpy(data_to_send+1, &data, 4);
    qDebug() << "data_to_send: ";
    for(int i =0; i<5; i++)
        qDebug() << i << ":  '" << data_to_send[i] << "'";
    uint8_t data_to_send_encoded[7] = {};
    uint8_t size = encode(data_to_send, 5, data_to_send_encoded);
    qDebug() << "data_to_send_encoded: ";
    for(int i =0; i<7; i++)
        qDebug() << i << ":  '" << data_to_send_encoded[i] << "'";
    qDebug() << "end of data_to_send_encoded";
    qDebug() << "size_encoded: " << size;
    qDebug() << " ";
    char data_to_send_encoded_char[7] = {};
    memcpy(data_to_send_encoded_char, data_to_send_encoded, 7);
    port_test->write(data_to_send_encoded_char, (qint64)size+1);
    if(port_test->waitForBytesWritten(10) == false)
        qDebug() << "error sending";
}

void MainWindow::SendByte(char command_code)
{   // как-то можно было делать функцию с одним названием, но разной реализацией для разных типов
                                                                    //отправка команды "код команды + число"
    char data_to_send[2] = {};
    data_to_send[0] = command_code;
    data_to_send[1] = 0;
    qDebug() << data_to_send;
    port_test->write(data_to_send, 2);
    if(port_test->waitForBytesWritten(10) == false)
        qDebug() << "error sending";
}

size_t encode(const uint8_t *ptr, size_t length, uint8_t *dst)
{    /*
     * StuffData byte stuffs "length" bytes of data
     * at the location pointed to by "ptr", writing
     * the output to the location pointed to by "dst".
     *
     * Returns the length of the encoded data.
     */
    const uint8_t *start = dst, *end = ptr + length;
    uint8_t code = 0, *code_ptr = nullptr; /* Where to insert the leading count */

    StartBlock();
    while (ptr < end)
    {
        if (code != 0xFF)
        {
            uint8_t c = *ptr++;
            if (c != 0)
            {
                *dst++ = c;
                code++;
                continue;
            }
        }
        FinishBlock();
        StartBlock();
    }
    FinishBlock();
    return (size_t)(dst - start);
}

/* Unstuffs "length" bytes of data at the location pointed to by
 * "input", writing the output * to the location pointed to by
 * "output". Returns the number of bytes written to "output" if
 * "input" was successfully unstuffed, and 0 if there was an
 * error unstuffing "input".
 */

size_t cobs_decode(const uint8_t * input, size_t length, uint8_t * output)
{
    size_t read_index = 0;
    size_t write_index = 0;
    uint8_t code;
    uint8_t i;

    while(read_index < length)
    {
        code = input[read_index];

        if(read_index + code > length && code != 1)
        {
            return 0;
        }

        read_index++;

        for(i = 1; i < code; i++)
        {
            output[write_index++] = input[read_index++];
        }
        if(code != 0xFF && read_index != length)
        {
            output[write_index++] = '\0';
        }
    }

    return write_index;
}

void MainWindow::on_pushButtonResetPlot_clicked()
{
    encoderPosPointsArr->clear();
    yMin = yMax = d_data_buf;
    plot_count = 0;
    //encoderPosChart->axisY()->setRange(yMin-1, yMax+1); //need
    //encoderPosChart->axisX()->setRange(0, plot_count);   //need
}

bool UploadToCsv(const QChart * chart,const QString filename);


void MainWindow::on_savePlotToFile_clicked()
{
    plot_enabled = false;
    save_to_file_enabled = false;
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Address Book"), "",
        tr("Address Book (*.csv);;All Files (*)"));

    // comment begin
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly
                  |QIODevice::Truncate
                  |QIODevice::Text))
    {
        // QDataStream out(&file);
        file.write("x;y;\n");
        float curr_pos = 0;
        float prev_pos = 0;
        float speed = 0;
        for(int i=0; i < series_vec.count(); ++i) {
            // out << QString::number( series_vec[i] ).toLocal8Bit() << ";";
            QByteArray ba;
            ba = QString::number( i ).toLatin1();
            ba += ";";
            ba += QString::number( (float)series_vec[i] ).toLatin1();
            ba += ";";
            file.write(ba);
            curr_pos = series_vec[i];
            speed = (curr_pos - prev_pos)*(200/6.28);
            prev_pos = curr_pos;
            ba += QString::number( speed ).toLatin1();
            ba += ";\n";
        }
        // out << series_vec;
        file.close();
    } // comment end

    // UploadToCsv(encoderPosChart,fileName); // need. original
    ui->pushButtonResetPlot->setDisabled(FALSE);
}


bool UploadToCsv(
        const QChart * chart,
        const QString filename)
{
    QFile csvfile(filename);
    if(chart->series().count()==0)
        return false;
    if (!csvfile.open(QIODevice::WriteOnly
                 |QIODevice::Truncate
                 |QIODevice::Text))
        return false;
    for (int i = 0; i < chart->series().count(); ++i)
    {
        QLineSeries * ls;
        ls = static_cast<QLineSeries *>(chart->series().at(i));
        csvfile.write(QByteArray("series")
                      + QString::number(i).toLatin1()
                      + QByteArray("\n"));
        csvfile.write("x;y;\n");
        for (int j=0; j < ls->count();++j)
        {
            QByteArray ba;
            ba = QString::number(ls->at(j).x(),'i',0).toLatin1();
            ba += ";";
            ba += QString::number(ls->at(j).y(),'f',2).toLatin1();
            ba += ";\n";
            csvfile.write(ba);
        }
    }
    csvfile.close();
    qDebug() << "Write successfull";
    return true;
}



void MainWindow::on_pushButtonStartSaveToFile_clicked()
{

    // encoderPosPointsArr->clear();
    //flag_show_plot = 0;
    //yMin = yMax = 0;
    //ui->pushButtonResetPlot->setDisabled(TRUE);
    save_to_file_enabled = true;
    series_vec.clear();
    //plot_enabled = false;
}

void MainWindow::on_plot_graphic_stateChanged(int enabled)
{
    if (enabled == false){
        plot_enabled = false;
        encoderPosPointsArr->clear();
        //ui->pushButtonStartSaveToFile->setDisabled(true);
        ui->pushButtonResetPlot->setDisabled(true);
    }
    else{
        ui->pushButtonStartSaveToFile->setEnabled(true);
        ui->pushButtonResetPlot->setEnabled(true);
        plot_enabled = true;
    }
}
