#include "baselink.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BaseLink w;
    w.show();
    if(argc>1)
    {
        w.setWindowTitle(argv[1]);
        w.PjtNameStart(argv[1]);
        w.PjtNameSet(argv[1]);
    }
    return a.exec();
}
