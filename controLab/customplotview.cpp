#include "customplotview.h"
#include "ui_customplotview.h"

#include <QDebug>
#include <QTimer>

#include "frdmjsonparser.h"



CustomPlotView::CustomPlotView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomPlotView)
{
    ui->setupUi(this);

    ///// Configure lineStyleComboBox
        ui->lineStyleComboBox->addItem("None", QCPGraph::lsNone);
        ui->lineStyleComboBox->addItem("Line", QCPGraph::lsLine);
        ui->lineStyleComboBox->addItem("StepLeft", QCPGraph::lsStepLeft);
        ui->lineStyleComboBox->addItem("StepRight", QCPGraph::lsStepRight);
        ui->lineStyleComboBox->addItem("StepCenter", QCPGraph::lsStepCenter);
        ui->lineStyleComboBox->addItem("Impulse", QCPGraph::lsImpulse);

    ///// Configure colorComboBox
        myColors.push_back(QColor(Qt::black));
        myColors.push_back(QColor(Qt::darkGray));
        myColors.push_back(QColor(Qt::gray));
        myColors.push_back(QColor(Qt::lightGray));
        myColors.push_back(QColor(Qt::red));
        myColors.push_back(QColor(Qt::green));
        myColors.push_back(QColor(Qt::blue));
        myColors.push_back(QColor(Qt::cyan));
        myColors.push_back(QColor(Qt::magenta));
        myColors.push_back(QColor(Qt::yellow));
        myColors.push_back(QColor(Qt::darkRed));
        myColors.push_back(QColor(Qt::darkGreen));
        myColors.push_back(QColor(Qt::darkBlue));
        myColors.push_back(QColor(Qt::darkCyan));
        myColors.push_back(QColor(Qt::darkMagenta));
        myColors.push_back(QColor(Qt::darkYellow));

        ui->colorComboBox->addItem("black", "");
        ui->colorComboBox->addItem("darkGray", "");
        ui->colorComboBox->addItem("gray", "");
        ui->colorComboBox->addItem("lightGray", "");
        ui->colorComboBox->addItem("red", "");
        ui->colorComboBox->addItem("green", "");
        ui->colorComboBox->addItem("blue", "");
        ui->colorComboBox->addItem("cyan", "");
        ui->colorComboBox->addItem("magenta", "");
        ui->colorComboBox->addItem("yellow", "");
        ui->colorComboBox->addItem("darkRed", "");
        ui->colorComboBox->addItem("darkGreen", "");
        ui->colorComboBox->addItem("darkBlue", "");
        ui->colorComboBox->addItem("darkCyan", "");
        ui->colorComboBox->addItem("darkMagenta", "");
        ui->colorComboBox->addItem("darkYellow", "");

    ///// Configure scatterStyleComboBox
    /*
        ui->scatterStyleComboBox->addItem("None", QCPScatterStyle::ssNone);
        ui->scatterStyleComboBox->addItem("Dot", QCPScatterStyle::ssDot);
        ui->scatterStyleComboBox->addItem("Cross", QCPScatterStyle::ssCross);
        ui->scatterStyleComboBox->addItem("Plus", QCPScatterStyle::ssPlus);
        ui->scatterStyleComboBox->addItem("Circle", QCPScatterStyle::ssCircle);
        ui->scatterStyleComboBox->addItem("Disc", QCPScatterStyle::ssDisc);
        ui->scatterStyleComboBox->addItem("Square", QCPScatterStyle::ssSquare);
        ui->scatterStyleComboBox->addItem("Diamond", QCPScatterStyle::ssDiamond);
        ui->scatterStyleComboBox->addItem("Star", QCPScatterStyle::ssStar);
        ui->scatterStyleComboBox->addItem("Triangle", QCPScatterStyle::ssTriangle);
        ui->scatterStyleComboBox->addItem("TriangleInverted", QCPScatterStyle::ssTriangleInverted);
        ui->scatterStyleComboBox->addItem("CrossSquare", QCPScatterStyle::ssCrossSquare);
        ui->scatterStyleComboBox->addItem("PlusSquare", QCPScatterStyle::ssPlusSquare);
        ui->scatterStyleComboBox->addItem("Peace", QCPScatterStyle::ssPeace);
        ui->scatterStyleComboBox->addItem("Pixmap", QCPScatterStyle::ssPixmap);
        ui->scatterStyleComboBox->addItem("Custom", QCPScatterStyle::ssCustom);
    */


    ///// canalsListComboBox Configuration
        connect(ui->canalsListComboBox, SIGNAL(currentIndexChanged(int)), SLOT(onCanalsListChanged(int)));

    ///// bouton
        connect(ui->addPlotButton, SIGNAL(clicked()), this, SLOT(onAddPlotButtonClicked()));
        connect(ui->deletePlotButton, SIGNAL(clicked()), this, SLOT(onDeletePlotButtonClicked()));

    ///// comboBoxes
        connect(ui->canalsListComboBox, SIGNAL(currentIndexChanged(int)), SLOT(onCanalsListChanged(int)));
        connect(ui->graphIdComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onGraphIdChanged(int)));
        //connect(ui->scatterStyleComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onScatterStyleComboBoxChanged(int)));
        connect(ui->lineStyleComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onLineStyleComboBoxChanged(int)));
        connect(ui->colorComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onColorComboBoxChanged(int)));

    ///// checkbox
        connect(ui->autoscaleCheckBox, SIGNAL(stateChanged(int)), this, SLOT(onAutoscaleCheckBoxChanged(int)));

        ui->autoscaleCheckBox->setChecked(true);
        customGraphs = QVector<CustomGraph *>();

    ///// spinBox
        ui->bufferSizeSpinBox->setMinimum(5);
        ui->bufferSizeSpinBox->setValue(50);
        ui->bufferSizeSpinBox->setMaximum(200);

        //buffered2DSamples = new Buffered2DSamples(50);
        //ui->customPlot->addGraph();
        //ui->customPlot->graph()->setName(QString("New graph %1").arg(ui->customPlot->graphCount()-1));

    ///// configure CustomPlot
        CustomPlotView::configureCustomPlot();

        //canal ="1";
    ///// push default graph in CustomPlot
        CustomPlotView::insertNewGraph();
        CustomPlotView::updateGraphsIds();

    ///// init time synchronisation
        TIME_SYNCHRONISATION = 0;


}





