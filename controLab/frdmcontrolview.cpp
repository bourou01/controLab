#include "frdmcontrolview.h"
#include "ui_frdmcontrolview.h"

#include <QDebug>

FRDMControlView::FRDMControlView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FRDMControlView)
{
    ui->setupUi(this);

    //temperature = {QString("temperature"), 27.0f, 20.0f, 30.0f};
    temperature.name = QString("temperature");
    temperature.value = 27;
    temperature.min = 0;
    temperature.max = 50;
    //pressure = {QString("pressure") 5.0f, 0.0f, 10.0f};
    pressure.name = QString("pressure");
    pressure.value = 5;
    pressure.min = 0;
    pressure.max = 30;
    //dimmer0 = {QString("dimmer0"), 50.0f, 0.0f, 100.0f};
    dimmer0.name = QString("dimmer0");
    dimmer0.value = 50;
    /*
    dimmer0.min = 0;
    dimmer0.max = 256;
    */
    dimmer0.min = -1000;
    dimmer0.max = 1000;


    setRange(0, 256);

    /// virtuals
    virtualSP.name = QString("virtualSP");
    virtualSP.value = 111;
    virtualSP.min = -1000;
    virtualSP.max = 1000;

    virtualSensor.name = QString("virtualSensor");
    virtualSensor.value = 1.0;
    virtualSensor.min = -1000;
    virtualSensor.max = 1000;



    ui->setPointSpinBox->setValue(temperature.value);
    ui->setPointSlider->setValue(ui->setPointSpinBox->value());

    ui->sourcesList->addItem("temperature");
    ui->sourcesList->addItem("dimmer0");
    ui->sourcesList->addItem("pressure");
    ui->sourcesList->addItem("virtualSP");
    ui->sourcesList->addItem("virtualSensor");
    ui->sourcesList->setCurrentIndex(1);

    connect(ui->sourcesList, SIGNAL(currentTextChanged(const QString &)), SLOT(onRessourceListChanged(const QString &)));
    //connect(ui->setPointSpinBox, SIGNAL(valueChanged(double)), SLOT(onSetPointValueChanged(double)));



    connect(ui->setPointSlider, SIGNAL(sliderReleased()), SLOT(onSetPointSliderLevelReleased()));
    connect(ui->setPointSpinBox, SIGNAL(valueChanged(int)),ui->setPointSlider, SLOT(setValue(int)));
    connect(ui->setPointSlider, SIGNAL(valueChanged(int)),ui->setPointSpinBox, SLOT(setValue(int)));

    connect(ui->setPointSpinBox, SIGNAL(valueChanged(int)), SLOT(onSetPointValueChanged(int)));

}

void FRDMControlView::onSetPointSliderLevelReleased() {
    //ui->setPointSpinBox
    onSetPointValueChanged(ui->setPointSpinBox->value());
}


void FRDMControlView::onSetPointValueChanged(int newValue) {
    if (ui->sourcesList->currentText().toLatin1() == "temperature") {
        temperature.value = newValue;
        serialConfigurationView->performRequest(QString("set temperature %1").arg(QString::number(newValue)));
    } else if (ui->sourcesList->currentText().toLatin1() == "dimmer0") {
        dimmer0.value = newValue;
        serialConfigurationView->performRequest(QString("set dimmer0 %1").arg(QString::number(newValue)));
    } else if (ui->sourcesList->currentText().toLatin1() == "pressure") {
        pressure.value =  newValue;
        serialConfigurationView->performRequest(QString("set pressure %1").arg(QString::number(newValue)));


    } else if (ui->sourcesList->currentText().toLatin1() == "virtualSP") {
        virtualSP.value = newValue;
        serialConfigurationView->performRequest(QString("set virtualSP %1").arg(QString::number(newValue)));
    } else if (ui->sourcesList->currentText().toLatin1() == "virtualSensor") {
        virtualSensor.value =  newValue;
        serialConfigurationView->performRequest(QString("set virtualSensor %1").arg(QString::number(newValue)));
    }




}

void FRDMControlView::setSerialConfigurationView(SerialConfigurationView *newSCV) {
    serialConfigurationView = newSCV;
}

void FRDMControlView::onRessourceListChanged(const QString &ressourceName) {

    if (ui->sourcesList->currentText().toLatin1() == "temperature") {
        serialConfigurationView->performRequest(QString("get temperature"));
        setRange(temperature.min, temperature.max);
    } else if (ui->sourcesList->currentText().toLatin1() == "dimmer0") {
        serialConfigurationView->performRequest(QString("get dimmer0"));
        setRange(dimmer0.min, dimmer0.max);
    } else if (ui->sourcesList->currentText().toLatin1() == "pressure") {
        serialConfigurationView->performRequest(QString("get pressure"));
        setRange(pressure.min, pressure.max);
    } else if (ui->sourcesList->currentText().toLatin1() == "virtualSP") {
        serialConfigurationView->performRequest(QString("get virtualSP"));
        setRange(virtualSP.min, virtualSP.max);
    } else if (ui->sourcesList->currentText().toLatin1() == "virtualSensor") {
        serialConfigurationView->performRequest(QString("get virtualSensor"));
        setRange(virtualSensor.min, virtualSensor.max);
    }
}

void FRDMControlView::setRange(double min, double max) {

    ui->setPointSpinBox->setRange(min, max);
    ui->setPointSlider->setRange(min, max);
}


void FRDMControlView::setTemperature(float nT) {
    temperature.value = nT;
    if (ui->sourcesList->currentText().toLatin1() == "temperature") {
        ui->setPointSpinBox->setValue(temperature.value);
    }
}
float FRDMControlView::getTemperature() {
    return temperature.value;
}
void FRDMControlView::setDimmer0(float nD0) {
    dimmer0.value = nD0;
    if (ui->sourcesList->currentText().toLatin1() == "dimmer0") {
        ui->setPointSpinBox->setValue(dimmer0.value);
    }
}
float FRDMControlView::getDimmer0() {
    return dimmer0.value;
}
void FRDMControlView::setPressure(float nP) {
    pressure.value = nP;
    if (ui->sourcesList->currentText().toLatin1() == "pressure") {
        ui->setPointSpinBox->setValue(pressure.value);
    }
}
float FRDMControlView::getPressure() {
    return pressure.value;
}


/// virtual ressources for test

void FRDMControlView::setVirtualSP(float nSP) {
    virtualSP.value = nSP;
    if (ui->sourcesList->currentText().toLatin1() == "virtualSP") {
        ui->setPointSpinBox->setValue(virtualSP.value);
    }
}
float FRDMControlView::getVirtualP() {
    return virtualSP.value;
}

void FRDMControlView::setVirtualSensor(float nVS) {
    virtualSensor.value = nVS;
    if (ui->sourcesList->currentText().toLatin1() == "virtualSensor") {
        ui->setPointSpinBox->setValue(virtualSensor.value);
    }
}
float FRDMControlView::getVirtualSensor() {
    return virtualSensor.value;
}

FRDMControlView::~FRDMControlView()
{
    delete ui;
}
