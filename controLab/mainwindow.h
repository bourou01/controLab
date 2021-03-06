#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QCustomPlot/qcustomplot.h"
#include "buffered2dsamples.h"
//#include "serialcomdialog.h"
#include "customplotview.h"
#include "serialconfigurationview.h"
#include "frdmcontrolview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
    QMenu *fileMenu;
    QAction *exitAct;
    QMenu *helpMenu;
    QAction *aboutAct;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void onGoButtonClicked();
    void onSerialNotificationPushed();

/// SerialComDialog slots:
    void onDatasReadyToBeRed(QString toParse);
    void onPlotButtonClicked();
/// CustomPlotDialog
    void aPlotHasBeenClosed(CustomPlotView *sender);
    void canalsListComboBoxChanged(CustomPlotView *sender);

private:
    Ui::MainWindow *ui;
    //SerialComDialog *serialComDialog;
    QVector <CustomPlotView *> *plots;

    SerialConfigurationView *serialConfigurationView;
    FRDMControlView *frdmControlView;

private:
    void createMenus();
    void createActions();

private slots:
    void about();



};

#endif // MAINWINDOW_H
