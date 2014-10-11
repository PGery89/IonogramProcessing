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
     QGraphicsScene * scene;
     Ionogram ionogram;
     double upperXRangeBound;
     double upperYRangeBound;

     //Plot initial methods
     void InitGraphicsScene();
     void SetOrdinaryDataScatter();
     void SetExtraordinaryDataScatter();
     void SetFilteredOrdinaryDataScatter();
     void SetFilteredExtraordinaryDataScatter();
     void SetPlot();
     void SetDefaultXAxis();
     void SetDefaultYAxis();
     void SetDefaultBackgrounds();
     void SetWhiteThemedXAxis();
     void SetWhiteThemedYAxis();
     void SetWhiteThemedBackgrounds();

private slots:
    void on_actionOpen_Ionogram_triggered();

    void plotRangeChangedX(const QCPRange & newRange);

    void plotRangeChangedY(const QCPRange & newRange);

    void on_pushButton_clicked();

    void on_oxCompRadioButton_toggled(bool checked);

    void on_oCompRadioButton_toggled(bool checked);

    void on_xCompRadioButton_toggled(bool checked);

    void on_oFilterRadioButton_toggled(bool checked);

    void on_xFilterRadioButton_toggled(bool checked);

    void on_actionCCL_filtering_triggered();

    void on_radioButton_blackTheme_toggled(bool checked);

    void on_radioButton_whiteTheme_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    labeling_dialog *cclLabelingUi;
};

#endif // MAINWINDOW_H
