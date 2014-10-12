#ifndef LABELING_DIALOG_H
#define LABELING_DIALOG_H

#include <QDialog>

namespace Ui {
class labeling_dialog;
}

class labeling_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit labeling_dialog(QWidget *parent = 0);
    ~labeling_dialog();

    int GetComponentIndex() { return component + 1; }
    int GetThreshold() { return threshold; }


private slots:
    void on_comboBox_components_currentIndexChanged(int index);

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::labeling_dialog *ui;
    int component;
    int threshold;

    void Init();
};

#endif // LABELING_DIALOG_H
