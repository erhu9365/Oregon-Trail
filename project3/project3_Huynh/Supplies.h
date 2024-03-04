// CS1300 Fall 2020
// Author: Eric Huynh
// Recitation: 221 – Sanskar Katiyar
// Project 3
#ifndef SUPPLIES_H //helps when calling a class
#define SUPPLIES_H //defines the class
#include <iostream>
#include <string>

using namespace std;

class Supplies
{
    public: //where functions go
        Supplies(); //Default constructor
        Supplies(string title, float money); //parameterized constructor
        //Mutators: access and then update
        void setName(string n);
        void setAmount(float num);
        void setCost(float mon);
        //Accessors: get something, return
        string getName() const;
        float getAmount() const;
        float getCost() const;
        
    private: //where variables go
        string name;
        float number;
        float cost;
};

#endif //end if not defined