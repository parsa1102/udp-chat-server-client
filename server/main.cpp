#include <QCoreApplication>
#include "runner.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    runner r;
    r.start();
    return a.exec();
}
