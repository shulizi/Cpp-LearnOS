#include <stdlib.h>
#include "PCB.h"

PCB::PCB(int id,int priority,int timeToFinish){
    this->id = id;
    this->priority = priority;
    this->timeToFinish = timeToFinish;
    this->timeOnCPU = 0;
    this->nextStruct = NULL;
    this->state = 'W';
}
