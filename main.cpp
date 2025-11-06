// COMSC-210 | Lab 30 | Dat Hoang Vien
// IDE used: Visual Studio Code

// Libraries
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <array>
#include <list>

// Headers
#include "Creature.h"

using namespace std;

// Constants
const int MIN_CREATURES = 3;
const int MAX_CREATURES = 5;
const int LAND_INDEX = 0;
const int WATER_INDEX = 1;
const int AIR_INDEX = 2;
const string DATA_FILE = "data.txt";

// Function prototypes
void readData(map<string, array<list<Creature>, 3>> &allCreatures, string data_path);
void readCreatures(list<Creature> &creatureList, string line);
bool isEra(string line);
void displayMap(map<string, array<list<Creature>, 3>> &creatureMap);

// Main function
int main()
{
    // Create 2 maps, 1 to store the creatures list, another one to simulate
    map<string, array<list<Creature>, 3>> allCreatures;         // A map to store all the Creatures
    map<string, array<list<Creature>, 3>> simulatedEras;        // A map to simulate all the eras

    // Create a string to store the data path
    string data_path = DATA_FILE;

    // Read all the data and populate the allCreatures map
    readData(allCreatures, data_path);    

    // Display the data of the allCreatures map
    displayMap(allCreatures);

    // Randomly add a number of creatures into each

    return 0;
}

// Function implementation
void readData(map<string, array<list<Creature>, 3>> &allCreatures, string data_path)
{
    // Create a file stream
    ifstream fin;
    fin.open(data_path);

    // Check for file open failure
    if (!fin)
    {
        // Display an error message
        cerr << "Error opening file" << endl;
        
        // Exit the function
        return;
    }

    // Create a string to store the line's data
    string line;

    // Create a string and 3 lists to store the key, and the creatures of each category
    string key;                           // The key for the map
    list<Creature> landCreatures;         // Land Creatures list
    list<Creature> waterCreatures;        // Water Creatures list
    list<Creature> airCreatures;          // Air Creatures list

    // Read the data file
    while(getline(fin, line))
    {
        // Check for empty lines
        if (line.empty())
        {
            continue;
        }

        // Check for the era
        if (isEra(line))
        {
            // If this line is the era, we store the key
            key = line;

            // We clear all the lists as well
            landCreatures.clear();
            waterCreatures.clear();
            airCreatures.clear();

            // Skip to the next line
            continue;
        }

        // Check for the Creatures type
        if (line.find("LAND: ") == 0)
        {
            // Store the land creatures into the list
            readCreatures(landCreatures, line);
        }
        else if (line.find("WATER: ") == 0)
        {
            // Store the water creatures into the list
            readCreatures(waterCreatures, line);
        }
        else if (line.find("AIR: ") == 0)
        {
            // Store the air creatures into the list
            readCreatures(airCreatures, line);
        }

        // Create an array and insert all the lists into it
        array<list<Creature>, 3> creaturesArray;
        creaturesArray[LAND_INDEX] = landCreatures;
        creaturesArray[WATER_INDEX] = waterCreatures;
        creaturesArray[AIR_INDEX] = airCreatures;

        // Make the data a pair and insert it into the map
        allCreatures.insert(make_pair(key, creaturesArray));
    }
}

void readCreatures(list<Creature> &creatureList, string line)
{
    // Remove the Creature category at the beginning of the line
    if (line.find("LAND: ") == 0)
    {
        // Remove the first 6 characters;
        line = line.substr(6);
    }
    else if (line.find("WATER: ") == 0)
    {
        // Remove the first 7 characters
        line = line.substr(7);
    }
    else if (line.find("AIR: ") == 0)
    {
        // Remove the first 5 characters
        line = line.substr(5);
    }

    // Create a string variable to store the name
    string name;

    // Split the Creatures and add to the list
    while (line.size() != 0)
    {
        // Create a new string from the start of the line to ", "
        name = line.substr(0, line.find(", "));

        // Create a new Creature and add to the list
        Creature c(name);
        creatureList.push_back(c);

        // Check whether there are anymore ", " (commas)
        if (line.find(", ") != string::npos)
        {
            // Cut the string from the Creature's name + ", " til the end
            line = line.substr(name.size() + 2);
        }
        else
        {
            // Exit the loop
            break;
        }
    }
}

bool isEra(string line)
{
    // Check whether it is one of the eras or not
    if (line == "Triassic" || line == "Jurassic" || line == "Cretaceous")
    {
        return true;
    }

    // Otherwise
    return false;
}

void displayMap(map<string, array<list<Creature>, 3>> &creatureMap)
{
    // Iterate through each pair of data
    for (auto pair : creatureMap)
    {
        // Display the era
        cout << " --- Era: " << pair.first << " --- " << endl;

        // Iterate through each list of the array
        for (int i = 0; i < pair.second.size(); i++)
        {
            // Display the type (land, water, air)
            if (i == 0)
            {
                // Land Creatures
                cout << " - Land Creatures: ";
            }
            else if (i == 1)
            {
                // Water Creatures
                cout << " - Water Creatures: ";
            }
            else if (i == 2)
            {
                // Air Creatures
                cout << " - Air Creatures: ";
            }

            // Iterate and display the Creatures in the list
            for (auto it = pair.second.at(i).begin(); it != pair.second.at(i).end(); ++it)
            {
                // Display the Creature using operator<<() function
                cout << *it;

                // Check if this is the last item of the list
                if (std::next(it) != pair.second.at(i).end())
                {
                    // Display ", " if it's not (the last item of the list)
                    cout << ", ";
                }
            }

            // Enter a new line
            cout << endl;
        }

        // Enter a new line
        cout << endl;
    }
}