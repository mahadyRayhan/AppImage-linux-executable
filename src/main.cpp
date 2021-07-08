#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFileInfo>
#include <QIcon>
#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP
using namespace std;


int main(int argc, char *argv[])
{

    el::Loggers::addFlag(el::LoggingFlag::StrictLogFileSizeCheck);  
  
    el::Configurations conf("my_log.conf");  
  
         /// The configuration of a certain logger can be set separately  
    el::Loggers::reconfigureLogger("default", conf);  
  
         /// You can also set all logger configurations  
    el::Loggers::reconfigureAllLoggers(conf);

    QGuiApplication app(argc, argv);
    QFileInfo fi(app.applicationDirPath() + "/../share/pixmaps/qtquickapp.png");
    QGuiApplication::setWindowIcon(QIcon(fi.absoluteFilePath()));
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    LOG(INFO) << "QT Works";
    app.exec();

    return 0;
    
}
