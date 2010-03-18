#include <QtGui/QApplication>
#include "tshelper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TsHelper w;
    w.show();
    return a.exec();
}
