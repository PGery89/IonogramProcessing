#include "labeling_dialog.h"
#include "ui_labeling_dialog.h"

labeling_dialog::labeling_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::labeling_dialog)
{
    ui->setupUi(this);
    Init();
}

labeling_dialog::~labeling_dialog()
{
    delete ui;
}

void labeling_dialog::Init()
{
    ui->filteringProgressBar->setValue(50);
    component = ui->comboBox_components->currentIndex();
    threshold = 0;
}

void labeling_dialog::on_comboBox_components_currentIndexChanged(int index)
{
    component = index;
}

void labeling_dialog::on_spinBox_valueChanged(int arg1)
{
    threshold = arg1;
}
