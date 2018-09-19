#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "sockethandler.h"
#include "backend.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);


    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    Backend backend(&engine);
    engine.rootContext()->setContextProperty("backend", &backend);

    SocketHandler handle;

    /*if(!handle.bindSocket(39978))
    {
        qDebug() << "COULD NOT BIND SOCKET" << '\n';
        exit(1);
    }*/
    //handle.connectToHost("palaven.de", 39978);
    //handle.writeSocket("lalalalalallalalalala\n");
    //qDebug() << handle.readSocket();

    return app.exec();
}
