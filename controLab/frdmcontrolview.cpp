#include "frdmcontrolview.h"
#include "ui_frdmcontrolview.h"

FRDMControlView::FRDMControlView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FRDMControlView)
{
    ui->setupUi(this);

    ui->sourcesList->addItem("Temperature");
    ui->sourcesList->addItem("-- Dimmer --");
    ui->sourcesList->addItem("Pressure");

}

FRDMControlView::~FRDMControlView()
{
    delete ui;
}
