#ifndef CUSTOMPLOTVIEW_H
#define CUSTOMPLOTVIEW_H

#include <QWidget>

namespace Ui {
class CustomPlotView;
}

class CustomPlotView : public QWidget
{
    Q_OBJECT
    
public:
    explicit CustomPlotView(QWidget *parent = 0);
    ~CustomPlotView();
    
private:
    Ui::CustomPlotView *ui;
};

#endif // CUSTOMPLOTVIEW_H
