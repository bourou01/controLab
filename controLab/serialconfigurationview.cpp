#include "serialconfigurationview.h"
#include "ui_serialconfigurationview.h"


#include "ui_serialcomdialog.h"
#include "qextserialport.h"
#include "qextserialenumerator.h"
#include <QtCore>

#include "frdmjsonparser.h"
#include <QEvent>
#include <QKeyEvent>


SerialConfigurationView::SerialConfigurationView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialConfigurationView)
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
    ui->baudRateBox->addItem("38400", BAUD38400);
    ui->baudRateBox->addItem("57600", BAUD57600);
    ui->baudRateBox->addItem("115200", BAUD115200);
    ui->baudRateBox->setCurrentIndex(7);

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
    timer->setInterval(40);
    //! [1]
   //PortSettings settings = {BAUD57600, DATA_8, PAR_NONE, STOP_1, FLOW_OFF, 10};

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
    connect(timer, SIGNAL(timeout()), SLOT(onReadyRead()));
    connect(port, SIGNAL(readyRead()), SLOT(onReadyRead()));

    connect(enumerator, SIGNAL(deviceDiscovered(QextPortInfo)), SLOT(onPortAddedOrRemoved()));
    connect(enumerator, SIGNAL(deviceRemoved(QextPortInfo)), SLOT(onPortAddedOrRemoved()));


    setWindowTitle(tr("Aquarium Control Serial Port"));

    //port->setTimeout(15);

    //ui->timeOutSpinBox->setValue(15);

    /// configure textEdit
    ui->message->installEventFilter(this);


    //request = new QString("exec sensors");

}


void SerialConfigurationView::performRequest(QString r) {
    request = r;
    request.append(" \n");
    SerialConfigurationView::transmitMsg();
}



bool SerialConfigurationView::eventFilter(QObject *object, QEvent *event)
{
    if (object == ui->message && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Return)
        {
            // Special tab handling
            //qDebug("Enter Key Pressed...");

            /// transmission
            if (ui->message->text().length() > 0) {
                //
                performRequest(ui->message->text());
                //appendEndCmd();
                transmitMsg();
                ui->message->clear();
            }
            return true;
        }
        else
        {
            return QWidget::eventFilter(object, event);
        }
    }
    else
    {
        return QWidget::eventFilter(object, event);
    }
}

void SerialConfigurationView::transmitMsg()
{
    //int i = port->write(ui->message->text().toLatin1());
    int i = port->write(request.toLatin1());
    qDebug("trasmitted : %d", i);

    qDebug() << "message : " << request.toLatin1();

    //receiveMsg();
}



void SerialConfigurationView::receiveMsg()
{
    char buff[1024];
    int numBytes;

    numBytes = port->bytesAvailable();
    if(numBytes > 1024)
        numBytes = 1024;

    int i = port->read(buff, numBytes);
    if (i != -1)
        buff[i] = '\0';
    else
        buff[0] = '\0';
    QString msg = QLatin1String(buff);

    ui->received_msg->append(msg);
    ui->received_msg->ensureCursorVisible();
    qDebug("bytes available: %d", numBytes);
    qDebug("received: %d", i);
}

void SerialConfigurationView::onReadyRead()
{
    char buff[1024];
    int numBytes;
    numBytes = port->bytesAvailable();
    if (numBytes) {
        if(numBytes > 1024)
            numBytes = 1024;

        int i = port->read(buff, numBytes);
        if (i != -1)
            buff[i] = '\0';
        else
            buff[0] = '\0';
        QString msg = QLatin1String(buff);

        datasReady(QString(msg));

        ui->received_msg->append(msg);
        ui->received_msg->ensureCursorVisible();
        qDebug("bytes available: %d", numBytes);
        qDebug("received: %d", i);
    }


    //receiveMsg();
}

void SerialConfigurationView::appendCR()
{
    ui->message->insert(QLatin1String("\x0D"));
}

void SerialConfigurationView::appendLF()
{
    ui->message->insert(QLatin1String("\x0A"));
}
void SerialConfigurationView::appendEndCmd() {
    ui->message->insert(" \n");
}


SerialConfigurationView::~SerialConfigurationView()
{
    delete ui;
    delete port;
}



void SerialConfigurationView::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void SerialConfigurationView::onPortNameChanged(const QString & /*name*/)
{
    if (port->isOpen()) {
        port->close();
        ui->led->turnOff();
    }
}
//! [2]
void SerialConfigurationView::onBaudRateChanged(int idx)
{
    port->setBaudRate((BaudRateType)ui->baudRateBox->itemData(idx).toInt());
}

void SerialConfigurationView::onParityChanged(int idx)
{
    port->setParity((ParityType)ui->parityBox->itemData(idx).toInt());
}

void SerialConfigurationView::onDataBitsChanged(int idx)
{
    port->setDataBits((DataBitsType)ui->dataBitsBox->itemData(idx).toInt());
}

void SerialConfigurationView::onStopBitsChanged(int idx)
{
    port->setStopBits((StopBitsType)ui->stopBitsBox->itemData(idx).toInt());
}

void SerialConfigurationView::onQueryModeChanged(int idx)
{
    port->setQueryMode((QextSerialPort::QueryMode)ui->queryModeBox->itemData(idx).toInt());
}

void SerialConfigurationView::onTimeoutChanged(int val)
{
    port->setTimeout(val);
}
//! [2]
//! [3]
void SerialConfigurationView::onOpenCloseButtonClicked()
{
    if (!port->isOpen()) {
        port->setPortName(ui->portBox->currentText());
        port->open(QIODevice::ReadWrite);
    }
    else {
        timer->stop();

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


void SerialConfigurationView::onPortAddedOrRemoved()
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

void SerialConfigurationView::onPlotButtonClicked() {
    plotButtonHasBeenClicked();
}
