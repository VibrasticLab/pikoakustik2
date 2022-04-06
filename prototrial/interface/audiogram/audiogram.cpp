#include "audiogram.h"
#include "ui_audiogram.h"

audiogram::audiogram(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::audiogram)
{
  ui->setupUi(this);

#if defined(Q_OS_LINUX)
  ui->btnBrowseFile->setIcon(QIcon(":/icons/folder.svg"));
  ui->btnSerialList->setIcon(QIcon(":/icons/reload.svg"));
  ui->btnSerialFlist->setIcon(QIcon(":/icons/reload.svg"));
#elif defined(Q_OS_WINDOWS)
  ui->btnBrowseFile->setIcon(QIcon(":/icons/folder.ico"));
  ui->btnSerialList->setIcon(QIcon(":/icons/reload.ico"));
  ui->btnSerialFlist->setIcon(QIcon(":/icons/reload.ico"));
#endif

  myPort = new QSerialPort(this);

  addSerialPortChoice();
  plotStart(ui->plotLeft);
  plotStart(ui->plotRight);
}

audiogram::~audiogram()
{
  delete ui;

  if(myPort->isOpen()) myPort->close();
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
        ui->cmbPortList->setEnabled(false);
        ui->btnSerialList->setEnabled(false);
        ui->cmbFlist->setEnabled(true);
        ui->btnSerialFlist->setEnabled(true);
      }
      else{
        QMessageBox::critical(this,"Failed","port failed on "+dev_name);
        ui->btnSerialOpen->setText("Open");
        ui->cmbPortList->setEnabled(true);
        ui->btnSerialList->setEnabled(true);
        ui->cmbFlist->setEnabled(false);
        ui->btnSerialFlist->setEnabled(false);
      }
    }
    else{
      if(myPort->isOpen()) myPort->close();
      ui->btnSerialOpen->setText("Open");
      ui->cmbPortList->setEnabled(true);
      ui->btnSerialList->setEnabled(true);
      ui->cmbFlist->setEnabled(false);
      ui->btnSerialFlist->setEnabled(false);
    }
}

