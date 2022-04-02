#include "audiogram.h"
#include "ui_audiogram.h"

audiogram::audiogram(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::audiogram)
{
  ui->setupUi(this);

  addSerialPortChoice();
}

audiogram::~audiogram()
{
  delete ui;
}

void audiogram::addSerialPortChoice(){
  auto portInfos = QSerialPortInfo::availablePorts();

  for(QSerialPortInfo &portInfo : portInfos){
    ui->cmbPortList->addItem(portInfo.portName());
  }
}

void audiogram::on_btnSerialList_clicked()
{
    addSerialPortChoice();
}

