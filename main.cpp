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
#include <vector>

// Headers
#include "Creature.h"

using namespace std;

// Constants
const int MIN_CREATURES = 3;
const int MAX_CREATURES = 5;
const int SIMULATIONS = 25;
const int LAND_INDEX = 0;
const int WATER_INDEX = 1;
const int AIR_INDEX = 2;
const int MIN_EVOLUTION_LEVEL = 5;
const int TOTAL_CHANCE = 100;
const int NEW_CREATURE_CHANCE = 40;
const int DELETE_CREATURE_CHANCE = 20;
const int EVOLVE_CHANCE = 10;
const string DATA_FILE = "data.txt";

// Function prototypes
void readData(map<string, array<list<Creature>, 3>> &allCreatures, string data_path);
void readCreatures(list<Creature> &creatureList, string line);
bool isEra(string line);
void displayList(const list<Creature> &creatureList);
void displayArray(const array<list<Creature>, 3> &creatureArray);
void displayMap(const map<string, array<list<Creature>, 3>> &creatureMap);
void populateEra(map<string, array<list<Creature>, 3>> &simulatedEras, const map<string, array<list<Creature>, 3>> &allCreatures, int eraIndex);
void addEvolvedCreatures(map<string, array<list<Creature>, 3>> &simulatedEras, int eraIndex);
void simulateEvents(map<string, array<list<Creature>, 3>> &simulatedEras, int eraIndex);
void evolve(array<list<Creature>, 3> &eraArray);
void newCreatures(array<list<Creature>, 3> &eraArray, const vector<string> &extinctedCreatures);
void extinction(array<list<Creature>, 3> &eraArray, vector<string> &extinctedCreatures);

// Main function
int main()
{
    // Call srand() and time()
    srand(time(0));

    // Create 2 maps, 1 to store the creatures list, another one to simulate
    map<string, array<list<Creature>, 3>> allCreatures;         // A map to store all the Creatures
    map<string, array<list<Creature>, 3>> simulatedEras;        // A map to simulate all the eras

    // Create a vector to store all extincted Creatures' names
    vector<string> extinctedCreatures;

    // Create a string to store the data path
    string data_path = DATA_FILE;

    // Read all the data and populate the allCreatures map
    readData(allCreatures, data_path);    

    // Display the data of the allCreatures map
    // displayMap(allCreatures);

    // Create a loop to simulate the eras
    for (int i = 0; i < allCreatures.size(); i++)
    {
        // Create an iterator
        auto it = allCreatures.begin();
        advance(it, i);

        // Store the era
        string era = it->first;
        string uppercasedEra = era;

        // Convert the string to uppercase
        transform(uppercasedEra.begin(), uppercasedEra.end(), uppercasedEra.begin(), [](unsigned char c)
        {
            return toupper(c);
        });

        // Display the era
        cout << " ===== " << uppercasedEra << " ===== " << endl;

        // Randomly add a number of Creatures into the first era
        populateEra(simulatedEras, allCreatures, i);

        // Add the high level Creatures from the previous era in
        addEvolvedCreatures(simulatedEras, i);

        // Display the Creatures in the array of the era
        displayArray(simulatedEras.at(era));

        // Simulate the events 25 times
        for (int j = 0; j < SIMULATIONS; j++)
        {
            // Display the simulation count
            cout << " # SIMULATION: " << j + 1 << endl;

            // Call the simulateEvents() function, pass in the map and the era index
            simulateEvents(simulatedEras, i);
        }

        // Enter a new line
        cout << endl;

        // Display result after simulation
        cout << " ----- AFTER SIMULATION ----- " << endl;
        cout << " ===== " << uppercasedEra << " ===== " << endl;
        
        // Display the Creatures in the array of the era
        displayArray(simulatedEras.at(era));

        // Display a barrier
        cout << "=================================================="          // Display 50 =         (50)
             << "=================================================="          // Display another 50 = (100)
             << "=================================================="          // Display another 50 = (150)
             << endl << endl;
    }

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
    displayArray()
    Display the Creatures from the array
    Arguments:
        - creatureArray: the array of Creatures (of the era)
    Return: none
*/
void displayArray(const array<list<Creature>, 3> &creatureArray)
{
    // Iterate through each list of the array
        for (int i = 0; i < creatureArray.size(); i++)
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
            displayList(creatureArray.at(i));
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

        // Display the array
        displayArray(creatureMap.at(pair.first));

        // Enter a new line
        cout << endl;
    }
}

