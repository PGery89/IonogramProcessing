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

    QCPScatterStyle ordinaryDataScatter;
    ordinaryDataScatter.setShape(QCPScatterStyle::ssSquare);
    ordinaryDataScatter.setPen(QPen(Qt::green));
    ordinaryDataScatter.setBrush(Qt::green);
    ordinaryDataScatter.setSize(1);

    ui->widget->graph(0)->setScatterStyle(ordinaryDataScatter);
    ui->widget->graph(0)->setName("Ordinary");
}

void MainWindow::SetExtraordinaryDataScatter()
{
    ui->widget->addGraph();
    ui->widget->graph(1)->setPen(QPen(Qt::red));
    ui->widget->graph(1)->setLineStyle(QCPGraph::lsNone);

    QCPScatterStyle extraordinaryDataScatter;
    extraordinaryDataScatter.setShape(QCPScatterStyle::ssSquare);
    extraordinaryDataScatter.setPen(QPen(Qt::red));
    extraordinaryDataScatter.setBrush(Qt::red);
    extraordinaryDataScatter.setSize(1);

    ui->widget->graph(1)->setScatterStyle(extraordinaryDataScatter);
    ui->widget->graph(1)->setName("Extraordinary");
}

void MainWindow::SetFilteredOrdinaryDataScatter()
{
    ui->widget->addGraph();
    ui->widget->graph(2)->setPen(QPen(Qt::white));
    ui->widget->graph(2)->setLineStyle(QCPGraph::lsNone);

    QCPScatterStyle filteredOrdScatter;
    filteredOrdScatter.setShape(QCPScatterStyle::ssSquare);
    filteredOrdScatter.setPen(QPen(Qt::white));
    filteredOrdScatter.setBrush(Qt::white);
    filteredOrdScatter.setSize(2);

    ui->widget->graph(2)->setScatterStyle(filteredOrdScatter);
    ui->widget->graph(2)->setName("FilteredOrdinary");
}

void MainWindow::SetFilteredExtraordinaryDataScatter()
{
    ui->widget->addGraph();
    ui->widget->graph(3)->setPen(QPen(Qt::blue));
    ui->widget->graph(3)->setLineStyle(QCPGraph::lsNone);

    QCPScatterStyle filteredXOScatter;
    filteredXOScatter.setShape(QCPScatterStyle::ssSquare);
    filteredXOScatter.setPen(QPen(Qt::blue));
    filteredXOScatter.setBrush(Qt::blue);
    filteredXOScatter.setSize(2);

    ui->widget->graph(3)->setScatterStyle(filteredXOScatter);
    ui->widget->graph(3)->setName("FilteredExtraordinary");
}

void MainWindow::SetXAxis()
{
    //comment
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

void MainWindow::SetYAxis()
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

void MainWindow::SetBackgrounds()
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

void MainWindow::SetPlot()
{
    SetBackgrounds();
    SetXAxis();
    SetYAxis();
    SetOrdinaryDataScatter();
    SetExtraordinaryDataScatter();
    SetFilteredOrdinaryDataScatter();
    SetFilteredExtraordinaryDataScatter();

    //zoom range signal to slot
    connect(ui->widget->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(plotRangeChangedX(QCPRange)));
    connect(ui->widget->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(plotRangeChangedY(QCPRange)));

    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
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
    ui->widget->graph(1)->setData(x2, y2);
    ui->widget->graph(1)->rescaleAxes();
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

void MainWindow::on_pushButton_clicked()
{
    if(ionogram.ionogram.empty())
    {
        QMessageBox::warning(this, tr("Warning"), "There is no previously loaded ionogram!");
    }
    else
    {
        ionogram.ComponentLabelingFor(1);

        QVector<double> x2, y2;
        x2 = ionogram.GetLabeledX(1, 80);
        y2 = ionogram.GetLabeledY(1, 80);

        upperXRangeBound = ionogram.ionogram.size();
        upperYRangeBound = ionogram.ionogram[0].size();

        ui->widget->graph(1)->setVisible(false);

        ui->widget->graph(2)->setData(x2, y2);
        ui->widget->graph(2)->rescaleAxes();
        ui->widget->graph(2)->setVisible(true);
        ui->widget->replot();
    }
}

//Theme radio buttons
void MainWindow::on_radioButton_toggled(bool checked)
{
    //TODO csinálni fehér és fekete initeket vagy paraméterezni az initeket színekkel
}

void MainWindow::on_radioButton_2_toggled(bool checked)
{
    //TODO same.
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
    ui->widget->graph(0)->setVisible(!checked);
    ui->widget->graph(1)->setVisible(checked);
    ui->widget->graph(2)->setVisible(checked);
    ui->widget->graph(3)->setVisible(!checked);
    ui->widget->replot();
}

void MainWindow::on_xFilterRadioButton_toggled(bool checked)
{
    ui->widget->graph(0)->setVisible(checked);
    ui->widget->graph(1)->setVisible(!checked);
    ui->widget->graph(2)->setVisible(!checked);
    ui->widget->graph(3)->setVisible(checked);
    ui->widget->replot();
}

//Filter menu, CCL filtering
void MainWindow::on_actionCCL_filtering_triggered()
{
    cclLabelingUi = new labeling_dialog(this);
    cclLabelingUi->show();
}
