#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <QObject>
#include <QTcpSocket>

#include "commandhandler_global.h"

#define SET_LED_STATE   "set-led-state"
#define GET_LED_STATE   "get-led-state"
#define SET_LED_COLOR   "set-led-color"
#define GET_LED_COLOR   "get-led-color"
#define SET_LED_RATE    "set-led-rate"
#define GET_LED_RATE    "get-led-rate"

#define STATE_ON        "on"
#define STATE_OFF       "off"
#define COLOR_RED       "red"
#define COLOR_GREEN     "green"
#define COLOR_BLUE      "blue"
#define RESULT_OK       "OK"
#define RESULT_FAILED   "FAILED"

static const int SIZE_COMMAND = 2;

class COMMANDHANDLERSHARED_EXPORT CommandHandler : public QObject
{
    Q_OBJECT
public:
    explicit CommandHandler(QObject* parent = 0);
    ~CommandHandler();

signals:
    void ok();
    void failed();
    void setLedStateOn();   // включить LED
    void setLedStateOff();   // выключить LED
    void setLedColorRed();   // изменить цвет LED (красный)
    void setLedColorGreen();   // изменить цвет LED (зеленый)
    void setLedColorBlue();   // изменить цвет LED (синий)
    void setLedRate(int);   // заменить частоту мерцания

    void getLedState();   // получить состояние
    void getLedColor();   // получить цвет
    void getLedRate();   // получитьчастоту мерцания

    void message(QString);

public slots:
    void messageResultOk();   // "OK\n"
    void messageResultFailed();   // "FAILED\n"

    void messageResultStateOn();   // "OK on\n"
    void messageResultStateOff();   // "OK off\n"
    void messageResultColorRed();   // "OK red\n"
    void messageResultColorGreen();   // "OK green\n"
    void messageResultColorBlue();   // "Ok blue\n"
    void messageResultRate(int);   // "Ok <rate>\n"

    void messageSetStateOn();   // "set-led-state on\n"
    void messageSetStateOff();   // "set-led-state off\n"
    void messageSetColorRed();   // "set-led-color red\n"
    void messageSetColorGreen();   // "set-led-color green\n"
    void messageSetColorBlue();   // "set-led-color blue\n"
    void messageSetRate(int);   // "set-led-rate <rate>\n"

    void messageGetState();   // "get-led-state\n"
    void messageGetColor();   // "get-led-color\n"
    void messageGetRate();   // "get-led-rate\n"

    void handleCommand(QString);   // parse message

private:

};

#endif // COMMANDHANDLER_H
