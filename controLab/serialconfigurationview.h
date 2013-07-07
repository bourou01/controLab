#ifndef SERIALCONFIGURATIONVIEW_H
#define SERIALCONFIGURATIONVIEW_H

#include <QWidget>

namespace Ui {
class SerialConfigurationView;
}

class QTimer;
class QextSerialPort;
class QextSerialEnumerator;


class SerialConfigurationView : public QWidget
{
    Q_OBJECT
    
public:
    explicit SerialConfigurationView(QWidget *parent = 0);
    ~SerialConfigurationView();

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
    void onReadyRead();
    void onPortAddedOrRemoved();
    void onPlotButtonClicked();
    ///:
    void transmitMsg();
    void receiveMsg();
    void appendCR();
    void appendLF();
    void appendEndCmd();


Q_SIGNALS:
     void datasReady(QString );
     void plotButtonHasBeenClicked();
     void onCloseButtonClicked();

private:
    QTimer *timer;
    QextSerialPort *port;
    QextSerialEnumerator *enumerator;

    QString request;

    void configureGUI();

public:
    void performRequest(QString r);


protected:
    bool eventFilter(QObject *object, QEvent *event);
    
private:
    Ui::SerialConfigurationView *ui;
};

#endif // SERIALCONFIGURATIONVIEW_H
