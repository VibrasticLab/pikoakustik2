#include "audiogram.h"
#include "ui_audiogram.h"

audiogram::audiogram(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::audiogram)
{
  ui->setupUi(this);

  addSerialPortChoice();
  plotDemo(ui->plotLeft);
  plotDemo(ui->plotRight);
}

audiogram::~audiogram()
{
  delete ui;
}

void audiogram::addSerialPortChoice(){
  auto portInfos = QSerialPortInfo::availablePorts();

  for(QSerialPortInfo &portInfo : portInfos){
#if defined(Q_OS_WIN) || defined(Q_OS_WIN32) || defined(Q_OS_WIN64)
    ui->cmbPortList->addItem(portInfo.portName());
#elif defined(Q_OS_LINUX) || defined(Q_OS_UNIX) || defined(Q_OS_FREEBSD)
    ui->cmbPortList->addItem("/dev/"+ portInfo.portName());
#endif
  }
}

void audiogram::on_btnSerialList_clicked()
{
    addSerialPortChoice();
}

void audiogram::plotDemo(QwtPlot *plotWidget){
  float vpoint;

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

  for(int i=0;i<24;i++){
    if(i<9){vpoint = pointArray[i];}
    else{vpoint = pointArray[8];}

    points << QPointF(i, vpoint);
  }

  curve->setSamples(points);
  curve->attach(plotWidget);
}
