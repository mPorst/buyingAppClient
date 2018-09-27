#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>
#include <QDate>
#include <QTimer>
#include <QQmlApplicationEngine>
#include "sockethandler.h"
#include <QThread>
#include <QSignalMapper>
#include "communicationprotocol.h"

class Backend : public QObject
{
    Q_OBJECT
    //Q_PROPERTY(QString domain MEMBER domain NOTIFY domainChanged)
    //Q_PROPERTY(quint16 port MEMBER port NOTIFY portChanged)
    //Q_PROPERTY(QString name MEMBER name NOTIFY nameChanged)

public:
    explicit Backend(QQmlApplicationEngine* newEngine, QThread* newMainThread, QObject *parent = nullptr);

public slots:
    void setPort(quint16 newPort);
    void setDomain(QString newDomain);
    void setName(QString newName);
    void updateUI();

    // just call the corresponding methods of CommunicationProtocol
    bool sendPurchase(QString price, QString buyer, QString date, QString receiver);
    bool removePurchase(QString buyer, QString date, QString receiver);
    bool getBalance();
    bool getSummary();
    bool sendConsumer(QString consumer, QString date, QString hasEaten);
    bool getConsumer();

    // UI updating
    void updateProperty(QString objectname, QString property, QString newText);
    void updateCheckbox(QString value);
    void updateMainTextbox(QString text);
    void updateSummaryTextbox(QString text);

    void dummyFunction();

signals:
    void portChanged();
    void domainChanged();
    void dateChanged();
    void nameChanged();
    void updateEaten(QString consumer, QString date);
    void sendPurchaseSignal(QString price, QString buyer, QString date, QString receiver);
    void removePurchaseSignal(QString buyer, QString date, QString receiver);
    void sendConsumerSignal(QString consumer, QString date, QString hasEaten);
    void getSummarySignal();
    void getBalanceSignal(QString employee);

private:
    QQmlApplicationEngine* engine;
    QObject* qmlRootObject;
    bool initialised;
    quint16 port=39978;
    QString domain="palaven.de";
    QString name = "Max Mustermann";
    CommunicationProtocol* comms;
    QThread* mainThread;
    QThread* mythread;
    QString threadValue;
    QTimer* timer;
};
#endif // BACKEND_H
