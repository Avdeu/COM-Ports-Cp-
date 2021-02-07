#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QBuffer>
#include <QDataStream>
#include <QLineEdit>
#include <QDebug>
#include <QtSerialPort/QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial = new QSerialPort(this); //новый экземпляр класса AbstractSerial

    // Заполняем Комбобокс доступными портами
    ui->comboBox->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->comboBox->addItem(info.portName());
    }
    ui->comboBox->setCurrentIndex(-1);

}

MainWindow::~MainWindow()
{
    delete ui;

    //Закрываем соединение при выходе
    serial->close();
    delete serial;
}

void MainWindow::serialRecieve() //Получаем данные
{
    QByteArray ba; //Массив байт
    //ba = serial->readAll(); //Читаем все
    //ui->label->setText(ba.toHex()); //Переводим в HEX
}


void MainWindow::on_pushButton_clicked()
{
    serial->setPortName(ui->comboBox->currentText()); //Указали COM порт и параметры порта (ниже)
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open((QIODevice::ReadWrite)); //Открыли порт
}

void MainWindow::on_pushButton_2_clicked()
{
    serial->close();
}

//void MainWindow::writeToPort(QString str)
//{
//    QByteArray arr;
//    QBuffer buff(&arr);
//    buff.open(QIODevice::ReadWrite);
//    QDataStream stream(&buff);
//    stream.setByteOrder(QDataStream::LittleEndian);
//    stream << str;

//    serial->write(arr);
//    serial->waitForBytesWritten(100);
//}



void MainWindow::on_pushButton_3_clicked()
{
     //writeToPort(ui->textEdit->toPlainText());

    QString text = ui->textEdit->toPlainText();
    QByteArray b;
    const char *c;
    b = text.toUtf8();
    c = b.constData();
    serial->write(c);
}

void MainWindow::on_pushButton_4_clicked()
{
    QString text = serial->readAll();
    //QByteArray b;
    //const char *c;
    //b = text.toUtf8();
    //c = b.constData();
    ui->textEdit_2->setText(text);
}
