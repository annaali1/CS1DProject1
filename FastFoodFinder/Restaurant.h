#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <QString>
#include <string>
using namespace std;

struct menu
{
    string name;
    double price;
};

class Restaurant
{
    private:
        vector<menu> menuItems;
        vector<double> distance;
        string sDistance;
        string rName;
        string stringid;
        int id;
        int NoOfMenuItems;
    public:
        Restaurant();
        Restaurant(string name);
        list<Restaurant> PopRestaurantList();
        void editMenu();//******************
        string getrName();//***************
        bool IsEmpty();
        void addMenu();//*********************
        void deleteMenu();//*************
        void addRestaurant(list<Restaurant> &r1); //adds restaurant to list
        void removeRestaurant(list<Restaurant> &r1);
        void setName(string newName);
        void setId(int newId);
        void setDistance(string distance);
        void setNumberMenuItems(int menuItems);
};
