#ifndef FRDMCONTROLVIEW_H
#define FRDMCONTROLVIEW_H

#include <QWidget>


#include "serialconfigurationview.h"



typedef struct FRDMRessource
{
  QString name;
  float value;
  float min;
  float max;
} FRDMRessource;


namespace Ui {
class FRDMControlView;
}

class FRDMControlView : public QWidget
{
    Q_OBJECT
    
public:
    explicit FRDMControlView(QWidget *parent = 0);
    ~FRDMControlView();
    

private slots:


    void onRessourceListChanged(const QString &);
    void onSetPointValueChanged(double);

Q_SIGNALS:



public:


    void setTemperature(float nT);
    float getTemperature();

    void setDimmer0(float nD0);
    float getDimmer0();

    void setPressure(float nP);
    float getPressure();

    void setSerialConfigurationView(SerialConfigurationView *);
private:
    float temperatureSP;

    FRDMRessource temperature;
    FRDMRessource pressure;
    FRDMRessource dimmer0;

    SerialConfigurationView *serialConfigurationView;


private:
    Ui::FRDMControlView *ui;
};

#endif // FRDMCONTROLVIEW_H
