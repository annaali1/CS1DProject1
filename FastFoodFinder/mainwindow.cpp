#include "mainwindow.hpp"
#include "ui_mainwindow.h"

/***********************************************
 * Class MainWindow will set up the ui for the
 * windows of this project. So far this is the
 * standard Qt implementation but it can be
 * modified later
 * *********************************************/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap pix;

    pix.load(":/eatALLthefood.jpg");

    ui->home_label->setPixmap(pix.scaled(pix.width(), pix.height(), Qt::KeepAspectRatio));
    const char *qt_version = qVersion();

    QMessageBox::information(this,tr(qt_version), tr(qt_version));


    Restaurant temp;
    restaurantList = temp.PopRestaurantList();
    for (std::list<Restaurant>::iterator it = restaurantList.begin(); it != restaurantList.end(); it++)
    {

        cout << "NAME: " << it->getrName();
    }
    DisplayRestaurant(ui->restaurants_listWidget);
    DisplayRestaurant(ui->restaurants_listWidget_PlanTrip);

    ui->buttonList->setCurrentWidget(ui->homePage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//If the View Plans button is clicked, the stack widget will move to the view plans page
void MainWindow::on_ViewPlansButton_clicked()
{
    ui->buttonList->setCurrentWidget(ui->viewPlansPage);

}

//If the Plan Trip button is clicked, the stack widget will move to the plan trip page
void MainWindow::on_PlanTripButton_clicked()
{

    ui->buttonList->setCurrentWidget(ui->planTripPage);

}

//If the View List button is clicked, the stack widget will move to the restaurant list page
void MainWindow::on_ListButton_clicked()
{
    ui->buttonList->setCurrentWidget(ui->restaurantListPage);

}

//If the Maintanence button is clicked, the stack widget will move to the maintenence page
void MainWindow::on_AdminButton_clicked()
{
    ui->buttonList->setCurrentWidget(ui->maintanencePage);
}

//If the Return to Home Screen button is clicked, the stack widget will move to the home screen page
void MainWindow::on_HomeScreenButton_clicked()
{
    ui->buttonList->setCurrentWidget(ui->homePage);
}

void MainWindow::DisplayRestaurant(QListWidget* list)
{
    //list->addItem("pre restaurant lsit->GetName()");


    for (std::list<Restaurant>::iterator it = restaurantList.begin(); it != restaurantList.end(); it++)
    {
        if(it->IsEmpty())
        {
            QMessageBox::information(this,tr("The Restaurant is Empty"), tr("some thing went wrong and the item was not saved"));
            break;
        }
        else
        {
            list->addItem(QString::fromStdString(it->getrName()));
        }
    }

    //list->addItem("post restaurant lsit->GetName()");

}




