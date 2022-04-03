#ifndef AUDIOGRAM_H
#define AUDIOGRAM_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>

#include <QwtPlot>
#include <QwtSymbol>
#include <QwtLegend>
#include <QwtPlotGrid>
#include <QwtPlotItem>
#include <QwtPlotCurve>

#define REQTYPE_FLIST 0
#define REQTYPE_JSON  1

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
  void on_btnSerialJson_clicked();

  void readData();

private:
  Ui::audiogram *ui;

  QSerialPort *myPort;
  QByteArray rawData;
  QString strRawData;
  uint8_t reqType;

  float pointArray[9] = {72.9, 66.9, 60.8, 54.8, 49.0, 43.5, 39.1, 36.3, 34.9};

  void addSerialPortChoice(void);
  void plotDemo(QwtPlot *plotWidget);
  void parseFlist(QString strInput);
};
#endif // AUDIOGRAM_H
