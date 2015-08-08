#ifndef CONNECTIONTHREAD_H
#define CONNECTIONTHREAD_H

#include <QObject>
#include <QTcpSocket>

#include "commandhandler.h"
#include "led.h"

class ConnectionThread : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionThread(const Led* pLed, const QString& address, quint16 port, QObject *parent = 0);
    ~ConnectionThread();


    bool isConnected();

signals:
    void command(QString);
    void error(QString);
    void succsess();

public slots:
    void run();
    void connectToHost(const QString&, quint16);

    void sendSetStateOn();
    void sendSetStateOff();
    void sendSetColorRed();
    void sendSetColorGreen();
    void sendSetColorBlue();
    void sendSetRate(int);

    void sendGetState();
    void sendGetColor();
    void sendGetRate();

private slots:
    void readMessage();
    void writeMessage(QString);
    void getAllParams();
    void failConnection(QAbstractSocket::SocketError);
    void successConnection();

private:
    QTcpSocket* _socket;
    QString _address;
    quint16 _port;

    CommandHandler* _handler;
    const Led* _pLed;

    QMutex _mutex;

};

#endif // CONNECTIONTHREAD_H
