#include "planwindow.h"
#include "ui_planwindow.h"

PlanWindow::PlanWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlanWindow)
{
    ui->setupUi(this);
}

PlanWindow::~PlanWindow()
{
    delete ui;
}
