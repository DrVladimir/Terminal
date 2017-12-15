#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtSerialPort/QSerialPort>
#include <vector>



class Connection: public QObject
{
    Q_OBJECT

public:
    struct Settings
    {
        QString name;
        qint32 baudRate;
        QString stringBaudRate;
        QSerialPort::DataBits dataBits;
        QString stringDataBits;
        QSerialPort::Parity parity;
        QString stringParity;
        QSerialPort::StopBits stopBits;
        QString stringStopBits;
        QSerialPort::FlowControl flowControl;
        QString stringFlowControl;
        bool localEchoEnabled;
    };
    
    Connection();
    ~Connection();

signals:
    void sendAvaliblePortsInfoSignal(std::vector<QStringList>* portsInfo);
    void dataSignal(QString data);

private slots:
    void connectSlot(void* settingsOfConnection);
    void disconnectSlot();
    void readDataSlot();
    void writeDataSlot(QString data);

    void getUpdateAvaliblePortsInfoSlot();
    
private:
    void checkAvaliblePorts();

    std::vector<QStringList> avaliblePorts;
    QSerialPort *serialPort;
    Settings *settingsOfSerialPort;



};

#endif // CONNECTION_H
