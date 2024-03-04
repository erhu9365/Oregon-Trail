// CS1300 Fall 2020
// Author: Eric Huynh
// Recitation: 221 – Sanskar Katiyar
// Project 3
#include <iostream>
#include <string>
#include "Group.h" //reference to blueprint file

using namespace std;

Group::Group() //Default constructor
{
    name = "None";
    alive = false;
    sick = 0;
}
Group::Group(string user) //parameterized constructor (set the leader/companion's name and status as alive)
{
    name = user;
    alive = true;
    sick = 0;
}

void Group::setName(string n) //sets the player's name
{
    name = n;
}
void Group::setStatus(bool sta) //sets the player's status
{
    alive = sta;
}
void Group::setSick(int s) //sets the player's sick days
{
    sick = s;
}

string Group::getName() const //returns the player's name
{
    return name;
}
bool Group::getStatus() const //returns the player's status
{
    return alive;
}
int Group::getSick() const //returns the player's sick days
{
    return sick;
}