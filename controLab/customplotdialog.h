#ifndef CUSTOMPLOTDIALOG_H
#define CUSTOMPLOTDIALOG_H

#include <QDialog>

#include "QCustomPlot/qcustomplot.h"
#include "buffered2dsamples.h"
#include "customgraph.h"


namespace Ui {
class CustomPlotDialog;
}

class CustomPlotDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CustomPlotDialog(QWidget *parent = 0);
    ~CustomPlotDialog();

//// Override
    void closeEvent(QCloseEvent *event);

/*
    void updateWith(double x, double y);
    void setTarget(int cible);
    int getTarget();
*/

    void updateCanalsListWith(QList<QString> liste);
    void updatePlotsFromNotification(QString toParse);



private slots:
    void onCanalsListChanged(int selected);
    void onAddPlotButtonClicked();
    void onDeletePlotButtonClicked();
    void onGraphIdChanged(int index);

    void onScatterStyleComboBoxChanged(int index);
    void onLineStyleComboBoxChanged(int index);
    void onColorComboBoxChanged(int index);

    void onAutoscaleCheckBoxChanged(int choice);

Q_SIGNALS:
    void close(CustomPlotDialog * me);
    void onCanalsListComboBoxChanged(CustomPlotDialog *sender);
/*
public:
    void setCanal(QString newCanal);
    QString getCanal();
    int getComboSelected();
    QVector<double> * getXVector();
    QVector<double> * getYVector();
*/

private:
    int insertNewGraph( );
    void updateGraphsIds();
    void configureCustomPlot();

private:
    Ui::CustomPlotDialog *ui;
    //Buffered2DSamples *buffered2DSamples; /// deprecated
    //int target; /// deprecated
    //int comboSelected; ///deprecated
    QList<QString> canals;
    //QString canal; /// deprecated
    QVector <CustomGraph *> customGraphs;
    QList<QColor> myColors;

    double TIME_SYNCHRONISATION;

};

#endif // CUSTOMPLOTDIALOG_H
