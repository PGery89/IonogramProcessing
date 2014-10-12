#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitGraphicsScene();
    SetPlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitGraphicsScene()
{
    scene = new QGraphicsScene(this);
}

void MainWindow::SetOrdinaryDataScatter()
{
    ui->widget->addGraph();
    ui->widget->graph(0)->setPen(QPen(Qt::green));
    ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, QPen(Qt::green), (Qt::green), 1));
    ui->widget->graph(0)->setName("Ordinary");
    ui->widget->graph(0)->setVisible(false);
}

void MainWindow::SetExtraordinaryDataScatter()
{
    ui->widget->addGraph();
    ui->widget->graph(1)->setPen(QPen(Qt::red));
    ui->widget->graph(1)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, QPen(Qt::red), (Qt::red), 1));
    ui->widget->graph(1)->setName("Extraordinary");
    ui->widget->graph(1)->setVisible(false);
}

void MainWindow::SetFilteredOrdinaryDataScatter()
{
    ui->widget->addGraph();
    ui->widget->graph(2)->setPen(QPen(Qt::white));
    ui->widget->graph(2)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, QPen(Qt::white), (Qt::white), 2));
    ui->widget->graph(2)->setName("FilteredOrdinary");
    ui->widget->graph(2)->setVisible(false);
}

void MainWindow::SetFilteredExtraordinaryDataScatter()
{
    ui->widget->addGraph();
    ui->widget->graph(3)->setPen(QPen(Qt::blue));
    ui->widget->graph(3)->setLineStyle(QCPGraph::lsNone);
    ui->widget->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, QPen(Qt::blue), (Qt::blue), 2));
    ui->widget->graph(3)->setName("FilteredExtraordinary");
    ui->widget->graph(3)->setVisible(false);
}

//black themed
void MainWindow::SetDefaultXAxis()
{
    ui->widget->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->widget->xAxis->setTickPen(QPen(Qt::white, 1));
    ui->widget->xAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->widget->xAxis->setTickLabelColor(Qt::white);
    ui->widget->xAxis->setLabelColor(Qt::white);
    ui->widget->xAxis->setLabel("MHz");
    ui->widget->xAxis->setTickLabels(false);

    ui->widget->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->widget->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->widget->xAxis->grid()->setSubGridVisible(false);
}

void MainWindow::SetDefaultYAxis()
{
    ui->widget->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->widget->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->widget->yAxis->setSubTickPen(QPen(Qt::white, 1));
    ui->widget->yAxis->setTickLabelColor(Qt::white);
    ui->widget->yAxis->setLabelColor(Qt::white);
    ui->widget->yAxis->setLabel("Virtual Height");
    ui->widget->yAxis->setTickLabels(false);

    ui->widget->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->widget->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
    ui->widget->yAxis->grid()->setSubGridVisible(false);
}

void MainWindow::SetDefaultBackgrounds()
{
    QLinearGradient plotGradient;
    plotGradient.setStart(0, 0);
    plotGradient.setFinalStop(0, 350);
    plotGradient.setColorAt(0, QColor(50, 50, 50));
    plotGradient.setColorAt(1, QColor(30, 30, 30));
    ui->widget->setBackground(plotGradient);
    QLinearGradient axisRectGradient;
    axisRectGradient.setStart(0, 0);
    axisRectGradient.setFinalStop(0, 350);
    axisRectGradient.setColorAt(0, QColor(50, 50, 50));
    axisRectGradient.setColorAt(1, QColor(20, 20, 20));
    axisRectGradient.setColorAt(2, QColor(10, 10, 10));
    ui->widget->axisRect()->setBackground(axisRectGradient);
}

//white themed
void MainWindow::SetWhiteThemedXAxis()
{
    ui->widget->xAxis->setBasePen(QPen(Qt::black, 1));
    ui->widget->xAxis->setTickPen(QPen(Qt::black, 1));
    ui->widget->xAxis->setSubTickPen(QPen(Qt::black, 1));
    ui->widget->xAxis->setTickLabelColor(Qt::black);
    ui->widget->xAxis->setLabelColor(Qt::black);
}

