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

private:
    Ui::labeling_dialog *ui;
};

#endif // LABELING_DIALOG_H
