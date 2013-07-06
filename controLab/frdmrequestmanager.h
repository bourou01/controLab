#ifndef FRDMREQUESTMANAGER_H
#define FRDMREQUESTMANAGER_H

#include <QStandardItemModel>

#include <QObject>
#include "qextserialport.h"

#include <QLineEdit>
#include <QTextEdit>



class FRDMRequestManager : public QStandardItemModel
{
public:
    FRDMRequestManager();
    ~FRDMRequestManager();



    void performRequestWith(QString *req);

private slots:
    void transmitMsg();
    void receiveMsg();
    void appendCR();
    void appendLF();
    void closePort();
    void openPort();



Q_SIGNALS:



private:
    QextSerialPort *port;
    QString *request;
    QLineEdit *message;
    QTextEdit *received_msg;


};

#endif // FRDMREQUESTMANAGER_H
