#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "sockethandler.h"
#include "backend.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);


    QGuiApplication app(argc, argv);
    qDebug() << "The main thread is: " << app.thread();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    Backend backend(&engine, (&app)->thread());
    QThread::msleep(200);
    engine.rootContext()->setContextProperty("backend", &backend);

    return app.exec();
}
