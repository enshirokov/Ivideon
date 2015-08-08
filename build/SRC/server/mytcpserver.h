#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QTcpServer>
#include <QMap>

#include "clientthread.h"
#include "led.h"


class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    MyTcpServer(const Led* pLed, QObject *parent = 0);
    ~MyTcpServer();

protected:
    void incomingConnection(qintptr descriptor);

private slots:
    void removeThread(qintptr);

private:
    QMap<qintptr, ClientThread*> _clients;
    const Led* _pLed;
};

#endif // MYTCPSERVER_H
