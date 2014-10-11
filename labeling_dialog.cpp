#include "labeling_dialog.h"
#include "ui_labeling_dialog.h"

labeling_dialog::labeling_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::labeling_dialog)
{
    ui->setupUi(this);
}

labeling_dialog::~labeling_dialog()
{
    delete ui;
}
