// CS1300 Fall 2020
// Author: Eric Huynh
// Recitation: 221 – Sanskar Katiyar
// Project 3
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <string>
#include "Traveler.h" //reference to blueprint file

using namespace std;
/*
This function clears the terminal whenever an option is chosen --> clear clutter on the terminal
Parameters: None
Return: None
*/
void clear()
{
    string enter = "";
    cout << "Please press enter to continue." << endl;
    getline(cin, enter); //user presses enter
    system("clear");
}
/*
This function saves the user's data, including the player's name, miles they've traveled, the food remaining, and the cash remaining
Parameters: the Traveler object of the player
Return: None
*/
void savedata(Traveler user)
{
    ofstream savefile; //creates a stream file to write to a file
    savefile.open("savestats.txt"); //writes to a file to save the user's data

    if(savefile.is_open()) //determines if the file stream is open
    {
        savefile << "Leader's Name: " << user.getPlayer(0).getName() << endl; //saves the player's name to the file
        savefile << "Miles Traveled: " << user.getMiles() << endl; //saves miles traveled to the file
        savefile << "Food Remaining: " << user.getMaterials(1).getAmount() << endl; //saves food remaining to the file
        savefile << "Cash Remaining: $" << user.getBalance() << endl; //saves the cash remaining to the file
    }
    else 
    {
        cout << "Failed to save." << endl; //tells the user that the file stream failed
    }
    savefile.close(); //the filestream is closed
    //this function will write to a file to save a user's data and stats whether they finish the game or not
}
/*
This function takes a minimum and maximum and randomly picks a number between the given range
--> used to randomize different possibilities in certain scenarios like hunting and misfortunes
Parameters: a given minimum and maximum
Return: a random number between the minimum and maximum
*/
int randnumbers(int min, int max)
{
    int number = 0;
    srand(time(0)); //seeds the random number generator
    return (rand() % (max - min + 1)) + min;
}
/*
The function is used whenever the player is required to solve a puzzle --> uses the random number generator 
to correctly guess the number between 1 and 10 with 3 attempts at their disposal
1. First sets the user's attempts to 0 and generates a randon number between 1 to 10
2. A while loop is used to iterate until the user uses up all 3 attempts
    - The player inputs a guess --> additional if statement and for loop is used to eliminate edge cases
    - Then, it checks if the input is the same as the random number --> if correct, tells the player they solved the puzzle and returns true,
    otherwise, it adds 1 to the user's attempts and tells them to try again
3. If the player uses up all 3 attempts, the while loop ends and tells them that they failed to solve the puzzle and returns false.
Parameters: None
Return: true or false
*/
bool puzzle()
{
    int attempts = 0;
    int range = randnumbers(1, 10); //randomly generates a number between 1 and 10
    string sguess;
    int guess = 0;
    while(attempts < 3) //while the number of attempts is less than 3
    {
        cout << "Guess the number between 1 - 10." << endl;
        getline(cin, sguess); //user inputs their guess
        if(sguess.length() == 0) //checks if the user inputs nothing
        {
            cout << "Your choice cannot be blank. Please try again." << endl;
        }
        for(int i = 0; i < sguess.length(); i++) //loops through the given guess
        {
            if(isdigit(sguess[i]) == false) //checks if the given input is a number or not
            {
                cout << "Your choice cannot contain characters. Please try again." << endl;
            }
            else
            {
                guess = stoi(sguess); //converts the given input into an integer
            }
        }
        if(guess == range) //checks if the given number is the same as the random generated number
        {
            cout << "You guessed the right number and solved the puzzle! Congratulations!" << endl;
            return true; //returns true
        }
        else
        {
            cout << "That is not the right number. Try again." << endl;
            attempts++; //adds to the user's attempts
        }
    }
    cout << "Sorry. You ran out of attempts and failed the puzzle." << endl;
    return false; //returns false;
}
/*
The function gives the user store information, displays the store menu, the user's current items and cost they want to buy. 
This function can also be used along different points of the journey. An constructor for the store is made so it keeps track
of the user's wanted items and once the user is done shopping, it adds whatever they wanted into their inventory
1. First, information about the store in a text file is read and get displays to the player
2. Once all variables are initalized, a while loop is set up to loop through the menu and current items until the user enters 0 to leave the store
- If user chooses 1, the user can buy oxens and inputs the amount they want (goes through statements for edge cases) and checks if
the user has enough money to purchase oxens. There is also a certain amount of oxens the user has to buy as well.
- If user chooses 2, the user can buy food and inputs the amount they want (goes through statements for edge cases) and checks if
the user has enough money to purchase food. There is also a recommended amount for users to buy.
- If user chooses 3, the user can buy box of bullets and inputs the amount they want (goes through statements for edge cases) and checks if
the user has enough money to purchase bullets. The user buys based on the number of boxes
- If user chooses 4, the user can buy wagons parts and medkits and inputs the amount they want (goes through statements for edge cases) and checks if
the user has enough money to purchase wagon parts and medkits. 
3. The screen is cleared for the next stage of the game and saves the user's item into the Traveler object ot the user
Parameters: the Traveler object of the player and the Traveler object of the store
Return: the Traveler object of the player 
*/
Traveler store(Traveler user, Traveler mainstore)
{
    //prints out the store information for the user
    ifstream StoreInfo;
    StoreInfo.open("store_info.txt");
    string line = "";
    system("clear");
    while(getline(StoreInfo, line))
    {
        cout << line << endl;
    }
    StoreInfo.close();
    clear(); //clears the screen
    
    int choice = 0;
    string amount = "";
    int NumAmount = 0;
    float bill = 0.0;
    while(true)
    {
        system("clear"); //clears terminal
        //displays what the user has currently in their inventory before, during, and after shopping
        cout << "Current Items:" << endl;
        cout << "Oxen: " << user.getMaterials(0).getAmount() + mainstore.getMaterials(0).getAmount() << endl;
        cout << "Food: " << user.getMaterials(1).getAmount() + mainstore.getMaterials(1).getAmount() << endl;
        cout << "Bullets: " << user.getMaterials(2).getAmount() + mainstore.getMaterials(2).getAmount() << endl;
        cout << "Wagons Parts (Axles, Wheels, Tongues): " << user.getMaterials(3).getAmount() + mainstore.getMaterials(3).getAmount() << endl;
        cout << "Medkits: " << user.getMaterials(4).getAmount() + mainstore.getMaterials(4).getAmount() << endl;
        //displays how much the user will have to pay for each item
        cout << "1. Oxen      " << "$" << user.getMaterials(0).getCost() * mainstore.getMaterials(0).getAmount() << endl;
        cout << "2. Food      " << "$" << user.getMaterials(1).getCost() * mainstore.getMaterials(1).getAmount() << endl;
        cout << "3. Bullets      " << "$" << user.getMaterials(2).getCost() * (mainstore.getMaterials(2).getAmount()/20) << endl;
        cout << "4. Spare Parts      " << "$" << (user.getMaterials(3).getCost() * mainstore.getMaterials(3).getAmount()) + (user.getMaterials(4).getCost() * mainstore.getMaterials(4).getAmount()) << endl;
        //initalized bill to calculate the total amount of money the user has to pay for their items
        bill = ((mainstore.getMaterials(0).getAmount() * user.getMaterials(0).getCost()) + (mainstore.getMaterials(1).getAmount() * user.getMaterials(1).getCost())
                + ((mainstore.getMaterials(2).getAmount())/20 * user.getMaterials(2).getCost()) + (mainstore.getMaterials(3).getAmount() * user.getMaterials(3).getCost())
                + (mainstore.getMaterials(4).getAmount() * user.getMaterials(4).getCost()));
        cout << "Your current bill is: $" << bill << endl;
        cout << "Your current balance is: $" << user.getBalance() - bill << endl;
        cout << "Which item would you like to purchase? Enter in 0 when you are done." << endl;

        string stemp;
        getline(cin, stemp); //user enters an option
        choice = stoi(stemp);
        if(choice == 1) //if the user wants to buy oxen
        {
            system("clear"); //clears terminal
            cout << "There are two oxens in a yoke and each yoke cost $" << user.getMaterials(0).getCost() << endl;
            cout << "Remember, you must spend between $120-$200 on oxens." << endl;
            cout << "How many yokes do you want?" << endl;
            getline(cin, amount); //user inputs the amount they want
            if(amount.length() == 0) //checks if the input is empty
            {
                cout << "Your choice cannot be blank. Please try again." << endl;
                continue;
            }
            for(int i = 0; i < amount.length(); i++) //loops through given input
            {
                if(isdigit(amount[i]) == false) //checks if there are digits
                {
                    cout << "Your choice cannot contain characters. Please try again." << endl;
                }
                else //they are numbers
                {
                    NumAmount = stoi(amount); //converts given number into an integer
                    NumAmount = NumAmount + user.getMaterials(0).getAmount(); //adds on to the user's current amount so later on, the user does not overbuy oxen
                }
            }
            //checks if the user has enough money and in range between $100 and $200
            if(NumAmount * user.getMaterials(0).getCost() < user.getBalance() - bill && NumAmount * user.getMaterials(0).getCost() >= 100 && NumAmount * user.getMaterials(0).getCost() <= 200)
            {
                mainstore.setMaterialAmount(NumAmount * 2, 0); //sets the number of oxens they want into their cart
            }
            else if(NumAmount * 40 > user.getBalance()) //checks if the user does not meet the budget requirement
            {
                cout << "Sorry! Looks you don't have enough." << endl;
                clear(); //clears screen
            }
            else //if the user does not between $120 - $200 worth of oxens
            {
                cout << "Sorry, you must spend between $120 and $200 on oxens." << endl;
                clear(); //clears screen
            }
        }
        if(choice == 2) //if the user wants to buy food
        {
            system("clear");
            cout << "I recommend you purchase at least 200 lbs. of food per person" << endl;
            cout << "The price of food is $" << user.getMaterials(1).getCost() << " cents per pound" << endl;
            cout << "How many pounds of food do you want?" << endl;
            getline(cin, amount); //user inputs the amount they want
            if(amount.length() == 0) //checks if the input is empty
            {
                cout << "Your choice cannot be blank. Please try again." << endl;
                continue;
            }
            for(int i = 0; i < amount.length(); i++) //loops through given input
            {
                if(isdigit(amount[i]) == false) //checks if there are digits
                {
                    cout << "Your choice cannot contain characters. Please try again." << endl;
                }
                else //they are numbers
                {
                    NumAmount = stoi(amount); //converts given number into an integer
                    NumAmount = NumAmount + user.getMaterials(1).getAmount(); //adds the to the user's inventory
                }
            }
            //checks if the user has enough money to buy
            if(NumAmount + mainstore.getMaterials(1).getAmount() > 1000) //if the user goes over the maximum amount of food they can have
            {
                cout << "The wagon can only hold 1000 lbs of food." << endl;
                clear(); //clears screen
            }
            else if(NumAmount * user.getMaterials(1).getCost() > user.getBalance() - bill) //if they don't have enough money
            {
                cout << "Sorry! Looks like you don't have enough." << endl;
                clear(); //clears screen
            }
            else 
            {
                mainstore.setMaterialAmount(NumAmount, 1); //sets the lbs of food they want into their cart
            }
        }
        if(choice == 3) //if the user wants to buy bullets
        {
            system("clear"); //clears terminal
            cout << "A box of 20 bullets costs $" << user.getMaterials(2).getCost() << ". You will need the bullets for hunting along the way." << endl;
            cout << "How many boxes do you want?" << endl;
            getline(cin, amount); //user inputs the amount they want
            if(amount.length() == 0) //checks if the input is empty
            {
                cout << "Your choice cannot be blank. Please try again." << endl;
                continue;
            }
            for(int i = 0; i < amount.length(); i++) //loops through given input
            {
                if(isdigit(amount[i]) == false) //checks if there are digits
                {
                    cout << "Your choice cannot contain characters. Please try again." << endl;
                }
                else //they are numbers
                {
                    NumAmount = stoi(amount); //converts given number into an integer
                }
            }
            //checks if the user has enough money to buy
            if(NumAmount * user.getMaterials(2).getCost() < user.getBalance() - bill)
            {
                mainstore.setMaterialAmount(NumAmount * 20, 2); //sets the number of bullets they want into their cart
            }
            else //if they don't have enough money
            {
                cout << "Sorry! Looks like you don't have enough." << endl;
                clear(); //clears screen
            }
        }
        if(choice == 4) //if the user wants to buy additional supplies
        {
            system("clear"); //clears terminal
            cout << "A wagon part (wheels, axles, tongues) costs $" << user.getMaterials(3).getCost() << ". If the wagon breaks along the way, any wagon parts will be used to fix it." << endl;
            cout << "How many wagon parts do you want?" << endl;
            getline(cin, amount); //user inputs the amount they want
            if(amount.length() == 0) //checks if the input is empty
            {
                cout << "Your choice cannot be blank. Please try again." << endl;
                continue;
            }
            for(int i = 0; i < amount.length(); i++) //loops through given input
            {
                if(isdigit(amount[i]) == false) //checks if there are digits
                {
                    cout << "Your choice cannot contain characters. Please try again." << endl;
                }
                else //they are numbers
                {
                    NumAmount = stoi(amount); //converts given number into an integer
                }
            }
            //checks if the user has enough money to buy
            if(NumAmount * user.getMaterials(3).getCost() < user.getBalance() - bill)
            {
                mainstore.setMaterialAmount(NumAmount, 3); //sets the number of wagon parts they want into their cart
            }
            else //if they don't have enough money
            {
                cout << "Sorry! Looks like you don't have enough." << endl;
                clear(); //clears screen
            }
        system("clear"); //clears terminal
        cout << "It is also good to bring some medkits along the way. A medical aid kit costs $" << user.getMaterials(4).getCost() << "." << endl;
        cout << "How many kits do you want?" << endl;
            getline(cin, amount); //user inputs the amount they want
            if(amount.length() == 0) //checks if the input is empty
            {
                cout << "Your choice cannot be blank. Please try again." << endl;
                continue;
            }
            for(int i = 0; i < amount.length(); i++) //loops through given input
            {
                if(isdigit(amount[i]) == false) //checks if there are digits
                {
                    cout << "Your choice cannot contain characters. Please try again." << endl;
                }
                else //they are numbers
                {
                    NumAmount = stoi(amount); //converts given number into an integer
                }
            }
            //checks if the user has enough money to buy
            if(NumAmount * user.getMaterials(4).getCost() < user.getBalance() - bill)
            {
                mainstore.setMaterialAmount(NumAmount, 4); //sets the number of medkits they want into their cart
            }
            else //if they don't have enough money
            {
                cout << "Sorry! Looks like you don't have enough." << endl;
                clear(); //clears screen
            }
        }
        else if(choice == 0) //if the user wants to leave the store
        {
            for(int i = 0; i < 7; i++) //loops through the array of materials
            {
                user.setMaterialAmount(mainstore.getMaterials(i).getAmount() + user.getMaterials(i).getAmount(), i); //adds new items into the player's inventory
            }
            user.setBalance(user.getBalance() - bill); //the user's money is subtracted by the bill
            break; //breaks the loop
        }
        else //the user must input a number with the given options
        {
            cout << "Sorry, you must input one of the numbers in the given range." << endl;
        }
    }
    system("clear"); //clears terminal
    return user; //saves the user's items into the object
    //this is where the shop simulation for the game will be
    //the user will get to buy materials before they go on their journey on the trail
    //there will also be an implementation of increased prices depending at which fort the user arrives at
}
/*
The function will given the user three options when under a raider attack which will either have a consequence or reward
1. First option: The player runs away and loses an ox, 10 lbs of food, and a wagon part
2. Second option: The player attack the raiders, either winning or losing the fight
- if the player wins, they receive 50 lbs of food and 50 bullets
- if the player loses, they lose 1/4 of their cash and 50 bullets
3. Third option: The player surrenders to the raiders and loses 1/4 of their cash
Parameters: the Traveler object of the user
Return: the Traveler object of the user
*/
Traveler raiderattack(Traveler user)
{
    int choice = 0;
    cout << "Riders ahead! They look hostile!" << endl;
    cout << "How would you like to proceed the situation?" << endl; //asks how the user wants to proceed in the situation
    cout << "1. Run" << endl;
    cout << "2. Attack" << endl;
    cout << "3. Surrender" << endl;
    string stemp;
    getline(cin, stemp); //users inputs their choice
    choice = stoi(stemp);
    if(choice == 1) //if the player chooses to run
    {
        system("clear"); //clears terminal
        cout << "Your party escaped the raiders, but at what cost?" << endl;
        cout << "You left behind 1 oxen, 10 lbs of food, and 1 wagon part." << endl;
        user.setMaterialAmount(-1, 0); //decreases the oxen amount by 1 from the player's inventory
        user.setMaterialAmount(-10, 1); //decreases the food amount by 10 from the player's inventory
        user.setMaterialAmount(-1, 3); //decreases the wagon parts amount by 1 from the player's inventory
        clear(); //clears terminal
    }
    else if(choice == 2) //if the player chooses to attack
    {
        system("clear"); //clears terminal
        bool fightchance = puzzle(); //calls the puzzle function to check if the player wins or not
        if(fightchance == true) //if the player wins
        {
            cout << "Congratulations! You defeated the raiders!" << endl;
            cout << "You gained 50 lbs of food and 50 bullets." << endl;
            user.setMaterialAmount(50, 1); //increases the food amount by 50 from the player's inventory
            user.setMaterialAmount(50, 2); //increases the bullets amount by 50 from the player's inventory
            clear(); //clears terminal
        }
        else //if the player loses
        {
            cout << "After fighting with the raiders, you and your party suffered great losses." << endl;
            cout << " You lost $" << user.getBalance()/4 << " and 50 bullets." << endl;
            user.setMaterialAmount(-50, 2);//decreases the bullet amount by 50 from the player's inventory
            user.setBalance(user.getBalance() - (user.getBalance()/4)); //decreases the amount of cash by 1/4 from the player's inventory
            clear(); //clears terminal
        }
    }
    else if(choice == 3) //if the player chooses to surrender
    {
        cout << "Your party surrenders. The raiders were merciful and took cash only." << endl;
        cout << "You lost $" << user.getBalance()/4 << endl;
        user.setBalance(user.getBalance() - (user.getBalance()/4));
        clear(); //clears terminal
    }
    else //if the player inputs something that is not in the given options
    {
        cout << "Invalid option. Please try again." << endl;
        getline(cin, stemp); //sends user back to enter an input again
    }
    //this is where the simulation of raider attacks will be (with a certain probability)
    //the user will be given options to either run, fight or surrender and there will be statements for each option
    return user; //returns the Traveler object of the user
}
/*
The function determines what misfortune the player will receive out of the three misfortunes
1. The random generator will pick a number between 1 to 5 to determine what misfortune the player will receive
2. Each misfortune has its own consequence and hinders the player from proceeding
3. After the misfortune, it returns the Traveler object of the player
Parameters: the Traveler object of the player
Return: the Traveler object of the player
*/
Traveler misfortune(Traveler user)
{
    system("clear"); //clears terminal
    int event = randnumbers(1, 3); //calls the randnumbers function to randomly pick a misfortune to occur
    if(event == 1) //if the event is chosen to be a illness
    {
        int choice;
        int sickperson = randnumbers(1, 5); //calls the randnumbers function to randomly pick a person in the party to receive an illness
        int sickness = randnumbers(1, 6); //calls the randnumbers function to randomly pick an illness for the chosen player to receive it
        if(sickness == 1) //the chosen person is given typhoid
        {
            cout << "Oh no! " << user.getPlayer(sickperson).getName() << " has typhoid!" << endl;
            if(user.getMaterials(4).getAmount() > 0) //uses a medkit if the player has any medkits
            {
                cout << "You have used a medkit but there is a 50% of them dying still." << endl;
                int chance = randnumbers(1, 100); //calls the randnumbers function to decide whether the chosen person dies
                if(chance >= 1 && chance <= 50) //if it is in 50% chance of dying
                {
                    cout << "Oh no! " << user.getPlayer(sickperson).getName() << " has died." << endl;
                    user.getPlayer(sickperson).setStatus(false); //sets the chosen person's status to false (dead)
                }
            }
            else //if they don't have any medkits
            {
                cout << "Would you like to (1) Rest or (2) Press on?" << endl;
                string stemp;
                getline(cin, stemp);
                choice = stoi(stemp);
                if(choice == 1) //if the player decides to rest
                {
                    cout << "You and your party will rest for 3 days." << endl;
                    user.setTimeDay(3); //rest for three days
                    int chance = randnumbers(1, 100); //calls the randnumbers function to decide whether the chosen person dies
                    if(chance >= 1 && chance <= 30) //if it is in 30% chance of dying
                    {
                        cout << "Oh no! " << user.getPlayer(sickperson).getName() << " has died." << endl;
                        user.getPlayer(sickperson).setStatus(false); //sets the chosen person's status to false (dead)
                    }
                }
                else if(choice == 2) //if the player decides to press on
                {
                    int chance = randnumbers(1, 100); //calls the randnumbers function to decide whether the chosen person dies
                    if(chance >= 1 && chance <= 70) //if it is in 70% chance of dying
                    {
                        cout << "Oh no! " << user.getPlayer(sickperson).getName() << " has died." << endl;
                        user.getPlayer(sickperson).setStatus(false); //sets the chosen person's status to false (dead)
                    }
                }
                else //if the player inputs something that is not in the given options
                {
                    cout << "Invalid choice. Please try again." << endl;
                    getline(cin, stemp); //returns the user back to input a choice
                }
            }
        }
        else if(sickness == 2) //the chosen person is given cholera
        {
            cout << "Oh no! " << user.getPlayer(sickperson).getName() << " has cholera!" << endl;
            if(user.getMaterials(4).getAmount() > 0) //uses a medkit if the player has any medkits
            {
                cout << "You have used a medkit but there is a 50% of them dying still." << endl;
                int chance = randnumbers(1, 100); //calls the randnumbers function to decide whether the chosen person dies
                if(chance >= 1 && chance <= 50) //if it is in 50% chance of dying
                {
                    cout << "Oh no! " << user.getPlayer(sickperson).getName() << " has died." << endl;
                    user.getPlayer(sickperson).setStatus(false); //sets the chosen person's status to false (dead)
                }
            }
            else //if they don't have any medkits
            {
                cout << "Would you like to (1) Rest or (2) Press on?" << endl;
                string stemp;
                getline(cin, stemp);
                choice = stoi(stemp);
                if(choice == 1) //if the player decides to rest
                {
                    cout << "You and your party will rest for 3 days." << endl;
                    user.setTimeDay(3); //rest for three days
                    int chance = randnumbers(1, 100); //calls the randnumbers function to decide whether the chosen person dies
                    if(chance >= 1 && chance <= 30) //if it is in 30% chance of dying
                    {
                        cout << "Oh no! " << user.getPlayer(sickperson).getName() << " has died." << endl;
                        user.getPlayer(sickperson).setStatus(false); //sets the chosen person's status to false (dead)
                    }
                }
                else if(choice == 2) //if the player decides to press on
                {
                    int chance = randnumbers(1, 100); //calls the randnumbers function to decide whether the chosen person dies
                    if(chance >= 1 && chance <= 70) //if it is in 70% chance of dying
                    {
                        cout << "Oh no! " << user.getPlayer(sickperson).getName() << " has died." << endl;
                        user.getPlayer(sickperson).setStatus(false); //sets the chosen person's status to false (dead)
                    }
                }
                else //if the player inputs something that is not in the given options
                {
                    cout << "Invalid choice. Please try again." << endl;
                    getline(cin, stemp); //returns the user back to input a choice
                }
            }
        }
        else if(sickness == 3) //the chosen person is given diarrhea
        {
            cout << "Oh no! " << user.getPlayer(sickperson).getName() << " has diarrhea!" << endl;
            if(user.getMaterials(4).getAmount() > 0) //uses a medkit if the player has any medkits
            {
                cout << "You have used a medkit but there is a 50% of them dying still." << endl;
                int chance = randnumbers(1, 100); //calls the randnumbers function to decide whether the chosen person dies
                if(chance >= 1 && chance <= 50) //if it is in 50% chance of dying
                {
                    cout << "Oh no! " << user.getPlayer(sickperson).getName() << " has died." << endl;
                    user.getPlayer(sickperson).setStatus(false); //sets the chosen person's status to false (dead)
                }
            }
            else //if they don't have any medkits
            {
                cout << "Would you like to (1) Rest or (2) Press on?" << endl;
                string stemp;
                getline(cin, stemp);
                choice = stoi(stemp);
                if(choice == 1) //if the player decides to rest
                {
                    cout << "You and your party will rest for 3 days." << endl;
                    user.setTimeDay(3); //rest for three days
                    int chance = randnumbers(1, 100); //calls the randnumbers function to decide whether the chosen person dies
                    if(chance >= 1 && chance <= 30) //if it is in 30% chance of dying
                    {
                        cout << "Oh no! " << user.getPlayer(sickperson).getName() << " has died." << endl;
                        user.getPlayer(sickperson).setStatus(false); //sets the chosen person's status to false (dead)
                    }
                }
                else if(choice == 2) //if the player decides to press on
                {
                    int chance = randnumbers(1, 100); //calls the randnumbers function to decide whether the chosen person dies
                    if(chance >= 1 && chance <= 70) //if it is in 70% chance of dying
                    {
                        cout << "Oh no! " << user.getPlayer(sickperson).getName() << " has died." << endl;
                        user.getPlayer(sickperson).setStatus(false); //sets the chosen person's status to false (dead)
                    }
                }
                else //if the player inputs something that is not in the given options
                {
                    cout << "Invalid choice. Please try again." << endl;
                    getline(cin, stemp); //returns the user back to input a choice
                }
            }
        }
        else if(sickness == 4) //the chosen person is given the measles
        {
            cout << "Oh no! " << user.getPlayer(sickperson).getName() << " has the measles!" << endl;
            if(user.getMaterials(4).getAmount() > 0) //uses a medkit if the player has any medkits
            {
                cout << "You have used a medkit but there is a 50% of them dying still." << endl;
                int chance = randnumbers(1, 100); //calls the randnumbers function to decide whether the chosen person dies
                if(chance >= 1 && chance <= 50) //if it is in 50% chance of dying
                {
                    cout << "Oh no! " << user.getPlayer(sickperson).getName() << " has died." << endl;
                    user.getPlayer(sickperson).setStatus(false); //sets the chosen person's status to false (dead)
                }
            }
            else //if they don't have any medkits
            {
                cout << "Would you like to (1) Rest or (2) Press on?" << endl;
                string stemp;
                getline(cin, stemp);
                choice = stoi(stemp);
                if(choice == 1) //if the player decides to rest
                {
                    cout << "You and your party will rest for 3 days." << endl;
                    user.setTimeDay(3); //rest for three days
                    int chance = randnumbers(1, 100); //calls the randnumbers function to decide whether the chosen person dies
                    if(chance >= 1 && chance <= 30) //if it is in 30% chance of dying
                    {
                        cout << "Oh no! " << user.getPlayer(sickperson).getName() << " has died." << endl;
                        user.getPlayer(sickperson).setStatus(false); //sets the chosen person's status to false (dead)
                    }
                }
                else if(choice == 2) //if the player decides to press on
                {
                    int chance = randnumbers(1, 100); //calls the randnumbers function to decide whether the chosen person dies
                    if(chance >= 1 && chance <= 70) //if it is in 70% chance of dying
                    {
                        cout << "Oh no! " << user.getPlayer(sickperson).getName() << " has died." << endl;
                        user.getPlayer(sickperson).setStatus(false); //sets the chosen person's status to false (dead)
                    }
                }
                else //if the player inputs something that is not in the given options
                {
                    cout << "Invalid choice. Please try again." << endl;
                    getline(cin, stemp); //returns the user back to input a choice
                }
            }
        }
        else if(sickness == 5) //the chosen person is given dysentery
        {
            cout << "Oh no! " << user.getPlayer(sickperson).getName() << " has dysentery!" << endl;
            if(user.getMaterials(4).getAmount() > 0) //uses a medkit if the player has any medkits
            {
                cout << "You have used a medkit but there is a 50% of them dying still." << endl;
                int chance = randnumbers(1, 100); //calls the randnumbers function to decide whether the chosen person dies
                if(chance >= 1 && chance <= 50) //if it is in 50% chance of dying
                {
                    cout << "Oh no! " << user.getPlayer(sickperson).getName() << " has died." << endl;
                    user.getPlayer(sickperson).setStatus(false); //sets the chosen person's status to false (dead)
                }
            }
            else //if they don't have any medkits
            {
                cout << "Would you like to (1) Rest or (2) Press on?" << endl;
                string stemp;
                getline(cin, stemp);
                choice = stoi(stemp);
                if(choice == 1) //if the player decides to rest
                {
                    cout << "You and your party will rest for 3 days." << endl;
                    user.setTimeDay(3); //rest for three days
                    int chance = randnumbers(1, 100); //calls the randnumbers function to decide whether the chosen person dies
                    if(chance >= 1 && chance <= 30) //if it is in 30% chance of dying
                    {
                        cout << "Oh no! " << user.getPlayer(sickperson).getName() << " has died." << endl;
                        user.getPlayer(sickperson).setStatus(false); //sets the chosen person's status to false (dead)
                    }
                }
                else if(choice == 2) //if the player decides to press on
                {
                    int chance = randnumbers(1, 100); //calls the randnumbers function to decide whether the chosen person dies
                    if(chance >= 1 && chance <= 70) //if it is in 70% chance of dying
                    {
                        cout << "Oh no! " << user.getPlayer(sickperson).getName() << " has died." << endl;
                        user.getPlayer(sickperson).setStatus(false); //sets the chosen person's status to false (dead)
                    }
                }
                else //if the player inputs something that is not in the given options
                {
                    cout << "Invalid choice. Please try again." << endl;
                    getline(cin, stemp); //returns the user back to input a choice
                }
            }
        }
        else if(sickness == 6) //the chosen person is given a fever
        {
            cout << "Oh no! " << user.getPlayer(sickperson).getName() << " has a fever!" << endl;
            if(user.getMaterials(4).getAmount() > 0) //uses a medkit if the player has any medkits
            {
                cout << "You have used a medkit but there is a 50% of them dying still." << endl;
                user.setTimeDay(3);
                int chance = randnumbers(1, 100); //calls the randnumbers function to decide whether the chosen person dies
                if(chance >= 1 && chance <= 50) //if it is in 50% chance of dying
                {
                    cout << "Oh no! " << user.getPlayer(sickperson).getName() << " has died." << endl;
                    user.getPlayer(sickperson).setStatus(false); //sets the chosen person's status to false (dead)
                }
            }
            else //if they don't have any medkits
            {
                cout << "Would you like to (1) Rest or (2) Press on?" << endl;
                string stemp;
                getline(cin, stemp);
                choice = stoi(stemp);
                if(choice == 1) //if the player decides to rest
                {
                    cout << "You and your party will rest for 3 days." << endl;
                    int chance = randnumbers(1, 100); //calls the randnumbers function to decide whether the chosen person dies
                    if(chance >= 1 && chance <= 30) //if it is in 30% chance of dying
                    {
                        cout << "Oh no! " << user.getPlayer(sickperson).getName() << " has died." << endl;
                        user.getPlayer(sickperson).setStatus(false); //sets the chosen person's status to false (dead)
                    }
                }
                else if(choice == 2) //if the player decides to press on
                {
                    int chance = randnumbers(1, 100); //calls the randnumbers function to decide whether the chosen person dies
                    if(chance >= 1 && chance <= 70) //if it is in 70% chance of dying
                    {
                        cout << "Oh no! " << user.getPlayer(sickperson).getName() << " has died." << endl;
                        user.getPlayer(sickperson).setStatus(false); //sets the chosen person's status to false (dead)
                    }
                }
                else //if the player inputs something that is not in the given options
                {
                    cout << "Invalid choice. Please try again." << endl;
                    getline(cin, stemp); //returns the user back to input a choice
                }
            }
        }
    }
    else if(event == 2) //the player loses an ox
    {
        user.setMaterialAmount(-1, 0); //decreases the oxen amount by 1 from the player's inventory
        cout << "Oh no! One of the oxen has died! You have " << user.getMaterials(0).getAmount() << " oxen left" << endl; 
    }
    else if(event == 3) //the player's wagon breaks down
    {
        int broken = randnumbers(3, 5); //the randnumbers function is called to determine which wagon part gets broken
        if(broken == 3) //one of the wheels breaks
        {
            cout << "Oh no! One of your wheels are broken." << endl;
        }
        else if(broken == 4) //one of the axles breaks
        {
            cout << "Oh no! One of your axles are broken." << endl;
        }
        else if(broken == 5) //one of the tongues breaks
        {
            cout << "Oh no! One of your tongues are broken." << endl;
        }
        
        user.setMaterialAmount(-1, 3); //decreases the wagon parts amount by 1 from the player's inventory to fix it
        if(user.getMaterials(3).getAmount() <= 0) //if the player has not more wagon parts to use
        {
            cout << "Your wagon has broke and you have no more spare parts!" << endl;
        }
        else //if the player has wagon parts to use
        {
            cout << "It will take 1 day to fix your wagon." << endl;
            user.setTimeDay(1); //adds 1 day to current time to fix the wagon
        }
    }
    clear(); //clears terminal
    return user; //returns the Traveler object of the player
    //this is where the simulation of misfortunes will be (with a probablity of 40% to be caused)
    /*The misfortunes can be: a person in the party gets sick (typhoid, cholera, diarrhea, measles, dysentery, and fever),
    an oxen dies, or one of the wagon parts break down
    */
    //depend on the misfortune, there will be consequences/options for the user to help with their situation
}
/*
The function allows the player to rest at any given point and between 1 to 3 days
1. The player is asked how many days they want to rest between 1 to 3 days
2. The input is checked for edge cases and fits into the day range
3. The time is set to however long the player wants to rest and adds to the date
4. Food is also taken out of the player's inventory to account for the amount of days for resting
Parameters: the Traveler object of the player
Return: the Traveler object of the player
*/
Traveler stop(Traveler user)
{
    system("clear"); //clears terminal
    string input;
    int restdays = 0;
    cout << "How many days would you like to rest? (1-3 days)" << endl;
    getline(cin, input); //user inputs amount of days
    if(input.length() == 0) //checks if the input is blank
    {
        cout << "Your choice cannot be blank. Please try again." << endl;
    }
    for(int i = 0; i < input.length(); i++) //loops through given input
    {
        if(isdigit(input[i]) == false) //checks if it is a number
        {
            cout << "Your choice cannot contain characters. Please try again." << endl;
        }
        else //given input is a number
        {
            restdays = stoi(input);
        }
    }
    if(restdays == 1||restdays == 2||restdays == 3) //if the user to rest between 1-3 days
    {
        user.setTimeDay(restdays); //sets the date the amount of rest days in advance
        cout << "You have stop and rest for " << restdays << " day(s)." << endl;
        for(int i = 0; i < 5; i++) //loops through the party array
        {
            if(user.getPlayer(i).getStatus() == true) //checks if the person is alive
            {
                user.setMaterialAmount((-3 * restdays), 1); //decreases the food amount by 3 * restdays from player's inventory
            }
        }
    }
    return user; //saves data and returns Traveler object of the user
}
/*
The function allows the player to go through a 2 week turn, traveling between 70 and 140 miles. It also allows the player to
know which landmark they are at and given certain options given the landmark they have made it to.
1. Sets the date two weeks in advance, how much the player traveled between 70 and 140 miles, and decrease the amount of food (3 lbs) within the 2 weeks
2. Determines if the player reaches a landmark and what kind of landmark they are at
- If it is a regular landmark, the user can either wait or continue on
- If it is a river, the user can either wait or continue on
- If it is a fort, the user can either wait, visit the store, or continue on
- Once the landmark is reached, the landmark arrays increase by one
3. the Traveler object of the player is returned
Parameters: the Traveler object of the player and the Traveler object of the shop
Return: the Traveler object of the player
*/
Traveler continueon(Traveler user, Traveler mainstore)
{
    system("clear"); //clears terminal
    user.setTimeDay(14); //sets the date two weeks in advance
    for(int i = 0; i < 5; i++) //loops through the party
    {
        if(user.getPlayer(i).getStatus() == true) //checks if the person is alive
        {
            user.setMaterialAmount((-3 * 14), 1); //decreases the food amount by 3 * 14 for each person from the player's inventory
        }
    }
    user.setMiles(user.getMiles() + randnumbers(70, 140)); //the user's travelled miles increases between 70 and 140 miles
    if(user.getMiles() >= user.getCheckpoint().getMiles()) //checks if the user is at a milestone
    {
        cout << "You have reached the " << user.getCheckpoint().getName() << endl;
        user.setMiles(user.getCheckpoint().getMiles()); //sets the miles travelled to where the milestone is so the player cannot go past it
        cout << "Miles Traveled: " << user.getMiles() << endl; 
        cout << "Next Milestone: " << user.getCheckpoint().getnextMiles() - user.getCheckpoint().getMiles() << endl;
        if(user.getCheckpoint().getType() == "l") //if the milestone is a regular landmark
        {
            int choice;
            cout << "What do you want to do?:" << endl;
            cout << "1. Rest" << endl;
            cout << "2. Continue" << endl;
            string stemp;
            getline(cin, stemp); //user inputs either options
            choice = stoi(stemp);
            while(true) //loops until the user inputs a valid choice
            {
                if(choice == 1) //if the player chooses to rest
                {
                    stop(user); //takes the user to the stop and rest function
                    user.setMiles(user.getMiles() + 1); //sets the player's miles + 1 so the player does not get stuck at the milestone
                    break; //loop breaks
                }
                else if(choice == 2) //if the player chooses to continue
                {
                    user.setTimeDay(14); //sets the date two weeks in advance
                    for(int i = 0; i < 5; i++) 
                    {
                        if(user.getPlayer(i).getStatus() == true) //checks if the person is alive
                        {
                            user.setMaterialAmount((-3 * 14), 1); //decreases the food amount by 3 * 14 for each person from the player's inventory
                        }
                    }
                    user.setMiles(user.getMiles() + randnumbers(70, 140)); //the user's travelled miles increases between 70 and 140 miles
                    break; //loop breaks
                }
                else //if the user does not input something that is not in the given options
                {
                    cout << "Invalid choice. Please try again." << endl;
                    getline(cin, stemp); //the user inputs another choice
                }
            }
        }
        else if(user.getCheckpoint().getType() == "f")
        {
            int choice;
            while(true) //loops until the user inputs a valid choice/wants to continue their journey
            {
            cout << "What do you want to do?:" << endl;
            cout << "1. Rest" << endl;
            cout << "2. Continue" << endl;
            cout << "3. Visit the store" << endl;
            string stemp;
            getline(cin, stemp); //user inputs either options
            choice = stoi(stemp);

                if(choice == 1) //if the player chooses to rest
                {
                    stop(user); //takes the user to the stop and rest function
                    user.setMiles(user.getMiles() + 1); //sets the player's miles + 1 so the player does not get stuck at the milestone
                }
                else if(choice == 2) //if the player chooses to continue on
                {
                    user.setTimeDay(14); //sets the date two weeks in advance
                    for(int i = 0; i < 5; i++) 
                    {
                        if(user.getPlayer(i).getStatus() == true) //checks if the person is alive
                        {
                            user.setMaterialAmount((-3 * 14), 1); //decreases the food amount by 3 * 14 for each person from the player's inventory
                        }
                    }
                    user.setMiles(user.getMiles() + randnumbers(70, 140)); //the user's travelled miles increases between 70 and 140 miles
                    break; //loop breaks
                }
                else if(choice == 3) //if the player chooses to visit the store
                {
                    if(user.getMiles() >= 304 && user.getMiles() < 640) //checks which fort the player is at
                    {
                        for(int i = 0; i < 5; i++) //loops through all of the supplies
                        {
                            user.setMaterialCost(user.getMaterials(i).getCost() * 1.25, i); //sets the cost of each materials by 25% more
                        }
                        user = store(user, mainstore); //takes the user to the store function
                        user.setMiles(user.getMiles() + 1); //sets the player's miles + 1 so the player does not get stuck at the milestone
                    }
                    else if(user.getMiles() >= 640 && user.getMiles() < 989)
                    {
                        for(int i = 0; i < 5; i++) //loops through all of the supplies
                        {
                            user.setMaterialCost(user.getMaterials(i).getCost() * 1.5, i); //sets the cost of each materials by 50% more
                        }
                        user = store(user, mainstore); //takes the user to the store function
                        user.setMiles(user.getMiles() + 1); //sets the player's miles + 1 so the player does not get stuck at the milestone
                    }
                    else if(user.getMiles() >= 989 && user.getMiles() < 1395)
                    {
                        for(int i = 0; i < 5; i++) //loops through all of the supplies
                        {
                            user.setMaterialCost(user.getMaterials(i).getCost() * 1.75, i); //sets the cost of each materials by 75% more
                        }
                        user = store(user, mainstore); //takes the user to the store function
                        user.setMiles(user.getMiles() + 1); //sets the player's miles + 1 so the player does not get stuck at the milestone
                    }
                    else if(user.getMiles() >= 1395 && user.getMiles() < 1648)
                    {
                        for(int i = 0; i < 5; i++) //loops through all of the supplies
                        {
                            user.setMaterialCost(user.getMaterials(i).getCost() * 2, i); //sets the cost of each materials by 100% more
                        }
                        user = store(user, mainstore); //takes the user to the store function
                        user.setMiles(user.getMiles() + 1); //sets the player's miles + 1 so the player does not get stuck at the milestone
                    }
                    else if(user.getMiles() >= 1648 && user.getMiles() < 1863)
                    {
                        for(int i = 0; i < 5; i++) //loops through all of the supplies
                        {
                            user.setMaterialCost(user.getMaterials(i).getCost() * 2.25, i); //sets the cost of each materials by 125% more
                        }
                        user = store(user, mainstore); //takes the user to the store function
                    }
                }
                else //if the user does not input something that is not in the given options
                {
                    cout << "Invalid choice. Please try again." << endl;
                    getline(cin, stemp); //the user inputs another choice
                }
            }
        }
        else if(user.getCheckpoint().getType() == "r") //if the milestone is a river
        {
            int choice;
            cout << "What do you want to do?:" << endl;
            cout << "1. Rest" << endl;
            cout << "2. Continue" << endl;
            string stemp;
            getline(cin, stemp); //user inputs either options
            choice = stoi(stemp);
            while(true) //loops until the user inputs a valid choice
            {
                if(choice == 1) //if the player chooses to rest
                {
                    stop(user); //takes the user to the stop and rest function
                    user.setMiles(user.getMiles() + 1); //sets the player's miles + 1 so the player does not get stuck at the milestone
                    break; //loop breaks
                }
                else if(choice == 2) //if the player chooses to continue on
                {
                    user.setTimeDay(14); //sets the date two weeks in advance
                    for(int i = 0; i < 5; i++) 
                    {
                        if(user.getPlayer(i).getStatus() == true) //checks if the person is alive
                        {
                            user.setMaterialAmount((-3 * 14), 1); //decreases the food amount by 3 * 14 for each person from the player's inventory
                        }
                    }
                    user.setMiles(user.getMiles() + randnumbers(70, 140)); //the user's travelled miles increases between 70 and 140 miles
                    break; //loop breaks
                }
                else //if the user does not input something that is not in the given options
                {
                    cout << "Invalid choice. Please try again." << endl;
                    getline(cin, stemp); //the user inputs another choice
                }
            }
        }
        user.setCheckpoint(); //each element in the milestone arrays increase by one
    }
    cout << "Miles Traveled: " << user.getMiles() << endl; 
    cout << "Next Milestone: " << user.getCheckpoint().getMiles() - user.getMiles() << endl;
    return user; //returns the Traveler object of the player
}
/*
The function gives the player a chance to hunt to randomly encounter an animal and solve a puzzle in order to successfully
hunt the animal (each animal gives different amount of food). The player also gets to choose how well each person wants to eat for the given day.
1. Random odds are generated for each different type of animal to determine which animal will be encountered
2. Depending of the odds works in favor of the player, the player decides whether they want to hunt the animal(s) or not
3. Then, the function determines if the player has enough bullets to hunt
- if so, they need to solve a puzzle in order to successfuly hunt the animal
- Depending on the animal and the player wins, they receive a certain amount of food. Otherwise, notifies the player that the hunt is unsuccessful
4. If the player has successfully hunted for food, they are asked how well they want to eat for the day
5. Checks if the total amount of food is more than 1000. If so, the player leaves behind extra food.
6. The date increases by 1 date and returns the Traveler object of the player
Parameters: the Traveler object of the player
Return: the Traveler object of the player
*/
Traveler hunt(Traveler user)
{
    system("clear"); //clears terminal
    int retrivedfood = 0;
    if(randnumbers(1, 2) == 1) //random number generator for rabbit encounter --> the player will encounter a rabbit
    {
        string choice;
        cout << "You got lucky! You encountered a rabbit. Do you want to hunt it? (Y/N)" << endl;
        getline(cin, choice); //user inputs yes or no
        if(choice == "Y") //if user inputs yes
        {
            if(user.getMaterials(2).getAmount() >= 10) //checks if the player has more than 10 bullets to hunt
            {
                if(puzzle() == true) //if the player passed the puzzle
                {
                    cout << "Your hunt was a success! You have gained 2 lbs of food." << endl;
                    retrivedfood = retrivedfood + 2; //the user gains 2 lbs of food
                    user.setMaterialAmount(-10, 2); //decreases the bullets amount by 10 from the player's inventory
                }
                else //if the player failed the puzzle
                {
                    cout << "The hunt was unsuccessful." << endl;
                }
            }
            else //if the user does not want to hunt it
            {
                cout << "The hunt was unsuccessful." << endl;
            }  
        }
    }
    if(randnumbers(1, 4) == 1) //the player will encounter a fox
    {
        string choice;
        cout << "You got lucky! You encountered a fox. Do you want to hunt it? (Y/N)" << endl;
        getline(cin, choice); //user inputs yes or no
        if(choice == "Y") //if user inputs yes
        {
            if(user.getMaterials(2).getAmount() >= 10) //checks if the player has more than 10 bullets to hunt
            {
                if(puzzle() == true) //if the player passed the puzzle
                {
                    cout << "Your hunt was a success! You have gained 5 lbs of food." << endl;
                    retrivedfood = retrivedfood + 8; //the user gains 5 lbs of food
                    user.setMaterialAmount(-8, 2); //decreases the bullets amount by 8 from the player's inventory
                }
                else //if the player failed the puzzle
                {
                    cout << "The hunt was unsuccessful." << endl;
                }
            }
            else //if the user does not want to hunt it
            {
                cout << "The hunt was unsuccessful." << endl;
            }  
        }
    }
    int deerchance = randnumbers(1, 100); //random number generator for deer encounter
    if(deerchance >= 1 && deerchance <= 15) //the player will encounter a deer
    {
        string choice;
        cout << "You got lucky! You encountered a deer. Do you want to hunt it? (Y/N)" << endl;
        getline(cin, choice); //user inputs yes or no
        if(choice == "Y") //if user inputs yes
        {
            if(user.getMaterials(2).getAmount() >= 10) //checks if the player has more than 10 bullets to hunt
            {
                if(puzzle() == true) //if the player passed the puzzle
                {
                    cout << "Your hunt was a success! You have gained 60 lbs of food." << endl;
                    retrivedfood = retrivedfood + 60; //the user gains 60 lbs of food
                    user.setMaterialAmount(-5, 2); //decreases the bullets amount by 5 from the player's inventory
                }
                else //if the player failed the puzzle
                {
                    cout << "The hunt was unsuccessful." << endl;
                }
            }
            else //if the user does not want to hunt it
            {
                cout << "The hunt was unsuccessful." << endl;
            }  
        }
    }
    int bearchance = randnumbers(1, 100); //random number generator for bear encounter
    if(bearchance >= 1 && bearchance <= 7) //the player will encounter a bear
    {
        string choice;
        cout << "You got lucky! You encountered a bear. Do you want to hunt it? (Y/N)" << endl;
        getline(cin, choice); //user inputs yes or no
        if(choice == "Y") //if user inputs yes
        {
            if(user.getMaterials(2).getAmount() >= 10) //checks if the player has more than 10 bullets to hunt 
            {
                if(puzzle() == true) //if the player passed the puzzle
                {
                    cout << "Your hunt was a success! You have gained 200 lbs of food." << endl;
                    retrivedfood = retrivedfood + 200; //the user gains 200 lbs of food
                    user.setMaterialAmount(-10, 2); //decreases the bullets amount by 10 from the player's inventory
                }
                else //if the player failed the puzzle
                {
                    cout << "The hunt was unsuccessful." << endl;
                }
            }
            else //if the user does not want to hunt it
            {
                cout << "The hunt was unsuccessful." << endl;
            }  
        }
    }
    if(randnumbers(1, 20) == 1) //random number generator for moose encounter --> the player will encounter a moose
    {
        string choice;
        cout << "You got lucky! You encountered a moose. Do you want to hunt it? (Y/N)" << endl;
        getline(cin, choice); //user inputs yes or no
        if(choice == "Y") //if user inputs yes
        {
            if(user.getMaterials(2).getAmount() >= 10) //checks if the player has more than 10 bullets to hunt 
            {
                if(puzzle() == true) //if the player passed the puzzle
                {
                    cout << "Your hunt was a success! You have gained 500 lbs of food." << endl;
                    retrivedfood =  retrivedfood + 500; //the user gains 500 lbs of food
                    user.setMaterialAmount(-12, 2); //decreases the bullets amount by 12 from the player's inventory
                }
                else //if the player failed the puzzle
                {
                    cout << "The hunt was unsuccessful." << endl;
                }
            }
            else //if the user does not want to hunt it
            {
                cout << "The hunt was unsuccessful." << endl;
            }  
        }
    }
    if(retrivedfood != 0) //if the user successfully hunted for any food
    {
        //the options for eating is displayed
        string choice;
        cout << "How well would you like to eat?" << endl;
        cout << "(P)oorly: 2 lbs of food per person" << endl;
        cout << "(M)oderately: 3 lbs of food per person" << endl;
        cout << "(W)ell: 5 lbs of food per person" << endl;
        getline(cin, choice); //user inputs either of the three options
        while(true) //loops until a break statement
        {
            if(choice == "P") //if the user chooses poor
            {
                for(int i = 0; i < 5; i++) //loops through the party array
                {
                    if(user.getPlayer(i).getStatus() == true) //if the person is alive
                    {
                        user.setMaterialAmount(-2, 1); //decreases the food amount by 2 from the player's inventory
                    }
                }
                break; //breaks the loop
            }
            else if(choice == "M") //if the user chooses moderate
            {
                for(int i = 0; i < 5; i++) //loops through the party array
                {
                    if(user.getPlayer(i).getStatus() == true) //if the person is alive
                    {
                        user.setMaterialAmount(-3, 1); //decreases the food amount by 3 from the player's inventory
                    }
                }
                break; //breaks the loop
            }
            else if(choice == "W") //if the user chooses well
            {
                for(int i = 0; i < 5; i++) //loops through the party array
                {
                    if(user.getPlayer(i).getStatus() == true) //if the person is alive
                    {
                        user.setMaterialAmount(-5, 1); //decreases the food amount by 5 from the player's inventory
                    }
                }
                break; //breaks the loop
            }
            else //if the user does not input something in the given options
            {
                cout << "Invalid choice. Please try again." << endl;
                getline(cin, choice);
            }
        }
    }
    else //if the player does not get any encounters
    {
        cout << "The hunt was unsuccessful." << endl;
    }
    if(user.getMaterials(1).getAmount() + retrivedfood <= 1000) //checks if the total amount of food is less than 1000 lbs
    {
        user.setMaterialAmount(user.getMaterials(1).getAmount() + retrivedfood, 1); //sets the total amount of food the player has to their inventory
    }
    else //if the total amount of food is more than 1000 lbs
    {
        cout << "The wagon can only hold 1000 lbs of food. Some of it had to be left behind." << endl;
        user.setMaterialAmount(1000, 1); //sets the player's total amount of food to 1000 
        clear();
    }
    user.setTimeDay(1); //sets 1 day in advance
    return user; //returns the Traveler object of the user
}
/*
The function ends the game for the player
1. Prints out a message that their trip was cut short
2. Their data is saved to a seperate file
3. Exits out of the program
Parameters: the Traveler object of the player
Return: None
*/
void quit(Traveler user)
{
    system("clear");
    cout << "I'm sorry you have to cut your trip short. Better luck next time!" << endl;
    savedata(user); //saves the user's data
    exit(0); //exits out of the program
}
/*
The function displays the user's stats and menu
1. All of the user stats will be displayed
2. Then, the menu will be displayed to ask what the player want to do next
3. Once the user is done with the menu, the Traveler object of the player will be returned
Parameters: the Traveler object of the player and the Traveler object of the shop
Return: the Traveler object of the player
*/
Traveler usermenu(Traveler user, Traveler mainstore)
{
    int choice = 0;
    while(true) //loops the menu until a break statement
    {
        //all the user's stats are displayed
        cout << "Today is " << user.getTime().getMonth() << ' ' << user.getTime().getDay() << ", " << user.getTime().getYear() << endl;
        cout << "Miles Traveled: " << user.getMiles() << " miles" << endl;
        cout << "Next Landmark: " << user.getCheckpoint().getMiles() - user.getMiles() << " miles" << endl;
        cout << "Food: " << user.getMaterials(1).getAmount() << " lbs" << endl;
        cout << "Bullets Left: " << user.getMaterials(2).getAmount() << endl;
        cout << "Money Left: $" << user.getBalance() << endl;
        //the menu and given options are displayed as well
        cout << "How would you like to proceed your journey?" << endl;
        cout << "1. Stop and rest" << endl;
        cout << "2. Continue on" << endl;
        cout << "3. Hunt for food" << endl;
        cout << "4. Quit" << endl;
        string stemp;
        getline(cin, stemp);
        choice = stoi(stemp);
        if(choice == 1) //if the user chooses to stop and rest
        {
            user = stop(user); //takes the user to the stop function
            break;
        }
        else if(choice == 2) //if the user chooses to continue on their journey
        {
            user = continueon(user, mainstore); //takes the user to the continueon function
            break;
        }
        else if(choice == 3) //if the user chooses to hunt
        {
            user = hunt(user); //takes the user to the hunt function
            break;
        }
        else if(choice == 4) //if the user chooses to quit
        {
            quit(user); //takes the user to the quit function
            break;
        }
        else if(choice != 1||choice != 2||choice != 3||choice != 4) //if the user inputs something not in the given options
        {
            cout << "Invalid choice. Please try again." << endl;
            clear();
        }
    }
    //this is where each turn of the game will be simulated, also given the status update of the user
    //the user will be given the options to either stop and rest, continue on, hunt for animals, or quit the game and will also have different statements for each option
    return user; //returns the Traveler object of the user
}

