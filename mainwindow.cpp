#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    InitGraphicsScene();
    InitSettingsGroupbox();
    SetPlot();

    //test
    //ui->lineEdit_fmin->installEventFilter(this);
}

/*bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if (target == ui->lineEdit_fmin) {
            if (event->type() == QEvent::MouseButtonPress) {
                QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
                if (keyEvent->key() == Qt::Key_Space) {
                    focusNextChild();
                    qDebug( ) << "Click on fmin";
                    return true;
                }
                qDebug( ) << "Click on fmin";
                return true;
            }
        }
    return MainWindow::eventFilter(target, event);
}*/

MainWindow::~MainWindow()
{
    delete ui;
}

//init qcustomplot
void MainWindow::InitGraphicsScene()
{
    scene = new QGraphicsScene(this);
}

void MainWindow::InitSettingsGroupbox()
{
    ui->groupBox_layers->setEnabled(false);
}

//set graphs
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

void MainWindow::SetAllGraphEnabled(bool enabled)
{
    ui->checkBox_ordinary->setChecked(enabled);
    ui->checkBox_extraordinary->setChecked(enabled);
    ui->checkBox_labeledOrdinary->setChecked(enabled);
    ui->checkBox_labeledExtraordinary->setChecked(enabled);
}

//black theme
void MainWindow::SetDefaultXAxis()
{
    //axis label
    ui->widget->xAxis->setLabel("MHz");
    ui->widget->xAxis->setLabelColor(Qt::white);
    //automatic tick
    ui->widget->xAxis->setAutoTicks(true);
    ui->widget->xAxis->setAutoSubTicks(true);
    //automatic tick label
    ui->widget->xAxis->setAutoTickLabels(false);
    ui->widget->xAxis->setTickLabels(false);
    //tick label color
    ui->widget->xAxis->setTickLabelColor(Qt::white);

    /*QVector< double > vec;
    for (int i = 0; i < 19; ++i) {
        vec.push_back(i);
    }
    ui->widget->xAxis->setTickVector(vec);
    ui->widget->xAxis->setRange(0, 18);*/

    ui->widget->xAxis->setBasePen(QPen(Qt::white, 1));
    ui->widget->xAxis->setTickPen(QPen(Qt::white, 1));
    ui->widget->xAxis->setSubTickPen(QPen(Qt::white, 1));

    ui->widget->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
    ui->widget->xAxis->grid()->setSubGridVisible(false);
}

void MainWindow::SetDefaultYAxis()
{
    //axis label
    ui->widget->yAxis->setLabel("Virtual Height");
    ui->widget->yAxis->setLabelColor(Qt::white);
    //automatic tick
    ui->widget->yAxis->setAutoTicks(true);
    ui->widget->yAxis->setAutoSubTicks(true);
    //automatic tick label
    ui->widget->yAxis->setAutoTickLabels(false);
    ui->widget->yAxis->setTickLabels(false);
    //tick label color
    ui->widget->yAxis->setTickLabelColor(Qt::white);

   /* QVector< double > vec;
    for (int i = 0; i < 18; ++i) {
        vec.push_back(i * 50);
    }
    ui->widget->yAxis->setTickVector(vec);
    ui->widget->yAxis->setRange(0, 800);*/

    ui->widget->yAxis->setBasePen(QPen(Qt::white, 1));
    ui->widget->yAxis->setTickPen(QPen(Qt::white, 1));
    ui->widget->yAxis->setSubTickPen(QPen(Qt::white, 1));

    ui->widget->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
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
    axisRectGradient.setColorAt(0.5, QColor(20, 20, 20));
    axisRectGradient.setColorAt(1, QColor(10, 10, 10));
    ui->widget->axisRect()->setBackground(axisRectGradient);
}

//white theme
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