void CustomPlotView::configureCustomPlot() {
    /*
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->customPlot->axisRect()->setupFullAxesBox(true);
*/
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
    ui->customPlot->xAxis->setRange(-8, 8);
    ui->customPlot->yAxis->setRange(-5, 5);
    ui->customPlot->axisRect()->setupFullAxesBox();

    ui->customPlot->plotLayout()->insertRow(0);
    ui->customPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(ui->customPlot, "Real time Plotting"));

    ui->customPlot->xAxis->setLabel("x Axis");
    ui->customPlot->yAxis->setLabel("y Axis");
    ui->customPlot->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->legend->setSelectedFont(legendFont);
    ui->customPlot->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items
}


void CustomPlotView::updatePlotsFromNotification(QString toParse) {


    FRDMJSONParser::getInstance()->setJson(&toParse);


    double last_time = FRDMJSONParser::getInstance()->xAtPort("1");

    /// to not getting the same time synchronisation
    if (!(last_time >CustomPlotView::TIME_SYNCHRONISATION))
        return;

    //qDebug() << (last_time >CustomPlotView::TIME_SYNCHRONISATION);


    if (last_time > TIME_SYNCHRONISATION)
        TIME_SYNCHRONISATION = last_time;


    QList<QString> listen =  FRDMJSONParser::getInstance()->ports();
    CustomPlotView::updateCanalsListWith(listen);
    for (int i=0; i<ui->customPlot->graphCount(); i++) {
        CustomGraph *customGraph = this->customGraphs.at(i);

        //// update the bufferSize
        customGraph->setBufferSize(ui->bufferSizeSpinBox->value());

        double frdmX = FRDMJSONParser::getInstance()->xAtPort(customGraph->getCurrentCanal());
        double frdmY = FRDMJSONParser::getInstance()->yAtPort(customGraph->getCurrentCanal());
        QString legend = FRDMJSONParser::getInstance()->nameAtPort(customGraph->getCurrentCanal());

        customGraph->updateWith(frdmX, frdmY);
        QCPGraph * currentGraph = ui->customPlot->graph(i);
        currentGraph->setData(*customGraph->getXVector(), *customGraph->getYVector());
        currentGraph->setName(legend);
    }
    if (ui->autoscaleCheckBox->checkState() == Qt::Checked) {
        ui->customPlot->rescaleAxes();
    }

    ui->customPlot->replot();
}

//////////////////////////// Settings Delegates ////////////////////////////
/// \brief --
/// \param --
///
void CustomPlotView::onScatterStyleComboBoxChanged(int index) {
    QCPGraph * currentGraph = ui->customPlot->graph(ui->graphIdComboBox->currentIndex());
    //currentGraph->setScatterStyle((QCPScatterStyle::ScatterShape)ui->scatterStyleComboBox->itemData(index).toInt());
}
void CustomPlotView::onLineStyleComboBoxChanged(int index) {
    QCPGraph * currentGraph = ui->customPlot->graph(ui->graphIdComboBox->currentIndex());
    currentGraph->setLineStyle((QCPGraph::LineStyle)ui->lineStyleComboBox->itemData(index).toInt());
}
void CustomPlotView::onColorComboBoxChanged(int index) {
    QCPGraph * currentGraph = ui->customPlot->graph(ui->graphIdComboBox->currentIndex());
    QPen graphPen;
    graphPen.setColor(myColors.at(index));
    //qDebug() << (QColor)ui->colorComboBox->itemData(index).Color;
    //graphPen.setWidthF(rand()/(double)RAND_MAX*2+1);
    currentGraph->setPen(graphPen);
    CustomGraph *customGraph = customGraphs.at(ui->graphIdComboBox->currentIndex());
    customGraph->setColorIndex(index);
}
void CustomPlotView::onAutoscaleCheckBoxChanged(int choice) {

}

