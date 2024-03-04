// CS1300 Fall 2020
// Author: Eric Huynh
// Recitation: 221 – Sanskar Katiyar
// Project 3
#ifndef GROUP_H //helps when calling a class
#define GROUP_H //defines the class
#include <iostream>
#include <string>

using namespace std;

class Group
{
    public: //where functions go
        Group(); //Default constructor
        Group(string name); //parameterized constructor
        //Mutators: access and then update
        void setName(string n);
        void setStatus(bool sta);
        void setSick(int s);
        //Accessors: get something, return
        string getName() const;
        bool getStatus() const;
        int getSick() const;
        
    private: //where variables go
        string name;
        bool alive;
        int sick;
};

#endif //end if not defined
