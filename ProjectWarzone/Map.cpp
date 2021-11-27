#include "Map.h"
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;

territory::territory(int id, string n, int c) :ID(id), name(n), continent(c)
{
	numOfArmies = 0;
}
//need to add somehting to include the bonnus
continent::continent(string n, int id, int bonus) :name(n), ID(id), Bonus(bonus)
{
	terrIDs;
}

Map::Map()
{
	land; 
	continents;
}
//the terriroty object is generated within the Map object that way it stays within scope while on the stack
void Map::addTerritory(int id, string n, int c)
{
	land.push_back(territory(id, n, c));
};

void Map::addToContinent(int c, int t)
{
	getContinent(c)->addTerrID(t);
}

void continent::addTerrID(int t)
{
	terrIDs.push_back(t);
}

territory* Map::getTerritory(int id)
{
	return &land[id];
}

continent* Map::getContinent(int id)
{
	return &continents[id];
}

int territory::getNumOfBorders()
{
	return borders.size();
}

int continent::getLength()
{
	return terrIDs.size();
}

int continent::getBonus()
{
	return Bonus;
}

void Map::addBorders(int territory, int border)
{
	land[territory - 1].addBorders(&land[border - 1]);
}

void territory::addBorders(territory* t)
{
	borders.push_back(t);
}
//need to add somehting here as well about the bonus
void Map::addContinent(string name, int id, int bonus)
{
	continents.push_back(continent(name, id, bonus));
};

Player* territory:: getOwner()
{
	return owner;
};

int Map::getNumOfTerr()
{
	return land.size();
}

string territory::getName()
{
	return name;
};

string continent::getName()
{
	return name;
}

void territory::setOwner(Player* o)
{
	owner = o;
};

int territory::getID()
{
	return ID;
}

int continent::getID()
{
	return ID;
}

void territory::setContinent(int c)
{
	continent = c;	
}

int territory::getBorderID(int pos)
{
	return borders[pos]->getID();
}

bool territory::isAdjacentTerritory(territory* target)
{
	std::vector<territory*>::iterator it = std::find(borders.begin(), borders.end(), target);
	if (it != borders.end())
	{
		return true;
	}
	return false;
}

int Map::getNumOfCont()
{
	return continents.size();
}

int continent::getTerrID(int index)
{
	return terrIDs[index];
}

bool validate(Map m)
{
	vector<int> memory;
	//testing the map starting from every possible territory on the map
	for ( int i =0; i < m.getNumOfTerr(); i++)
	{
		memory.clear();
		validateMap(m, memory, i);
		if (memory.size() != m.getNumOfTerr())
		{
			cout << memory.size() << " mem vs actual " << m.getNumOfTerr() << endl;
			cout << "invalid map" << endl;
			return false;
		}
	}
	//the testing for each continent
	for (int i = 0; i < m.getNumOfCont(); i++)
	{
		//starting from every territory in the continent
		for (int j = 0; j < m.getContinent(i)->getLength(); j++)
		{
			memory.clear();
			validateContinent(m, i, memory, m.getContinent(i)->getTerrID(j));
			if (memory.size() != m.getContinent(i)->getLength())
			{
				cout << memory.size() << " mem vs actual " << m.getContinent(i)->getLength() << endl;
				cout << "invalid map" << endl;
				return false;
			}
		}
		
	}
	return true;
}
void validateMap(Map m, vector<int>& memory, int reference)
{
	//adds the current ID to the memory
	memory.push_back(reference);
	bool been;
	for (int i = 0; i < m.getTerritory(reference)->getNumOfBorders(); i++)
	{
		been = false;
		//the following loop checks if the country ID is already in the memory vector
		for (int j = 0; j < memory.size(); j++)
		{
			if (m.getTerritory(reference)->getBorderID(i) == memory[j])
			{
				been = true;
				break;
			}
		}
		//if the country ID isn't in the memory vector, then that country is used as the new start off pointz
		if (been)
		{
			continue;
		}
		validateMap(m, memory, m.getTerritory(reference)->getBorderID(i));
	}
}

void validateContinent(Map m, int c, vector<int>& memory, int reference)
{
	//instering current location into the memory
	memory.push_back(reference);
	bool been;;
	bool inContinent;
	for (int i = 0; i < m.getTerritory(reference)->getNumOfBorders(); i++)
	{
		been = false;
		inContinent = false;
		//ensures not to call the functiont again on territory that the code has already been in
		for (int j = 0; j < memory.size(); j++)
		{
			if (m.getTerritory(reference)->getBorderID(i) == memory[j])
			{
				been = true;
				break;
			}
		}
		//ensures that the only territories called are within the continent
		for (int j = 0; j < m.getContinent(c)->getLength(); j++)
		{
			if (m.getTerritory(reference)->getBorderID(i) == m.getContinent(c)->getTerrID(j))
			{
				inContinent = true;
				break;
			}
		}
		if (!been && inContinent)
		{
			validateContinent(m, c, memory, m.getTerritory(reference)->getBorderID(i));
		}

	}
}
