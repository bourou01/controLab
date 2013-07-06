/* qesptest.h
**************************************/
#ifndef _QESPTEST_H_
#define _QESPTEST_H_

#include <QWidget>


#include <QDebug>


#include <QEvent>
#include <QKeyEvent>

#include "qextserialenumerator.h"

class QLineEdit;
class QTextEdit;
class QextSerialPort;
class QSpinBox;

class QespTest :  public QWidget
{
    Q_OBJECT
public:
    QespTest(QWidget *parent=0);

    virtual ~QespTest();

private:
    QLineEdit *message;
    QSpinBox *delaySpinBox;
    QTextEdit *received_msg;
    QextSerialPort *port;


    QTimer *timer;
    QextSerialEnumerator *enumerator;

private:
    /// port parameters
    ///
    QString *portName;

private slots:
    void transmitMsg();
    void receiveMsg();
    void appendCR();
    void appendLF();
    void appendEndCmd();
    void closePort();
    void openPort();


private Q_SLOTS:
    /// protocoles
    void onReadyRead();
    void onPortAddedOrRemoved();


protected:
    bool eventFilter(QObject *object, QEvent *event);
};

#endif
