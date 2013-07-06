#ifndef FRDMCONTROLVIEW_H
#define FRDMCONTROLVIEW_H

#include <QWidget>

namespace Ui {
class FRDMControlView;
}

class FRDMControlView : public QWidget
{
    Q_OBJECT
    
public:
    explicit FRDMControlView(QWidget *parent = 0);
    ~FRDMControlView();
    
private:
    Ui::FRDMControlView *ui;
};

#endif // FRDMCONTROLVIEW_H
