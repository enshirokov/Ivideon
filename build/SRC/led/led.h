#ifndef LED_H
#define LED_H

#include "led_global.h"

#include <QWidget>
#include <QMutex>
#include <QMutexLocker>
#include <QPainter>
#include <QTimer>

class LEDSHARED_EXPORT Led : public QWidget
{
    Q_OBJECT
public:
    explicit Led(QWidget *parent = 0);

signals:
    void resultOk();   // результат состояния OK
    void resultFailed();   // результат состояния FAILED

    void resultStateOn();   // результат состояния OK on
    void resultStateOff();   // результат состояния OK off
    void resultColorRed();   // результат цвета OK red
    void resultColorGreen();   // результат цвета OK green
    void resultColorBlue();   // результат цвета OK blue
    void resultRate(int);   // результат частоты мерцания (int)

public slots:

    void update();

    void setLedStateOn();   // включить LED
    void setLedStateOff();   // выключить LED
    void setLedColorRed();   // изменить цвет LED (красный)
    void setLedColorGreen();   // изменить цвет LED (зеленый)
    void setLedColorBlue();   // изменить цвет LED (синий)
    void setLedRate(int);   // заменить частоту мерцания

    void getLedState();   // получить состояние
    void getLedColor();   // получить цвет
    void getLedRate();   // получитьчастоту мерцания

private slots:
    void startLed();   // включить led
    void stopLed();   // выключить led
    void setRate(int);   // установить частоту led



protected:
    void paintEvent(QPaintEvent *);

private:
    bool _ledState;   // состояние LED (ON/OFF)
    Qt::GlobalColor _ledColor;   // цвет LED (RED/GREEN/BLUE)
    int _ledRate;   // частота LED (0...5)

    QMutex mutexState;   // mutex for state
    QMutex mutexColor;   // mutex for color
    QMutex mutexRate;   // mutex for rate

    QTimer* _timer;
    bool _on;   // for rate

};

#endif // LED_H
