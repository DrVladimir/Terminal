#ifndef FILTER_H
#define FILTER_H

#include <QLabel>



class Filter: public QLabel
{
    Q_OBJECT
public:
    explicit Filter(bool initType = false, QString initExpresion = "", QWidget *parent = 0);
    ~Filter();

private slots:
    void getDataSlot(QString data);

private:
    bool type;
    QString expresion;


};

#endif // FILTER_H
