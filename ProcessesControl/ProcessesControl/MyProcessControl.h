#ifndef MyProcessControl_h
#define MyProcessControl_h
#include <queue>
#include <iostream>
#include "PCB.h"
using namespace std;
class MyProcessControlClass{
private:
    PCB* run;
    PCB* finishedtail;
    PCB* finishedhead;
    queue<PCB* > finishedQueue;
    int lengthOfPBP;
    PCB* processesByPriority[10];
    void deleteP(PCB*,PCB*);

public:
    void createProcesses();
    void startProcesses();
    void showProcesses();
    void insertProcessByPriority(PCB*);
};
#endif /* MyProcessControl_h */
