#include "Restaurant.h"

Restaurant::Restaurant()
{
    rName = "";
    id = 0;
    sDistance = "";
}

Restaurant::Restaurant(string name)
{
    rName = name;
    id = 0;
    sDistance = "";
}

//void Restaurant::editMenu()
//{
//    string itemname = "";
//    double newprice = 0.0;
//    menu mitem;
//    int check = 0;
//    cout << " Which menu item would you like to edit? "; // These parts will be implemented in QT***
//    getline(cin, itemname); 									 //***
//    cout << endl;										 //***
//    vector <menu> ::iterator ptr;
//    for (ptr = menuItems.begin(); ptr != menuItems.end(); ++ptr)
//    {
//        mitem = *ptr;
//        if (mitem.name == itemname)
//        {
//            ++check;
//            break;
//        }
//    }
//    if (check == 0)
//    {
//        cout << " Menu item not found. Please make sure you entered the item correctly. " << endl;
//        return;
//    }
//    cout << " What would you like to change the price of " << mitem.name << " to?: ";// These parts will be implemented in QT***
//    cin >> newprice;															   //***

//    mitem.price = newprice;
//    *ptr = mitem;
//    cout << endl;
//    for (unsigned int i = 0; i < menuItems.size(); ++i)
//    {
//        cout << menuItems[i].name << endl;
//        cout << menuItems[i].price << endl;
//    }
//    cout << endl;

//}

//void Restaurant::addMenu()
//{
//    string tempname = "";
//    double tempprice = 0.0;
//    cout << endl << " What will be the name of the menu item?: ";//***implemented in QT
//    getline(cin, tempname); //***implemented in QT
//    cout << endl << " What will be the price of the menu item?: "; //***implemented in QT
//    cin >> tempprice; //***implemented in QT
//    menu tempmenu;
//    tempmenu.name = tempname;
//    tempmenu.price = tempprice;

//    menuItems.push_back(tempmenu);


//    cout << endl;
//    for (unsigned int i = 0; i < menuItems.size(); ++i)
//    {
//        cout << menuItems[i].name << endl;
//        cout << menuItems[i].price << endl;
//    }
//    cout << endl;
//}

//void Restaurant::deleteMenu()
//{
//    string tempname = "";
//    int check = 0;
//    cout << endl << " What is the name of the menu item you'd like to delete?: ";
//    getline(cin, tempname);

//    //vector <menu> ::iterator ptr;
//    for (unsigned int i = 0; i < menuItems.size(); ++i)
//    {

//        if (menuItems[i].name == tempname)
//        {
//            menuItems.erase(menuItems.begin()+i);
//            ++check;
//            break;
//        }
//    }
//    if (check == 0)
//    {
//        cout << " Menu item not found. Please make sure you entered the item correctly. " << endl;
//    }
//    cout << endl;
//    for (unsigned int i = 0; i < menuItems.size(); ++i)
//    {
//        cout << menuItems[i].name << endl;
//        cout << menuItems[i].price << endl;
//    }
//    cout << endl;
//}

//This method will pop the restaurant list using a file SPECIFIC to the user
list<Restaurant> Restaurant::PopRestaurantList()
{
    list<Restaurant> r1;
    string file = "C:/Users/lukes/OneDrive/Desktop/CS1DProject1/FastFoodFinder/restaurants.txt";
    ifstream inFile;
    double d = 0.0, doublePrice;
    string menItems, dist, item, dprice;
    menu m;
    m.name =  "";
    m.price = 0.0;

    inFile.open(file);
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
        for(int i = 0; i < 10; i++)
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
            m = {item, doublePrice};
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
    string menItems, dist, item, dprice;
    menu m;
    m.name =  "";
    m.price = 0.0;

    inFile.open(file);
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
        for(int i = 0; i < 10; i++)
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
            m = {item, doublePrice};
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


string Restaurant::getrName()
{
   return rName;
}

string Restaurant::getsDistance()
{
    return sDistance;
}

int Restaurant::getId()
{
    return id;
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