//set plot
void MainWindow::SetPlot()
{
    SetDefaultBackgrounds();
    SetDefaultXAxis();
    SetDefaultYAxis();
    SetOrdinaryDataScatter();
    SetExtraordinaryDataScatter();
    SetFilteredOrdinaryDataScatter();
    SetFilteredExtraordinaryDataScatter();

    //lines
    /*QCPItemLine *line = new QCPItemLine(ui->widget);
    line->setPen(QPen(Qt::yellow));
    line->start->setCoords(QCPRange::minRange, 100);
    line->end->setCoords(QCPRange::maxRange, 100);

    QCPItemLine *line2 = new QCPItemLine(ui->widget);
    line2->setPen(QPen(Qt::yellow));
    line2->start->setCoords(100, QCPRange::minRange);
    line2->end->setCoords(100, QCPRange::maxRange);*/

    //zooming slot
    connect(ui->widget->xAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(plotRangeChangedX(QCPRange)));
    connect(ui->widget->yAxis, SIGNAL(rangeChanged(QCPRange)), this, SLOT(plotRangeChangedY(QCPRange)));
    //onclick slot
    connect(ui->widget, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(onPlotClick(QMouseEvent*)));

    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom );
}


//open menu
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

    /*QVector< double > v1, v2;
    v1 = ionogram.GetXTickLabels();
    v2 = ionogram.GetYTickLabels();

    ui->widget->xAxis->setTickVector(v1);
    ui->widget->xAxis->setRange(0, v1[v1.length() - 1]);
    ui->widget->yAxis->setTickVector(v2);
    ui->widget->yAxis->setRange(0, v2[v2.length() - 1]);*/

    ui->widget->graph(0)->setData(ionogram.GetX(1), ionogram.GetY(1));
    ui->widget->graph(0)->rescaleAxes();
    ui->widget->graph(0)->setVisible(true);

    ui->widget->graph(1)->setData(ionogram.GetX(2), ionogram.GetY(2));
    ui->widget->graph(1)->rescaleAxes();
    ui->widget->graph(1)->setVisible(true);
    ui->widget->replot();

    ui->groupBox_layers->setEnabled(true);
    ui->checkBox_ordinary->setChecked(true);
    ui->checkBox_extraordinary->setChecked(true);
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

void MainWindow::onPlotClick(QMouseEvent *mouse)
{
    int x = ui->widget->xAxis->pixelToCoord(mouse->pos().x());
    int y = ui->widget->yAxis->pixelToCoord(mouse->pos().y());
    qDebug( )<< "pixelToCoord:  "<< x << y;
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

//layers checkboxes
void MainWindow::on_checkBox_ordinary_toggled(bool checked)
{
    ui->widget->graph(0)->setVisible(checked);
    ui->widget->replot();
}

void MainWindow::on_checkBox_extraordinary_toggled(bool checked)
{
    ui->widget->graph(1)->setVisible(checked);
    ui->widget->replot();
}

void MainWindow::on_checkBox_labeledOrdinary_toggled(bool checked)
{
    ui->widget->graph(2)->setVisible(checked);
    ui->widget->replot();
}

void MainWindow::on_checkBox_labeledExtraordinary_toggled(bool checked)
{
    ui->widget->graph(3)->setVisible(checked);
    ui->widget->replot();
}

void MainWindow::SetLabeledVisible(int labeled_layer)
{
    if (labeled_layer == 2) {
        ui->checkBox_labeledOrdinary->setChecked(true);
    } else if (labeled_layer == 3) {
        ui->checkBox_labeledExtraordinary->setChecked(true);
    }
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

            QVector<double> x, y;
            x = ionogram.GetLabeledX(cclLabelingUi->GetComponentIndex(), cclLabelingUi->GetThreshold());
            y = ionogram.GetLabeledY(cclLabelingUi->GetComponentIndex(), cclLabelingUi->GetThreshold());

            SetAllGraphEnabled(false);

            ui->widget->graph(cclLabelingUi->GetComponentIndex() + 1)->setData(x, y);
            SetLabeledVisible(cclLabelingUi->GetComponentIndex() + 1);
        }
    }
}


void MainWindow::on_actionExit_triggered()
{
    close();
}
