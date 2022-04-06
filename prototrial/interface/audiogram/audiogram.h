#ifndef AUDIOGRAM_H
#define AUDIOGRAM_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QStyleFactory>
#include <QFileDialog>
#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#if defined(Q_OS_LINUX)
  #include <QwtPlot>
  #include <QwtSymbol>
  #include <QwtPlotGrid>
  #include <QwtPlotItem>
  #include <QwtPlotCurve>
#elif defined (Q_OS_WIN)
  #include "qwt_plot.h"
  #include "qwt_symbol.h"
  #include "qwt_plot_grid.h"
  #include "qwt_plot_item.h"
  #include "qwt_plot_curve.h"
#endif

#define REQTYPE_FLIST 0
#define REQTYPE_JSON  1

#define RECORD_SIZE   24

#define CHANNEL_LEFT  "ch_0"
#define CHANNEL_RIGHT "ch_1"

#define FREQ_250  "freq_0"
#define FREQ_500  "freq_1"
#define FREQ_1000 "freq_2"
#define FREQ_2000 "freq_3"
#define FREQ_4000 "freq_4"
#define FREQ_8000 "freq_5"

#define TIMEOUT_MS  500

QT_BEGIN_NAMESPACE
namespace Ui { class audiogram; }
QT_END_NAMESPACE

class audiogram : public QMainWindow
{
  Q_OBJECT

public:
  audiogram(QWidget *parent = nullptr);
  ~audiogram();

private slots:
  void on_btnSerialList_clicked();
  void on_btnSerialOpen_clicked();
  void on_btnSerialFlist_clicked();
  void on_btnBrowseFile_clicked();
  void on_btnDataJson_clicked();
  void on_btnDataPlot_clicked();
  void on_btnDataReset_clicked();
  void on_rbtFile_clicked();
  void on_rbtSerial_clicked();
  void on_btnDataSummary_clicked();
  void dialogSaveSummary(void);

private:
  Ui::audiogram *ui;

  QSerialPort *myPort;

  QJsonObject inputJsonObj;
  QString dataSummary;
  QString saveFnameSummary;

  float dummyData[24] =  {6,5,4,3,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

  void addSerialPortChoice(void);
  void parseFlist(QString strInput);
  float scale2dBstr(int scale);
  void plotStart(QwtPlot *plotWidget);
  void plotReset(QwtPlot *plotWidget);
  void plotFromJson(QwtPlot *plotWidget, QJsonArray scaleInput);
  void validateLoadJson(QString strJson);
  int fnameToFnum(QString fName);
  QString indexToFrequency(int idx);
  QJsonArray parseJsonRecord(QJsonObject audJsonObj, QString strChannel, QString strFreq);
  int parseJsonAmpl(QJsonObject audJsonObj, QString strChannel, QString strFreq);
  void dialogSummary(void);
  QString buildSummary(QJsonObject audJsonObj);
};
#endif // AUDIOGRAM_H
