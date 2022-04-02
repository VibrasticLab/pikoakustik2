#include "audiogram.h"

#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  audiogram w;
  w.show();
  return a.exec();
}
