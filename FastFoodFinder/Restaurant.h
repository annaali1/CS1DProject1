#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>
#include <vector>
#include <queue>
#include <sstream>
#include <QString>
#include <string>
using namespace std;

struct menu
{
    string name;
    double price;
    int quantity = 0;
};

class Restaurant
{
    private:
        vector<menu> menuItems;
        vector<double> distance;
        double sDistance;
        string rName;
        string stringid;
        int id;
        int NoOfMenuItems;
        double totalRev;
        void setTotalRev();
    public:
        Restaurant();
        Restaurant(string name);
        list<Restaurant> PopRestaurantList(string file, int counter = 0);
        list<Restaurant> PopRestaurantListFromFile(string filename);
        int editMenu(string menuItemName, double newPrice);
        string getrName();
        double getsDistance();
        double getTotalRev();
        int getId();
        void setQty(int menuIndex, int qty);
        vector<double> getDistances();
        vector<menu> getMenu();
        bool IsEmpty();
        void addMenu(string menuItemName, double price);
        int deleteMenu(string menuItemName);
        void addRestaurant(list<Restaurant> &r1); //adds restaurant to list
        void removeRestaurant(list<Restaurant> &r1); //removes restaurant from list
        void setName(string newName);
        void setId(int newId);
        void setDistances(vector<double> distanceVec);
        void setNumberMenuItems(int menuItems);
        void setMenuItems(vector<menu> newMenues);
        void output(list<Restaurant> restaurantList);
        void addDistances(list<Restaurant> &r1, Restaurant* temp);
        //int getCounter();
};
