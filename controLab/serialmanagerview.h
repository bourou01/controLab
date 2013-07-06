#ifndef SERIALMANAGERVIEW_H
#define SERIALMANAGERVIEW_H


#include <QWidget>

#include <QDebug>


#include <QEvent>
#include <QKeyEvent>

#include "qextserialenumerator.h"

class QLineEdit;
class QTextEdit;
class QextSerialPort;
class QSpinBox;

class SerialManagerView :  public QWidget
{
    Q_OBJECT
public:
    SerialManagerView(QWidget *parent=0);

    virtual ~SerialManagerView();

private: // UI
    QLineEdit *message;
    QSpinBox *delaySpinBox;
    QTextEdit *received_msg;
    QextSerialPort *port;
    QextSerialEnumerator *enumerator;

    QTimer *timer;

    void setupGUI();

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

#endif // SERIALMANAGERVIEW_H

