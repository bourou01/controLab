#ifndef BUFFERED2DSAMPLES_H
#define BUFFERED2DSAMPLES_H

#include <QStandardItemModel>
#include <QVector>
#include <QDebug>



class Buffered2DSamples : public QStandardItemModel
{
public:
    Buffered2DSamples();
    Buffered2DSamples(int bufferSize);
    ~Buffered2DSamples();

    bool insert2DSample(double x, double y);

/// getters

    QVector <double> * getXVector();
    QVector <double> * getYVector();

    int getBufferSize(void);
    int getSize();

/// setters
    void setBufferSize(int bufferSize);

private:
    int bufferSize;
    int size;

    QVector <double> * xVector;
    QVector <double> * yVector;
};

#endif // BUFFERED2DSAMPLES_H
