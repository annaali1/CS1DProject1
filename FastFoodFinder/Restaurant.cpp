#include "Restaurant.h"
#include <QFileDialog>
#include <QWidget>
Restaurant::Restaurant()
{
    rName = "";
    id = 0;
    sDistance = 0;
}

Restaurant::Restaurant(string name)
{
    rName = name;
    id = 0;
    sDistance = 0;
}

int Restaurant::editMenu(string menuItemName, double newPrice)
{
    menu mitem;
    int check = 0;

    vector <menu> ::iterator ptr;
    for (ptr = menuItems.begin(); ptr != menuItems.end(); ++ptr)
    {
        mitem = *ptr;
        if (mitem.name == menuItemName)
        {
            ++check;
            break;
        }
    }


    if(check > 0)
    {
        mitem.price = newPrice;
        *ptr = mitem;
    }

    return check;
}

void Restaurant::addMenu(string menuItemName, double price)
{
    menu tempmenu;
    tempmenu.name = menuItemName;
    tempmenu.price = price;

    menuItems.push_back(tempmenu);
}

int Restaurant::deleteMenu(string menuItemName)
{
    int check = 0;

    //vector <menu> ::iterator ptr;
    for (unsigned int i = 0; i < menuItems.size(); ++i)
    {

        if (menuItems[i].name == menuItemName)
        {
            menuItems.erase(menuItems.begin()+i);
            ++check;
            break;
        }
    }

    return check;
}

//This method will pop the restaurant list using a file SPECIFIC to the user
list<Restaurant> Restaurant::PopRestaurantList(string file, int counter)
{
    list<Restaurant> r1;
    //string file = "C:/Users/lukes/OneDrive/Desktop/CS1DProject1/FastFoodFinder/restaurants.txt";
    ifstream inFile;
    double d = 0.0, doublePrice;
    string menItems, dist, item, dprice, saddle_distance, stringcounter;
    menu m;
    m.name =  "";
    m.price = 0.0;

    int tempInt;
    inFile.open(file);
    inFile >> tempInt;
    counter += tempInt;
    inFile.ignore(1000, '\n');
    while(!inFile.eof()){
        Restaurant *temp = new Restaurant;
        inFile.ignore(1000, 'N');
        inFile.ignore(1000, ':');
        inFile.ignore(1);
        getline(inFile, temp->rName);

        if (!temp->rName.empty() && temp->rName[temp->rName.size() - 1] == '\r')
        {
            temp->rName.erase(temp->rName.size() - 1);
        }
        inFile.clear();
        inFile.ignore(28);
        getline(inFile, temp->stringid);
        if (!temp->stringid.empty() && temp->stringid[temp->stringid.size() - 1] == '\r')
        {
           temp->stringid.erase(temp->stringid.size() - 1);
        }
        stringstream convertID(temp->stringid);
        convertID >> temp->id;
        for(int i = 0; i < counter; i++)
        {

            inFile.ignore(1);
            inFile >> dist;
            stringstream convertDist(dist);
            convertDist >> d;
            temp->distance.push_back(d);
        }
        inFile >> saddle_distance;
        stringstream convertSDistance(saddle_distance);
        convertSDistance >> temp->sDistance;
        inFile.ignore(1000, '\n');
        inFile >> menItems;
        stringstream convertNo(menItems);
        convertNo >> temp->NoOfMenuItems;
        for(int i = 0; i < temp->NoOfMenuItems; i++)
        {
            inFile.ignore(1000, '\n');
            getline(inFile, item);
            if (!item.empty() && item[item.size() - 1] == '\r')
            {
                item.erase(item.size() - 1);
            }
            inFile >> dprice;
            stringstream convertPrice(dprice);
            convertPrice >> doublePrice;
            m = {item, doublePrice, 0};
            temp->menuItems.push_back(m);
        }
        if(inFile.fail())
        {
            break;
        }
        r1.push_back(*temp);
    delete temp;
    }
    inFile.close();
    return r1;
}

//This method will pop the restaurants from a given file by taking in a string for the filename
list<Restaurant> Restaurant::PopRestaurantListFromFile(string file)
{
    list<Restaurant> r1;
    ifstream inFile;
    double d = 0.0, doublePrice;
    string menItems, dist, item, dprice, stringcounter;
    menu m;
    m.name =  "";
    m.price = 0.0;

    inFile.open(file);
    int counter;
    inFile >> counter;
    inFile.ignore(100000, '\n');
    while(!inFile.eof()){
        Restaurant *temp = new Restaurant;
        inFile.ignore(1000, ':');
        inFile.ignore(1);
        getline(inFile, temp->rName);

        if (!temp->rName.empty() && temp->rName[temp->rName.size() - 1] == '\r')
        {
            temp->rName.erase(temp->rName.size() - 1);
        }
        inFile.clear();
        inFile.ignore(28);
        getline(inFile, temp->stringid);
        if (!temp->stringid.empty() && temp->stringid[temp->stringid.size() - 1] == '\r')
        {
           temp->stringid.erase(temp->stringid.size() - 1);
        }
        stringstream convertID(temp->stringid);
        convertID >> temp->id;
        for(int i = 0; i < counter; i++)
        {

            inFile.ignore(1);
            inFile >> dist;
            stringstream convertDist(dist);
            convertDist >> d;
            temp->distance.push_back(d);
        }
        inFile >> temp->sDistance;
        inFile.ignore(1000, '\n');
        inFile >> menItems;
        stringstream convertNo(menItems);
        convertNo >> temp->NoOfMenuItems;
        for(int i = 0; i < temp->NoOfMenuItems; i++)
        {
            inFile.ignore(1000, '\n');
            getline(inFile, item);
            if (!item.empty() && item[item.size() - 1] == '\r')
            {
                item.erase(item.size() - 1);
            }
            inFile >> dprice;
            stringstream convertPrice(dprice);
            convertPrice >> doublePrice;
            m = {item, doublePrice, 0};
            temp->menuItems.push_back(m);
        }
        if(inFile.fail())
        {
            break;
        }
        r1.push_back(*temp);
    delete temp;
    }
    inFile.close();
    return r1;
}
//void Restaurant::addDistances(list<Restaurant> &r1, Restaurant* temp)
//{
//        list<Restaurant>::iterator ptr = r1.begin();
//        for(int i =0; i < temp->id; i++)
//        {
//                ptr->distance.push_back(temp->distance[i]);
//                ptr++;
//        }
//}

