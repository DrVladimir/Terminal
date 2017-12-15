#ifndef MAINHANDLER_H
#define MAINHANDLER_H

#include <QObject>


class Connection;

class MainHandler: public QObject
{
    Q_OBJECT

public:
    MainHandler();
    ~MainHandler();

signals:
    void connectSignal(void *settingsOfConnection);
    void disconnectSignal();
    void commandSignal(QString command);
    void dataSignal(QString data);
    void updateAvaliblePortsInfoSignal();
    void sendAvaliblePortsInfoSignal(std::vector<QStringList>*  portsInfo);
    

private slots:
    void connectSlot(void *settingsOfConnection);
    void disconnectSlot();
    void commandSlot(QString command);
    void getDataSlot(QString data);


    
    void getUpdateAvaliblePortsInfoSlot();
    void getAvaliblePortsInfoSlot(std::vector<QStringList>* portsInfo);


private:
    void initConnections();
    
    Connection *newConnection;

};

#endif // MAINHANDLER_H
