// CS1300 Fall 2020
// Author: Eric Huynh
// Recitation: 221 – Sanskar Katiyar
// Project 3
#include <iostream>
#include <string>
#include "Date.h" //reference to blueprint file

using namespace std;
//Default constructor
Date::Date()
{
    //default date
    month = "March";
    day = 28;
    year = 1847;
    //sets each month in its specific index in the months array
    Months[3] = "March";
    Months[4] = "April";
    Months[5] = "May";
    Months[6] = "June";
    Months[7] = "July";
    Months[8] = "August";
    Months[9] = "September";
    Months[10] = "October";
    Months[11] = "November";
}
//parameterized constructor
Date::Date(int sday, string smonth)
{
    //a different date between 03/01/1847 and 05/01/1847
    month = smonth;
    day = sday;
    year = 1847;
    //sets each month in its specific index in the months array
    Months[3] = "March";
    Months[4] = "April";
    Months[5] = "May";
    Months[6] = "June";
    Months[7] = "July";
    Months[8] = "August";
    Months[9] = "September";
    Months[10] = "October";
    Months[11] = "November";
}
/*
This function is used to reset the days and the month if the number of days exceeds a certain amount in a certain month
1. It will find the current month and day
2. Then a variable will be used to combine the current day and days pasted, one for the month as a number, and one for 
3. It takes the current month through a if-else statement for months that have 30 days or 31 days to check the number of days. 
For both, if the number of days goes past either treshold, then it progresses the next month and changes 
the day to fit the month.
*/
void Date::setDay(int diffday)
{
    string currentmonth = getMonth();
    int currentday = getDay();
    int numdays = diffday + currentday;
    int i, nextmonth = 0;

    if(currentmonth == "March"||currentmonth == "May"||currentmonth == "July"||currentmonth == "August"||currentmonth == "October")
    {
        if(numdays >= 1 && numdays <= 31)
        {
            day = numdays;
        }
        else
        {
            i = numMonth(currentmonth);
            nextmonth = i + 1;
            setMonth(nextmonth);
            day = numdays - 31;
        }
    }
    else
    {
        if(numdays >= 1 && numdays <= 30)
        {
            day = numdays;
        }
        else
        {
            i = numMonth(currentmonth);
            nextmonth = i + 1;
            setMonth(nextmonth);
            day = numdays - 30;
        }   
    }
}

void Date::setMonth(int diffmonth) //sets the month in the months array
{
    month = Months[diffmonth];
}
/*
The function changes the month into an integer
1. runs through the month array and compares the month until a match is found
2. the index of the month matched returns
*/
int Date::numMonth(string month)
{
    for(int i = 1; i < 11; i++) //loops through the month array
    {
        if(month == Months[i]) //if the month matches a month in the array
        {
            return i;
        }
    }
    return 0;
}

void Date::setYear(int diffyear) //sets the year
{
    year = diffyear;
}

int Date::getDay() const //returns the day
{
    return day; 
}
string Date::getMonth() const //returns the month
{
    return month;
}
int Date::getYear() const //returns the year
{
    return year;
}
