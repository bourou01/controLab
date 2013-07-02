#include "mainwindow.h"
#include <QApplication>
#include "frdmjsonparser.h"
#include "customplotdialog.h"

#include "serialcomdialog.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


        MainWindow w;
        //w.show();



/*
    CustomPlotDialog d;
    d.show();

    */

    /*
    FRDMJSONParser::getInstance()->setJson(new QString("{\"1\":{\"name\": \"pression\",\"x\": \"4\",\"y\": \"5\"}, \"2\":{\"name\": \"temperature\",\"x\": \"86.45\",\"y\": \"5\"}}"));
    QList<QString> ports =  FRDMJSONParser::getInstance()->ports();
    qDebug() << FRDMJSONParser::getInstance()->xAtPort("2");
    //qDebug() << ports;
   // return -1;
   */

    return a.exec();
}



