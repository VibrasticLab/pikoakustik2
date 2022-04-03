#ifndef AUDIOGRAM_H
#define AUDIOGRAM_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>

#include <QwtPlot>
#include <QwtSymbol>
#include <QwtLegend>
#include <QwtPlotGrid>
#include <QwtPlotItem>
#include <QwtPlotCurve>

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

private:
  Ui::audiogram *ui;
  QSerialPort *myPort;

  float pointArray[9] = {72.9, 66.9, 60.8, 54.8, 49.0, 43.5, 39.1, 36.3, 34.9};

  void addSerialPortChoice(void);
  void plotDemo(QwtPlot *plotWidget);
};
#endif // AUDIOGRAM_H
