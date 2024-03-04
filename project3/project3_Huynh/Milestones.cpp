// CS1300 Fall 2020
// Author: Eric Huynh
// Recitation: 221 – Sanskar Katiyar
// Project 3
#include <iostream>
#include <string>
#include "Milestones.h" //reference to blueprint file

using namespace std;

Milestones::Milestones() //Default constructor
{
    //each landmark is set to their specificed index in the array
    name[0] = "Kansas River Crossing";
    name[1] = "Big Blue River Crossing";
    name[2] = "Fort Kearney";
    name[3] = "Chimney Rock";
    name[4] = "Fort Laramie";
    name[5] = "Independence Rock";
    name[6] = "South Pass";
    name[7] = "Fort Bridger";
    name[8] = "Green River Crossing";
    name[9] = "Soda Springs";
    name[10] = "Fort Hall";
    name[11] = "Snake River Crossing";
    name[12] = "Fort Boise";
    name[13] = "Blue Mountains";
    name[14] =  "Fort Walla Walla";
    //each landmark miles is set to their specificed index in the array
    miles[0] = 102;
    miles[1] = 185;
    miles[2] = 304;
    miles[3] = 554;
    miles[4] = 640;
    miles[5] = 830;
    miles[6] = 932;
    miles[7] = 989;
    miles[8] = 1151;
    miles[9] = 1295;
    miles[10] = 1395;
    miles[11] = 1534;
    miles[12] = 1648;
    miles[13] = 1808;
    miles[14] = 1863;
    //each landmark type is set to their specificed index in the array
    type[0] = "r";
    type[1] = "r";
    type[2] = "f";
    type[3] = "l";
    type[4] = "f";
    type[5] = "l";
    type[6] = "l";
    type[7] = "f";
    type[8] = "r";
    type[9] = "l";
    type[10] = "f";
    type[11] = "r";
    type[12] = "f";
    type[13] = "l";
    type[14] = "f";
    //the index of each array is set to 0
    nameland = 0;
    milesland = 0;
    typeland = 0;
}

void Milestones::setInfo() //all milestone array is set to 1 ahead
{
    nameland++;
    milesland++;
    typeland++;
}

string Milestones::getName() const //returns the name of the landmark at a specificed index
{
    return name[nameland];
}
int Milestones::getMiles() const //returns the miles of the landmark at a specificed index
{
    return miles[milesland];
}
string Milestones::getType() const //returns the type of the landmark at a specificed index
{
    return type[typeland];
}