#include "audiogram.h"
#include "ui_audiogram.h"

audiogram::audiogram(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::audiogram)
{
  ui->setupUi(this);

  myPort = new QSerialPort(this);
  QObject::connect(myPort, SIGNAL(readyRead()), SLOT(readData()));

  addSerialPortChoice();
  plotDemo(ui->plotLeft);
  plotDemo(ui->plotRight);
}

audiogram::~audiogram()
{
  delete ui;
}

void audiogram::readData(){
  rawData = myPort->readLine();
  strRawData = QString::fromLocal8Bit(rawData);

  qInfo() << strRawData;
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

void audiogram::plotDemo(QwtPlot *plotWidget){
  float vpoint;

  plotWidget->setCanvasBackground(Qt::gray);
  plotWidget->setAxisScale(QwtPlot::yLeft, 0, 110, 10);
  plotWidget->setAxisScale(QwtPlot::xBottom, 1, 24, 1);
  plotWidget->enableAxis(QwtPlot::xBottom, false);

  QwtPlotGrid *grid = new QwtPlotGrid();
  grid->attach(plotWidget);

  QwtPlotCurve *curve = new QwtPlotCurve();
  curve->setPen(Qt::blue,4);
  curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);

  QwtSymbol *symbol = new QwtSymbol(
        QwtSymbol::Ellipse,
        QBrush(Qt::yellow),
        QPen(Qt::red,2),
        QSize(8,8));
  curve->setSymbol(symbol);

  QPolygonF points;

  for(int i=0;i<24;i++){
    if(i<9){vpoint = pointArray[i];}
    else{vpoint = pointArray[8];}

    points << QPointF(i, vpoint);
  }

  curve->setSamples(points);
  curve->attach(plotWidget);
}

void audiogram::on_btnSerialOpen_clicked()
{
    const QString dev_name = "ttyACM0";
    QSerialPort::BaudRate dev_baud=QSerialPort::Baud9600;

    if(ui->btnSerialOpen->text()== "Open"){
      myPort->setPortName(dev_name);
      myPort->setBaudRate(dev_baud, QSerialPort::AllDirections);
      myPort->setDataBits(QSerialPort::Data8);
      myPort->setStopBits(QSerialPort::OneStop);
      myPort->setFlowControl(QSerialPort::NoFlowControl);
      myPort->setParity(QSerialPort::NoParity);

      if(myPort->open(QIODevice::ReadWrite)){
        QMessageBox::information(this,"success","port success on "+dev_name );
        ui->btnSerialOpen->setText("Close");
      }
      else{
        QMessageBox::critical(this,"Failed","port failed on "+dev_name);
        ui->btnSerialOpen->setText("Open");
      }
    }
    else{
      if(myPort->isOpen()) myPort->close();
      ui->btnSerialOpen->setText("Open");
    }
}

