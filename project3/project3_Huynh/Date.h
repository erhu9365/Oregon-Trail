// CS1300 Fall 2020
// Author: Eric Huynh
// Recitation: 221 – Sanskar Katiyar
// Project 3
#ifndef DATE_H //helps when calling a class
#define DATE_H //defines the class
#include <iostream>
#include <string>

using namespace std;

class Date 
{
    public: //where functions go
        Date(); //Default constructor
        Date(int sday, string smonth); //parameterized constructor
        //Mutators: access and then update
        void setDay(int diffday);
        void setMonth(int diffmonth);
        int numMonth (string month);
        void setYear(int diffyear);
        //Accessors: get something, return
        int getDay() const; 
        string getMonth() const; 
        int getYear() const; 

    private: //where variables go
        int day;
        string month;
        int year;
        string Months[12]; //holds the months that exist in the game
};

#endif //end if not defined