void MainWindow::SetWhiteThemedYAxis()
{
    ui->widget->yAxis->setBasePen(QPen(Qt::black, 1));
    ui->widget->yAxis->setTickPen(QPen(Qt::black, 1));
    ui->widget->yAxis->setSubTickPen(QPen(Qt::black, 1));
    ui->widget->yAxis->setTickLabelColor(Qt::black);
    ui->widget->yAxis->setLabelColor(Qt::black);
}

void MainWindow::SetWhiteThemedBackgrounds()
{
    ui->widget->setBackground(Qt::white);
    ui->widget->axisRect()->setBackground(Qt::white);
}

void MainWindow::SetPlot()
{
    SetDefaultBackgrounds();
    SetDefaultXAxis();
    SetDefaultYAxis();
    SetOrdinaryDataScatter();
    SetExtraordinaryDataScatter();
    SetFilteredOrdinaryDataScatter();
    SetFilteredExtraordinaryDataScatter();

    //zoom range signal to slot, or MAXVALUE??
    connect(ui->widget->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(plotRangeChangedX(QCPRange)));
    connect(ui->widget->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(plotRangeChangedY(QCPRange)));

    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom );
}

void MainWindow::on_actionOpen_Ionogram_triggered()
{
    //ellenőrizni, hogy van-e visszatérési érték a file-ba...
    //esetleg azt is ellenőrizni hogy ionogrammot nyitottunk-e meg...
    QString file = QFileDialog::getOpenFileName(this, tr("Open file"), "D:\\", "Text File (*.txt)");

    if(ionogram.ionogram.empty())
    {
       ionogram = Ionogram(file.toStdString());
    }
    else
    {
        ionogram.Clear();
        ionogram = Ionogram(file.toStdString());
    }

    upperXRangeBound = ionogram.ionogram.size();
    upperYRangeBound = ionogram.ionogram[0].size();

    QVector<double> x1, y1, x2, y2;
    x1 = ionogram.GetX(1);
    y1 = ionogram.GetY(1);
    x2 = ionogram.GetX(2);
    y2 = ionogram.GetY(2);

    ui->widget->graph(0)->setData(x1, y1);
    ui->widget->graph(0)->rescaleAxes();
    ui->widget->graph(0)->setVisible(true);
    ui->widget->graph(1)->setData(x2, y2);
    ui->widget->graph(1)->rescaleAxes();
    ui->widget->graph(1)->setVisible(true);
    ui->widget->replot();

    ui->groupBox_components->setEnabled(true);
}

void MainWindow::plotRangeChangedX(const QCPRange &newRange)
{
    QCPRange boundedRange = newRange;
    double lowerRangeBound = 0;    
    if (boundedRange.size() > upperXRangeBound-lowerRangeBound)
    {
      boundedRange = QCPRange(lowerRangeBound, upperXRangeBound);
    } else
    {
      double oldSize = boundedRange.size();
      if (boundedRange.lower < lowerRangeBound)
      {
        boundedRange.lower = lowerRangeBound;
        boundedRange.upper = lowerRangeBound+oldSize;
      }
      if (boundedRange.upper > upperXRangeBound)
      {
        boundedRange.lower = upperXRangeBound-oldSize;
        boundedRange.upper = upperXRangeBound;
      }
    }
    ui->widget->xAxis->setRange(boundedRange);
}

void MainWindow::plotRangeChangedY(const QCPRange &newRange)
{
    QCPRange boundedRange = newRange;
    double lowerRangeBound = 0;
    if (boundedRange.size() > upperYRangeBound-lowerRangeBound)
    {
      boundedRange = QCPRange(lowerRangeBound, upperYRangeBound);
    } else
    {
      double oldSize = boundedRange.size();
      if (boundedRange.lower < lowerRangeBound)
      {
        boundedRange.lower = lowerRangeBound;
        boundedRange.upper = lowerRangeBound+oldSize;
      }
      if (boundedRange.upper > upperYRangeBound)
      {
        boundedRange.lower = upperYRangeBound-oldSize;
        boundedRange.upper = upperYRangeBound;
      }
    }
    ui->widget->yAxis->setRange(boundedRange);
}

