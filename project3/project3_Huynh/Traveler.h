// CS1300 Fall 2020
// Author: Eric Huynh
// Recitation: 221 – Sanskar Katiyar
// Project 3
#ifndef TRAVELER_H //helps when calling a class
#define TRAVELER_H //defines the class
#include <iostream>
#include <string>
#include "Date.h"
#include "Milestones.h"
#include "Group.h"
#include "Supplies.h" //all .h files = reference to blueprint file

using namespace std;

class Traveler
{
    public: //where functions go
        Traveler(); //Default constructor
        Traveler(int shop); //set for shop materials
        //Mutators: access and then update
        void setMaterialAmount(int namount, int index);
        void setMaterialCost(float ncost, int index);
        void setPlayerStatus(bool status, int index);
        void setPlayerSick(int days, int index);
        void setTimeMonth(int month);
        void setTimeDay(int day);
        void setBalance(float nbalance);
        void setMiles(int nmiles);
        void setCheckpoint();
        //Accessors: get something, return
        Date getTime() const;
        Group getPlayer(int in) const;
        Supplies getMaterials(int mat) const;
        float getMaterialsAmount(int mat) const;
        Milestones getCheckpoint() const;
        float getBalance() const;
        int getMiles() const;

    private: //where variables go
        Date time; //stores objects for time/date
        Group players[5]; //stores all wagon members
        Supplies materials[5]; //stores all materials/supplies
        float balance;
        int miles;
        Milestones checkpoint; //stores object for milestone/checkpoints
};

#endif //end if not defined