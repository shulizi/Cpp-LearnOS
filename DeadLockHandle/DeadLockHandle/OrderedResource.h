//
//  OrderedResourceUsage.hpp
//  DeadLockHandle
//
//  Created by 杜李 on 2018/12/15.
//  Copyright © 2018年 杜李. All rights reserved.
//

#ifndef OrderedResource_h
#define OrderedResource_h
#include "PCB.h"
#include <iostream>
#include <queue>
using namespace std;
class OrderedResource{
private:
    PCB* run;
    PCB* head;
    PCB* tail;
    queue<PCB*> finishedQueue;
    int lockedResources[100];
    bool resourceIsLocked(int resource,int id);
    void lockResource(int resource,int id);
    void releaseResources(int id);
public:
    void createProcesses();
    void startProcesses();
    void showProcesses();
    
};
#endif /* OrderedResource_h */
