#include <iostream>
#include <list>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
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
		string id;
		int NoOfMenuItems;
	public:
		Restaurant();
		list<Restaurant> readFile();
		friend ostream& operator<<(ostream& os, const Restaurant& rest);
};

Restaurant::Restaurant()
{
	rName = "";
	id = "";
	sDistance = "";
}

list<Restaurant> Restaurant::readFile()
{
	list<Restaurant> r1;
	ifstream inFile;
	double d = 0.0, doublePrice;
	string menItems, dist, item, dprice;
	menu m;
	m.name =  "";
	m.price = 0.0;

	inFile.open("input.txt");
	while(!inFile.eof()){
		Restaurant *temp = new Restaurant;
		inFile.ignore(30,':');
		getline(inFile, temp->rName);
		inFile.ignore('\n');
		getline(inFile, temp->id);
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

ostream& operator<<(ostream& os, const Restaurant& rest)
{
	os << "restaurant name: " << rest.rName << endl;
	os  << rest.id << endl;
	os << "restaurant distance: ";
        for(int i = 0; i < rest.distance.size(); i++)
        {
                cout << rest.distance[i] << endl;
        }
        os << " Distance from Saddleback: " << rest.sDistance << endl;
	os << "Number of menu items: " << rest.NoOfMenuItems << endl;
	for(int i = 0; i < rest.NoOfMenuItems; i++)
	{
		cout << rest.menuItems[i].name << endl;
		cout << rest.menuItems[i].price << endl;
	}
	return os;
}
