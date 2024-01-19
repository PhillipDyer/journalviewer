#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "journalinterface.h"
#include "journalview.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    JournalView journalView;

    qmlRegisterType<JournalView>("JournalView", 1, 0, "JournalViewModel");

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);


    engine.loadFromModule("journalviewer", "Main");

    JournalInterface jrnl;

    auto fields = jrnl.retrieveFields();

    std::cout << "Journal Fields as follows: " << std::endl;
    for(auto & f : fields)
    {
        std::cout << f << std::endl;
    }

    std::cout << "Number of Fields " << fields.size() << std::endl;

    return app.exec();
}
