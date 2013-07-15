#include "customgraph.h"

CustomGraph::CustomGraph()
{
    buffered2DSamples = new Buffered2DSamples(50);
    colorIndex = 0;
}
CustomGraph::~CustomGraph()
{
    delete buffered2DSamples;
}

int CustomGraph::index() {
    return graphIndex;
}
void CustomGraph::setIndex(int id) {
    graphIndex = id;
}

void CustomGraph::updateWith(double x, double y) {
    buffered2DSamples->insert2DSample(x, y);
}

QVector<double> * CustomGraph::getXVector() {
    return buffered2DSamples->getXVector();
}
QVector<double> * CustomGraph::getYVector() {
     return buffered2DSamples->getYVector();
}

void CustomGraph::setColorIndex(int cI) {
    colorIndex = cI;
}
int CustomGraph::getColorIndex() {
    return colorIndex;
}


QString CustomGraph::getCurrentCanal() {
    return currentCanal;
}
void CustomGraph::setCurrentCanal(QString canal) {
    currentCanal = canal;
}

int CustomGraph::getComboSelected() {
    return comboSelected;
}

void CustomGraph::setComboSelected(int combo) {
    comboSelected = combo;
}

void CustomGraph::setBufferSize(int buffer) {
    buffered2DSamples->setBufferSize(buffer);
}

void CustomGraph::resetBuffer() {
    buffered2DSamples->reset();
}
