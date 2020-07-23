#include "clientwidget.h"
#include "loginwidget.h"
#include "registerwidget.h"
#include <QApplication>
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));

    QApplication a(argc, argv);
    RegisterWidget w;
    w.show();

    return a.exec();
}
