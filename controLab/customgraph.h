#ifndef CUSTOMGRAPH_H
#define CUSTOMGRAPH_H

#include "QCustomPlot/qcustomplot.h"
#include "buffered2dsamples.h"


class CustomGraph
{
public:
    CustomGraph();
    ~CustomGraph();


    void updateWith(double x, double y);
    int index();
    void setIndex(int id);

    QVector<double> * getXVector();
    QVector<double> * getYVector();

    QString getCurrentCanal();
    void setCurrentCanal(QString canal);

    int getComboSelected();
    void setComboSelected(int combo);

    void setColorIndex(int cI);
    int getColorIndex();

    void setBufferSize(int buffer);

private:
    int graphIndex;
    Buffered2DSamples *buffered2DSamples;
    QString currentCanal;
    int comboSelected;
    int colorIndex;

};

#endif // CUSTOMGRAPH_H
