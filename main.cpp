#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "journalmodel.h"
#include "navmodel.h"


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<JournalModel>("JournalModel", 1, 0, "JournalModel");
    qmlRegisterType<NavModel>("NavModel", 1, 0, "NavModel");

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);


    engine.loadFromModule("journalviewer", "Main");

    return app.exec();
}
