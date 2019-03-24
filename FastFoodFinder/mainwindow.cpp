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
    counter = 0;
    addRestCheck = 0;
    isRemoved = false;

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
    counter += restaurantList.size();
    //Update both the listWidget for restaurant list and the plan trip widget
    //so that they now display the restaurants
    DisplayRestaurant(ui->restaurants_listWidget);
    DisplayRestaurant(ui->restaurants_listWidget_PlanTrip);
    DisplayRestaurant(ui->maintenance_listWidget);
    DisplayRestaurant(ui->maintenanceR_listWidget);
    DisplayPlan(ui->loadedPlanList, restaurantPlans);

    //Set the default page upon opening the main window to the home page
    ui->buttonList->setCurrentWidget(ui->homePage);

    ui->restaurants_listWidget_PlanTrip->setSelectionMode(QAbstractItemView::ExtendedSelection);
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
    ui->buttonList->setCurrentWidget(ui->choosePlanPage);
}

void MainWindow::on_saddlebackPlanButton_clicked()
{
    list<planStruct> displayList;

    planStruct *temp = new planStruct;
    if (ui->saddlebackPlan_lineEdit->text().isEmpty())
    {
        QMessageBox::information(this, tr("ERROR"), tr("Please enter a name for your plan!"));
    }
    else
    {
        vector<int> restids;
        if (restaurantList.size() == 10 && isRemoved == false)
        {
            restids.push_back(5);
            restids.push_back(2);
            restids.push_back(6);
            restids.push_back(9);
            restids.push_back(8);
            restids.push_back(7);
            restids.push_back(10);
            restids.push_back(1);
            restids.push_back(4);
            restids.push_back(3);
        }
        else if (restaurantList.size() == 12 && isRemoved == false)
        {
            restids.push_back(5);
            restids.push_back(2);
            restids.push_back(6);
            restids.push_back(9);
            restids.push_back(12);
            restids.push_back(11);
            restids.push_back(8);
            restids.push_back(7);
            restids.push_back(10);
            restids.push_back(1);
            restids.push_back(4);
            restids.push_back(3);
        }
        else if(isRemoved == true)
        {
            QMessageBox::information(this, tr("ERROR"),
            tr("Saddleback trip cannot activate if restaurants have been removed from initial list!"));
            return;
        }

        QString splanName = ui->saddlebackPlan_lineEdit->text();
        temp->planName = splanName.toStdString();
        int index = 0;
        list <Restaurant>::iterator ptr;
        while (index < restids.size())
        {
            ptr = restaurantList.begin();
            for (ptr = restaurantList.begin(); ptr != restaurantList.end(); ++ptr)
            {
               if (ptr->getId() == restids[index])
               {
                   temp->restaurantQueue.push_back(*ptr);
               }
            }
            ++index;
        }
        temp->startFromSaddleback = true;
        restaurantPlans.push_back(*temp);
        displayList.push_back(*temp);
        DisplayPlan(ui->loadedPlanList, displayList);
        displayList.pop_front();
        QMessageBox::information(this, tr("SUCCESS"), tr("Saddleback plan created!"));

        foreach(QLineEdit* lEdit, ui->choosePlanPage->findChildren<QLineEdit*>())
        {
            lEdit->clear();
        }

    }
}

