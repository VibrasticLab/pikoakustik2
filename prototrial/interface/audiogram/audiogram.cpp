#include "audiogram.h"
#include "ui_audiogram.h"

audiogram::audiogram(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::audiogram)
{
  ui->setupUi(this);

#if defined(Q_OS_LINUX)
  ui->btnBrowseFile->setIcon(QIcon::fromTheme("folder"));
  ui->btnSerialList->setIcon(QIcon::fromTheme("reload"));
  ui->btnSerialFlist->setIcon(QIcon::fromTheme("reload"));
#elif defined(Q_OS_WINDOWS)
  ui->btnBrowseFile->setText("D");
  ui->btnSerialList->setText("C");
  ui->btnSerialFlist->setText("C");
#endif

  myPort = new QSerialPort(this);
  QObject::connect(myPort, SIGNAL(readyRead()), SLOT(readData()));

  addSerialPortChoice();
  plotStart(ui->plotLeft);
  plotStart(ui->plotRight);
}

audiogram::~audiogram()
{
  delete ui;
}

void audiogram::readData(){
  rawData = myPort->readLine();
  strRawData = QString::fromLocal8Bit(rawData);

  qInfo() << strRawData;

  if(reqType==REQTYPE_FLIST){
    parseFlist(strRawData);
  }
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

void audiogram::plotStart(QwtPlot *plotWidget){
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

  for(int i=0;i<RECORD_SIZE;i++){
    points << QPointF(i, 0.0);
  }

  curve->setSamples(points);
  curve->attach(plotWidget);
}

void audiogram::on_btnSerialOpen_clicked()
{
    const QString dev_name = ui->cmbPortList->currentText();
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


void audiogram::on_btnSerialFlist_clicked()
{
    if(!myPort->isOpen()) return;

    QByteArray dataReq = "mmc lsnum\r\n";
    reqType = REQTYPE_FLIST;
    ui->cmbFlist->clear();
    myPort->write(dataReq);
}

void audiogram::parseFlist(QString strInput){
  uint16_t fnum;
  QStringList strVal= strInput.split(",");

  for(uint16_t i=0;i<strVal.count();i++){
    fnum = strVal[i].toInt();
    if(fnum!=0){
      ui->cmbFlist->addItem("HT_"+QString::number(fnum)+".TXT");
    }
  }
}

void audiogram::on_btnBrowseFile_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Load ElbiCare Audiometri Save File");

    if(fileName.isEmpty()) return;

    ui->editFile->clear();
    ui->editFile->setText(fileName);

    ui->rbtFile->setChecked(true);
}

float audiogram::scale2dBstr(int scale){
  float dB;

  switch (scale) {
    case 9: dB = 72.9; break;
    case 8: dB = 66.9; break;
    case 7: dB = 60.8; break;
    case 6: dB = 54.8; break;
    case 5: dB = 49.0; break;
    case 4: dB = 43.5; break;
    case 3: dB = 39.1; break;
    case 2: dB = 36.3; break;
    case 1: dB = 34.9; break;
    default: dB = 0;break;
  }

  return dB;
}

void audiogram::plotFromJson(QwtPlot *plotWidget, QJsonArray scaleInput){
  plotWidget->detachItems();

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
    points << QPointF(i, scale2dBstr(scaleInput[i].toInt()));
  }

  curve->setSamples(points);
  curve->attach(plotWidget);
  plotWidget->replot();
}

void audiogram::parseJson(QJsonObject audJsonObj, QString freqLeft, QString freqRight){
  //  ch_0: {
  QJsonValue ch_0 = audJsonObj["ch_0"];
  QJsonObject ob_ch_0 = ch_0.toObject();
  //    freq_L {
  QJsonValue freq_L = ob_ch_0[freqLeft];
  QJsonObject ob_freq_L = freq_L.toObject();
  //      ampl
  QJsonValue ampl_fL = ob_freq_L["ampl"];
  //      record [
  QJsonArray rec_fL = ob_freq_L["record"].toArray();
  //      ]
  //    }
  //  }

  ui->editAmplL->setText(QString::number(scale2dBstr(ampl_fL.toInt())));
  plotFromJson(ui->plotLeft,rec_fL);

  //  ch_1: {
  QJsonValue ch_1 = audJsonObj["ch_1"];
  QJsonObject ob_ch_1 = ch_1.toObject();
  //    freq_R {
  QJsonValue freq_R = ob_ch_1[freqRight];
  QJsonObject ob_freq_R = freq_R.toObject();
  //      ampl
  QJsonValue ampl_fR = ob_freq_R["ampl"];
  //      record [
  QJsonArray rec_fR = ob_freq_R["record"].toArray();
  //      ]
  //    }
  //  }

  ui->editAmplR->setText(QString::number(scale2dBstr(ampl_fR.toInt())));
  plotFromJson(ui->plotRight,rec_fR);
}


void audiogram::on_btnDataJson_clicked()
{
  if(ui->rbtFile->isChecked()){
     QString stringJson;
     QFile saveFile;

     saveFile.setFileName(ui->editFile->text());
     saveFile.open(QIODevice::ReadOnly | QIODevice::Text);
     stringJson = saveFile.readAll();
     saveFile.close();

     QJsonDocument docJson = QJsonDocument::fromJson(stringJson.toUtf8());
     QJsonObject obJson = docJson.object();

     /* audiogram */
     QJsonValue datJson = obJson.value(QString("audiogram"));
     QJsonObject obDatJson = datJson.toObject();

     parseJson(obDatJson, "freq_0", "freq_0");
  }
}

