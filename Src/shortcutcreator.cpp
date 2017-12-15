#include "shortcutcreator.h"
#include "ui_shortcutcreator.h"

ShortcutCreator::ShortcutCreator(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShortcutCreator)
{
    ui->setupUi(this);

    connect(ui->cancelButton,SIGNAL(clicked(bool)),this,SLOT(cancelButtonSlot()));
    connect(ui->okButton,SIGNAL(clicked(bool)),this,SLOT(okButtonSlot()));
    connect(ui->deleteButton,SIGNAL(clicked(bool)),this,SLOT(deleteButtonSlot()));

}

ShortcutCreator::~ShortcutCreator()
{
    delete ui;
}

void ShortcutCreator::deleteButtonSlot()
{
    emit deleteShortcutSignal(currentShortcut);
    hide();
}

void ShortcutCreator::okButtonSlot()
{
    emit updateShortcutSignal(currentShortcut,ui->titleEdit->text(),ui->commandEdit->text());
    hide();
}

void ShortcutCreator::cancelButtonSlot()
{
 hide();
}

void ShortcutCreator::updateShortcutSlot(int shortcutID, QString newTitleShortcut, QString newCommandShortcut)
{
    show();
    currentShortcut = shortcutID;
    ui->titleEdit->setText(newTitleShortcut);
    ui->commandEdit->setText(newCommandShortcut);

}




