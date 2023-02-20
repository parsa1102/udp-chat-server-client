#include "widget.h"

#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("parsaChat");
    QCoreApplication::setApplicationName("Chat");
    QSettings settings(QCoreApplication::organizationName() , QCoreApplication::applicationName());
    settings.beginGroup("Ports");
    if(settings.contains("port")){
        int tmp = settings.value("port").toInt();
        settings.setValue("port" , tmp+1);
    }else{
        settings.setValue("port" , 1500);
    }
    Widget w;
    w.show();
    return a.exec();
}