/*
    populateEra()
    Populate an era with Creatures based on the allCreatures map
    Arguments:
        - simulatedEras: the map storing all the eras to simulate
        - allCreatures: the map storing all Creatures from all eras
        - eraIndex: the index of the era to simulate
    Return: none
*/
void populateEra(map<string, array<list<Creature>, 3>> &simulatedEras, const map<string, array<list<Creature>, 3>> &allCreatures, int eraIndex)
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

        // Create a vector for random access
        vector<Creature> originalVector(originalArray[i].begin(), originalArray[i].end());

        // Shuffle the list
        shuffle(originalVector.begin(), originalVector.end(), gen);

        // Copy first n shuffled creatures into a list
        list<Creature> creatureList(originalVector.begin(), originalVector.begin() + n);

        // Add the list into the era array
        eraArray[i] = creatureList;
    }

    // Add the array into the map
    simulatedEras.insert(make_pair(key, eraArray));
}

/*
    addEvolvedCreatures()
    Add the Creatures whose level is above MIN_EVOLUTION_LEVEL
    Arguments:
        - simulatedEras: the map of all the eras to simulate
        - eraIndex: the index of the era to simulate
    Return: none
*/
void addEvolvedCreatures(map<string, array<list<Creature>, 3>> &simulatedEras, int eraIndex)
{
    // If this is the first era, we skip
    if (eraIndex == 0)
    {
        // Exit the function
        return;
    }
    else        // Otherwise, add the Creatures whose evolution level are high
    {
        // Create an iterator and advance eraIndex - 1 positions
        auto it = simulatedEras.begin();
        advance(it, eraIndex - 1);

        // Get the previous era's key
        string prevKey = it->first;

        // Create another iterator and advance to eraIndex positions
        auto it2 = simulatedEras.begin();
        advance(it2, eraIndex);

        // Get this current era's key
        string currentKey = it2->first;

        // Iterate through each of the lists (land, water, air)
        for (int i = 0; i < it->second.size(); i++)
        {
            // Create another iterator to iterate through each of the lists
            auto it3 = it->second.at(i).begin();

            // Iterate through each Creature in the list
            while(it3 != it->second.at(i).end())
            {
                // Check the Creatures' evolution level
                if (it3->getLevel() >= MIN_EVOLUTION_LEVEL)
                {
                    // Display the Creature
                    cout << " - High level Creature: " << *it3 << " - " << endl;

                    // Copy into a new Creature
                    Creature temp = *it3;

                    // Reset the Ceature's evolution level
                    temp.resetLevel();

                    // Display the Creature's new info
                    cout << " --- Adding: " << temp << " --- " << endl;

                    // Add the Creature into the current Era
                    simulatedEras.at(currentKey).at(i).push_back(temp);
                }

                // Advance the iterator by 1 position
                advance(it3, 1);
            }
        }
    }
}

/*
    simulatedEvents()
    Simulate different events for the eras
    Arguments:
        - simulatedEras: the map of all the eras to simulate
    Return: none
*/
void simulateEvents(map<string, array<list<Creature>, 3>> &simulatedEras, int eraIndex)
{
    // Create an iterator and advance eraIndex positions
    auto it = simulatedEras.begin();
    advance(it, eraIndex);

    // Get the previous era's key
    string key = it->first;

    // Simulate all the events for that era (the array of the era)
    evolve(simulatedEras.at(key));
}

/*
    evolve()
    Evolve Creatures (each Creature has a 10% chance)
    Arguments:
        - eraArray: the array storing all the Creatures of the era
    Return: none
*/
void evolve(array<list<Creature>, 3> &eraArray)
{
    // Iterate through the array
    for (int i = 0; i < eraArray.size(); i++)
    {
        // Create an iterator
        auto it = eraArray[i].begin();

        // Iterate through each lists
        while (it != eraArray[i].end())
        {
            // Generate a random number
            int chance = rand() % TOTAL_CHANCE + 1;

            // Compare the chance
            if (chance <= EVOLVE_CHANCE)
            {
                // Evolve the Creature
                it->increaseLevel();
                
                // Display a message
                cout << " --- " << it->getName() << " has evolved! --- " << endl;
            }

            // Advance the iterator by 1 position
            advance(it, 1);
        }
    }
}

/*
    addCreatures()
*/
void addCreatures(array<list<Creature>, 3> &eraArray, const vector<string> &extinctedCreatures)
{
}

void extinction(array<list<Creature>, 3> &eraArray, vector<string> &extinctedCreatures)
{
}