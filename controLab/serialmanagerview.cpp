#include "serialmanagerview.h"

/* SerialManagerView.cpp
**************************************/
#include "SerialManagerView.h"
#include "qextserialport.h"
#include <QLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QTimer>
#include "qextserialenumerator.h"

#include <QIODevice>


SerialManagerView::SerialManagerView(QWidget *parent)
    : QWidget(parent)

{

    /// Timer for Polling
    timer = new QTimer(this);
    timer->setInterval(40);


    PortSettings settings = {BAUD115200, DATA_8, PAR_NONE, STOP_1, FLOW_OFF, 10};
    port = new QextSerialPort(QLatin1String("/dev/tty.usbmodem622"), settings, QextSerialPort::Polling);


    connect(timer, SIGNAL(timeout()), SLOT(onReadyRead()));
    /// protocoles
    connect(port, SIGNAL(readyRead()), SLOT(onReadyRead()));

    /// Enumerator
    ///
    enumerator = new QextSerialEnumerator(this);
    enumerator->setUpNotifications();
    connect(enumerator, SIGNAL(deviceDiscovered(QextPortInfo)), SLOT(onPortAddedOrRemoved()));
    connect(enumerator, SIGNAL(deviceRemoved(QextPortInfo)), SLOT(onPortAddedOrRemoved()));


    message = new QLineEdit(this);



    setupGUI();


}


void SerialManagerView::setupGUI() {






    // transmit receive
    QPushButton *transmitButton = new QPushButton(tr("Transmit"));
    connect(transmitButton, SIGNAL(clicked()), SLOT(transmitMsg()));
    QPushButton *receiveButton = new QPushButton(tr("Receive"));
    connect(receiveButton, SIGNAL(clicked()), SLOT(receiveMsg()));
    QHBoxLayout *trLayout = new QHBoxLayout;
    trLayout->addWidget(transmitButton);
    trLayout->addWidget(receiveButton);

    //CR LF
    QPushButton *CRButton = new QPushButton(tr("CR"));
    connect(CRButton, SIGNAL(clicked()), SLOT(appendCR()));
    QPushButton *LFButton = new QPushButton(tr("LF"));
    connect(LFButton, SIGNAL(clicked()), SLOT(appendLF()));
    QHBoxLayout *crlfLayout = new QHBoxLayout;
    crlfLayout->addWidget(CRButton);
    crlfLayout->addWidget(LFButton);

    //open close
    QPushButton *openButton = new QPushButton(tr("Open"));
    connect(openButton, SIGNAL(clicked()), SLOT(openPort()));
    QPushButton *closeButton = new QPushButton(tr("Close"));
    connect(closeButton, SIGNAL(clicked()), SLOT(closePort()));
    QHBoxLayout *ocLayout = new QHBoxLayout;
    ocLayout->addWidget(openButton);
    ocLayout->addWidget(closeButton);

    received_msg = new QTextEdit();

    QVBoxLayout *myVBox = new QVBoxLayout;
    myVBox->addWidget(message);
    myVBox->addLayout(crlfLayout);
    myVBox->addLayout(trLayout);
    myVBox->addLayout(ocLayout);
    myVBox->addWidget(received_msg);
    setLayout(myVBox);

    qDebug("isOpen : %d", port->isOpen());

    /// configure textEdit
    message->installEventFilter(this);
}

bool SerialManagerView::eventFilter(QObject *object, QEvent *event)
{
    if (object == message && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if (keyEvent->key() == Qt::Key_Return)
        {
            // Special tab handling
            //qDebug("Enter Key Pressed...");

            /// transmission
            if (message->text().length() > 0) {
                appendEndCmd();
                transmitMsg();
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

SerialManagerView::~SerialManagerView()
{
    delete port;
    port = NULL;
}

void SerialManagerView::transmitMsg()
{
    int i = port->write(message->text().toLatin1());
    qDebug("trasmitted : %d", i);

    qDebug() << "message : " << message->text().toLatin1();

    //receiveMsg();

    message->clear();
}

void SerialManagerView::receiveMsg()
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

    received_msg->append(msg);
    received_msg->ensureCursorVisible();
    qDebug("bytes available: %d", numBytes);
    qDebug("received: %d", i);
}

void SerialManagerView::onReadyRead()
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

        received_msg->append(msg);
        received_msg->ensureCursorVisible();
        qDebug("bytes available: %d", numBytes);
        qDebug("received: %d", i);
    }
}


void SerialManagerView::appendCR()
{
    message->insert(QLatin1String("\x0D"));
}

void SerialManagerView::appendLF()
{
    message->insert(QLatin1String("\x0A"));
}
void SerialManagerView::appendEndCmd() {
    message->insert(" \n");
}

void SerialManagerView::closePort()
{
    timer->stop();
    port->close();
    qDebug("is open: %d", port->isOpen());
}

void SerialManagerView::openPort()
{

    port->open(QIODevice::ReadWrite | QIODevice::Unbuffered);
    //If using polling mode, we need a QTimer
    if (port->isOpen() && port->queryMode() == QextSerialPort::Polling)
        timer->start();
    else
        timer->stop();

    qDebug("is open: %d", port->isOpen());
}


void SerialManagerView::onPortAddedOrRemoved()
{
    foreach (QextPortInfo info, QextSerialEnumerator::getPorts()) {
        qDebug() << "liste ports : " << info.portName;
    }

}
