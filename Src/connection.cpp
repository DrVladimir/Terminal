#include "connection.h"

#include <QtSerialPort/QSerialPortInfo>


Connection::Connection()
{
   checkAvaliblePorts();
   serialPort =new QSerialPort(this);
   connect(serialPort,SIGNAL(readyRead()),this,SLOT(readDataSlot()));

}

Connection::~Connection()
{

}

void Connection::checkAvaliblePorts()
{
    avaliblePorts.clear();

    const QString blankString = QObject::tr("N/A");

    foreach (const QSerialPortInfo &portInfo, QSerialPortInfo::availablePorts())
    {
        QStringList portInfolist;
        portInfolist << portInfo.portName()
                     << (!portInfo.description().isEmpty() ? portInfo.description() : blankString)
                     << (!portInfo.manufacturer().isEmpty() ? portInfo.manufacturer() : blankString)
                     << (!portInfo.serialNumber().isEmpty() ? portInfo.serialNumber() : blankString)
                     << (!portInfo.systemLocation().isEmpty() ? portInfo.systemLocation() : blankString)
                     << (portInfo.vendorIdentifier() ? QString::number(portInfo.vendorIdentifier(), 16) : blankString)
                     << (portInfo.productIdentifier() ? QString::number( portInfo.productIdentifier(), 16) : blankString);

        avaliblePorts.push_back(portInfolist);



    }

}

void Connection::connectSlot(void *settingsOfConnection)
{
    settingsOfSerialPort = (Settings*)settingsOfConnection;
    serialPort->setPortName(settingsOfSerialPort->name);
    if (serialPort->open(QIODevice::ReadWrite))
    {
        if(serialPort->setBaudRate(settingsOfSerialPort->baudRate) &&
           serialPort->setDataBits(settingsOfSerialPort->dataBits) &&
           serialPort->setParity(settingsOfSerialPort->parity)     &&
           serialPort->setStopBits(settingsOfSerialPort->stopBits) &&
           serialPort->setFlowControl(settingsOfSerialPort->flowControl))
        {


        }
        else
        {
            serialPort->close();

        }

    }
    else
    {


    }
}

void Connection::disconnectSlot()
{
    serialPort->close();
    //emit sendInfoToHandlerSignal(tr("Disconect"));
}

void Connection::readDataSlot()
{
    emit dataSignal(serialPort->readAll());
}

void Connection::writeDataSlot(QString data)
{
    QByteArray dataBA;
    serialPort->write(dataBA.append(data+"\n\r"));
}

void Connection::getUpdateAvaliblePortsInfoSlot()
{
   checkAvaliblePorts();
   emit sendAvaliblePortsInfoSignal(&avaliblePorts);

}