void audiogram::on_btnSerialFlist_clicked()
{
    if(!myPort->isOpen()) return;

    QByteArray dataReq = "mmc lsnum\r\n";

    ui->cmbFlist->clear();

    myPort->write(dataReq);
    myPort->flush();
    myPort->waitForBytesWritten(TIMEOUT_MS);

    myPort->waitForReadyRead(TIMEOUT_MS);
    QByteArray rawData = myPort->readAll();
    while(myPort->waitForReadyRead(TIMEOUT_MS)) rawData.append(myPort->readAll());

    QString strRawData = QString::fromLocal8Bit(rawData);
    qInfo() << strRawData;
    parseFlist(strRawData);

    QMessageBox::information(this, "Updated", "Record List File updated");
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
    if(myPort->isOpen()){
        myPort->close();
        ui->btnSerialOpen->setText("Open");
        ui->cmbPortList->setEnabled(true);
        ui->btnSerialList->setEnabled(true);
    }
    ui->cmbPortList->setEnabled(false);
    ui->btnSerialList->setEnabled(false);
    ui->btnSerialFlist->setEnabled(false);
    ui->btnSerialOpen->setEnabled(false);
    ui->cmbFlist->setEnabled(false);
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

QJsonArray audiogram::parseJsonRecord(QJsonObject audJsonObj, QString strChannel, QString strFreq){
  // ch_x {
  QJsonValue ch = audJsonObj[strChannel];
  QJsonObject ob_ch = ch.toObject();
  //  freq_y {
  QJsonValue freq = ob_ch[strFreq];
  QJsonObject ob_freq = freq.toObject();
  //   ampl,
  //   record [
  QJsonArray rec_f = ob_freq["record"].toArray();
  //   ]
  //  }
  // }

  return rec_f;
}

int audiogram::parseJsonAmpl(QJsonObject audJsonObj, QString strChannel, QString strFreq){
  // ch_x {
  QJsonValue ch = audJsonObj[strChannel];
  QJsonObject ob_ch = ch.toObject();
  //  freq_y {
  QJsonValue freq = ob_ch[strFreq];
  QJsonObject ob_freq = freq.toObject();
  //   ampl,
  QJsonValue ampl_f = ob_freq["ampl"];
  //   record [
  //   ]
  //  }
  // }

  return ampl_f.toDouble();
}

void audiogram::validateLoadJson(QString strJson){
  QString strErrJson;
  QJsonParseError jsonError;

  if(strJson.length()<9) {
      strErrJson = "JSON not fully received";
      strErrJson += "\n";
      strErrJson += "Please Try again";

      QMessageBox::critical(this, "JSON Too Short", strErrJson);

      return;
  }

  QJsonDocument docJson = QJsonDocument::fromJson(strJson.toUtf8(),&jsonError);

  if(docJson.isNull()){
    strErrJson = "JSON Error:";
    strErrJson += jsonError.errorString();
    strErrJson += "\n";
    strErrJson += "Please Try again";

    QMessageBox::critical(this, "JSON Invalid", strErrJson);

    return;
  }
  else{
    QJsonObject obJson = docJson.object();

    /* audiogram */
    QJsonValue datJson = obJson.value(QString("audiogram"));
    inputJsonObj = datJson.toObject();

    QMessageBox::information(this, "JSON OK", "JSON Valid and OK");

    ui->btnDataReset->setEnabled(true);
    ui->btnDataPlot->setEnabled(true);
    ui->btnDataSummary->setEnabled(true);

    dataSummary = buildSummary(inputJsonObj);
  }

  return;
}

int audiogram::fnameToFnum(QString fName){
  if(fName.isNull()) return 0;
  if(fName.isEmpty()) return 0;

  fName.remove("HT_");
  fName.remove(".TXT");

  return fName.toInt();
}

void audiogram::on_btnDataJson_clicked()
{
  QString stringJson;

  if(ui->rbtFile->isChecked()){

     QFile saveFile;

     saveFile.setFileName(ui->editFile->text());
     saveFile.open(QIODevice::ReadOnly | QIODevice::Text);
     stringJson = saveFile.readAll();
     saveFile.close();

     validateLoadJson(stringJson);
  }

  if(ui->rbtSerial->isChecked()){
      int fnum = 0;

      if(!myPort->isOpen())return;

      fnum = fnameToFnum(ui->cmbFlist->currentText());

      if(fnum != 0){
        QByteArray dataReq = "mmc cat " + QByteArray::number(fnum) + "\r\n";
        myPort->write(dataReq);
        myPort->flush();
        myPort->waitForBytesWritten(TIMEOUT_MS);

        myPort->waitForReadyRead(TIMEOUT_MS);
        QByteArray rawData = myPort->readAll();
        while(myPort->waitForReadyRead(TIMEOUT_MS)) rawData.append(myPort->readAll());

        QString strRawData = QString::fromLocal8Bit(rawData);
        qInfo() << strRawData;
        validateLoadJson(strRawData);
      }
  }
}

QString audiogram::indexToFrequency(int idx){
  QString freq;

  switch (idx) {
    case 0: freq = FREQ_250; break;
    case 1: freq = FREQ_500; break;
    case 2: freq = FREQ_1000; break;
    case 3: freq = FREQ_2000; break;
    case 4: freq = FREQ_4000; break;
    case 5: freq = FREQ_8000; break;
  }

  return freq;
}

void audiogram::on_btnDataPlot_clicked()
{
  ui->editAmplL->setText(QString::number(scale2dBstr(parseJsonAmpl(inputJsonObj,CHANNEL_LEFT, indexToFrequency(ui->cmbFreqL->currentIndex())))));
  ui->editAmplR->setText(QString::number(scale2dBstr(parseJsonAmpl(inputJsonObj,CHANNEL_RIGHT, indexToFrequency(ui->cmbFreqR->currentIndex())))));

  plotFromJson(ui->plotLeft,parseJsonRecord(inputJsonObj,CHANNEL_LEFT, indexToFrequency(ui->cmbFreqL->currentIndex())));
  plotFromJson(ui->plotRight,parseJsonRecord(inputJsonObj,CHANNEL_RIGHT, indexToFrequency(ui->cmbFreqR->currentIndex())));
}

void audiogram::on_btnDataReset_clicked()
{
  plotReset(ui->plotLeft);
  plotReset(ui->plotRight);

  ui->btnDataReset->setEnabled(false);
  ui->btnDataPlot->setEnabled(false);
  ui->btnDataSummary->setEnabled(false);
}

void audiogram::plotReset(QwtPlot *plotWidget){
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
    points << QPointF(i, 0.0);
  }

  curve->setSamples(points);
  curve->attach(plotWidget);
  plotWidget->replot();
}


void audiogram::on_rbtFile_clicked()
{
  if(myPort->isOpen()){
      myPort->close();
      ui->btnSerialOpen->setText("Open");
      ui->cmbPortList->setEnabled(true);
      ui->btnSerialList->setEnabled(true);
  }

  ui->cmbPortList->setEnabled(false);
  ui->btnSerialList->setEnabled(false);
  ui->btnSerialFlist->setEnabled(false);
  ui->btnSerialOpen->setEnabled(false);
  ui->cmbFlist->setEnabled(false);
}


void audiogram::on_rbtSerial_clicked()
{
  if(myPort->isOpen()){
      ui->btnSerialOpen->setText("Close");
      ui->cmbPortList->setEnabled(false);
      ui->btnSerialList->setEnabled(false);
      ui->cmbFlist->setEnabled(true);
      ui->btnSerialFlist->setEnabled(true);
  }
  else{
      ui->btnSerialOpen->setText("Open");
      ui->cmbPortList->setEnabled(true);
      ui->btnSerialList->setEnabled(true);
      ui->cmbFlist->setEnabled(false);
      ui->btnSerialFlist->setEnabled(false);
  }

  ui->btnSerialOpen->setEnabled(true);
}

