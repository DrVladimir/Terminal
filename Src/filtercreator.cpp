#include "filtercreator.h"
#include "ui_filtercreator.h"

FilterCreator::FilterCreator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterCreator)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("New filter"));
    this->setModal(true);

    ui->expresionEdit->clear();
    ui->onOffCheckBox->setChecked(true);
    ui->typeCheckBox->setChecked(false);

    initConnections();
}

void FilterCreator::initConnections()
{
    connect(ui->cancelButton,SIGNAL(clicked(bool)),this,SLOT(cancelButtonSlot()));
    connect(ui->okButton,SIGNAL(clicked(bool)),this,SLOT(okButtonSlot()));
}

FilterCreator::~FilterCreator()
{
    delete ui;
}



void FilterCreator::okButtonSlot()
{
    if (ui->expresionEdit->text().isEmpty())
    {
         hide();
    }
    else
    {
        emit createFilterSignal(ui->onOffCheckBox->isChecked(), ui->typeCheckBox->isChecked(),ui->expresionEdit->text());
        ui->expresionEdit->clear();
        ui->onOffCheckBox->setChecked(true);
        ui->typeCheckBox->setChecked(false);
        hide();
    }

}

void FilterCreator::cancelButtonSlot()
{
    ui->expresionEdit->clear();
    ui->onOffCheckBox->setChecked(true);
    ui->typeCheckBox->setChecked(false);
    hide();
}


