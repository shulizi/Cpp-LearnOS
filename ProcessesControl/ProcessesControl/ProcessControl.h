//
//  ProcessControl.hpp
//  ProcessesControl
//
//  Created by 杜李 on 2018/12/15.
//  Copyright © 2018年 杜李. All rights reserved.
//

#ifndef ProcessControl_h
#define ProcessControl_h
#include "PCB.h"
#include <queue>
#include <iostream>
using namespace std;
using namespace std;
class PriorityClass{
private:
    PCB* run;
    PCB* head;
    queue<PCB*> finishedQueue;
    void insertProcessByPriority(PCB*);
    void deleteP(PCB*);
    PCB* getNextP(PCB*);
public:
    void createProcesses();
    void startProcesses();
    void showProcesses();
    
};

class RoundRobinClass{
private:
    PCB* run;
    PCB* head;
    PCB* tail;
    queue<PCB*> finishedQueue;
    PCB* getNextP(PCB*);
public:
    void createProcesses();
    void startProcesses();
    void showProcesses();
};
#endif /* ProcessControl_h */
