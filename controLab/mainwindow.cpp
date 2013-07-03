#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

#include <QTimer>
#include "frdmjsonparser.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    srand(QDateTime::currentDateTime().toTime_t());
    ui->setupUi(this);

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
/*
    QTimer *timer = new QTimer (this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onSerialNotificationPushed()));
    timer->start(500);
    */


/////// Attache le bouton 'GO' a l'action ouvrir la fenetre de la communication serie
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(onGoButtonClicked()));

/////// Connexion SerialComDialog
    connect(serialComDialog, SIGNAL(datasReady(QString *)), this, SLOT(onDatasReadyToBeRed(QString *)));
    connect(serialComDialog, SIGNAL(plotButtonHasBeenClicked()), this, SLOT(onPlotButtonClicked()));


    dummy=0;
}

void MainWindow::onGoButtonClicked() {
    serialComDialog->show();
}



////////////////////////////////////////////////////////
/// SerialComDialog dele
///ga
///
void MainWindow::onDatasReadyToBeRed(QString *toParse) {

    /*
    FRDMJSONParser::getInstance()->setJson(toParse);
    QList<QString> listen =  FRDMJSONParser::getInstance()->ports();
    double frdmX = FRDMJSONParser::getInstance()->xAtPort("1");
    double frdmY = FRDMJSONParser::getInstance()->yAtPort("1");

    if (frdmY>dummy)
        dummy = frdmY;


    qDebug() << "(x=" << frdmX << ",y=" << frdmY << ")";

    for (int i=0; i<plots->size(); i++) {
        //plots->at(i)->updateWith(dummy, (double)((int)dummy % 10));

        if (frdmY== dummy)
            plots->at(i)->updateWith(frdmY, frdmX);
    }
    */
/*
    FRDMJSONParser::getInstance()->setJson(toParse);
    QList<QString> listen =  FRDMJSONParser::getInstance()->ports();

    for (int i=0; i<plots->size(); i++) {
            double frdmX = FRDMJSONParser::getInstance()->xAtPort(plots->at(i)->getCanal());
            double frdmY = FRDMJSONParser::getInstance()->yAtPort(plots->at(i)->getCanal());

            if (frdmY>dummy)
                dummy = frdmY;

            plots->at(i)->updateWith(frdmY, frdmX);
            plots->at(i)->updateCanalsListWith(listen);
    }

dummy++;
*/

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
    //newCustomPlotDialog->setTarget(plots->size() - 1);

    newCustomPlotDialog->show();
}

////////////////////////////////////////////////////////
/// CustomPlotDialog delegate
///
void MainWindow::aPlotHasBeenClosed(CustomPlotDialog *sender) {
    // qDebug() << "aPlotHasBeenClosed"<< sender->getTarget()  << "total: " << plots->size();

    for (int i=0; i<plots->size(); i++) {
        if (plots->at(i) == sender)
            plots->remove(i);
    }
    //plots->resize(plots->size());
}

void MainWindow::canalsListComboBoxChanged(CustomPlotDialog *sender) {
    //qDebug() << "changed" << sender->getTarget()  << "to" << sender->getComboSelected();
    /*
    for (int i=0; i<plots->size(); i++) {
        if (plots->at(i) == sender) {

        }
            plots->at(i)->updateWith(frdmX, frdmY);
            plots->at(i)->updateCanalsListWith(listen);
    }
*/
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

    /*
    FRDMJSONParser::getInstance()->setJson(toParse);
    QList<QString> listen =  FRDMJSONParser::getInstance()->ports();



    for (int i=0; i<plots->size(); i++) {
//        for (int j=0; j<) {
            double frdmX = FRDMJSONParser::getInstance()->xAtPort(plots->at(i)->getCanal());
            double frdmY = FRDMJSONParser::getInstance()->yAtPort(plots->at(i)->getCanal());

            if (frdmY>dummy)
                dummy = frdmY;

           plots->at(i)->updateWith(frdmX, frdmY);
  //      }
           plots->at(i)->updateCanalsListWith(listen);
    }

*/


}

MainWindow::~MainWindow()
{
    delete ui;
    delete serialComDialog;
}
