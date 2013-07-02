#include "buffered2dsamples.h"

Buffered2DSamples::Buffered2DSamples()
{
    this->xVector = new QVector <double>();
    this->yVector = new QVector <double>();
    this->size = -1;
    bufferSize = 70;
}

Buffered2DSamples::Buffered2DSamples(int bufferSize)
{
    //Buffered2DSamples::Buffered2DSamples();
    this->xVector = new QVector <double>();
    this->yVector = new QVector <double>();
    this->size = -1;
    this->setBufferSize(bufferSize);

}

bool Buffered2DSamples::insert2DSample(double x, double y) {
    if (this->getSize() < this->bufferSize) {

        this->xVector->push_back(x);
        this->yVector->push_back(y);
        this->size++;
    }
    else if (this->getSize() == this->bufferSize) {
        this->xVector->remove(0);
        this->yVector->remove(0);

        this->xVector->resize(this->bufferSize - 1);
        this->yVector->resize(this->bufferSize - 1);

        this->xVector->push_back(x);
        this->yVector->push_back(y);
    }
    else {

        this->xVector->clear();
        this->yVector->clear();

        //this->xVector->resize(this->bufferSize - 1);
        //this->yVector->resize(this->bufferSize - 1);

    }
    return true;
}

/// setteurs
void Buffered2DSamples::setBufferSize(int bufferSize) {
    this->bufferSize = bufferSize;
}

/// getters
QVector <double> * Buffered2DSamples::getXVector() {
    return this->xVector;
}
QVector <double> * Buffered2DSamples::getYVector() {
    return this->yVector;
}

int Buffered2DSamples::getSize() {
    return this->size = this->xVector->size();
}

int Buffered2DSamples::getBufferSize(void) {
    return this->bufferSize;
}

Buffered2DSamples::~Buffered2DSamples()
{
    this->xVector->clear();
    delete this->xVector;

    this->yVector->clear();
    delete this->yVector;
}
