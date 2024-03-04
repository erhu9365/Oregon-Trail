// CS1300 Fall 2020
// Author: Eric Huynh
// Recitation: 221 – Sanskar Katiyar
// Project 3
#include <iostream>
#include <string>
#include "Supplies.h" //reference to blueprint file

using namespace std;

Supplies::Supplies() //Default constructor
{
    name = "None";
    number = 0;
    cost = 0;
}
Supplies::Supplies(string title, float money) //parameterized constructor
{
    //set the name and cost of the supply while the amount equals 0
    name = title;
    number = 0;
    cost = money;
}
void Supplies::setName(string n) //set the name of the supply
{
    name = n;
}
void Supplies::setAmount(float num) //set the amount of the supply
{
    number = number + num;
}
void Supplies::setCost(float mon) //set the cost of the supply
{
    cost = mon;
}
string Supplies::getName() const //returns the name of the supply
{
    return name;
}
float Supplies::getAmount() const //returns the amount of the supply
{
    return number;
}
float Supplies::getCost() const //returns the cost of the supply
{
    return cost;
}
