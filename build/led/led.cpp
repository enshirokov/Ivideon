#include "led.h"
#include <QDebug>

Led::Led(QWidget *parent)
    : QWidget(parent),
    _ledState(false),
    _ledColor(Qt::red),
    _ledRate(0),
    _on(false)
{
    //_painter = new QPainter(this);

    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(update()));
    _timer->setInterval(1000);

    //startLed();


}

void Led::paintEvent(QPaintEvent* event)
{
    QPainter _painter(this);

    if(_on){
        _painter.setBrush(_ledColor);
        _on = false;
    }
    else{
        _painter.setBrush(Qt::gray);
        _on = true;
    }
    _painter.drawEllipse(QPoint(this->width()/2, this->height()/2), 20, 20);

}

void Led::update()
{
    repaint();
}

void Led::startLed()
{
    _on = true;
    _timer->start();
}

void Led::stopLed()
{
    _on = false;
    repaint();
    _timer->stop();

}

void Led::setRate(int rate)
{
    _timer->setInterval(rate * 1000);

}

void Led::setLedStateOn()
{
    // lock
    //QMutexLocker lock(&mutexState);

    // and set
    _ledState = true;
    qDebug() << "led state ON";

    startLed();

    emit resultOk();
}

void Led::setLedStateOff()
{
    // lock
    //QMutexLocker lock(&mutexState);

    // and set
    _ledState = false;
    qDebug() << "led state OFF";

    stopLed();

    emit resultOk();
}

void Led::setLedColorRed()
{
    // lock
    //QMutexLocker lock(&mutexColor);

    // and set
    _ledColor = Qt::red;
    qDebug() << "led color RED";

    emit resultOk();
}

void Led::setLedColorGreen()
{
    // lock
    //QMutexLocker lock(&mutexColor);

    // and set
    _ledColor = Qt::green;
    qDebug() << "led color GREEN";

    emit resultOk();
}

void Led::setLedColorBlue()
{
    // lock
    //QMutexLocker lock(&mutexColor);

    // and set
    _ledColor = Qt::blue;
    qDebug() << "led color BLUE";

    emit resultOk();
}

void Led::setLedRate(int rate)
{
    // lock
    //QMutexLocker lock(&mutexRate);

    // and set
    _ledRate = rate;
    qDebug() << "led rate " << rate;

    setRate(_ledRate);

    emit resultOk();
}

void Led::getLedState()
{
    // lock
    //QMutexLocker lock(&mutexState);

    // and get
    if(_ledState){
        emit resultStateOn();
    }
    else{
        emit resultStateOff();
    }
}

void Led::getLedColor()
{
    // lock
   // QMutexLocker lock(&mutexColor);

    // and get
    switch (_ledColor) {
    case Qt::red:
        emit resultColorRed();
        break;
    case Qt::blue:
        emit resultColorBlue();
        break;
    case Qt::green:
        emit resultColorGreen();
        break;
    default:
        break;
    }
}

void Led::getLedRate()
{
    // lock
    //QMutexLocker lock(&mutexRate);

    // and get
    emit resultRate(_ledRate);

}
