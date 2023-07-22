#include "bpfk.h"
#include "ui_bpfk.h"

bpfk::bpfk(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::bpfk)
{
    ui->setupUi(this);

    ui->rbtOut_50->setEnabled(false);
    ui->rbtOut_90->setEnabled(false);
    ui->rbtOut_100->setEnabled(false);

    serPort = new QSerialPort(this);
    serPort->setBaudRate(QSerialPort::Baud38400);
    serPort->setDataBits(QSerialPort::Data8);
    serPort->setStopBits(QSerialPort::OneStop);
    serPort->setFlowControl(QSerialPort::NoFlowControl);
    serPort->setParity(QSerialPort::NoParity);

    serialPortPopulate();

    ui->btnReqSend->setEnabled(false);

    connect(serPort,SIGNAL(readyRead()),this,SLOT(serialDataRead()));
}

bpfk::~bpfk()
{
    delete ui;
}


void bpfk::on_actionQuit_triggered()
{
    QApplication::quit();
}


void bpfk::on_actionAboutQt_triggered()
{
    QApplication::aboutQt();
}


void bpfk::on_actionAbout_triggered()
{
    QMessageBox msgAbout;

    msgAbout.setText("Elbicare Audiometri Interface by Achmadi ST MT");
    msgAbout.setWindowTitle("ECU Interface");
    msgAbout.setIcon(QMessageBox::Information);
    msgAbout.exec();
}

void bpfk::serialPortPopulate(){
    ui->cmbPortList->clear();

    foreach (QSerialPortInfo portInfo,QSerialPortInfo::availablePorts()){
        ui->cmbPortList->addItem(portInfo.portName());
    }
}

void bpfk::on_btnPortRefresh_clicked()
{
    serialPortPopulate();
}


void bpfk::on_btnSerialOpen_clicked()
{
    QString strBtnName = ui->btnSerialOpen->text();
    serPort->setPortName(ui->cmbPortList->currentText());

    if(strBtnName=="Open"){
        if(serPort->open(QIODevice::ReadWrite)){
            ui->statusbar->showMessage("Serial Opened");
            ui->btnSerialOpen->setText("Close");
            ui->cmbPortList->setEnabled(false);
            ui->btnPortRefresh->setEnabled(false);
            ui->btnReqSend->setEnabled(true);
        }
        else{
            ui->statusbar->showMessage("Serial Opening Failed");
        }
    }
    else if(strBtnName=="Close"){
        if(serPort->isOpen()) serPort->close();
        ui->btnSerialOpen->setText("Open");
        ui->statusbar->showMessage("Serial Closed");
        ui->cmbPortList->setEnabled(true);
        ui->btnPortRefresh->setEnabled(true);
        ui->btnReqSend->setEnabled(false);
    }
}

void bpfk::serialDataRead(){
    QByteArray rawData = serPort->readAll();
    ui->txtSerialConsole->insertPlainText(rawData);
}

void bpfk::serialDataRequest(){
    ui->txtSerialConsole->clear();
    QByteArray dataReq = "info\r";
    serPort->write(dataReq);
}

void bpfk::on_btnReqSend_clicked()
{
    serialDataRequest();
}

