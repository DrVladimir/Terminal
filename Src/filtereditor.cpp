#include "filtereditor.h"
#include "ui_filtereditor.h"

#include <QCheckBox>
#include <QDebug>


FilterEditor::FilterEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterEditor)
{
    ui->setupUi(this);
    this->setModal(true);
    this->setWindowTitle(tr("List of filters"));
    filterCreator = new FilterCreator;

    ui->filterTable->setColumnCount(3);
    ui->filterTable->setShowGrid(true);
    ui->filterTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->filterTable->setHorizontalHeaderLabels(QStringList() << trUtf8("On/Off")
                                                             << trUtf8("Reg. Exp.")
                                                             << trUtf8("Filter"));
    ui->filterTable->horizontalHeader()->setStretchLastSection(true);

    initConnections();


}

void FilterEditor::initConnections()
{
    connect(ui->okButton,SIGNAL(clicked(bool)),this, SLOT(okSlot()));
    connect(ui->cancelButton,SIGNAL(clicked(bool)),this, SLOT(cancelSlot()));
    connect(ui->addButton,SIGNAL(clicked(bool)),filterCreator, SLOT(show()));
    connect(filterCreator, SIGNAL(createFilterSignal(bool,bool,QString)), this, SLOT(addSlot(bool,bool,QString)));
    connect(ui->deleteButton,SIGNAL(clicked(bool)),this, SLOT(deleteSlot()));


}
FilterEditor::~FilterEditor()
{
    delete filterCreator;
    delete ui;
}
void FilterEditor::updateFiltersSlot(QList<FilterInfo> newFiltersList)
{

   for(int filterNumber = 0; filterNumber < newFiltersList.size(); filterNumber++)
    {
        ui->filterTable->insertRow(ui->filterTable->rowCount());
        QWidget *checkBoxWidget = new QWidget();
        QCheckBox *checkBox = new QCheckBox();
        QHBoxLayout *layoutCheckBox = new QHBoxLayout(checkBoxWidget);
        layoutCheckBox->addWidget(checkBox);
        layoutCheckBox->setAlignment(Qt::AlignCenter);
        layoutCheckBox->setContentsMargins(0,0,0,0);
        checkBox->setChecked(newFiltersList[filterNumber].getState());
        ui->filterTable->setCellWidget(ui->filterTable->rowCount()-1, 0, checkBoxWidget);

        ui->filterTable->setItem(ui->filterTable->rowCount()-1, 1, new QTableWidgetItem(newFiltersList[filterNumber].getExpresion()));

    }

}

void FilterEditor::okSlot()
{
       QList<FilterInfo> filtersList;

    for (int row = 0; row < ui->filterTable->rowCount(); row++)
    {
        FilterInfo info;

        QWidget *widget =  ui->filterTable->cellWidget(row,0);
        // Забираем виджет из слоя и кастуем его в QCheckBox
        QCheckBox *checkBox = qobject_cast <QCheckBox*> (widget->layout()->itemAt(0)->widget());
        // Проверяем состояние чекбокса
        info.setState(checkBox->isChecked());

        widget =  ui->filterTable->cellWidget(row,1);
        checkBox = qobject_cast <QCheckBox*> (widget->layout()->itemAt(0)->widget());
        info.setType(checkBox->isChecked());




        QTableWidgetItem *item = ui->filterTable->item(row,2);
        info.setExpresion(item->text());
        filtersList.append(info);
    }

    emit updateFiltersSignal(filtersList);
    hide();

}

void FilterEditor::cancelSlot()
{
    hide();
}

void FilterEditor::addSlot(bool newOnOff, bool newType, QString newExpresion)
{
    ui->filterTable->insertRow(ui->filterTable->rowCount());
    QWidget *checkBoxWidget = new QWidget();
    QCheckBox *checkBox = new QCheckBox();
    QHBoxLayout *layoutCheckBox = new QHBoxLayout(checkBoxWidget);
    layoutCheckBox->addWidget(checkBox);
    layoutCheckBox->setAlignment(Qt::AlignCenter);
    layoutCheckBox->setContentsMargins(0,0,0,0);
    checkBox->setChecked(newOnOff);
    ui->filterTable->setCellWidget(ui->filterTable->rowCount()-1, 0, checkBoxWidget);

    checkBoxWidget = new QWidget();
    checkBox = new QCheckBox();
    layoutCheckBox = new QHBoxLayout(checkBoxWidget);
    layoutCheckBox->addWidget(checkBox);
    layoutCheckBox->setAlignment(Qt::AlignCenter);
    layoutCheckBox->setContentsMargins(0,0,0,0);
    checkBox->setChecked(newType);
    ui->filterTable->setCellWidget(ui->filterTable->rowCount()-1, 1, checkBoxWidget);


    ui->filterTable->setItem(ui->filterTable->rowCount()-1, 2, new QTableWidgetItem(newExpresion));


}

void FilterEditor::deleteSlot()
{
    QList<QTableWidgetSelectionRange> rangesList = ui->filterTable->selectedRanges();
    QVector<int> rowIndexes;    // Список строк для удаления

    foreach (QTableWidgetSelectionRange range, rangesList)
    {
       for (int i = range.topRow(); i <= range.bottomRow(); i++)
        {
            // Заполняем список
            rowIndexes.append(i);
        }
    }

    // Сортируем номера строк по возрастанию
    std::sort(rowIndexes.begin(), rowIndexes.end());

    // Используя обратный итератор удаляем все строки
    // Удалять нужно обязательно с последней строки
    for (auto it = rowIndexes.rbegin(); it != rowIndexes.rend(); it++)
    {
        ui->filterTable->removeRow(*it);
    }

}













