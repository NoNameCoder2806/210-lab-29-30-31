// COMSC-210 | Lab 30 | Dat Hoang Vien
// IDE used: Visual Studio Code

// Libraries
#include <iostream>
#include <string>

// Creature class
class Creature
{
private:
    string name;
    int level;
public:
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

    void setLevel()
}