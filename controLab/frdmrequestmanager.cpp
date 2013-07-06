#include "frdmrequestmanager.h"

FRDMRequestManager::FRDMRequestManager()
{

}

void FRDMRequestManager::performRequestWith(QString *req) {
    request = req;

}


FRDMRequestManager::~FRDMRequestManager()
{
    delete port;
}



void FRDMRequestManager::transmitMsg()
{
    int i = port->write(message->text().toLatin1());
    qDebug("trasmitted : %d", i);
}

void FRDMRequestManager::receiveMsg()
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


void FRDMRequestManager::appendCR()
{
    message->insert(QLatin1String("\x0D"));
}

void FRDMRequestManager::appendLF()
{
    message->insert(QLatin1String("\x0A"));
}

void FRDMRequestManager::closePort()
{
    port->close();
    qDebug("is open: %d", port->isOpen());
}

void FRDMRequestManager::openPort()
{
    port->open(QIODevice::ReadWrite | QIODevice::Unbuffered);
    qDebug("is open: %d", port->isOpen());
}

