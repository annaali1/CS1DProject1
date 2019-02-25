#include "Restaurant.h"

int main(){
	Restaurant temp; 
	list<Restaurant> rest;
	
	rest = temp.readFile();

	for(auto v : rest)
	{
		cout << v << endl;
		cout << '\n' << '\n';
	}


return 0;
}
