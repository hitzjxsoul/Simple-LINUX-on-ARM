#include <QtGui/QApplication>
#include <test.h>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    srand(unsigned(time(0)));
    QApplication app(argc, argv);
    QDesktopWidget *desktop = app.desktop();
    Test test;
    test.move(desktop->width()/2-test.width()/2,desktop->height()/2-test.height()/2);
    test.show();
    return app.exec();
}
