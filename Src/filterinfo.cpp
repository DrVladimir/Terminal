#include "filterinfo.h"


FilterInfo::FilterInfo(bool initState, bool initType, QString initExpresion):
    state(initState),
    type(initType),
    expresion(initExpresion)
{

}

FilterInfo::~FilterInfo()
{

}

bool FilterInfo::getState()
{
    return state;
}

void FilterInfo::setState(bool newState)
{
    state = newState;
}

bool FilterInfo::getType()
{
    return type;
}

void FilterInfo::setType(bool newType)
{
    type = newType;
}

QString FilterInfo::getExpresion()
{
    return expresion;
}

void FilterInfo::setExpresion(QString newExpresion)
{
    expresion = newExpresion;
}



