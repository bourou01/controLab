#ifndef SERIALCOMDIALOG_H
#define SERIALCOMDIALOG_H

#include <QDialog>
#include "customplotdialog.h"

namespace Ui {
class SerialComDialog;
}
class QTimer;
class QextSerialPort;
class QextSerialEnumerator;

class SerialComDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SerialComDialog(QWidget *parent = 0);
    ~SerialComDialog();

protected:
    void changeEvent(QEvent *e);

private Q_SLOTS:
    void onPortNameChanged(const QString &name);
    void onBaudRateChanged(int idx);
    void onParityChanged(int idx);
    void onDataBitsChanged(int idx);
    void onStopBitsChanged(int idx);
    void onQueryModeChanged(int idx);
    void onTimeoutChanged(int val);
    void onOpenCloseButtonClicked();
    void onSendButtonClicked();
    void onReadyRead();
    void onPortAddedOrRemoved();
    void onPlotButtonClicked();


Q_SIGNALS:
     void datasReady(QString *);
     void plotButtonHasBeenClicked();
     void onCloseButtonClicked();

private:
    Ui::SerialComDialog *ui;
    QTimer *timer;
    QextSerialPort *port;
    QextSerialEnumerator *enumerator;

    QString *datasBuffer;


public:
    QVector <CustomPlotDialog *> *plots;



};

#endif // SERIALCOMDIALOG_H
