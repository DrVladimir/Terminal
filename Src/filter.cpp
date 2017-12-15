#include "filter.h"
#include <QDebug>

Filter::Filter(bool initType, QString initExpresion, QWidget *parent):
    QLabel(parent)
{
    type = initType;
    expresion = initExpresion;
    this->setStyleSheet("QLabel {background-color : white}");
    this->setFrameShape(QFrame::Box);
    this->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Fixed);
    this->setMinimumHeight(23);
    this->setMaximumHeight(23);

}

Filter::~Filter()
{

}


void Filter::getDataSlot(QString data)
{
    if (type)
    {
        QRegExp regExpresion;
        regExpresion.setPattern(expresion);
        if(regExpresion.indexIn(data) > -1)
        {
          this->setText(regExpresion.cap());
        }
    }
    else
    {
        if(data.contains(expresion))
        {
            QString a;
            QStringList list = data.split('\n', QString::SkipEmptyParts);
            QStringList result = list.filter(expresion);
            this->setText(result.first()/*.replace(QRegExp("\\$")," ")*/);
        }

    }
}
