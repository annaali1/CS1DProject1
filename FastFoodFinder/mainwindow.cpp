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

    //Declare a QPixmap for our open logo
    QPixmap pix;

    //Load the pix map
    pix.load(":/eatALLthefood.jpg");

    //Set it as the home label and to keep the aspect ratio so it wont oversize
    ui->home_label->setPixmap(pix.scaled(pix.width(), pix.height(), Qt::KeepAspectRatio));

    //Declare our temp restaurant variable to store the initial list
    Restaurant temp;

    QString file;

    file = QFileDialog::getOpenFileName(this, "Please Choose a Starting File", "C://", "txt(*.txt)");

    //Store the items into our restaurantList
    restaurantList = temp.PopRestaurantList(file.toStdString());

    //Update both the listWidget for restaurant list and the plan trip widget
    //so that they now display the restaurants
    DisplayRestaurant(ui->restaurants_listWidget);
    DisplayRestaurant(ui->restaurants_listWidget_PlanTrip);
    DisplayRestaurant(ui->maintenance_listWidget);
    DisplayRestaurant(ui->maintenanceR_listWidget);

    //Set the default page upon opening the main window to the home page
    ui->buttonList->setCurrentWidget(ui->homePage);
}

//Default destructor
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
    //Declare a variable type from AccountType, this will be used to check for admin status
    fastFoodFinder::AccountType type;

    //Store the type of the user into variable 'type'
    type = Login::getType();

    //Check if the user is an admin
    if(type == fastFoodFinder::AccountType::ADMIN)
    {
        ui->buttonList->setCurrentWidget(ui->maintanencePage);
    }
    else
    {
        //If all else is false, then the user is not an admin.
        QMessageBox::information(this, tr("ERROR"), tr("You must be an admin to enter this page!"));
    }

}

//If the Return to Home Screen button is clicked, the stack widget will move to the home screen page
void MainWindow::on_HomeScreenButton_clicked()
{
    ui->buttonList->setCurrentWidget(ui->homePage);
}

//Once the AddRest button is clicked, it will ask for a .txt file from the user and update the
//current list.
void MainWindow::on_AddRestButton_clicked()
{
    //Declare a variable type from AccountType, this will be used to check for admin status
    fastFoodFinder::AccountType type;

    //Store the type of the user into variable 'type'
    type = Login::getType();

    //Check if the user is an admin
    if(type == fastFoodFinder::AccountType::ADMIN)
    {
        //If true, declare a filename variable
        QString filename;

        //Prompt the user to choose a file of .txt from directory, store name of file into filename
        filename = QFileDialog::getOpenFileName(this, "Please Choose File", "C://", "txt(*.txt)");

        //Declare our temp Restaurant variable to store a new list
        Restaurant temp;

        //Declare a temporary list of restaurants
        list<Restaurant> tempList;

        //Set our tempList to the new list using filename
        tempList = temp.PopRestaurantListFromFile(filename.toStdString());

        //Insert the tempList's contents into our CURRENT restaurantList
        restaurantList.insert(restaurantList.end(), tempList.begin(), tempList.end());

        //Output that the restaurants have been added successfully
        QMessageBox::information(this, tr("SUCCESS"), tr("Restaurants have been added successfully!"));

        //Since we now have a new list, call UpdateRestaurants to update the list and plan trip widgets with new data
        UpdateRestaurants(ui->restaurants_listWidget);
        UpdateRestaurants(ui->restaurants_listWidget_PlanTrip);
        UpdateRestaurants(ui->maintenance_listWidget);
        UpdateRestaurants(ui->maintenanceR_listWidget);
    }
    else
    {
      //If all else is false, then the user is not an admin.
      QMessageBox::information(this, tr("ERROR"), tr("You must be an admin to add, remove, or edit restaurants!"));
    }
}

//If removeRestaurant button is clicked, it will check if the user is an admin, if they are it will move
//to the desired page. If not, an error message will pop up
void MainWindow::on_removeRestaurantButton_clicked()
{
    //Declare our type variable from AccountType to check for admin status
    fastFoodFinder::AccountType type;

    //Get the type from the user and store it into variable 'type'
    type = Login::getType();

    //If the user is an admin, go to desired page, if not output error message
    if(type == fastFoodFinder::AccountType::ADMIN)
    {
        ui->buttonList->setCurrentWidget(ui->removeRestaurantPage);
    }
    else
    {
       QMessageBox::information(this, tr("ERROR"), tr("You must be an admin to add, remove, or edit restaurants!"));
    }

}

//If confirm button is clicked, then the restaurant submitted in the line edit will be removed
void MainWindow::on_confirmButton_clicked()
{
    //Declare a QString for the user's inputted restaurant name
    QString restaurantName;

    //Set restaurantName equal to the text submitted by the user
    restaurantName = ui->lineEdit_RestaurantName->text();

    //Declare an iterator for our restaurantList
    list<Restaurant>::iterator it;

    //This for loop checks if the restaurantName exists within the restaurantList
    for(it = restaurantList.begin(); it != restaurantList.end(); ++it)
    {
        if(it->getrName() == restaurantName.toStdString())
        {
            //If the name was found, break out of the loop and save iterator
            break;
        }
    }

    //Checks if the iterator did not hit the end of the list, meaning a valid name was found
    if(it != restaurantList.end())
    {
        //Delete the data stored at the iterators location
        restaurantList.erase(it);

        //Output a status complete message
        QMessageBox::information(this,tr("SUCCESS"),
                                 tr("The restaurant was deleted successfully!"));

        //Delete the input still stored in the lineEdit
        foreach(QLineEdit* lEdit, ui->removeRestaurantPage->findChildren<QLineEdit*>())
        {
            lEdit->clear();
        }
    }
    else
    {
        //If this else is reached, the restaurant was not found, output an error message
        QMessageBox::information(this,tr("ERROR"),
                                 tr("The desired item is not in this list"));
        //Still, clear the input from the line edit
        foreach(QLineEdit* lEdit, ui->removeRestaurantPage->findChildren<QLineEdit*>())
        {
            lEdit->clear();
        }
    }

    //Update the list and plan trip widgets accordingly to show the removal
    UpdateRestaurants(ui->restaurants_listWidget);
    UpdateRestaurants(ui->restaurants_listWidget_PlanTrip);
    UpdateRestaurants(ui->maintenance_listWidget);
    UpdateRestaurants(ui->maintenanceR_listWidget);
}

//If the cancel button is clicked from the remove restaurant page, the line edit is cleared and
//the user is returned to the home screen
void MainWindow::on_cancelButton_clicked()
{
    foreach(QLineEdit* lEdit, ui->removeRestaurantPage->findChildren<QLineEdit*>())
    {
        lEdit->clear();
    }
    ui->buttonList->setCurrentWidget(ui->homePage);
}

//This method is used in the constructor to display the current restaurant list
void MainWindow::DisplayRestaurant(QListWidget* list)
{
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
}

//This method is used to update the restaurant list AFTER it has been loaded in once in the constructor
void MainWindow::UpdateRestaurants(QListWidget* list)
{
    //Clear the initial list widgets
    list->clear();

    //Since the list has been cleared, we must update what is shown in the main window
    ui->restaurants_listWidget->update();
    ui->restaurantInPlan_listWidget->update();
    ui->maintenance_listWidget->update();
    ui->maintenanceR_listWidget->update();

    //Loop through the restaurantList once again(since it will have new data) and fill the list widgets again
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
}

list<Restaurant> MainWindow::getRestaurantList()
{
    return restaurantList;
}




