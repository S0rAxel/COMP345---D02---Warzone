#pragma once
#include <vector>
#include <string>
using namespace std;

class territory
{
public:
	territory(int id, string n, int c);
	string getOwner();
	string getName();
	void setOwner(string o);
	int getID();
	void setContinent(int c);
	void addBorders(territory* t);
	int getNumOfBorders();
	int getBorderID(int pos);
private:
	int numOfArmies;
	vector<territory*> borders; //vector of pointers to neigboting territories
	string owner;
	int continent;
	string name; 
	int ID; //ID of the territory (1 above its index in the <vector>)
};
class continent
{
public:
	int getID();
	string getName();
	continent(string n, int id, int bonus);
	int getLength();
	int getTerrID(int index);
	void addTerrID(int id);
	int getBonus();
private:
	int bonus;
	string name;
	int ID;
	vector<int> terrIDs;
};

class Map
{
public:
	Map();
	void addTerritory(int id,string n, int c);
	void addContinent(string n, int id);
	continent* getContinent(int id);
	territory* getTerritory(int id);
	void addBorders(int territory, int border);
	int getNumOfTerr();
	int getNumOfCont();
	void addToContinent(int c, int t);
private:
	vector<territory> land;
	vector<continent> continents;
};


bool validate(Map m);

void validateMap(Map m, vector<int>& memory, int reference);

void validateContinent(Map m, int c, vector<int>& memory, int reference);


