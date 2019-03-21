#include "menuscreen.h"
#include "ui_menuscreen.h"

MenuScreen::MenuScreen(QString& name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MenuScreen)
{
    ui->setupUi(this);
    ui->label->setText(name);
}

MenuScreen::~MenuScreen()
{
    delete ui;
}
