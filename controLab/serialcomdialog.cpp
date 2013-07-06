#include "serialcomdialog.h"
#include "ui_serialcomdialog.h"
#include "qextserialport.h"
#include "qextserialenumerator.h"
#include <QtCore>

#include "frdmjsonparser.h"
#include "customplotdialog.h"

#include <iostream>

SerialComDialog::SerialComDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SerialComDialog)
{
    ui->setupUi(this);

    //! [0]
    foreach (QextPortInfo info, QextSerialEnumerator::getPorts())
        ui->portBox->addItem(info.portName);
    //make sure user can input their own port name!
    ui->portBox->setEditable(true);

    ui->baudRateBox->addItem("1200", BAUD1200);
    ui->baudRateBox->addItem("2400", BAUD2400);
    ui->baudRateBox->addItem("4800", BAUD4800);
    ui->baudRateBox->addItem("9600", BAUD9600);
    ui->baudRateBox->addItem("19200", BAUD19200);
    ui->baudRateBox->addItem("115200", BAUD115200);

    ui->baudRateBox->setCurrentIndex(5);

    ui->parityBox->addItem("NONE", PAR_NONE);
    ui->parityBox->addItem("ODD", PAR_ODD);
    ui->parityBox->addItem("EVEN", PAR_EVEN);

    ui->dataBitsBox->addItem("5", DATA_5);
    ui->dataBitsBox->addItem("6", DATA_6);
    ui->dataBitsBox->addItem("7", DATA_7);
    ui->dataBitsBox->addItem("8", DATA_8);
    ui->dataBitsBox->setCurrentIndex(3);

    ui->stopBitsBox->addItem("1", STOP_1);
    ui->stopBitsBox->addItem("2", STOP_2);

    ui->queryModeBox->addItem("Polling", QextSerialPort::Polling);
    ui->queryModeBox->addItem("EventDriven", QextSerialPort::EventDriven);
    //! [0]

    ui->led->turnOff();

    timer = new QTimer(this);
    //timer->setInterval(40);
    timer->setInterval(40);
    //! [1]
   //PortSettings settings = {BAUD9600, DATA_8, PAR_NONE, STOP_1, FLOW_OFF, 10};

    PortSettings settings = {BAUD115200, DATA_8, PAR_NONE, STOP_1, FLOW_OFF, 10};

     port = new QextSerialPort(ui->portBox->currentText(), settings, QextSerialPort::Polling);

    //! [1]

    enumerator = new QextSerialEnumerator(this);
    enumerator->setUpNotifications();

    connect(ui->baudRateBox, SIGNAL(currentIndexChanged(int)), SLOT(onBaudRateChanged(int)));
    connect(ui->parityBox, SIGNAL(currentIndexChanged(int)), SLOT(onParityChanged(int)));
    connect(ui->dataBitsBox, SIGNAL(currentIndexChanged(int)), SLOT(onDataBitsChanged(int)));
    connect(ui->stopBitsBox, SIGNAL(currentIndexChanged(int)), SLOT(onStopBitsChanged(int)));
    connect(ui->queryModeBox, SIGNAL(currentIndexChanged(int)), SLOT(onQueryModeChanged(int)));


    connect(ui->timeOutSpinBox, SIGNAL(valueChanged(int)), SLOT(onTimeoutChanged(int)));
    connect(ui->portBox, SIGNAL(editTextChanged(QString)), SLOT(onPortNameChanged(QString)));
    connect(ui->openCloseButton, SIGNAL(clicked()), SLOT(onOpenCloseButtonClicked()));
    connect(ui->sendButton, SIGNAL(clicked()), SLOT(onSendButtonClicked()));
    connect(timer, SIGNAL(timeout()), SLOT(onReadyRead()));
    connect(port, SIGNAL(readyRead()), SLOT(onReadyRead()));

    connect(enumerator, SIGNAL(deviceDiscovered(QextPortInfo)), SLOT(onPortAddedOrRemoved()));
    connect(enumerator, SIGNAL(deviceRemoved(QextPortInfo)), SLOT(onPortAddedOrRemoved()));

    connect(ui->plotButton, SIGNAL(clicked()), SLOT(onPlotButtonClicked()));

    setWindowTitle(tr("Aquarium Control Serial Port"));

    datasBuffer = new QString();


    //port->setTimeout(15);

    //ui->timeOutSpinBox->setValue(15);


}

void SerialComDialog::onPlotButtonClicked() {
    plotButtonHasBeenClicked();
}



SerialComDialog::~SerialComDialog()
{
    delete ui;
    delete port;
}

void SerialComDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void SerialComDialog::onPortNameChanged(const QString & /*name*/)
{
    if (port->isOpen()) {
        port->close();
        ui->led->turnOff();
    }
}
//! [2]
void SerialComDialog::onBaudRateChanged(int idx)
{
    port->setBaudRate((BaudRateType)ui->baudRateBox->itemData(idx).toInt());
}

void SerialComDialog::onParityChanged(int idx)
{
    port->setParity((ParityType)ui->parityBox->itemData(idx).toInt());
}

void SerialComDialog::onDataBitsChanged(int idx)
{
    port->setDataBits((DataBitsType)ui->dataBitsBox->itemData(idx).toInt());
}

void SerialComDialog::onStopBitsChanged(int idx)
{
    port->setStopBits((StopBitsType)ui->stopBitsBox->itemData(idx).toInt());
}

void SerialComDialog::onQueryModeChanged(int idx)
{
    port->setQueryMode((QextSerialPort::QueryMode)ui->queryModeBox->itemData(idx).toInt());
}

void SerialComDialog::onTimeoutChanged(int val)
{
    port->setTimeout(val);
}
//! [2]
//! [3]
void SerialComDialog::onOpenCloseButtonClicked()
{
    if (!port->isOpen()) {
        port->setPortName(ui->portBox->currentText());
        port->open(QIODevice::ReadWrite);
    }
    else {
        port->close();
    }

    //If using polling mode, we need a QTimer
    if (port->isOpen() && port->queryMode() == QextSerialPort::Polling)
        timer->start();
    else
        timer->stop();

    //update led's status
    ui->led->turnOn(port->isOpen());
}
//! [3]
//! [4]
void SerialComDialog::onSendButtonClicked()
{
    if (port->isOpen() && !ui->sendEdit->toPlainText().isEmpty())
        port->write(ui->sendEdit->toPlainText().toLatin1());
}

void SerialComDialog::onReadyRead()
{


    if (port->bytesAvailable()) {
        QByteArray bytes = QByteArray(port->readAll());


        ui->recvEdit->moveCursor(QTextCursor::End);
        ui->recvEdit->insertPlainText(QString::fromLatin1(bytes));

        datasReady(new QString(bytes));


    }
}

void SerialComDialog::onPortAddedOrRemoved()
{
    QString current = ui->portBox->currentText();

    ui->portBox->blockSignals(true);
    ui->portBox->clear();
    foreach (QextPortInfo info, QextSerialEnumerator::getPorts())
        ui->portBox->addItem(info.portName);

    ui->portBox->setCurrentIndex(ui->portBox->findText(current));

    ui->portBox->blockSignals(false);
}

//! [4]


