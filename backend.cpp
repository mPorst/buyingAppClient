#include "backend.h"

Backend::Backend(QQmlApplicationEngine* newEngine, QThread* newMainThread, QObject *parent) : QObject(parent)
{
    engine = newEngine;
    qmlRootObject = engine->rootObjects().first();
    mainThread = newMainThread;

    // timer to update UI constantly
    timer = new QTimer(this);
    //connect(timer, &QTimer::timeout, this, &Backend::updateUI);
    //connect(timer, &QTimer::timeout, mythread, &QThread::start);
    timer->start(2000);

    //set up the comms object for server communication
    comms = new CommunicationProtocol(mainThread);
    comms->setDomain(domain);
    comms->setPort(port);

    //set up a new thread
    mythread = new QThread();

    mainThread->setObjectName("mainThread");
    mythread->setObjectName("updateThread");

    QObject::connect(timer, &QTimer::destroyed, this, &Backend::dummyFunction);
    QObject::connect(timer, &QTimer::timeout, this, &Backend::updateUI);
    // connections for updateUI
    //QObject::connect(mythread, &QThread::started, this, &Backend::getConsumer);
    QObject::connect(this, &Backend::startGetConsumer, this, &Backend::getConsumer);
    QObject::connect(this, &Backend::updateEaten, comms, &CommunicationProtocol::getConsumer);
    //QObject::connect(comms, &CommunicationProtocol::gotConsumer, mythread, &QThread::quit);
    QObject::connect(comms, &CommunicationProtocol::gotConsumer, this, &Backend::updateCheckbox);
    //QObject::connect(mythread, SIGNAL(finished()), mythread, SLOT(deleteLater()));

    /// connections for other server communication
    // sendPurchase
    QObject::connect(this, &Backend::sendPurchaseSignal, comms, &CommunicationProtocol::sendPurchase);
    QObject::connect(comms, &CommunicationProtocol::sentPurchase, this, &Backend::updateMainTextbox );
    //removePurchase
    QObject::connect(this, &Backend::removePurchaseSignal, comms, &CommunicationProtocol::removePurchase);
    QObject::connect(comms, &CommunicationProtocol::removedPurchase, this, &Backend::updateMainTextbox );
    //sendConsumer
    QObject::connect(this, &Backend::sendConsumerSignal, comms, &CommunicationProtocol::sendConsumer);
    QObject::connect(comms, &CommunicationProtocol::sentConsumer, this, &Backend::updateMainTextbox );
    //getSummary
    QObject::connect(this, &Backend::getSummarySignal, comms, &CommunicationProtocol::getSummary);
    QObject::connect(comms, &CommunicationProtocol::gotSummary, this, &Backend::updateSummaryTextbox);
    //removePurchase
    QObject::connect(this, &Backend::getBalanceSignal, comms, &CommunicationProtocol::getBalance);
    QObject::connect(comms, &CommunicationProtocol::gotBalance, this, &Backend::updateSummaryTextbox);

    comms->moveToThread(mythread);
    mythread->start();
}

void Backend::setPort(quint16 newPort)
{
    port = newPort;
    comms->setPort(port);
}

void Backend::setDomain(QString newDomain)
{
    domain = newDomain;
    comms->setDomain(domain);
}

void Backend::setName(QString newName)
{
    name = newName;
}


void Backend::updateUI(){
    QString today = QDate::currentDate().toString();
    QObject *dateLabel = qmlRootObject->findChild<QObject*>("dateTextObject");
    if(dateLabel != nullptr)
        dateLabel->setProperty("text", QDate::currentDate());
    else
        qDebug() << "Could not find the date text field. \n";

    emit startGetConsumer();
    //mythread->start();
    return;
}

bool Backend::sendPurchase(QString price, QString buyer, QString date, QString receiver)
{
    // the actual server communication is done in the comms object
    //QString serverAnswer = comms->sendPurchase(price, buyer, date, receiver);
    emit sendPurchaseSignal(price, buyer, date, receiver);
    //answer->setProperty("text", serverAnswer);
    return true;
}

bool Backend::removePurchase(QString buyer, QString date, QString receiver)
{
    emit removePurchaseSignal(buyer, date, receiver);
    return true;
}

bool Backend::getBalance()
{
    emit getBalanceSignal(name);
    return true;
}

bool Backend::getSummary()
{
    emit getSummarySignal();
    return true;
}

bool Backend::sendConsumer(QString consumer, QString date, QString hasEaten)
{
    emit sendConsumerSignal(consumer, date, hasEaten);
    return true;
}

bool Backend::getConsumer()
{
    QString date = QDate::currentDate().toString(Qt::ISODate);
    // the signal updateEaten() starts the method getConsumer in comms
    qDebug() << "Emitting updateEaten...";
    emit updateEaten(name, date);
    qDebug() << "Emitted updateEaten...";
    //QString serverAnswer = comms->getConsumer(consumer, date);
    qDebug() << "Exiting getConsumer...";
    return true;
}

void Backend::updateProperty(QString objectname, QString property, QString newValue)
{
    QObject* toBeUpdated = qmlRootObject->findChild<QObject*>(objectname);

    if(toBeUpdated == nullptr)
    {
        qDebug() << "serverAnswerObject was not found. PANIC !!! \n";
        return;
    }
    toBeUpdated->setProperty(property.toStdString().c_str(), newValue);
}

void Backend::updateMainTextbox(QString text)
{
    qDebug() << "NOW UPDATING THE MAIN TEXT BOX";
    QObject* toBeUpdated = qmlRootObject->findChild<QObject*>("serverAnswerAreaObject");

    if(toBeUpdated == nullptr)
    {
        qDebug() << "serverAnswerObject was not found in updateMainTextbox. PANIC !!! \n";
        return;
    }
    toBeUpdated->setProperty("text", text);
}

void Backend::updateSummaryTextbox(QString text)
{
    qDebug() << "NOW UPDATING THE SUMMARY TEXT BOX";
    QObject* toBeUpdated = qmlRootObject->findChild<QObject*>("serverAnswerSummaryAreaObject");

    if(toBeUpdated == nullptr)
    {
        qDebug() << "serverAnswerSummaryAreaObject was not found in updateMainTextbox. PANIC !!! \n";
        return;
    }
    toBeUpdated->setProperty("text", text);
}

void Backend::updateCheckbox(QString value)
{
    qDebug() << "STARTING UPDATE CHECKBOX";
    // the truncate operation removes the new line character from the end of the string
    value.truncate(value.size()-1);
    qDebug() << value << " was received";
    if(value == "true" || value == "false")
    {
        updateProperty("eatenCheckboxObject", "checked", value);
        return;
    }
    else
    {
        QString answer = "Server responded with an error: " + value;
        updateProperty("serverAnswerAreaObject", "text", answer);
        return;
    }
}

void Backend::dummyFunction()
{
    qDebug("THE TIMER WAS KILLED!!!!!!!!!!!!!!!!!!!!!!!!!!!");
}

void Backend::switchUpdate(bool value)
{
   if(value == true)
       timer->start(2000);
   else
       timer->stop();
}
