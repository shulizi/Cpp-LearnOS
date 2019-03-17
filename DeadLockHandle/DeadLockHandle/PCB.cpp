#include <stdlib.h>
#include <algorithm>
#include "PCB.h"
using namespace std;
PCB::PCB(int ID,int dynamicResources[10],int maxResource){
this->ID = ID;
    for (int i=0;i<10;i++){
        this->dynamicResources[i] =dynamicResources[i];
        if (dynamicResources[i] == 0)
            break;
    }
    this->dynamicResourceIndex = 0;
    this->maxResource = maxResource;
this->currentResource = 0;
this->T = 1;
this->isOver = false;
this->isFound = false;
};
bool sortFunction (int i,int j) { return (i>j); }
PCB::PCB(int ID,int resources[10]){
    this->ID = ID;
    this->nextStruct = NULL;
    for (int i=0;i<10;i++){
        this->orderedResources[i] =resources[i];
    }
    sort(orderedResources,orderedResources+10,sortFunction);
    
};
