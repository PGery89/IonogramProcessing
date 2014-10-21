#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtWidgets>
#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>

#include "qcustomplot.h"
#include "ionogram.h"
#include "labeling_dialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

     //Plot initial methods
     void InitGraphicsScene();
     void InitSettingsGroupbox();
     void SetOrdinaryDataScatter();
     void SetExtraordinaryDataScatter();
     void SetFilteredOrdinaryDataScatter();
     void SetFilteredExtraordinaryDataScatter();
     void SetAllGraphEnabled(bool enabled);
     void SetPlot();
     void SetDefaultXAxis();
     void SetDefaultYAxis();
     void SetDefaultBackgrounds();
     void SetWhiteThemedXAxis();
     void SetWhiteThemedYAxis();
     void SetWhiteThemedBackgrounds();

     //bool eventFilter(QObject *target, QEvent *event);

private slots:
    void on_actionOpen_Ionogram_triggered();

    void plotRangeChangedX(const QCPRange & newRange);

    void plotRangeChangedY(const QCPRange & newRange);

    void on_actionCCL_filtering_triggered();

    void on_radioButton_blackTheme_toggled(bool checked);

    void on_radioButton_whiteTheme_toggled(bool checked);

    void on_checkBox_ordinary_toggled(bool checked);

    void on_checkBox_extraordinary_toggled(bool checked);

    void on_checkBox_labeledOrdinary_toggled(bool checked);

    void on_checkBox_labeledExtraordinary_toggled(bool checked);

    void on_actionExit_triggered();

    //test
    void onPlotClick(QMouseEvent* mouse);

private:
    Ui::MainWindow *ui;
    labeling_dialog *cclLabelingUi;
    QGraphicsScene * scene;
    Ionogram ionogram;
    double upperXRangeBound;
    double upperYRangeBound;
};

#endif // MAINWINDOW_H