void MainWindow::on_dominosPlanButton_clicked()
{
    list<planStruct> displayList;

    QString restaurantName;

    restaurantName = "Domino's Pizza";

    std::list<Restaurant>::iterator it2;

    for(it2 = restaurantList.begin(); it2 != restaurantList.end(); it2++)
    {
        if(it2->getrName() == restaurantName.toStdString())
        {
            break;
        }
    }

    if(it2 == restaurantList.end())
    {
        QMessageBox::information(this, tr("ERROR"), tr("Domino's Pizza must exist within the list for this trip!"));

        foreach(QLineEdit* lEdit, ui->choosePlanPage->findChildren<QLineEdit*>())
        {
            lEdit->clear();
        }
        return;
    }

    planStruct *temp = new planStruct;
    if (ui->dominosPlan_lineEdit->text().isEmpty())
    {
        QMessageBox::information(this, tr("ERROR"), tr("Please enter a name for your plan!"));
    }
    else if (ui->dominosPlanNumber_lineEdit->text().isEmpty())
    {
        QMessageBox::information(this, tr("ERROR"), tr("Please enter how many other restaurants to visit!"));
    }
    else if (ui->dominosPlanNumber_lineEdit->text().toInt() > (restaurantList.size()-1))
    {
        QMessageBox::information(this, tr("ERROR"), tr("Please do not enter a number larger than the amount of other restaurants!"));
    }
    else
    {
        vector<int> restids;
        if (addRestCheck == 0)
        {
            restids.push_back(4);
            restids.push_back(5);
            restids.push_back(2);
            restids.push_back(6);
            restids.push_back(9);
            restids.push_back(8);
            restids.push_back(7);
            restids.push_back(10);
            restids.push_back(1);
        }
        else if (addRestCheck > 0)
        {
            restids.push_back(4);
            restids.push_back(5);
            restids.push_back(2);
            restids.push_back(6);
            restids.push_back(9);
            restids.push_back(12);
            restids.push_back(11);
            restids.push_back(8);
            restids.push_back(7);
            restids.push_back(10);
            restids.push_back(1);
        }
        QString dplanName = ui->dominosPlan_lineEdit->text();
        temp->planName = dplanName.toStdString();
        list <Restaurant>::iterator it;
        for (it = restaurantList.begin(); it != restaurantList.end(); ++it)
        {
           if (it->getId() == 3)
           {
               temp->restaurantQueue.push_back(*it);
           }
        }
        QString dplannum = ui->dominosPlanNumber_lineEdit->text();
        int index = 0;
        int plannum = dplannum.toInt();
        list <Restaurant>::iterator ptr;

        if (restids.size() > restaurantList.size() - 1)
        {
            plannum = plannum + (restids.size() - (restaurantList.size() - 1));
            cout << plannum << endl;
        }
        while (index < plannum)
        {
            ptr = restaurantList.begin();
            for (ptr = restaurantList.begin(); ptr != restaurantList.end(); ++ptr)
            {
               if (ptr->getId() == restids[index])
               {
                   temp->restaurantQueue.push_back(*ptr);
               }

            }

            ++index;
        }
        temp->startFromSaddleback = false;
        restaurantPlans.push_back(*temp);
        displayList.push_back(*temp);
        DisplayPlan(ui->loadedPlanList, displayList);
        displayList.pop_front();
        QMessageBox::information(this, tr("SUCCESS"), tr("Dominos plan created!"));

        foreach(QLineEdit* lEdit, ui->choosePlanPage->findChildren<QLineEdit*>())
        {
            lEdit->clear();
        }
    }
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
        tempList = temp.PopRestaurantList(filename.toStdString(), 12);
        counter += tempList.size();
        //Insert the tempList's contents into our CURRENT restaurantList
        restaurantList.insert(restaurantList.end(), tempList.begin(), tempList.end());

        //Output that the restaurants have been added successfully
        QMessageBox::information(this, tr("SUCCESS"), tr("Restaurants have been added successfully!"));

        //Since we now have a new list, update the list and plan trip widgets with new data
        for (std::list<Restaurant>::iterator it = tempList.begin(); it != tempList.end(); it++)
        {
            if(it->IsEmpty())
            {
                QMessageBox::information(this,tr("The Restaurant is Empty"), tr("some thing went wrong and the item was not saved"));
                break;
            }
            else
            {
                ui->restaurants_listWidget_PlanTrip->clear();
                ui->restaurants_listWidget->clear();
                ui->maintenance_listWidget->clear();
                ui->maintenanceR_listWidget->clear();
                DisplayRestaurant(ui->restaurants_listWidget_PlanTrip);
                DisplayRestaurant(ui->restaurants_listWidget);
                DisplayRestaurant(ui->maintenance_listWidget);
                DisplayRestaurant(ui->maintenanceR_listWidget);
                addRestCheck++;
            }
        }
    }
    else
    {
      //If all else is false, then the user is not an admin.
      QMessageBox::information(this, tr("ERROR"), tr("You must be an admin to add, remove, or edit restaurants!"));
    }
}

