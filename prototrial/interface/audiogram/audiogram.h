#ifndef AUDIOGRAM_H
#define AUDIOGRAM_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>

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

  void addSerialPortChoice(void);
};
#endif // AUDIOGRAM_H
