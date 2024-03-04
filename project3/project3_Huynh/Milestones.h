// CS1300 Fall 2020
// Author: Eric Huynh
// Recitation: 221 – Sanskar Katiyar
// Project 3
#ifndef MILESTONES_H //helps when calling a class
#define MILESTONES_H //defines the class
#include <iostream>
#include <string>

using namespace std;

class Milestones
{
    public: //where functions go
        Milestones(); //Default constructor
        //Mutators: access and then update
        void setInfo();
        //Accessors: get something, return
        string getName() const;
        int getMiles() const;
        string getType() const;

    private: //where variables go
        string name[15]; //holds the names of each landmark, fort, and river
        int miles[15]; //holds the miles to each landmark, fort, and river from the starting point
        string type[15]; //holds the type of place (landmark, fort, or river)
        int nameland;
        int milesland;
        int typeland;
};

#endif //end if not defined