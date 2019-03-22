#pragma once
#include "accountType.hpp"
#include <QMainWindow>
#include <QMessageBox>
#include <QListWidget>
#include <QFileDialog>
#include <menuscreen.h>
#include "Restaurant.h"
#include "loginwindow.hpp"

/*****************************************************
 * Class MainWindow will be within the Ui namespace
 * and will handle outputting the user interface as
 * well as managing the file variable
 * ***************************************************/
struct planStruct{
    string planName;
    queue<Restaurant> restaurantQueue;
};

namespace Ui{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();
        list<Restaurant> getRestaurantList();

    private slots:
        //These slots will register from the home screen if each push button has been clicked
        //and redirect them to the appropriate stack widget
        void on_ListButton_clicked();
        void on_PlanTripButton_clicked();
        void on_AddRestButton_clicked();
        void on_AddRestPlanButton_clicked();
        void on_removeRestaurantButton_clicked();
        void on_removeRestaurantPlanButton_clicked();
        void on_confirmButton_clicked();
        void on_cancelButton_clicked();
        void on_ViewPlansButton_clicked();
        void on_AdminButton_clicked();
        void on_HomeScreenButton_clicked();
        void on_viewMenuButton_clicked();
        void on_closeMenu_clicked();
        void on_customPlanButton_clicked();
        void on_trip_button_clicked();
        void on_addMenuItemTrip_clicked();

private:
        Ui::MainWindow *ui;
        QString currentFile; // Directory of the file containing restaurants currently loaded into the program
        list<Restaurant> restaurantList;
        // Setup the menus and widgets in the window
        void setupMenusAndWidgets();
        void DisplayRestaurant(QListWidget *list);
        void UpdateRestaurants(QListWidget *list);
        Restaurant* searchRestaurant(QString& searchName);
        int searchMenuItem(QString& searchName, Restaurant& rest);
        int counter = 0;
        planStruct restaurantPlans;

};
