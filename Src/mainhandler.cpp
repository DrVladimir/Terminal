#include "mainhandler.h"
#include "connection.h"

MainHandler::MainHandler()
{
   newConnection = new Connection;
   initConnections();

}

MainHandler::~MainHandler()
{

}

void MainHandler::initConnections()
{
    connect(this,SIGNAL(connectSignal(void*)),newConnection,SLOT(connectSlot(void*)));
    connect(this,SIGNAL(disconnectSignal()),newConnection,SLOT(disconnectSlot()));
    connect(this,SIGNAL(commandSignal(QString)),newConnection,SLOT(writeDataSlot(QString)));
    connect(newConnection,SIGNAL(dataSignal(QString)),this, SLOT(getDataSlot(QString)));
    connect(this,SIGNAL(updateAvaliblePortsInfoSignal()),newConnection,SLOT(getUpdateAvaliblePortsInfoSlot()));
    connect(newConnection,SIGNAL(sendAvaliblePortsInfoSignal(std::vector<QStringList>* )),this, SLOT(getAvaliblePortsInfoSlot(std::vector<QStringList>*)));

}

void MainHandler::connectSlot(void *settingsOfConnection)
{
    emit connectSignal(settingsOfConnection);

}

void MainHandler::disconnectSlot()
{
    emit disconnectSignal();

}

void MainHandler::commandSlot(QString command)
{
    emit commandSignal(command);

}

/*void MainHandler::addExpresionSlot(QString newExpresion)
{
    if (!expresionlist.contains(newExpresion))
    {
        expresionlist.append(newExpresion);
        emit dataSignal(expresionlist.last());
        emit dataSignal(" add new expresion");
    }
}

void MainHandler::deleteExpresionSlot(QString newExpresion)
{
    if (expresionlist.contains(newExpresion))
    {
        expresionlist.removeAll(newExpresion);
        emit dataSignal( " delete new expresion");
    }
}
*/
void MainHandler::getDataSlot(QString data)
{
   /*if(!(expresionlist.isEmpty()))
    {

        foreach (const QString &expresion, expresionlist )
        {
            if(data.contains(expresion))
            {
                 emit dataSignal(data);
            }

        }

    }
    else
    {*/
        emit dataSignal(data);

   //}
}


void MainHandler::getUpdateAvaliblePortsInfoSlot()
{
    emit updateAvaliblePortsInfoSignal();

}

void MainHandler::getAvaliblePortsInfoSlot(std::vector<QStringList>* portsInfo)
{
    emit sendAvaliblePortsInfoSignal(portsInfo);

}

