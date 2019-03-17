//
//  main.cpp
//  SoftwareEngineering
//
//  Created by 杜李 on 2018/12/27.
//  Copyright © 2018年 杜李. All rights reserved.
//

#include <iostream>
#include <string>
#include "GameClass.hpp"
using namespace std;      //introduces namespace std
int main( void )
{
   
    string name; //used to store the player’s name
    
    int menu_choice; //stores the user’s choice from the menu
    
    GameClass game;
    
    //stores which numbers correspond to which menu choices
    int archers_menu, catapults_menu, swordsmen_menu;
    int fight_menu;
    
    cout << "Welcome Adventurer, what is your name?\n";
    cin >> name;
    cout << "Well, " << name
    << " welcome to the Roman Commander Game.\n"
    << "\nYou are the commander of the Roman Army"
    << " attacking Germania.";
    while (!game.isGameOver()) //main game loop
    {
        //variables to store how many units the player sends
        int archers_sent=0, catapults_sent=0;
        int swordsmen_sent=0;
        cout << "\nYou have " << game.getArchers()
        << " archers, " << game.getCatapults()
        << " catapults, and "
        << game.getSwordsmen() << " swordsmen.\n"
        << "\nGermania has " << game.getGArchers()
        << " archers, "
        << game.getGCatapults() << " catapults, and "
        << game.getGSwordsmen()
        << " swordsmen.\n";
        do //pre-battle loop
        {
            //keeps track of which menu numbers
            //are being used
            int i = 1;
            if (game.getArchers() > 0 &&
                ((game.getArchers() - archers_sent) != 0))
            {
                archers_menu = i;
                cout << "[" << i << "] Send Archers\n";
                i++;
            }
            else archers_menu = 0;
            if (game.getCatapults() > 0 &&
                ((game.getCatapults() - catapults_sent) != 0))
            {
                catapults_menu = i;
                cout << "[" << i << "] Send Catapults\n";
                i++;
            }
            else catapults_menu = 0;
            if (game.getSwordsmen() > 0 &&
                ((game.getSwordsmen() - swordsmen_sent) != 0))
            {
                swordsmen_menu = i;
                cout << "[" << i << "] Send Swordsmen\n";
                i++;
            }
            else swordsmen_menu = 0;
            fight_menu = i;
            cout <<"["<< i <<"] Go Fight\n";
            
            cin >> menu_choice;
            if (menu_choice == archers_menu)
            {
                do {
                    cout << "How many archers"
                    " would you like to send?\n";
                    cin >> archers_sent;
                }while (!(archers_sent > -1
                          && archers_sent <= game.getArchers()));
            }
            else if  (menu_choice == catapults_menu)
            {
                do {
                    cout << "How many catapults"
                    " would you like to send?\n";
                    cin >> catapults_sent;
                }while (!(catapults_sent > -1 &&
                          catapults_sent <= game.getCatapults()));
            }
            else if (menu_choice == swordsmen_menu)
            {
                do {
                    cout << "How many swordsmen"
                    " would you like to send?\n";
                    cin >> swordsmen_sent;
                }
                while (!(swordsmen_sent > -1 &&
                         swordsmen_sent <= game.getSwordsmen()));
            }
        }
        //end pre-battle loop
        while (menu_choice != fight_menu);
        
        cout << "\nEntering Battle...\n";
        
        int* army_dead = game.fight(archers_sent, catapults_sent, swordsmen_sent);
       
        
        
        cout << "It was a long battle. "
        << army_dead[0] << " archers died.\n"
        << army_dead[1] << " catapults died.\n"
        << army_dead[2] << " swordsmen died.\n";
        
    } //end of main game loop
    
    //display appropriate ending message
    if (!game.isGameWon())
    {
        cout << "\nYou lost. Try again next time.\n";
        return 0;
    }
    cout << "\nCongratulations, you won!\n";
    return 0;
}
