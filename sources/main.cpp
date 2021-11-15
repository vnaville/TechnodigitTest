#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "includes/distancemanager.h"
#include <QCommandLineParser>
#include "includes/integrationtest.h"
#include <QDebug>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QCommandLineParser parser;

    QCommandLineOption integrationTestOption(QStringList() << "i" << "integrationTest", "Play integration tests");
    parser.addOption(integrationTestOption);

    if (!parser.parse(QCoreApplication::arguments())) {
        qDebug() << "Error" << parser.errorText();
    }

    if (parser.isSet("integrationTest"))
    {
        IntegrationTest integrationTest;
        if (integrationTest.doIntegrationTests())
        {
            qDebug() << "Integration tests succeeded";
        } else {
            qDebug() << "Integration tests failed";
        }
    }

    QQmlApplicationEngine engine;

    // Déclaration of c++ classes used inside QML
    qmlRegisterType<DistanceManager>("DistanceManager", 1, 0, "DistanceManager");

    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
