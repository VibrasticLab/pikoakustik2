#ifndef AUDIOGRAM_H
#define AUDIOGRAM_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class audiogram; }
QT_END_NAMESPACE

class audiogram : public QMainWindow
{
  Q_OBJECT

public:
  audiogram(QWidget *parent = nullptr);
  ~audiogram();

private:
  Ui::audiogram *ui;
};
#endif // AUDIOGRAM_H
