#include "qfilterstring.h"

QFilterString::QFilterString()
{

}

QFilterString::~QFilterString()
{

}

bool QFilterString::getState()
{
    return state;
}

void QFilterString::setState(bool newState)
{
    state = newState;
}
