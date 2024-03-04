// CS1300 Fall 2020
// Author: Eric Huynh
// Recitation: 221 – Sanskar Katiyar
// Project 3
#include <iostream>
#include <string>
#include "Traveler.h" //reference to blueprint file

using namespace std;
/*
The constructor is used to get information on the group and what date they would like to start on.
1. The user inputs the name of the leader along with the companions
2. The user is asked if they want to start on the default date or on another date in a specificed range --> creates time object
3. Then the milestone object is created, balance of group, and and miles
4. The necessary materials are also created and set.
*/
Traveler::Traveler()
{
    string leader = "";
    string companion = "";
    while (true) //runs until it reaches the break statement
    {
        cout << "What is the first name of the wagon leader?" << endl;
        getline(cin, leader); //user inputs leader's name
        if(leader != "") //if the given name is not an empty string
        {
            Group player = Group(leader); //creates a new person with name
            players[0] = leader; //set players[0] as the leader 
            break;
        }
        else
        {
            cout << "Sorry, your leader must have a name." << endl;
        }
    }
    cout << "And who are your companions who will be joining you on your journey?" << endl;
    for(int i = 1; i < 5; i++) //loops to create 4 other companions (until all 4 are created)
    {
        while(true) //runs until it reaches the break statement
        {
            cout << i << ":" << endl;
            getline(cin, companion); //user inputs name of companion(s)
            if(companion != "")
            {
                Group player = Group(companion); //creates a new companion with name
                players[i] = companion; //puts new companion into players array
                break; //while statement ends
            }
            else
            {
                cout << "Sorry, your companion must have a name." << endl;
            }   
        }
    }
    string choice;
    cout << "The starting date is March 28, 1847. Would you like to start on a different date? Y for yes, N or no." << endl;
    getline(cin, choice); //user inputs either yes or no
    if(choice == "Y" || choice == "y") //if y, user changes date to a different date
    {
        string Sday;
        string month;
        cout << "It must be between 03/01/1847 and 05/01/1847" << endl;
        cout << "What day would you like to start on?" << endl;
        getline(cin, Sday); //user inputs a day they would like to start on
        cout << "What month would you like to start on? On March, April or June?" << endl;
        getline(cin, month); //user inputs a month in the given range they would like to start on
        int day = stoi(Sday); //converts the given day into an integer
        Date today = Date(day, month); //sets the starting date with given day and month
    }
    else if(choice == "N"|| choice == "n") //if n, user starts with default date
    {
        Date today = Date(); //sets date to default date
    }
    Milestones checkpoint; //sets default checkpoint
    balance = 1600; //sets the group's balance at 1600
    miles = 0; //sets the wagon's miles at 0
    //sets all wagon supplies with the initial name and cost and then into their specificed index
    Supplies oxen("oxen", 40);
    materials[0] = oxen; 
    Supplies food("food", 0.5);
    materials[1] = food; 
    Supplies bullets("bullets", 2);
    materials[2] = bullets; 
    Supplies wagonparts("wagon parts", 20);
    materials[3] = wagonparts; 
    Supplies kits("med kits", 25);
    materials[4] = kits;
}
Traveler::Traveler(int shop)
{
    //sets all wagon supplies with the initial name and cost and then into their specificed index
    Supplies oxen("oxen", 40);
    materials[0] = oxen; 
    Supplies food("food", 0.5);
    materials[1] = food; 
    Supplies bullets("bullets", 2);
    materials[2] = bullets; 
    Supplies wagonparts("wagon parts", 20);
    materials[3] = wagonparts; 
    Supplies kits("med kits", 25);
    materials[4] = kits;
}
void Traveler::setMaterialAmount(int namount, int index) //uses the materials array to set amount of a material
{
    materials[index].setCost(namount);
}
void Traveler::setMaterialCost(float ncost, int index) //uses the materials array to set cost of a material
{
    materials[index].setCost(ncost);
}
void Traveler::setPlayerStatus(bool status, int index) //uses the players array to set their dead/alive status
{
    players[index].setStatus(status);
}
void Traveler::setPlayerSick(int days, int index) //uses the players array to set their sick days
{
    players[index].setSick(days);
}
void Traveler::setTimeMonth(int month) //sets the time object to a new month
{
    time.setMonth(month);
}
void Traveler::setTimeDay(int day) //sets the time object to a new day
{
    time.setDay(day);
}
void Traveler::setBalance(float nbalance) //sets the group's balance
{
    balance = nbalance;
}
void Traveler::setMiles(int nmiles) //set the wagon's miles
{
    miles = nmiles;
}
void Traveler::setCheckpoint() //sets the milestone object ahead of in all milestone arrays
{
    checkpoint.setInfo();
}

Date Traveler::getTime() const //returns the time object
{
    return time;
}
Group Traveler::getPlayer(int in) const //returns the person object at a specificed index
{
    return players[in];
}
Supplies Traveler::getMaterials(int mat) const //return the supply object at a specificed index
{
    return materials[mat];
}
float Traveler::getMaterialsAmount(int mat) const //return the supply object at a specificed index
{
    return materials[mat].getAmount();
}
Milestones Traveler::getCheckpoint() const //return the current checkpoint the group has reached
{
    return checkpoint;
}
float Traveler::getBalance() const //return the group's balance
{
    return balance;
}
int Traveler::getMiles() const //returns the wagon's miles
{
    return miles;
}