//void Restaurant::addRestaurant(list<Restaurant> &r1)
//{
//    menu m;
//    m.name = "";
//    m.price = 0.0;
//        double d = 0.0;
//    char choice = 'n';
//    do{
//        Restaurant *temp = new Restaurant;
//        cout << "What is the name of the restaurant?:  ";
//        cin >> temp->rName;
//        cout << "What is the restaurant ID?: ";
//        cin >> temp->id;
//        for(int i = 0; i < temp->id; i++)
//        {
//            cout << "What is the distance from the restaurant with ID " << i+1 << "?: ";
//            cin >> d;
//                        temp->distance.push_back(d);
//        }
//        temp.addDistances(r1, temp);
//        cout << "What is the distance from Saddleback?: ";
//        cin >> temp->sDistance;
//        cout << "What is the number of menu items?: ";
//        cin >> temp->NoOfMenuItems;
//        for(int i = 0; i < temp->NoOfMenuItems; i++)
//        {
//            cout << "What is the name of the menu item? ";
//            cin >> m.name;
//            cout << "What is the price of the menu item? ";
//            cin >> m.price;
//            temp->menuItems.push_back(m);
//        }
//        r1.push_back(*temp);
//        delete temp;
//        cout << "Do you want to add another restaurant? Enter Y/y for yes, N/n for no: ";
//        cin >> choice;
//    }while(choice == 'Y' || choice == 'y');
//}

//void removeRestaurant(list<Restaurant> &r1)
//{
//    string temp = "";
//    list<Restaurant> temp1;
//    list<Restaurant>::iterator it;
//    cout << "Which restaurant would you like to delete? Enter the name:  ";
//    cin >> temp;
//        for(it = r1.begin(); it != r1.end(); ++it)
//        {
//        if(it->getrName() == QString::fromStdString(temp))
//        {
//            break;
//        }
//    }
// r1.erase(it);
//}
void Restaurant::setTotalRev()
{
    totalRev = 0;
    for(unsigned int i = 0; i < menuItems.size(); i++)
    {
        totalRev += menuItems[i].price * menuItems[i].quantity;
    }
}

double Restaurant::getTotalRev()
{
    setTotalRev();
    return  totalRev;
}
string Restaurant::getrName()
{
   return rName;
}

double Restaurant::getsDistance()
{
    return sDistance;
}

int Restaurant::getId()
{
    return id;
}

vector<double> Restaurant::getDistances()
{
    return distance;
}

vector<menu> Restaurant::getMenu()
{
    return menuItems;
}

bool Restaurant::IsEmpty()
{
    return (rName == "");
}

void Restaurant::setName(string newName)
{
    rName = newName;
}

void Restaurant::setId(int newId)
{
    id = newId;
}

void Restaurant::setDistances(vector<double> distanceVec)
{
    for(double i = 0; i <= distanceVec.size(); i++)
    {
        distance.swap(distanceVec);
    }
}

void Restaurant::setNumberMenuItems(int menuItems)
{
    NoOfMenuItems = menuItems;
}

void Restaurant::setMenuItems(vector<menu> newMenues)
{
    menuItems.swap(newMenues);
}

//void Restaurant::output(list <Restaurant> restaurantList)
//{
//    ofstream outFile;
//    outFile.open("input.txt");
//    list<Restaurant>::iterator ptr;
//    for (ptr = restaurantList.begin(); ptr != restaurantList.end(); ++ptr)
//    {
//        outFile << ptr->getCounter() << endl;
//        ptr->counter = 1;
//        outFile << "Name of Fast Food Restaurant: " << ptr->getrName() << endl;
//        outFile << "Fast Food restaurant number " << ptr->getID() << endl << endl;
//        vector<double> dist = ptr->getDistances();
//        for (int i = 0; i < dist.size(); ++i)
//        {
//            outFile << dist[i] << endl;
//        }
//        outFile << ptr->getSDistance() << " miles to Saddleback College"<< endl;
//        outFile << ptr->getNoOfMenuItems() << " menu items" << endl;
//        vector<menu> mItems = ptr->getMenu();
//        for (int i = 0; i < mItems.size(); ++i)
//        {
//            outFile << mItems[i].name << endl;
//            outFile << mItems[i].price << endl;
//        }
//        ptr->counter++;
//        outFile << endl;
//    }
//    outFile.close();
//}

void Restaurant::setQty(int menuIndex, int qty)
{
    this->menuItems[menuIndex].quantity = qty;
}