QString audiogram::buildSummary(QJsonObject audJsonObj){
  QString strSummary;

  strSummary = "audiogram table:\n";
  strSummary += "----------------------\n";

  strSummary += "left channel:\n";
  strSummary += "----------------------\n";
  strSummary += "250 Hz: " + QString::number(scale2dBstr(parseJsonAmpl(audJsonObj,CHANNEL_LEFT, FREQ_250))) + " dB SPL\n";
  strSummary += "500 Hz: " + QString::number(scale2dBstr(parseJsonAmpl(audJsonObj,CHANNEL_LEFT, FREQ_500))) + " dB SPL\n";
  strSummary += "1000 Hz: " + QString::number(scale2dBstr(parseJsonAmpl(audJsonObj,CHANNEL_LEFT, FREQ_1000))) + " dB SPL\n";
  strSummary += "2000 Hz: " + QString::number(scale2dBstr(parseJsonAmpl(audJsonObj,CHANNEL_LEFT, FREQ_2000))) + " dB SPL\n";
  strSummary += "4000 Hz: " + QString::number(scale2dBstr(parseJsonAmpl(audJsonObj,CHANNEL_LEFT, FREQ_4000))) + " dB SPL\n";
  strSummary += "8000 Hz: " + QString::number(scale2dBstr(parseJsonAmpl(audJsonObj,CHANNEL_LEFT, FREQ_8000))) + " dB SPL\n";
  strSummary += "----------------------\n";

  strSummary += "right channel:\n";
  strSummary += "----------------------\n";
  strSummary += "250 Hz: " + QString::number(scale2dBstr(parseJsonAmpl(audJsonObj,CHANNEL_RIGHT, FREQ_250))) + " dB SPL\n";
  strSummary += "500 Hz: " + QString::number(scale2dBstr(parseJsonAmpl(audJsonObj,CHANNEL_RIGHT, FREQ_500))) + " dB SPL\n";
  strSummary += "1000 Hz: " + QString::number(scale2dBstr(parseJsonAmpl(audJsonObj,CHANNEL_RIGHT, FREQ_1000))) + " dB SPL\n";
  strSummary += "2000 Hz: " + QString::number(scale2dBstr(parseJsonAmpl(audJsonObj,CHANNEL_RIGHT, FREQ_2000))) + " dB SPL\n";
  strSummary += "4000 Hz: " + QString::number(scale2dBstr(parseJsonAmpl(audJsonObj,CHANNEL_RIGHT, FREQ_4000))) + " dB SPL\n";
  strSummary += "8000 Hz: " + QString::number(scale2dBstr(parseJsonAmpl(audJsonObj,CHANNEL_RIGHT, FREQ_8000))) + " dB SPL\n";
  strSummary += "----------------------\n";

  return strSummary;
}

void audiogram::dialogSaveSummary(){
  saveFnameSummary = QFileDialog::getSaveFileName(this, "Save Data Summary");

  if(saveFnameSummary.isEmpty()) return;
  else{
    QFile saveSummary;

    saveSummary.setFileName(saveFnameSummary);
    if(!saveSummary.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)){
      QMessageBox::critical(this, "Save Invalid", "File save path invalid: " + saveSummary.errorString());
      return;
    }

    QTextStream outSave(&saveSummary);
    outSave << dataSummary;

    saveSummary.flush();
    saveSummary.close();
  }
}

void audiogram::dialogSummary(){
  QDialog *dlgSummary = new QDialog();
  dlgSummary->setFixedSize(400,600);

  QVBoxLayout *vLayout = new QVBoxLayout;
  QHBoxLayout *hLayout = new QHBoxLayout;

  QLabel *label = new QLabel(dataSummary);
  QAbstractButton *bExit = new QPushButton("Close");
  QAbstractButton *bSave = new QPushButton("Save");

  bExit->setToolTip("Close this dialog");
  bSave->setToolTip("Save this summary data");

  QFont summaryFont = label->font();
  summaryFont.setPointSize(18);
  label->setFont(summaryFont);

  vLayout->addWidget(label);
  hLayout->addWidget(bSave);
  hLayout->addWidget(bExit);
  vLayout->addLayout(hLayout);

  dlgSummary->setLayout(vLayout);
  dlgSummary->connect(bExit, SIGNAL(clicked()), dlgSummary, SLOT(close()));
  dlgSummary->connect(bSave, SIGNAL(clicked()), this, SLOT(dialogSaveSummary()));
  dlgSummary->show();
}

void audiogram::on_btnDataSummary_clicked()
{
  dialogSummary();
}

