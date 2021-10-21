#include "Map.h"
#include "MapDriver.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;
#include <iostream>
using namespace std;

Map readfile(string filename)
{
	string fileText;
	ifstream input;
	int orderOperation = 0;
	bool check = false;
	int mode = 0; //this indicated the mode of construction: 0 default, 1 continents, 2 countries, 3 borders 
	int counter = 0;
	string country;
	string delim = " ";
	int int1, int2, int3;
	size_t pos;
	input.open(filename);
	input >> fileText;
	Map map;
	//reading the file line by line
	while (getline(input, fileText))
	{

		//cheking if the order is correct
		if (orderOperation == 4)
		{
			break;
		}
		//beggining the creation of the continentns
		if (fileText == "[continents]")
		{
			orderOperation = 1;
			counter = 0;
			cout << "continent" << endl;
			while (getline(input, fileText))
			{
				counter++;
				//ending the continents
				if (fileText == "[countries]")
				{
					break;
				}
				//this repeating while loop 
				while ((pos = fileText.find(delim)) != string::npos) 
				{
					map.addContinent((fileText.substr(0, pos)), counter);
					fileText.erase(0, pos + delim.length());
					//need to add another part to read and add the bonus for continent integer
					break;
				}

			}
		}
		check = false;
		//beggining the making of the land vector in the map that contains all od the territories
		if (fileText == "[countries]")
		{

			//cheking if the order is correct
			if (orderOperation != 1)
			{
				cout << "invalid file submitted, pleas input a valid Map file" << endl;
				orderOperation = 4;
				break;
			}
			orderOperation = 2;
			while (getline(input, fileText))
			{
				counter = 0;
				//ending if we rech borders
				if (fileText == "[borders]")
				{
					break;
				}
				while ((pos = fileText.find(delim)) != string::npos && !check)
				{
					//skipping anythign prior to the introduction of the first map element (that should starts with a 1)
					if ((fileText.substr(0, pos)) == "1")
					{
						check = true;
						break;
					}
					fileText.erase(0, pos + delim.length());
					
				}
				
				while ((pos = fileText.find(delim)) != string::npos && check)
				{
					if (counter == 0)
					{
						int1 = stoi(fileText.substr(0, pos));
					}
					if (counter == 1)
					{
						country = (fileText.substr(0, pos));
					}
					if (counter == 2)
					{
						int3 = stoi(fileText.substr(0, pos));
					}
					fileText.erase(0, pos + delim.length());
					counter++;
					if (counter == 3)
					{
						//making the territory and adding it to the map
						map.addTerritory(int1 -1, country, int3 -1);
						//adding the territory to the appropriate continent
						//here the continent only holds the index of the territory and not a pointer since the vector changes with each addition
						map.addToContinent(int3 -1, int1 -1);
						break;
					}
				}

			}
		}
		check = false;
		//making the borders
		if (fileText == "[borders]")
		{
			//cheking if the order is correct
			if (orderOperation != 2)
			{
				cout << "invalid file submitted, pleas input a valid Map file" << endl;
				orderOperation = 4;
				break;
			}
			orderOperation = 3;
			while (getline(input, fileText))
			{
				counter = 0;
				while ((pos = fileText.find(delim)) != string::npos && !check)
				{
					//skipping anythign prior to the introduction of the first map element (that should starts with a 1)
					if ((fileText.substr(0, pos)) == "1")
					{
						check = true;
						break;
					}
					fileText.erase(0, pos + delim.length());
				}
				//start of reading approptiate border digits 
				while ((pos = fileText.find(delim)) != string::npos && check)
				{
					//counter to help the program catch the first element of the line
					counter++;
					int1 = stoi(fileText.substr(0, pos));
					if (counter == 1)
					{
						//getting the ID of the territory who's borders are being declared
						int2 = int1;
					}
					else
					{
						map.addBorders(int2, int1);
					}
					fileText.erase(0, pos + delim.length());
				}
				// this is a condition for the parser not to break since the parser only takes everything between 2 " " 
				//characters it normally doesn't catch the last digit for the borders, however on rare occasions the line
				//ende with a " " and so, to aboit both, here the if checks that a) the file is actually in the right place
				//the check implies it hit a 1 after starting to read [borders] so the rest should be ints, b) ensures that the
				//string remainder isn't of length 0 after deleting the previous integer
				if(check && fileText.length()>0)
				{
					int1 = stoi(fileText);
					//adding the borders to the pre determines territory
					map.addBorders(int2, int1);
				}
				//end of reding appropriate border digits
			}
		}
	}
	if (orderOperation !=3)
	{
		cout << "Incorrect file submitted, pleas submit a valid file"<<endl;
	}
	input.close();
	return map;
}
		
void MapDriverDemo()
{
	string filename;
	cout << "pleas enter the name of the file for the map generation" << endl;
	cin >> filename;
	Map map = readfile(filename);
	cout << "map has been made" << endl;
	if (validate(map))
	{
		cout << "the map is valid!!" << endl;
	}
	else
	{
		cout << "the map is not valid!!" << endl;
	}
}