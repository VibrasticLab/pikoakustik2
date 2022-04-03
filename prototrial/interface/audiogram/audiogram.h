#ifndef AUDIOGRAM_H
#define AUDIOGRAM_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QStyleFactory>
#include <QFileDialog>
#include <QDebug>

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
  void readData();

  void on_btnSerialList_clicked();
  void on_btnSerialOpen_clicked();
  void on_btnSerialFlist_clicked();
  void on_btnSerialJson_clicked();
  void on_btnBrowseFile_clicked();

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
