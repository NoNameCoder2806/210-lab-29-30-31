// COMSC-210 | Lab 31 | Dat Hoang Vien
// IDE used: Visual Studio Code

// Libraries
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
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
void displayList(const list<Creature> &creatureList);
void displayMap(const map<string, array<list<Creature>, 3>> &creatureMap);
void populateList(map<string, array<list<Creature>, 3>> &simulatedEras, const map<string, array<list<Creature>, 3>> &allCreatures, int eraIndex);

// Main function
int main()
{
    // Call srand() and time()
    srand(time(0));

    // Create 2 maps, 1 to store the creatures list, another one to simulate
    map<string, array<list<Creature>, 3>> allCreatures;         // A map to store all the Creatures
    map<string, array<list<Creature>, 3>> simulatedEras;        // A map to simulate all the eras

    // Create a string to store the data path
    string data_path = DATA_FILE;

    // Read all the data and populate the allCreatures map
    readData(allCreatures, data_path);    

    // Display the data of the allCreatures map
    displayMap(allCreatures);

    // Randomly add a number of Creatures into the first era
    

    return 0;
}

// Function implementation
/*
    readData()
    Read the data from the file data.txt and populate the map
    Arguments:
        - allCreatures: the map containing all the Creatures from all eras (passed by reference)
        - data_path: the path to the data file
    Return: none
*/
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

    // Create a string, an array, and 3 lists to store the key, and the creatures of each category
    string key;                                     // The key for the map
    array<list<Creature>, 3> creaturesArray;        // Array to store all the Creatures lists
    list<Creature> landCreatures;                   // Land Creatures list
    list<Creature> waterCreatures;                  // Water Creatures list
    list<Creature> airCreatures;                    // Air Creatures list

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

            // Insert the list into the array
            creaturesArray[LAND_INDEX] = landCreatures;
        }
        else if (line.find("WATER: ") == 0)
        {
            // Store the water creatures into the list
            readCreatures(waterCreatures, line);

            // Insert the list into the array
            creaturesArray[WATER_INDEX] = waterCreatures;
        }
        else if (line.find("AIR: ") == 0)
        {
            // Store the air creatures into the list
            readCreatures(airCreatures, line);

            // Insert the list into the array
            creaturesArray[AIR_INDEX] = airCreatures;

            // Insert the data into the map after Air Creatures were read
            allCreatures.insert(make_pair(key, creaturesArray));
        }
    }
}

/*
    readCreatures()
    Read the Creatures data from a line and populate the list
    Arguments:
        - creatureList: a list of Creatures (passed by reference)
        - line: the data line
    Return: none
*/
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

/*
    isEra()
    Check whether the line of string is the name of an era or not
    Arguments:
        - line: a string
    Return:
        - true if the line is a name of an era
        - false if otherwise
*/
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

/*
    displayList()
    Display the Creatures from the list
    Arguments:
        - creatureList: the list of Creatures (passed by const reference)
    Return: none
*/
void displayList(const list<Creature> &creatureList)
{
    // Iterate and display the Creatures in the list
    for (auto it = creatureList.begin(); it != creatureList.end(); ++it)
    {
        // Display the Creature using operator<<() function
        cout << *it;

        // Check if this is the last item of the list
        if (std::next(it) != creatureList.end())
        {
            // Display ", " if it's not (the last item of the list)
            cout << ", ";
        }
    }

    // Enter a new line
    cout << endl;
}

/*
    displayMap()
    Display all the eras of the map and all the Creatures of those eras
    Arguments:
        - creatureMap: the map of eras and the Creatures of those eras (passed by const reference)
    Return: none
*/
void displayMap(const map<string, array<list<Creature>, 3>> &creatureMap)
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

            // Display the Creatures in the list
            displayList(pair.second.at(i));
        }

        // Enter a new line
        cout << endl;
    }
}

/*
    populateList()
    Populate one of the list (an era) with Creatures based on the allCreatures map
    Arguments:
        - simulatedEras: the map storing all the eras to simulate
        - allCreatures: the map storing all Creatures from all eras
        - eraIndex: the index of the era to simulate
    Return: none
*/
void populateList(map<string, array<list<Creature>, 3>> &simulatedEras, const map<string, array<list<Creature>, 3>> &allCreatures, int eraIndex)
{
    // Create an iterator and advance eraIndex positions
    auto it = allCreatures.begin();
    advance(it, eraIndex);

    // Create variables to store the key and the Creatures lists
    string key = it->first;                                     // The key (the name of the era, i.e. "Jurassic")
    array<list<Creature>, 3> originalArray = it->second;        // The original array of Creatures
    array<list<Creature>, 3> eraArray;                          // The array we are going to use

    // Setup a random generator
    random_device rd;
    mt19937 gen(rd());

    // Iterate through the array
    for (int i = 0; i < originalArray.size(); i++)
    {
        // Generate a random number of Creatures
        int n = rand() % (MAX_CREATURES - MIN_CREATURES + 1) + MIN_CREATURES;

        // Create a list and copy the Creatures into it
        list<Creature> originalList = originalArray[i];

        // Create our own Creature list
        list<Creature> creatureList;

        // Shuffle the list
        shuffle(originalList.begin(), originalList.end(), gen);

        // Copy the first n elements into our Creature list
        for (int j = 0; j < n; j++)
        {
            // Create another iterator to get the element
            // Note: we use next() instead of advance() to keep the original position
            auto it2 = next(originalList.begin(), j);

            // Add the Creature at the index into the list
            creatureList.push_back(*it2);
        }
    }
}