//This method will add a restaurant from the available restaurants page to the restaurants in plan page
void MainWindow::on_AddRestPlanButton_clicked()
{
    //Check and make sure that there are restaurants selected
    if(ui->restaurants_listWidget_PlanTrip->selectedItems().count() < 1)
    {
        //If not, output an error message
        QMessageBox::information(this, tr("ERROR"), tr("No restaurants have been selected, please try again!"));
    }
    else
    {
        //Set the current item equal to the first item in the widget
        QListWidgetItem *current = ui->restaurants_listWidget_PlanTrip->currentItem();
        //Set the current index equal to the first row, same as doing currIndex = 0
        int currIndex = ui->restaurants_listWidget_PlanTrip->row(current);

        //Set the next pointer to increment the rows by 1
        QListWidgetItem *next = ui->restaurants_listWidget_PlanTrip->
                                item(ui->restaurants_listWidget_PlanTrip->row(current) + 1);
        //Initialize count and index
        int count;
        int index = 0;

        //Count is initialized to the number of restaurants available
        count = ui->restaurants_listWidget_PlanTrip->count();

        //Declare our item variable to add
        QListWidgetItem *item;

        //Makes sure that we will never add more than we have in the list
        while(index < count)
        {
            //Adds the selected restaurant to the current plan widget, removes it from the available restaurants
            if(ui->restaurants_listWidget_PlanTrip->currentItem()->isSelected())
            {
                item = ui->restaurants_listWidget_PlanTrip->takeItem(currIndex);
                ui->restaurantInPlan_listWidget->addItem(item);

            }
            else
            {
                //If not selected, move on to the next row
                current = next;
            }

            //Increment the index
            index++;
        }

        //Update the widgets
        ui->restaurantInPlan_listWidget->update();
        ui->restaurants_listWidget_PlanTrip->update();
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

//Moves page to the edit menu page
void MainWindow::on_editMenuButton_clicked()
{
    ui->buttonList->setCurrentWidget(ui->editMenuItemPage);
}

//This method removes the restaurant from the 'current restaurants in plan' widget
void MainWindow::on_removeRestaurantPlanButton_clicked()
{
    //Checks if there are items in the widget, if it is empty, output an error message
    if(ui->restaurantInPlan_listWidget->selectedItems().count() < 1)
    {
        QMessageBox::information(this, tr("ERROR"), tr("No restaurants have been selected to remove, please try again!"));
    }
    else
    {
        //Set the first item in the widget to current
        QListWidgetItem *current = ui->restaurantInPlan_listWidget->currentItem();
        //Set current index equal to the row of the current item, this is the same as saying currIndex = 0;
        int currIndex = ui->restaurantInPlan_listWidget->row(current);

        //Set the next pointer equal to the next row(next element) of the widget
        QListWidgetItem *next = ui->restaurantInPlan_listWidget->
                                item(ui->restaurantInPlan_listWidget->row(current) + 1);

        //Declare our item pointer to store the desired item to remove
        QListWidgetItem *item;

        if(ui->restaurantInPlan_listWidget->currentItem()->isSelected())
        {
            //If the desired item is selected, remove it from the current plan widget
            item = ui->restaurantInPlan_listWidget->takeItem(currIndex);
            //Store the item into the available restaurants widget
            ui->restaurants_listWidget_PlanTrip->addItem(item);
        }
        else
        {
            //If not found, go to next row
            current = next;
        }

        //Update the widgets to show changes
        ui->restaurantInPlan_listWidget->update();
        ui->restaurants_listWidget_PlanTrip->update();

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
        counter--;
        //Output a status complete message
        QMessageBox::information(this,tr("SUCCESS"),
                                 tr("The restaurant was deleted successfully!"));

        isRemoved = true;

        //Delete the input still stored in the lineEdit
        foreach(QLineEdit* lEdit, ui->removeRestaurantPage->findChildren<QLineEdit*>())
        {
            lEdit->clear();
        }

        //If a restaurant was removed, clear the restaurants in plan widget to avoid invalid input
        ui->restaurantInPlan_listWidget->clear();

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

//Moves the widget to the add menu page
void MainWindow::on_addMenuButton_clicked()
{
    ui->buttonList->setCurrentWidget(ui->addMenuItemPage);
}

//Moves widget to the remove menu page
void MainWindow::on_removeMenuButton_clicked()
{
    ui->buttonList->setCurrentWidget(ui->removeMenuItemPage);
}


//If user clicks cancel, it will clear the input and return to home page
void MainWindow::on_cancelRemoveButton_clicked()
{
    foreach(QLineEdit* lEdit, ui->removeMenuItemPage->findChildren<QLineEdit*>())
    {
        lEdit->clear();
    }
    ui->buttonList->setCurrentWidget(ui->homePage);
}

//If confirm is hit, it will remove the desired menu item
void MainWindow::on_confirmRemoveButton_clicked()
{
    //Loads the restaurant name
    QString restaurantName = ui->adminRestaurantNameR->text();

    //Makes sure that the restaurant exists in the list first
    std::list<Restaurant>::iterator it;

    for(it = restaurantList.begin(); it != restaurantList.end(); it++)
    {
        if(it->getrName() == restaurantName.toStdString())
        {
            break;
        }
    }

    if(it != restaurantList.end())
    {
        int index = 0;

        //If it does exist it will obtain the menu item name
        QString menuItemName = ui->adminMenuItemNameR->text();

        //Will return index 0 if the menu item could not be placed, or 1 if it was
        index = it->deleteMenu(menuItemName.toStdString());

        //If index was zero, output an error message or output a success message
        if(index == 0)
        {
            QMessageBox::information(this,tr("ERROR"), tr("Menu Item does not exist, please enter valid item!"));
            foreach(QLineEdit* lEdit, ui->addMenuItemPage->findChildren<QLineEdit*>())
            {
                lEdit->clear();
            }
        }
        else
        {
            QMessageBox::information(this,tr("SUCCESS"), tr("Menu Item has been deleted!"));
            foreach(QLineEdit* lEdit, ui->addMenuItemPage->findChildren<QLineEdit*>())
            {
                lEdit->clear();
            }
        }
    }
    else
    {
        QMessageBox::information(this,tr("ERROR"), tr("Restaurant does not exist in list!"));
        foreach(QLineEdit* lEdit, ui->addMenuItemPage->findChildren<QLineEdit*>())
        {
            lEdit->clear();
        }
    }
}

//This method will change the price of a given menu item, it follows the same structure as method onConfirmRemove
void MainWindow::on_confirmEditButton_clicked()
{
    QString restaurantName = ui->editMenuRestName->text();

    std::list<Restaurant>::iterator it;

    for(it = restaurantList.begin(); it != restaurantList.end(); it++)
    {
        if(it->getrName() == restaurantName.toStdString())
        {
            break;
        }
    }

    if(it != restaurantList.end())
    {
        int index = 0;

        QString menuItemName = ui->editMenuName->text();
        QString newPrice = ui->editMenuNewPrice->text();

        index = it->editMenu(menuItemName.toStdString(), newPrice.toDouble());

        if(index == 0)
        {
            QMessageBox::information(this,tr("ERROR"), tr("Menu Item does not exist, please enter valid item!"));
        }
        else
        {
            QMessageBox::information(this,tr("SUCCESS"), tr("Menu Item price has been changed!"));
            foreach(QLineEdit* lEdit, ui->editMenuItemPage->findChildren<QLineEdit*>())
            {
                lEdit->clear();
            }
        }
    }
    else
    {
        QMessageBox::information(this,tr("ERROR"), tr("Restaurant does not exist in list!"));
    }
}

//If cancel is clicked it will clear the input and remove
void MainWindow::on_cancelEditMenuButton_clicked()
{
    foreach(QLineEdit* lEdit, ui->editMenuItemPage->findChildren<QLineEdit*>())
    {
        lEdit->clear();
    }
    ui->buttonList->setCurrentWidget(ui->homePage);
}

//This will add a menu item to a given restaurant
void MainWindow::on_adminConfirmMenuButton_clicked()
{
    QString restaurantName = ui->adminRestaurantName->text();

    std::list<Restaurant>::iterator it;

    for (it = restaurantList.begin(); it != restaurantList.end(); it++)
    {

        if(it->getrName() == restaurantName.toStdString())
        {
            break;
        }
    }

    if(it != restaurantList.end())
    {
        QString menuItemName = ui->adminNewMenuItemName->text();
        QString menuItemPrice = ui->adminMenuItemPrice->text();

        it->addMenu(menuItemName.toStdString(), menuItemPrice.toDouble());

        QMessageBox::information(this,tr("SUCCESS"), tr("Menu Item has been added!"));
        foreach(QLineEdit* lEdit, ui->addMenuItemPage->findChildren<QLineEdit*>())
        {
            lEdit->clear();
        }
    }
    else
    {
        QMessageBox::information(this,tr("ERROR"), tr("Cannot add to a non existant restaurant, please enter valid name!"));

        foreach(QLineEdit* lEdit, ui->addMenuItemPage->findChildren<QLineEdit*>())
        {
            lEdit->clear();
        }
    }
}

//If cancel is clicked, return to the home page
void MainWindow::on_adminCancelMenuButton_clicked()
{
    foreach(QLineEdit* lEdit, ui->addMenuItemPage->findChildren<QLineEdit*>())
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

//This method is used in the constructor to display the current restaurant list
void MainWindow::DisplayPlan(QListWidget* list, std::list<planStruct> restaurantList)
{
    for (std::list<planStruct>::iterator it = restaurantList.begin(); it != restaurantList.end(); it++)
    {
        if(it->restaurantQueue.empty())
        {
            QMessageBox::information(this,tr("The Plan is Empty"), tr("some thing went wrong and the item was not saved"));
            break;
        }
        else
        {
            list->addItem(QString::fromStdString(it->planName));
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

void MainWindow::on_viewMenuButton_clicked()
{
    if(ui->restaurants_listWidget->selectedItems().count() < 1)
    {
        //If not, output an error message
        QMessageBox::information(this, tr("ERROR"), tr("No restaurants have been selected, please try again!"));
    }
    else
    {
        QString restaurant = ui->restaurants_listWidget->selectedItems().first()->text();

        ui->restaurantNameMenu->setText(restaurant + "'s Menu");
        Restaurant* temp =

                searchRestaurant(restaurant);

        vector<menu> tempMenu = temp->getMenu();

        ui->menuViewList->clear();

        for(unsigned int i = 0; i < tempMenu.size(); i++)
        {
            ui->menuViewList->addItem(QString::fromStdString(tempMenu[i].name) + " - $" + QString::number(tempMenu[i].price));
        }
        ui->buttonList->setCurrentWidget(ui->menuList);
    }
}

void MainWindow::on_closeMenu_clicked()
{
    ui->buttonList->setCurrentWidget(ui->restaurantListPage);
}


void MainWindow::on_customPlanButton_clicked()
{
    ui->buttonList->setCurrentWidget(ui->planTripPage);
}

void MainWindow::on_trip_button_clicked()
{
    if(ui->loadedPlanList->selectedItems().count() < 1)
    {
        //If not, output an error message
        QMessageBox::information(this, tr("ERROR"), tr("No restaurants have been selected, please try again!"));
    }
    else
    {
        QString planName = ui->loadedPlanList->selectedItems().first()->text();
        tempPlan = searchPlan(planName);
        if(tempPlan != nullptr)
        {
            tempPlanNonPtr = *tempPlan;
            for (std::deque<Restaurant>::iterator it = tempPlan->restaurantQueue.begin(); it != tempPlan->restaurantQueue.end(); it++)
            {
                ui->tripPlanList->addItem(QString::fromStdString(it->getrName()));
            }
            ui->takingTripLabel->setText("Taking Plan (" + QString::fromStdString(tempPlan->planName) + ") For Trip");
            ui->buttonList->setCurrentWidget(ui->tripPage);
        }
    }
}

void MainWindow::on_addMenuItemTrip_clicked()
{
    if(ui->menuTripList->selectedItems().count() < 1)
    {
        //If not, output an error message
        QMessageBox::information(this, tr("ERROR"), tr("No restaurants have been selected, please try again!"));
    }
    else
    {
        QString menuName = ui->menuTripList->selectedItems().first()->text();
         cout << menuName.toStdString() << endl;
         cout << flush;
        QString restName = ui->restaurantNameTrip->text();
        cout << restName.toStdString() << endl;
        cout << flush;
        menuName = menuName.section('*',1,1);
        menuName = menuName.trimmed();
        restName = restName.section('`',0,0);
        restName = restName.trimmed();
        Restaurant *temp = searchRestaurant(restName);
        int menuIndex;
        if(temp != nullptr)
        {
            menuIndex = searchMenuItem(menuName, *temp);
        }
        else
        {
            cout << "No Restaurant Found"<< endl;
        }
        if(menuIndex >= 0)
        {
            QString planName  = QString::fromStdString(tempPlan->planName);
            planStruct* planTemp = searchPlan(planName);
            if(planTemp != nullptr)
            {
                for(unsigned int i = 0; i < planTemp->restaurantQueue.size(); i++)
                {
                     if(planTemp->restaurantQueue[i].getrName() == restName.toStdString())
                     {
                         planTemp->restaurantQueue[i].setQty(menuIndex, ui->menuQty->value());
                         QMessageBox::information(this, tr("Menu"), tr("Item has been saved!"));
                     }
                     else {
                         cout << planTemp->restaurantQueue[i].getrName() << endl;
                     }
                }
            }
            else
            {
                cout << "No Plan Found"<< endl;
            }
        }
        else
        {
            cout << "No Menu Item Found"<< endl;
        }
    }
}
void MainWindow::on_savePlanButton_clicked()
{
    if(ui->restaurantInPlan_listWidget->count() == 0)
    {
        //If not, output an error message
        QMessageBox::information(this, tr("ERROR"), tr("Please add restaurants to your plan!"));
    }
    else if(ui->NameOfPlan_lineEdit->text().isEmpty())
    {
        //If not, output an error message
        QMessageBox::information(this, tr("ERROR"), tr("Please enter a name for your plan!"));
    }
    else if(ui->restaurantInPlan_listWidget->count() == 0 && ui->NameOfPlan_lineEdit->text().isEmpty())
    {
        //If not, output an error message
        QMessageBox::information(this, tr("ERROR"), tr("Please load restaurants into your plan and enter a restaurant name!"));
    }
    else
    {
        //Declare a QString for the user's inputted restaurant name
        QString planName;

        //Set restaurantName equal to the text submitted by the user
        planName = ui->NameOfPlan_lineEdit->text();


        //vector<int> indexVec = getIndexesFromPlan(tempPlan->restaurantQueue);
       // tempPlan->restaurantQueue = recursiveSort(tempPlan->restaurantQueue,indexVec);

        insertIntoPlan(ui->restaurantInPlan_listWidget, planName);
//        planStruct* tempPlan = searchPlan(planName);
//        if (tempPlan != nullptr)
//        {
//            vector<int> indexVec = getIndexesFromPlan(tempPlan->restaurantQueue);
//            for (int i = 0; i < tempPlan->restaurantQueue.size(); i++) {
//                cout << 0 << " " << tempPlan->restaurantQueue[i].getrName() << endl;
//            }
//            recursiveSort(tempPlan->restaurantQueue,indexVec, 0);
//            for (int i = 0; i < tempPlan->restaurantQueue.size(); ++i)
//            {
//                cout << tempPlan->restaurantQueue[i].getrName() << endl;
//            }

//        }

        QMessageBox::information(this,tr("SUCCESS"), tr("Plan has been added successfully!"));
        ui->loadedPlanList->clear();
        DisplayPlan(ui->loadedPlanList, restaurantPlans);
    }
}

Restaurant* MainWindow::searchRestaurant(QString& searchName)
{
    Restaurant* returned;

    list<Restaurant>::iterator it;
    for(it = restaurantList.begin(); it != restaurantList.end(); it++)
    {
        returned = &*it;
        if(returned->getrName() == searchName.toStdString())
        {
            return returned;
        }
    }
    return nullptr;
}

planStruct* MainWindow::searchPlan(QString& searchName)
{
    planStruct* returned;

    list<planStruct>::iterator it;
    for(it = restaurantPlans.begin(); it != restaurantPlans.end(); it++)
    {
        returned = &*it;
        if(returned->planName == searchName.toStdString())
        {
            return returned;
        }
    }
    return nullptr;
}


// pass the plan
int MainWindow::searchMenuItem(QString& searchName, Restaurant& rest)
{
    vector<menu> returned = rest.getMenu();

    for (unsigned int i = 0; i < returned.size(); i++)
    {
        if(returned[i].name == searchName.toStdString())
        {
            return int(i);
        }
    }
    return -1;
}

void MainWindow::insertIntoPlan(QListWidget *theList, QString planName)
{
    planStruct *temp = new planStruct;

    string theName = planName.toStdString();

    temp->planName = theName;

    //Initialize count and index
    int count;
    int index = 0;

    //Count is initialized to the number of restaurants available
    count = theList->count();

    //Makes sure that we will never add more than we have in the list
    while(index < count)
    {
        QString string = theList->item(index)->text();


        for (std::list<Restaurant>::iterator it = restaurantList.begin(); it != restaurantList.end(); it++)
        {
            if(it->IsEmpty())
            {
                QMessageBox::information(this,tr("The Restaurant is Empty"), tr("some thing went wrong and the item was not saved"));
                break;
            }

            if(string.toStdString() == it->getrName())
            {
                temp->restaurantQueue.push_back(*it);
            }
        }
        index++;
    }
    temp->startFromSaddleback = false;
    restaurantPlans.push_back(*temp);
    UpdateRestaurants(ui->restaurants_listWidget_PlanTrip);

    ui->restaurantInPlan_listWidget->clear();

    ui->NameOfPlan_lineEdit->clear();
}

void MainWindow::on_startTrip_clicked()
{
    ui->tripPlanList->clear();
    for (std::deque<Restaurant>::iterator it = tempPlanNonPtr.restaurantQueue.begin(); it != tempPlanNonPtr.restaurantQueue.end(); it++)
    {
        ui->tripPlanList->addItem(QString::fromStdString(it->getrName()));
    }

    Restaurant currentRes;
    vector<menu> currentMenu;

    if(!tempPlanNonPtr.restaurantQueue.empty())
    {
        ui->startTrip->setText("Continue");

        currentRes = tempPlanNonPtr.restaurantQueue.at(0);
        currentMenu = currentRes.getMenu();
        ui->menuTripList->clear();
        for (unsigned int i = 0; i < currentMenu.size(); i++)
        {
            ui->menuTripList->addItem("$" + QString::number(currentMenu[i].price)
                                      + " * " + QString::fromStdString(currentMenu[i].name));
        }
        tempPlanNonPtr.restaurantQueue.pop_front();
        ui->restaurantNameTrip->setText(QString::fromStdString(currentRes.getrName()) + "`s Menu");
    }
    else
    {
        //tempPlanNonPtr.restaurantQueue.pop_front();
        double totalPlanRev = 0;
        double totalDistance = totalDistanceTraveled(tempPlan->restaurantQueue, tempPlan->startFromSaddleback);
        ui->startTrip->setText("Start");
        ui->menuTripList->clear();
        ui->finalRevList->clear();
        for (std::deque<Restaurant>::iterator it = tempPlan->restaurantQueue.begin(); it != tempPlan->restaurantQueue.end(); it++)
        {
            totalPlanRev += it->getTotalRev();
            ui->finalRevList->addItem(QString::fromStdString(it->getrName()) + "'s Revenue - $" + QString::number(it->getTotalRev()));
        }
        ui->totalRevLabel->setText("Total Revenue - $" + QString::number(totalPlanRev));
        ui->totalDistanceLabel->setText("Total Distance - " + QString::number(totalDistance) + " miles");
        ui->buttonList->setCurrentWidget(ui->finishedTripPage);
    }

}

double MainWindow::totalDistanceTraveled(deque<Restaurant>& resDeque, bool startFromSaddleback)
{
    double returned = 0;
    vector<double> distVec;
    int restaurantId;
    if(startFromSaddleback)
    {
        returned = resDeque[0].getsDistance();
    }
    for (unsigned int i = 0; i < resDeque.size(); i++)
    {
        distVec = resDeque[i].getDistances();

        if((i+1) < resDeque.size())
        {
            restaurantId = resDeque[i+1].getId();
            returned += distVec[restaurantId-1];
        }
    }
    return returned;
}

//Restaurant MainWindow::recursiveSort(deque<Restaurant>& restaurantsInPlan, vector<int>& indexVec, int index)
//{
//    deque<Restaurant> tempDeque = restaurantsInPlan;
//    Restaurant tempRes;
//    int smallestIndex;

//    for (int i = 0; i < restaurantsInPlan.size(); i++) {
//        cout << index << ":" << restaurantsInPlan[i].getrName() << endl;
//    }

//    for (int i = 0; i < tempDeque.size(); i++) {
//        cout << index << "-" << tempDeque[i].getrName() << endl;
//    }
//}

vector<int> MainWindow::getIndexesFromPlan(deque<Restaurant> &restaurantsInPlan)
{
    deque<Restaurant>::iterator it;

    vector<int> indexVec;
    for(unsigned int index = 0; index < restaurantsInPlan.size(); index++)
    {
        indexVec.push_back(restaurantsInPlan[index].getId());
    }

    return indexVec;
}

int MainWindow::smallestDistance(vector<int> indexVec, Restaurant res)
{
    vector<double> tempVec = res.getDistances();
    int smallest = indexVec[1];
    for (unsigned int i = 1; i < indexVec.size(); i++)
    {
        if(tempVec[smallest] >= tempVec[indexVec[i]])
        {
            smallest = indexVec[i];
        }
    }
    return smallest;
}
