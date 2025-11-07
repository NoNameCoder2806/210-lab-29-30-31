// COMSC-210 | Lab 30 | Dat Hoang Vien
// IDE used: Visual Studio Code

// Libraries
#include <iostream>
#include <string>
using namespace std;

// Creature class
class Creature
{
private:
    string name;        // The name of the Creature
    int level;          // The evolution level of the Creature

public:
    // Constructors
    Creature()                       // Default constructor
    {
        name = "";
        level = 0;
    }

    Creature(string n)               // Parameters constructor (name only)
    {
        name = n;
        level = rand() % 3;
    }

    Creature(string n, int l)        // Parameters constructor (name and level)
    {
        name = n;
        level = l;
    }

    // Accessors / Getters
    string getName()
    {
        return name;
    }

    int getLevel()
    {
        return level;
    }
    
    // Mutators / Setters
    void setName(string n)
    {
        name = n;
    }

    void setLevel(int l)
    {
        level = l;
    }

    // Member functions
    void increaseLevel()        // Increase evolution level by 1
    {
        level++;
    }

    void decreaseLevel()        // Decrease evolution level by 1
    {
        level--;
    }

    void resetLevel()           // Reset the evolution level
    {
        level = 0;
    }

    friend ostream& operator<<(ostream &o, const Creature& c)        // Overload the << operator
    {
        return o << c.name << "(" << c.level << ")";
    }
};