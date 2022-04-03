#include "audiogram.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  a.setStyle(QStyleFactory::create("Fusion"));

  audiogram w;
  w.setFixedHeight(500);
  w.setFixedWidth(700);
  w.show();

  return a.exec();
}
