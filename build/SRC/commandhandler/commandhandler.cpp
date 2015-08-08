#include "commandhandler.h"

CommandHandler::CommandHandler(QObject* parent)
    : QObject(parent)
{


}

CommandHandler::~CommandHandler()
{
}

void CommandHandler::handleCommand(QString message)
{
    qDebug() << "message: " << message;

    //QString command = message.simplified(); // remove '\n'
    QStringList lexemes = message.split(' ');

 // command for server
    if(lexemes.at(0) == SET_LED_STATE){

        if(lexemes.size() == SIZE_COMMAND && lexemes.at(1) == STATE_ON){
            emit setLedStateOn();
        }
        else if(lexemes.at(1) == STATE_OFF){
            emit setLedStateOff();
        }
        else{
            qDebug() << "Wrong argument";
            messageResultFailed();
        }

    }
    else if(lexemes.at(0) == GET_LED_STATE){
        emit getLedState();
    }
    else if(lexemes.at(0) == SET_LED_COLOR){

        if(lexemes.size() == SIZE_COMMAND && lexemes.at(1) == COLOR_RED){
            emit setLedColorRed();
        }
        else if(lexemes.at(1) == COLOR_GREEN){
            emit setLedColorGreen();
        }
        else if(lexemes.at(1) == COLOR_BLUE){
            emit setLedColorBlue();
        }
        else{
            qDebug() << "Wrong argument";
            messageResultFailed();
        }

    }
    else if(lexemes.at(0) == GET_LED_COLOR){

        emit getLedColor();

    }
    else if(lexemes.at(0) == SET_LED_RATE){

        if(lexemes.size() == SIZE_COMMAND){
            emit setLedRate(QString(lexemes.at(1)).toInt());
        }
        else{
            qDebug() << "Wrong argument";
            messageResultFailed();
        }

    }
    else if(lexemes.at(0) == GET_LED_RATE){

        emit getLedRate();

    }
    else if(lexemes.size() == 1 && lexemes.at(0) == RESULT_OK){

        emit ok();

    }
    else if(lexemes.at(0) == RESULT_FAILED){

        emit failed();

    }
    else if(lexemes.size() == 2 && lexemes.at(0) == RESULT_OK){

        // command for client
        if(lexemes.at(1) == STATE_ON)
            emit setLedStateOn();
        else if(lexemes.at(1) == STATE_OFF)
            emit setLedStateOff();
        else if(lexemes.at(1) == COLOR_RED)
            emit setLedColorRed();
        else if(lexemes.at(1) == COLOR_GREEN)
            emit setLedColorGreen();
        else if(lexemes.at(1) == COLOR_BLUE)
            emit setLedColorBlue();
        else
            emit setLedRate(QString(lexemes.at(1)).toInt());
    }
    else{

        qDebug() << "Wrong command: ";
        messageResultFailed();

    }



}

void CommandHandler::messageResultOk()
{
    emit message(RESULT_OK + QString("\n"));
}
void CommandHandler::messageResultFailed()
{
    emit message(RESULT_FAILED + QString("\n"));
}

void CommandHandler::messageResultStateOn()
{
    emit message(RESULT_OK + QString(" ") + STATE_ON + QString("\n"));
}

void CommandHandler::messageResultStateOff()
{
    emit message(RESULT_OK + QString(" ") + STATE_OFF + QString("\n"));
}

void CommandHandler::messageResultColorRed()
{
    emit message(RESULT_OK + QString(" ") + COLOR_RED + QString("\n"));
}

void CommandHandler::messageResultColorGreen()
{
    emit message(RESULT_OK + QString(" ") + COLOR_GREEN + QString("\n"));
}

void CommandHandler::messageResultColorBlue()
{
    emit message(RESULT_OK + QString(" ") + COLOR_BLUE + QString("\n"));
}

void CommandHandler::messageResultRate(int rate)
{
    emit message(RESULT_OK + QString(" ") + QString::number(rate) + QString("\n"));
}

void CommandHandler::messageSetStateOn()
{
    emit message(SET_LED_STATE + QString(" ") + STATE_ON + QString("\n"));
}

void CommandHandler::messageSetStateOff()
{
    emit message(SET_LED_STATE + QString(" ") + STATE_OFF + QString("\n"));
}

void CommandHandler::messageSetColorRed()
{
    emit message(SET_LED_COLOR + QString(" ") + COLOR_RED + QString("\n"));
}

void CommandHandler::messageSetColorGreen()
{
     emit message(SET_LED_COLOR + QString(" ") + COLOR_GREEN + QString("\n"));
}

void CommandHandler::messageSetColorBlue()
{
     emit message(SET_LED_COLOR + QString(" ") + COLOR_BLUE + QString("\n"));
}

void CommandHandler::messageSetRate(int rate)
{
     emit message(SET_LED_RATE + QString(" ") + QString::number(rate) + QString("\n"));
}

void CommandHandler::messageGetState()
{
    emit message(GET_LED_STATE + QString("\n"));
}

void CommandHandler::messageGetColor()
{
    emit message(GET_LED_COLOR + QString("\n"));
}

void CommandHandler::messageGetRate()
{
    emit message(GET_LED_RATE + QString("\n"));
}

