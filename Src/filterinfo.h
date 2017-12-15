#ifndef FILTERINFO_H
#define FILTERINFO_H

#include <QString>


class FilterInfo
{
public:
    FilterInfo(bool initState = false, bool initType = false, QString initExpresion = "");
    ~FilterInfo();

    bool getState();
    void setState(bool newState);
    bool getType();
    void setType(bool newType);
    QString getExpresion();
    void setExpresion(QString newExpresion);

private:
    bool state;
    bool type;
    QString expresion;

};

#endif // FILTERINFO_H
