#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <QTimer>

#include <QMessageBox>
#include <QMenuBar>


#include "frdmjsonparser.h"

#include "MessageWindow.h"
#include "serialmanagerview.h"
#include "customplotview.h"

#include "frdmcontrolview.h"

#include "serialconfigurationview.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    srand(QDateTime::currentDateTime().toTime_t());
    ui->setupUi(this);


/*
/////// Configuration du dialogue du port Serie
    serialComDialog = new SerialComDialog();
    serialComDialog->show();

/////// Alloue et passe au serialComDialog le pointeur sur le tableau des graphiques
    plots = new QVector<CustomPlotDialog *>();
    serialComDialog->plots = plots;

/////// Configuration d'un timer de test
///
///
///

    //QTimer *timer = new QTimer (this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(onSerialNotificationPushed()));
    //timer->start(500);



/////// Attache le bouton 'GO' a l'action ouvrir la fenetre de la communication serie
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onGoButtonClicked()));

/////// Connexion SerialComDialog
    connect(serialComDialog, SIGNAL(datasReady(QString *)), this, SLOT(onDatasReadyToBeRed(QString *)));
    connect(serialComDialog, SIGNAL(plotButtonHasBeenClicked()), this, SLOT(onPlotButtonClicked()));
    dummy=0;
    */


    // custom plot View
    CustomPlotView *customPlotView = new CustomPlotView();
    QDockWidget *W2 = new QDockWidget();
    W2->setWidget(customPlotView);
    setCentralWidget(W2);

    //central widget
    SerialConfigurationView *qespTest = new SerialConfigurationView();
    QDockWidget *W1 = new QDockWidget();
    W1->setWidget(qespTest);
    addDockWidget(Qt::RightDockWidgetArea, W1);

    //bottom dock widget
    MessageWindow *msgWindow = new MessageWindow();
    addDockWidget(Qt::BottomDockWidgetArea, msgWindow);

    // Control View
    FRDMControlView *frdmControlView = new FRDMControlView();
    QDockWidget *W3 = new QDockWidget();
    W3->setWidget(frdmControlView);
    addDockWidget(Qt::LeftDockWidgetArea, W3);

    ///
    createActions();
    createMenus();


    setWindowTitle(tr("QextSerialPort Test Application"));
}

void MainWindow::onGoButtonClicked() {
    serialComDialog->show();
}



////////////////////////////////////////////////////////
/// SerialComDialog dele
///ga
///
void MainWindow::onDatasReadyToBeRed(QString *toParse) {
    dummy++;
    for (int i=0; i<plots->size(); i++) {
           plots->at(i)->updatePlotsFromNotification(*toParse);
    }
}

void MainWindow::onPlotButtonClicked() {
    CustomPlotDialog *newCustomPlotDialog = new CustomPlotDialog();
    /////// Connexion SerialComDialog
    connect(newCustomPlotDialog, SIGNAL(close(CustomPlotDialog *)), this, SLOT(aPlotHasBeenClosed(CustomPlotDialog *)));
    connect(newCustomPlotDialog, SIGNAL(onCanalsListComboBoxChanged(CustomPlotDialog *)), this, SLOT(canalsListComboBoxChanged(CustomPlotDialog *)));
    /// attache un evenement
    plots->push_back(newCustomPlotDialog);
    /// pour pouvoir le supprimer plutard
    newCustomPlotDialog->show();
}

////////////////////////////////////////////////////////
/// CustomPlotDialog delegate
///
void MainWindow::aPlotHasBeenClosed(CustomPlotDialog *sender) {
    for (int i=0; i<plots->size(); i++) {
        if (plots->at(i) == sender)
            plots->remove(i);
    }
}

void MainWindow::canalsListComboBoxChanged(CustomPlotDialog *sender) { /// deprecated

}
////////////////////////////////////////////////////////
///
///
void MainWindow::onSerialNotificationPushed() {

    dummy++;
    double y = (rand()/(double)RAND_MAX + 0.5)*2;
    QString *toParse = new QString(QString("{\"1\":{\"name\": \"pression\",\"x\": \"%1\",\"y\": \"%2\"}, \"2\":{\"name\": \"temperature\",\"x\": \"%3\",\"y\": \"%4\"}}").arg(QString::number(dummy), QString::number(sin(dummy)), QString::number(dummy), QString::number(y)));

    for (int i=0; i<plots->size(); i++) {
           plots->at(i)->updatePlotsFromNotification(*toParse);
    }
}



////////////////////////////////////////////////////////////////////////
///
///

void MainWindow::about()
{
    QMessageBox::about(this, tr("About "),
                       tr("<B>""</B><BR>"
                          "author: Michal Policht<br>"
                          "<a href='mailto:xpolik@users.sourceforge.net'>xpolik@users.sourceforge.net</a>"));
}

void MainWindow::createActions()
{
    //File actions
    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(tr("CTRL+D"));
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    //Help actions
    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setShortcut(tr("CTRL+A"));
    aboutAct->setStatusTip(tr("About application"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(exitAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}


////////////////////////////////////////////////////////////////////////
///
///


MainWindow::~MainWindow()
{
    //delete ui;
    //delete serialComDialog;
}



