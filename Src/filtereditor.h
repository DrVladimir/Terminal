#ifndef FILTEREDITOR_H
#define FILTEREDITOR_H

#include "filterinfo.h"
#include "filtercreator.h"

#include <QDialog>
#include <QList>


namespace Ui {
class FilterEditor;
}


class FilterEditor : public QDialog
{
    Q_OBJECT

public:
    explicit FilterEditor(QWidget *parent = 0);
    ~FilterEditor();
signals:
    void updateFiltersSignal(QList<FilterInfo> filtersList);
private slots:
    void updateFiltersSlot(QList<FilterInfo> newFiltersList);
    void okSlot();
    void cancelSlot();
    void addSlot(bool newOnOff, bool newType, QString newExpresion);
    void deleteSlot();

private:
    void initConnections();


    Ui::FilterEditor *ui;
    FilterCreator *filterCreator;
};

#endif // FILTEREDITOR_H