//////////////////////////// Graph Selection Delegates ////////////////////////////
/// \brief --
/// \param --
///
void CustomPlotView::onGraphIdChanged(int index) {
    if (index != -1) {
        CustomGraph *selectedGraph =customGraphs.at(index);
        ui->canalsListComboBox->setCurrentText(selectedGraph->getCurrentCanal());

        QCPGraph * currentGraph = ui->customPlot->graph(ui->graphIdComboBox->currentIndex());

        //ui->scatterStyleComboBox->setCurrentIndex((int)currentGraph->scatterStyle().shape());
        ui->lineStyleComboBox->setCurrentIndex((int)currentGraph->lineStyle());
        ui->colorComboBox->setCurrentIndex(selectedGraph->getColorIndex());
    }
}

void CustomPlotView::onAddPlotButtonClicked() {
    CustomPlotView::insertNewGraph();
    CustomPlotView::updateGraphsIds();
}

void CustomPlotView::onDeletePlotButtonClicked() {
    int index = ui->graphIdComboBox->currentIndex();
    if (index > 0) {
        qDebug()<< "delete : " << ui->graphIdComboBox->currentIndex();
        customGraphs.remove(ui->graphIdComboBox->currentIndex());
        ui->customPlot->removeGraph(ui->graphIdComboBox->currentIndex());
        ui->graphIdComboBox->removeItem(index);
    }
}


int CustomPlotView::insertNewGraph() {

    CustomGraph *customGraph = new CustomGraph();

    customGraph->setCurrentCanal("1");

    customGraph->setIndex(ui->customPlot->graphCount());
    customGraphs.push_back(customGraph);

    ui->customPlot->addGraph();
    ui->customPlot->graph()->setScatterStyle(QCPScatterStyle::ssDisc);
    ui->customPlot->graph()->setName(QString("New graph %1").arg(ui->customPlot->graphCount()-1));

    return 0;
}

void CustomPlotView::updateGraphsIds() {
   int i = customGraphs.size() - 1;
   ui->graphIdComboBox->addItem(QString("%1").arg(QString::number(i)), QString("%1").arg(QString::number(i)));
}

//////////////////////////// Canals Delegates  ////////////////////////////
/// \brief --
/// \param --
///
void CustomPlotView::onCanalsListChanged(int selected) {
   //comboSelected = selected;

   CustomGraph *selectedGraph = customGraphs.at(ui->graphIdComboBox->currentIndex());
   selectedGraph->setCurrentCanal(ui->canalsListComboBox->currentText());

   onCanalsListComboBoxChanged(this);
}

void CustomPlotView::updateCanalsListWith(QList<QString> liste) {
    canals = liste;

    if (ui->canalsListComboBox->count()<canals.size()) {
        for (int i=0; i<liste.size(); i++) {
            ui->canalsListComboBox->addItem(liste.at(i), liste.at(i));
        }
    }

    /*
    if (comboSelected<=ui->canalsListComboBox->count())
            ui->canalsListComboBox->setCurrentIndex(comboSelected);
            */
}

//////////////////////////// Methods  ////////////////////////////
/// \brief --
/// \param --
///
/*
void CustomPlotView::setCanal(QString newCanal) {
    canal = newCanal;
}
QString CustomPlotView::getCanal() {
    //return canal;
    if (canals.size()> comboSelected)
        return canal = canals.at(comboSelected);
    else return "1";
}

int CustomPlotView::getComboSelected() {
    return comboSelected;
}

QVector<double> * CustomPlotView::getXVector() {
    return buffered2DSamples->getXVector();
}
QVector<double> * CustomPlotView::getYVector() {
     return buffered2DSamples->getYVector();
}
*/


void CustomPlotView::closeEvent(QCloseEvent *event) {
    /*
if (maybeSave()) {
writeSettings();
    event->accept(); // close window
} else {
    event->ignore(); // keep window
}
*/
    close(this);
    event->accept(); // close window

}

/*
void CustomPlotView::updateWith(double x, double y) {

    buffered2DSamples->insert2DSample(x, y);
    if (buffered2DSamples->getSize()>0) {
        ui->customPlot->graph()->setData(*buffered2DSamples->getXVector(), *buffered2DSamples->getYVector());


        ui->customPlot->rescaleAxes();
        ui->customPlot->replot();
    }
}

void CustomPlotView::setTarget(int cible) {
    target = cible;
    this->setWindowTitle(QString("New graph %1").arg(this->getTarget()));
}


///////
/// \brief CustomPlotView::getTarget
/// \return
///
int CustomPlotView::getTarget() {
    return target;
}

*/
CustomPlotView::~CustomPlotView()
{
    delete ui;
   // delete buffered2DSamples;

    for (int i=0; i<customGraphs.size(); i++) {
        delete customGraphs.at(i);
    }
}
