#include "customplotview.h"
#include "ui_customplotview.h"

CustomPlotView::CustomPlotView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomPlotView)
{
    ui->setupUi(this);
}

CustomPlotView::~CustomPlotView()
{
    delete ui;
}
