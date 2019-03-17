//
//  GameClass.hpp
//  SoftwareEngineering
//
//  Created by 杜李 on 2018/12/27.
//  Copyright © 2018年 杜李. All rights reserved.
//

#ifndef GameClass_hpp
#define GameClass_hpp
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
class GameClass{
private:
    int archers;
    int catapults;
    int swordsmen;
    
    int g_archers;
    int g_catapults;
    int g_swordsmen;
    
public:
    int getArchers();
    int getCatapults();
    int getSwordsmen();
    int getGArchers();
    int getGCatapults();
    int getGSwordsmen();
    int* fight(int archers_sent,int catapults_sent,int swordsmen_sent);
    bool isGameOver();
    bool isGameWon();
    GameClass();
};

#endif /* GameClass_hpp */
