#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QRadioButton>
#include <QGroupBox>
#include <QPushButton>
#include <QSpinBox>
#include <QAction>
#include <QMenuBar>
#include <QThread>

#include "connectionthread.h"
#include "led.h"
#include "netsettingsdlg.h"

static const QString LED_ON = "LED On";
static const QString LED_OFF = "LED Off";

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();

signals:
    void connectToHost(QString, quint16);

private slots:
    void slotConnected();
    void buttonState();   // change buton state and send on/off message

    QGroupBox* createColorGroup();   // greate color group
    void createCentralWidget();   // create central widget
    void createActions();
    void createMenu();

    void quit();
    void showConnectDlg();
    void handleError(QString);
    void handleSuccess();

private:
    ConnectionThread* _connectionThread;
    QThread* _thread;

    Led* _led;   // led idicator

    QRadioButton* _rbColorRed;   // color red
    QRadioButton* _rbColorGreen;   // color green
    QRadioButton* _rbColorBlue;   // color blue
    QGroupBox* _group;   // group of radiobuttons

    QPushButton* _pbState;   // push button led on/off
    QSpinBox* _sbRate;   // led rate
    QLabel* _labelRate;   // label "Rate"

    QAction* _quitAct;   // quit action
    QAction* _connectionAct;   // connection action

    QMenu* _fileMenu;
    QMenu* _connectionMenu;

    NetSettingsDlg* _dialog;

    bool _state;   // state of button (on/off)

    QString _address;
    quint16 _port;

};

#endif // CLIENT_H