int main()
{
    cout << "Hello and Welcome to the Oregon Trail!" << endl;
    Traveler user = Traveler(); //calls the default constructor to create the user and the part and set a startin date
    Traveler mainstore = Traveler(1); //calls another constructor for the shop
    cout << "Your goal is to travel from Independence, Missouri to Oregon City (2040 miles) by the end of the fall" << endl;
    cout << "The trail will be long and treacherous so make sure you get prepared first." << endl;
    clear(); //clears the terminal
    user = store(user, mainstore); //calls to the store function and then saves the data once the user is done
    while(user.getMiles() < 2048) //while the player has not reach the end which is Oregon City
    {
        user = usermenu(user, mainstore); //takes the player to the menu and saves data once the user finishes with options
        int randmisfortune = randnumbers(1, 10); //randomly picks a number between 1 and 10 for the misfortune
        if(randmisfortune >= 1 && randmisfortune <= 4) //if the number is between 1 - 4 (40%)
        {
            user = misfortune(user); //takes the user to the misfortune function 
        }
        int attackprobability = (((pow((user.getMiles()/100)-4,2)+72)/(pow((user.getMiles()/100)-4, 2)+12))-1) * 10; //probability of meeting raiders
        int rand = randnumbers(1, 100); //randomly picks a number between 1 and 100 for raider attack
        if(rand >= 1 && rand <= attackprobability) //if the number is between 1 - probability of raider attack
        {
            user = raiderattack(user); //takes the user to the raider attack function
        }
        //this if statement checks if the player does not meet any of conditions needed to finish the game
        if(user.getPlayer(0).getStatus() == false||user.getMaterials(0).getAmount() == 0||
        user.getMaterials(1).getAmount() <= 0||user.getMaterials(3).getAmount() < 0||
        (user.getTime().getMonth() == "November" && user.getTime().getDay() == 30))
        {   //prints out their data and that they have failed/died
            cout << "YOU HAVE DIED OF DYSENTERY!" << endl;
            cout << "Leader's Name: " << user.getPlayer(0).getName() << endl;
            cout << "Miles Traveled: " << user.getMiles() << endl;
            if(user.getMaterials(1).getAmount() <= 0) //if the user's food amount is less than or equal to 0
            {
                cout << "Food Remaining: 0" << endl;
            }
            else //prints out the user's remaining food
            {
                cout << "Food Remaining: " << user.getMaterials(1).getAmount() << endl;
            }
            cout << "Cash Remaining: $" << user.getBalance() << endl; //prints out the user's remaining cash
            savedata(user); //saves the user's data
            exit(0); //exits out of the program
        }
        clear(); //after each turn, the terminal is cleared
        //each function/class will probably run under this loop
    }
    cout << "Congratulations! You have made it to Oregon!" << endl; //otherwise, the player wins and the game is finished
    savedata(user); //saves the user's data
}