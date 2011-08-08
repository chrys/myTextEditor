#include <QtGui/QApplication>
#include "mytexteditor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    myTextEditor w;
    w.show();

    return a.exec();
}
