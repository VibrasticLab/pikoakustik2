#ifndef BPFK_H
#define BPFK_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class bpfk; }
QT_END_NAMESPACE

class bpfk : public QMainWindow
{
    Q_OBJECT

public:
    bpfk(QWidget *parent = nullptr);
    ~bpfk();

private slots:
    void on_actionQuit_triggered();
    void on_actionAboutQt_triggered();
    void on_actionAbout_triggered();

    void on_btnPortRefresh_clicked();
    void on_btnSerialOpen_clicked();
    void on_btnReqSend_clicked();

    void serialPortPopulate();
    void serialDataRead();
    void serialDataRequest();
    QString serialStringRequest();

private:
    Ui::bpfk *ui;

    QSerialPort *serPort;
};
#endif // BPFK_H
