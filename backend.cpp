#include "backend.h"
#include "sockethandler.h"

Backend::Backend(QQmlApplicationEngine* newEngine, QObject *parent) : QObject(parent)
{ // timer to update UI constantly
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Backend::updateUI);
    timer->start(1000);

    engine = newEngine;
    qmlRootObject = engine->rootObjects().first();
}

void Backend::initSocket()
{
    if(!handle.bindSocket(port))
    {
        qDebug() << "Could not bind socket!\n"; return;
    }
}

void Backend::writeSocket(QString data)
{
    handle.connectToHost(domain, port);
    //qDebug() << "connected to: " << domain << " and " << port << '\n';
    handle.writeSocket(data);
    qDebug() << "Wrote data: " << data << '\n';
}

QString Backend::readSocket()
{
    return handle.readSocket();
}

void Backend::initAndWriteSocket(QString data)
{
    if(isInitialised() == false)
    {
        initSocket();
        initialised=true;
        qDebug() << "Initialised socket \n";
    }
    writeSocket(data);
}

void Backend::closeSocket()
{
    handle.closeSocket();
}

void Backend::setPort(quint16 newPort)
{
    port = newPort;
}

void Backend::setDomain(QString newDomain)
{
    domain = newDomain;
}

void Backend::setName(QString newName)
{
    name = newName;
}

bool Backend::isInitialised()
{
    return initialised;
}

void Backend::updateUI(){
    QObject *dateLabel = qmlRootObject->findChild<QObject*>("dateTextObject");
    QString today = QDate::currentDate().toString();
    if(dateLabel != nullptr)
        dateLabel->setProperty("text", QDate::currentDate());
    else
        qDebug() << "Could not find the date text field. \n";
    getConsumer(name, today);
}

bool Backend::sendPurchase(QString price, QString buyer, QString date, QString receiver)
{
    initAndWriteSocket("send purchase\n");
    QThread::msleep(50);
    QObject* answer = qmlRootObject->findChild<QObject*>("serverAnswerAreaObject");

    if(answer == nullptr)
    {
        qDebug() << "serverAnswerObject was not found. PANIC !!! \n";
        return false;
    }

    if(readSocket() != "ack\n")
    {
        qDebug() << "Entering != ack case \n";
        closeSocket();
        answer->setProperty("text", "Server error, did not send data");
        return false; // server didn't answer
    }

    answer->setProperty("text", "ack");
    QThread::msleep(50);
    initAndWriteSocket(buyer.append("\n"));
    QThread::msleep(50);
    initAndWriteSocket(date.append("\n"));
    QThread::msleep(50);
    initAndWriteSocket(price.append("\n"));
    QThread::msleep(50);
    initAndWriteSocket(receiver.append("\n"));
    answer->setProperty("text", readSocket());
    closeSocket();
    return true;
}

bool Backend::removePurchase(QString buyer, QString date, QString receiver)
{
    initAndWriteSocket("remove purchase\n");
    QThread::msleep(50);
    QObject* answer = qmlRootObject->findChild<QObject*>("serverAnswerAreaObject");

    if(answer == nullptr)
    {
        qDebug() << "serverAnswerObject was not found. PANIC !!! \n";
        return false;
    }

    if(readSocket() != "ack\n")
    {
        qDebug() << "Entering != ack case \n";
        closeSocket();
        answer->setProperty("text", "Server error, did not send data");
        return false; // server didn't answer
    }

    answer->setProperty("text", "ack");
    QThread::msleep(50);
    initAndWriteSocket(buyer.append("\n"));
    QThread::msleep(50);
    initAndWriteSocket(date.append("\n"));
    QThread::msleep(50);
    initAndWriteSocket(receiver.append("\n"));
    answer->setProperty("text", readSocket());
    closeSocket();
    return true;
}

bool Backend::getBalance()
{
    initAndWriteSocket("get balance\n");
    QThread::msleep(50);
    QObject* answer = qmlRootObject->findChild<QObject*>("serverAnswerSummaryAreaObject");
    QString buyer = name;

    if(answer == nullptr)
    {
        qDebug() << "serverAnswerObject was not found. PANIC !!! \n";
        return false;
    }

    if(readSocket() != "ack\n")
    {
        qDebug() << "Entering != ack case \n";
        closeSocket();
        answer->setProperty("text", "Server error, did not send data");
        return false; // server didn't answer
    }

    initAndWriteSocket(buyer.append("\n"));
    answer->setProperty("text", readSocket());
    closeSocket();
    return true;
}

bool Backend::getSummary()
{
    initAndWriteSocket("get summary\n");
    QThread::msleep(50);
    QObject* answer = qmlRootObject->findChild<QObject*>("serverAnswerSummaryAreaObject");
    QString serverResponse;

    if(answer == nullptr)
    {
        qDebug() << "serverAnswerObject was not found. PANIC !!! \n";
        return false;
    }

    QString mystr = readSocket();
    if(mystr != "ack\n")
    {
        qDebug() << "Entering != ack case, received " << mystr << " \n";
        closeSocket();
        answer->setProperty("text", "Server error, did not send data");
        return false; // server didn't answer
    }

    for(int i=0; i<12; i++)
    {
        serverResponse.append(readSocket());
    }
    qDebug() << serverResponse;
    answer->setProperty("text", serverResponse);
    closeSocket();
    return true;
}

bool Backend::sendConsumer(QString consumer, QString date, QString hasEaten)
{
    initAndWriteSocket("send consumer\n");
    QThread::msleep(50);
    QObject* answer = qmlRootObject->findChild<QObject*>("serverAnswerAreaObject");
    if(answer == nullptr)
    {
        qDebug() << "serverAnswerObject was not found. PANIC !!! \n";
        return false;
    }
    if(readSocket() != "ack\n")
    {
        qDebug() << "Entering != ack case \n";
        closeSocket();
        answer->setProperty("text", "Server error, did not send data");
        return false; // server didn't answer
    }

    answer->setProperty("text", "ack");
    QThread::msleep(50);
    initAndWriteSocket(consumer.append("\n"));
    QThread::msleep(50);
    initAndWriteSocket(date.append("\n"));
    QThread::msleep(50);
    initAndWriteSocket(hasEaten.append("\n"));
    answer->setProperty("text", readSocket());
    closeSocket();
    return true;
}

bool Backend::getConsumer(QString consumer, QString date)
{
    initAndWriteSocket("get consumer\n");
    QThread::msleep(50);
    QObject* checkbox = qmlRootObject->findChild<QObject*>("eatenCheckboxObject");
    QObject* answer = qmlRootObject->findChild<QObject*>("serverAnswerAreaObject");

    if(answer == nullptr)
    {
        qDebug() << "serverAnswerObject was not found. PANIC !!! \n";
        return false;
    }
    if(checkbox == nullptr)
    {
        qDebug() << "eatenCheckboxObject was not found. PANIC !!! \n";
        return false;
    }

    if(readSocket() != "ack\n")
    {
        qDebug() << "Entering != ack case \n";
        closeSocket();
        answer->setProperty("text", "Can't reach server on regular UI update");
        return false; // server didn't answer
    }

    QThread::msleep(30);
    initAndWriteSocket(consumer.append("\n"));
    QThread::msleep(30);
    initAndWriteSocket(date.append("\n"));
    QString answerFromServer = readSocket();
    if(answerFromServer == "true")
    {
        checkbox->setProperty("checked", true);
    }
    else if(answerFromServer == "false")
    {
        checkbox->setProperty("checked", false);
    }
    closeSocket();
    return true;
}

