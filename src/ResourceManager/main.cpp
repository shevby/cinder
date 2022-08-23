#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "Resman.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Resman * resman = new Resman();
    engine.rootContext()->setContextProperty("resman", resman);
    const QUrl url(u"qrc:/ui/qml/main.qml"_qs);
    engine.load(url);

    return app.exec();
}
