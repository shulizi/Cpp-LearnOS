//
//  main.cpp
//  MemoryManage
//
//  Created by 杜李 on 2018/12/14.
//  Copyright © 2018年 杜李. All rights reserved.
//

#include <iostream>
#include "InstructionStruct.h"
#include "MemoryManage.h"

using namespace std;
int main(int argc, const char * argv[]) {
    MemoryManage memoryManage;
    memoryManage.createInstructions();
    memoryManage.startOPT();
//    memoryManage.createInstructions();
//    memoryManage.startLRU();
//    memoryManage.createInstructions();
//    memoryManage.startF();
    cout<<"hello"<<endl;
    return 0;
}
