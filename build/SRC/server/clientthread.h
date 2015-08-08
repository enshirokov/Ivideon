#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H

#include <QObject>
#include <QTcpSocket>

#include "led.h"
#include "commandhandler.h"

class ClientThread : public QObject
{
    Q_OBJECT
public:
    explicit ClientThread(const Led* pLed, qintptr socketDescriptor, QObject *parent = 0);
    ~ClientThread();

signals:
    void command(QString);
    void disconnect(qintptr);

public slots:
    void run();

private slots:
    void readMessage();
    void writeMessage(QString);
    void disconnected();

private:
    QTcpSocket* _socket;
    qintptr _socketDescriptor;

    const Led* _pLed;
    CommandHandler* _handler;

};

#endif // CLIENTSOCKET_H
