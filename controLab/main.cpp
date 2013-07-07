#include "mainwindow.h"
#include <QApplication>
#include "frdmjsonparser.h"

#include "MessageWindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //! [0]
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    //redirect debug messages to the MessageWindow dialog
    qInstallMsgHandler(MessageWindow::AppendMsgWrapper);
#else
    qInstallMessageHandler(MessageWindow::AppendMsgWrapper);
#endif
    //! [0]


        MainWindow w;
        w.show();

/*
    CustomPlotDialog d;
    d.show();

    */
    return a.exec();
}



