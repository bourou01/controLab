#ifndef FRDMCONTROLVIEW_H
#define FRDMCONTROLVIEW_H

#include <QWidget>

#include <QSpinBox>
#include <QSlider>


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
    void onSetPointSliderLevelReleased();

Q_SIGNALS:

public:


    void setTemperature(float nT);
    float getTemperature();

    void setDimmer0(float nD0);
    float getDimmer0();

    void setPressure(float nP);
    float getPressure();


    /// virtual Ressources for test
    void setVirtualSP(float nSP);
    float getVirtualP();

    void setVirtualSensor(float nVS);
    float getVirtualSensor();
    ///


    void setSerialConfigurationView(SerialConfigurationView *);


    void setRange(double min, double max);

private:
    float temperatureSP;

    FRDMRessource temperature;
    FRDMRessource pressure;
    FRDMRessource dimmer0;

    /// Virtual Ressources for test
    FRDMRessource virtualSP;
    FRDMRessource virtualSensor;



    SerialConfigurationView *serialConfigurationView;


private:
    Ui::FRDMControlView *ui;
};

#endif // FRDMCONTROLVIEW_H
