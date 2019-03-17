//
//  OrderedResourceUsage.cpp
//  DeadLockHandle
//
//  Created by 杜李 on 2018/12/15.
//  Copyright © 2018年 杜李. All rights reserved.
//

#include "OrderedResource.h"


void OrderedResource::createProcesses(){
    for(int i=0;i<100;i++){
        lockedResources[i] = -1;
    }
    int a1[10] = {1000, 2, 3, 17, 50,-1,-1,-1,-1,-1};
    int a2[10] = {2, 5, 3, 17, 50,-1,-1,-1,-1,-1};
    int a3[10] = {8, 2, 92, 4, 9,6,8,191,-1,-1};
    int a4[10] = {5, 11, 30, 17, 3,9,3,-1,-1,-1};
    int a5[10] = {2, 24, 31, 9, 4,-1,-1,-1,-1,-1};
    head = new PCB(1,a1);
    PCB* p2 = new PCB(2,a2);
    PCB* p3 = new PCB(3,a3);
    PCB* p4 = new PCB(4,a4);
    PCB* p5 = new PCB(5,a5);
    
    head->nextStruct = p2;
    p2->nextStruct = p3;
    p3->nextStruct = p4;
    p4->nextStruct = p5;
    
    tail = p5;
    
    
}
void OrderedResource::startProcesses(){
    
    
    while (head != NULL) {
        showProcesses();
        run = head;
        
        if(resourceIsLocked(run->orderedResources[0],run->ID)){
            cout<<run->ID<<"'s resource "<<run->orderedResources[0]<<" is locked."<<endl;
            tail->nextStruct = run;
            tail = run;
            head = head->nextStruct;
            tail->nextStruct = NULL;
            
            
            continue;
        }
        cout<<"running "<<run->ID<<endl;
        lockResource(run->orderedResources[0],run->ID);
        for(int i=0;i<9;i++){
            run->orderedResources[i] = run->orderedResources[i+1];
        }
        if (run->orderedResources[0] == -1){
            
            finishedQueue.push(run);
            releaseResources(run->ID);
            head = head->nextStruct;
        }else{
            tail->nextStruct = run;
            tail = run;
            head = head->nextStruct;
            tail->nextStruct = NULL;
            
        }
        
    }
};
void OrderedResource::releaseResources(int id){
    
    for (int i=0;i<100;i+=2){
        if(lockedResources[i] == id){
            lockedResources[i] = -1;
            lockedResources[i+1] = -1;
        }
    }
};
void OrderedResource::lockResource(int resource,int id){
    for (int i=0;i<100;i+=2){
        if(lockedResources[i] == -1){
            lockedResources[i] = id;
            lockedResources[i+1] = resource;
            return ;
        }
    }
};
bool OrderedResource::resourceIsLocked(int resource,int id){
    for (int i=0 ;i<100;i+=2){
        if(lockedResources[i+1] == resource && lockedResources[i] != id){
            
            return true;
        } else if(lockedResources[i+1] == resource && lockedResources[i] == id){
            lockedResources[i] = -1;
            lockedResources[i+1] = -1;
            return false;
        }
    }
    return false;
};
void OrderedResource::showProcesses(){
    cout << "--------" << endl;
    PCB* temp = head;
    while (temp != NULL) {
        cout << "id: "<<temp->ID <<" resource: ";
        for(int i=0;i<10;i++){
            if(temp->orderedResources[i]==-1){
                break;
            }
            cout << temp->orderedResources[i] << " ";
        }
        temp = temp->nextStruct;
        cout<<endl;
    }
    cout << "###locked resource: " ;
    for(int i=0;i<100;i+=2){
        if(lockedResources[i]!=-1){
            cout<<lockedResources[i]<<"-";
            cout<<lockedResources[i+1]<<" ";
        }
    }
    cout<<endl;
};

