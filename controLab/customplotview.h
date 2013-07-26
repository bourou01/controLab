#ifndef CUSTOMPLOTVIEW_H
#define CUSTOMPLOTVIEW_H

#include <QWidget>


#include "QCustomPlot/qcustomplot.h"
#include "buffered2dsamples.h"
#include "customgraph.h"


namespace Ui {
class CustomPlotView;
}

class CustomPlotView : public QWidget
{
    Q_OBJECT
    
public:
    explicit CustomPlotView(QWidget *parent = 0);
    ~CustomPlotView();

    //// Override
        void closeEvent(QCloseEvent *event);

    void updateCanalsListWith(QList<QString> liste);
    void updatePlotsFromNotification(QString toParse);



private slots:
    void onCanalsListChanged(int selected);
    void onAddPlotButtonClicked();
    void onDeletePlotButtonClicked();
    void onResetPlotButtonClicked();

    void onGraphIdChanged(int index);

    void onScatterStyleComboBoxChanged(int index);
    void onLineStyleComboBoxChanged(int index);
    void onColorComboBoxChanged(int index);

    void onAutoscaleCheckBoxChanged(int choice);

Q_SIGNALS:
    void close(CustomPlotView * me);
    void onCanalsListComboBoxChanged(CustomPlotView *sender);

private:
    int insertNewGraph( );
    void updateGraphsIds();
    void configureCustomPlot();

private:
    QList<QString> canals;
    QVector <CustomGraph *> customGraphs;
    QList<QColor> myColors;

    double TIME_SYNCHRONISATION;



    QString toParseStr;
    
private:
    Ui::CustomPlotView *ui;
};

#endif // CUSTOMPLOTVIEW_H
