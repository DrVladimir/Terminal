#ifndef FILTERCREATOR_H
#define FILTERCREATOR_H

#include <QDialog>

QT_USE_NAMESPACE

QT_BEGIN_NAMESPACE

namespace Ui {
class FilterCreator;
}

QT_END_NAMESPACE

class FilterCreator : public QDialog
{
    Q_OBJECT

public:
    explicit FilterCreator(QWidget *parent = 0);
    ~FilterCreator();

signals:
    void createFilterSignal(bool newOnOff, bool newType, QString newExpresion);

private slots:
    void okButtonSlot();
    void cancelButtonSlot();

private:
    void initConnections();

    Ui::FilterCreator *ui;
};

#endif // FILTERCREATOR_H
