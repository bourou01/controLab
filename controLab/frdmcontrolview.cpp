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
    temperature.value = 27.0f;
    temperature.min = 20.0f;
    temperature.max = 30.0f;
    //pressure = {QString("pressure") 5.0f, 0.0f, 10.0f};
    pressure.name = QString("pressure");
    pressure.value = 5.0f;
    pressure.min = 0.0f;
    pressure.max = 10.0f;
    //dimmer0 = {QString("dimmer0"), 50.0f, 0.0f, 100.0f};
    dimmer0.name = QString("dimmer0");
    dimmer0.value = 50.0f;
    dimmer0.min = 0.0f;
    dimmer0.max = 100.0f;


    ui->setPointSpinBox->setRange(0, 100);
    ui->setPointSlider->setRange(0, 100);
    ui->setPointSpinBox->setValue(temperature.value);
    ui->setPointSlider->setValue(ui->setPointSpinBox->value());

    ui->sourcesList->addItem("temperature");
    ui->sourcesList->addItem("dimmer0");
    ui->sourcesList->addItem("pressure");


    connect(ui->sourcesList, SIGNAL(currentTextChanged(const QString &)), SLOT(onRessourceListChanged(const QString &)));
    connect(ui->setPointSpinBox, SIGNAL(valueChanged(double)), SLOT(onSetPointValueChanged(double)));



    connect(ui->setPointSlider, SIGNAL(sliderReleased()), SLOT(onSetPointSliderLevelReleased()));
    connect(ui->setPointSpinBox, SIGNAL(valueChanged(int)),ui->setPointSlider, SLOT(setValue(int)));
    connect(ui->setPointSlider, SIGNAL(valueChanged(int)),ui->setPointSpinBox, SLOT(setValue(int)));



}

void FRDMControlView::onSetPointSliderLevelReleased() {
    //ui->setPointSpinBox
    onSetPointValueChanged(ui->setPointSpinBox->value());
}


void FRDMControlView::onSetPointValueChanged(double newValue) {
    if (ui->sourcesList->currentText().toLatin1() == "temperature") {
        temperature.value = newValue;
        serialConfigurationView->performRequest(QString("set temperature %1").arg(QString::number(newValue)));
    } else if (ui->sourcesList->currentText().toLatin1() == "dimmer0") {
        dimmer0.value = newValue;
        serialConfigurationView->performRequest(QString("set dimmer0 %1").arg(QString::number(newValue)));
    } else if (ui->sourcesList->currentText().toLatin1() == "pressure") {
        pressure.value =  newValue;
        serialConfigurationView->performRequest(QString("set pressure %1").arg(QString::number(newValue)));
    }
}

void FRDMControlView::setSerialConfigurationView(SerialConfigurationView *newSCV) {
    serialConfigurationView = newSCV;
}

void FRDMControlView::onRessourceListChanged(const QString &ressourceName) {

    if (ui->sourcesList->currentText().toLatin1() == "temperature") {
        serialConfigurationView->performRequest(QString("get temperature"));
        //ui->setPointSpinBox->setValue(temperature.value);

    } else if (ui->sourcesList->currentText().toLatin1() == "dimmer0") {
        serialConfigurationView->performRequest(QString("get dimmer0"));
        //ui->setPointSpinBox->setValue(dimmer0.value);

    } else if (ui->sourcesList->currentText().toLatin1() == "pressure") {
        serialConfigurationView->performRequest(QString("get pressure"));
        //ui->setPointSpinBox->setValue(pressure.value);
    }

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

FRDMControlView::~FRDMControlView()
{
    delete ui;
}