//Theme radio buttons
void MainWindow::on_radioButton_blackTheme_toggled(bool checked)
{
    SetDefaultXAxis();
    SetDefaultYAxis();
    SetDefaultBackgrounds();
    ui->widget->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, QPen(Qt::white), (Qt::white), 2));
    ui->widget->replot();
}

void MainWindow::on_radioButton_whiteTheme_toggled(bool checked)
{
    SetWhiteThemedBackgrounds();
    SetWhiteThemedXAxis();
    SetWhiteThemedYAxis();
    ui->widget->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssSquare, QPen(Qt::black), (Qt::black), 2));
    ui->widget->replot();
}

//Component radio buttons
void MainWindow::on_oxCompRadioButton_toggled(bool checked)
{
    ui->widget->graph(0)->setVisible(checked);
    ui->widget->graph(1)->setVisible(checked);
    ui->widget->graph(2)->setVisible(!checked);
    ui->widget->graph(3)->setVisible(!checked);
    ui->widget->replot();
}

void MainWindow::on_oCompRadioButton_toggled(bool checked)
{
    ui->widget->graph(0)->setVisible(checked);
    ui->widget->graph(1)->setVisible(!checked);
    ui->widget->graph(2)->setVisible(!checked);
    ui->widget->graph(3)->setVisible(!checked);
    ui->widget->replot();
}

void MainWindow::on_xCompRadioButton_toggled(bool checked)
{
    ui->widget->graph(0)->setVisible(!checked);
    ui->widget->graph(1)->setVisible(checked);
    ui->widget->graph(2)->setVisible(!checked);
    ui->widget->graph(3)->setVisible(!checked);
    ui->widget->replot();
}

//Filtered radio buttons
void MainWindow::on_oFilterRadioButton_toggled(bool checked)
{
    ui->widget->graph(0)->setVisible(checked);
    ui->widget->graph(1)->setVisible(!checked);
    ui->widget->graph(2)->setVisible(checked);
    ui->widget->graph(3)->setVisible(!checked);
    ui->widget->replot();
}

void MainWindow::on_xFilterRadioButton_toggled(bool checked)
{
    ui->widget->graph(0)->setVisible(!checked);
    ui->widget->graph(1)->setVisible(checked);
    ui->widget->graph(2)->setVisible(!checked);
    ui->widget->graph(3)->setVisible(checked);
    ui->widget->replot();
}

//Filter menu, CCL filtering
void MainWindow::on_actionCCL_filtering_triggered()
{
    if(ionogram.ionogram.empty())
    {
        QMessageBox::warning(this, tr("Warning"), "There is no previously imported ionogram!");
    }
    else
    {
        cclLabelingUi = new labeling_dialog(this);
        if (cclLabelingUi->exec() == QDialog::Accepted) {
            ionogram.ComponentLabelingFor(cclLabelingUi->GetComponentIndex());

            //get filtered data
            QVector<double> x, y;
            x = ionogram.GetLabeledX(cclLabelingUi->GetComponentIndex(), cclLabelingUi->GetThreshold());
            y = ionogram.GetLabeledY(cclLabelingUi->GetComponentIndex(), cclLabelingUi->GetThreshold());

            ui->widget->graph(0)->setVisible(false);
            ui->widget->graph(1)->setVisible(false);
            ui->widget->graph(2)->setVisible(false);
            ui->widget->graph(3)->setVisible(false);

            //set filtered data
            ui->widget->graph(cclLabelingUi->GetComponentIndex() + 1)->setData(x, y);
            ui->widget->graph(cclLabelingUi->GetComponentIndex() + 1)->setVisible(true);
            ui->widget->replot();

            ui->groupBox_labeled->setEnabled(true);
        }
    }
}
