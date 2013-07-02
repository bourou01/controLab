#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QCustomPlot/qcustomplot.h"
#include "buffered2dsamples.h"
#include "serialcomdialog.h"
#include "customplotdialog.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void onGoButtonClicked();
    void onSerialNotificationPushed();

/// SerialComDialog slots:
    void onDatasReadyToBeRed(QString *toParse);
    void onPlotButtonClicked();
/// CustomPlotDialog
    void aPlotHasBeenClosed(CustomPlotDialog *sender);
    void canalsListComboBoxChanged(CustomPlotDialog *sender);

private:
    Ui::MainWindow *ui;
    SerialComDialog *serialComDialog;
    QVector <CustomPlotDialog *> *plots;

    double dummy;

};

#endif // MAINWINDOW_H
