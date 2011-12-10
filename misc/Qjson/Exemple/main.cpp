#include <QtCore/QCoreApplication>

#include <QtCore/QDebug>
#include <QtCore/QVariant>

#include <qjson/parser.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QJson::Parser parser;
    bool ok;
    QVariant result = parser.parse("[1,2,3]", &ok);

    if (!ok)
        qDebug() << "something went wrong during the conversion";
    else
        qDebug() << "converted to" << result;

    return a.exec();
}
