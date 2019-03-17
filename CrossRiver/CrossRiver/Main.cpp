//
//  main.c
//  CrossRiver
//
//  Created by 杜李 on 2018/12/21.
//  Copyright © 2018年 杜李. All rights reserved.
//

#include <iostream>
#include <queue>
#include "MyProcessControl.h"
using namespace std;
#define len(x) (sizeof(x)/sizeof((x)[0]))
int main(){
    
    MyProcessControlClass  myProcessControl;
    myProcessControl.startSearch();
    
    
    return 0;
}
