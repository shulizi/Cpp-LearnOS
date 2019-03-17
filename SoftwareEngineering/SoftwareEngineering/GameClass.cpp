//
//  GameClass.cpp
//  SoftwareEngineering
//
//  Created by 杜李 on 2018/12/27.
//  Copyright © 2018年 杜李. All rights reserved.
//

#include "GameClass.hpp"

GameClass::GameClass(){
    archers = 50;
    catapults = 25;
    swordsmen = 100;
    
    //units that the Germanians start with (random)
    // random number between 70 and 20
    g_archers = rand() % (51) + 20;
    g_catapults = rand() % (41) + 10; //between 50 and 10
    //between 150 and 50
    g_swordsmen = rand() % (101) + 50;
}
int* GameClass::fight(int archers_sent,int catapults_sent,int swordsmen_sent){
    int archers_dead, catapults_dead, swordsmen_dead;
    int g_archers_dead, g_catapults_dead;
    int g_swordsmen_dead;
    
    //each catapult kills 2 archers
    archers_dead = 2 * g_catapults;
    //each swordsman kills 1 catapult
    catapults_dead = g_swordsmen;
    //each archer kills 3 swordsmen
    swordsmen_dead = 3 * g_archers;
    
    g_archers_dead = 2 * catapults_sent;
    g_catapults_dead = swordsmen_sent;
    g_swordsmen_dead = 3 * archers_sent;
    //makes sure that the number of
    //units does not go below 0.
    archers = (archers_dead < archers) ?
    archers - archers_dead : 0;
    catapults = (catapults_dead < catapults) ?
    catapults - catapults_dead : 0;
    swordsmen = (swordsmen_dead < swordsmen) ?
    swordsmen - swordsmen_dead : 0;
    
    g_archers = (g_archers_dead < g_archers) ?
    g_archers - g_archers_dead : 0;
    g_catapults = (g_catapults_dead < g_catapults) ?
    g_catapults - g_catapults_dead : 0;
    g_swordsmen = (g_swordsmen_dead < g_swordsmen) ?
    g_swordsmen - g_swordsmen_dead : 0;
    
    int* army_dead = new int[3];
    army_dead[0] = archers_dead;
    army_dead[1] = catapults_dead;
    army_dead[2] = swordsmen_dead;
    
    return army_dead;
}
bool GameClass::isGameOver(){
    if ((archers + catapults + swordsmen) == 0 || (g_archers + g_catapults + g_swordsmen) == 0)
        return true;
    return false;
}
bool GameClass::isGameWon(){
    if ((g_archers + g_catapults + g_swordsmen) == 0)
        return true;
    else
        return false;
}
int GameClass::getArchers(){
    return archers;
}
int GameClass::getCatapults(){
    return catapults;
}
int GameClass::getSwordsmen(){
    return swordsmen;
}
int GameClass::getGArchers(){
    return g_archers;
}
int GameClass::getGCatapults(){
    return g_catapults;
}
int GameClass::getGSwordsmen(){
    return g_swordsmen;
}
