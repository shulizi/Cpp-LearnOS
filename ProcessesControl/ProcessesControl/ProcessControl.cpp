//
//  ProcessControl.cpp
//  ProcessesControl
//
//  Created by 杜李 on 2018/12/15.
//  Copyright © 2018年 杜李. All rights reserved.
//

#include "ProcessControl.h"


void PriorityClass::createProcesses(){
    head = new PCB(1,3,5);
    PCB* p2 = new PCB(2,6,2);
    PCB* p3 = new PCB(3,2,4);
    PCB* p4 = new PCB(4,4,5);
    PCB* p5 = new PCB(5,8,4);
    
    insertProcessByPriority(p2);
    insertProcessByPriority(p3);
    insertProcessByPriority(p4);
    insertProcessByPriority(p5);
    
}
void PriorityClass::insertProcessByPriority(PCB* p){
    PCB* temp = head;
    PCB* preStruct = NULL;
    
    while (temp != NULL) {
        
        if(p->priority > temp->priority){
            if(preStruct == NULL){
                p->nextStruct = head;
                head = p;
            } else{
                preStruct->nextStruct = p;
                p->nextStruct = temp;
            }
            break;
        }
        preStruct = temp;
        temp = temp->nextStruct;
        
    }
    if(temp == NULL){
        preStruct -> nextStruct = p;
        
    }
}
void PriorityClass::startProcesses(){
    run = head;
    while (run != NULL) {
        run->state = 'R';
        showProcesses();
        while (true){
            
            run->priority -= 3;
            run->timeOnCPU++;
            if (run->timeOnCPU == run->timeToFinish){
                
                finishedQueue.push(run);
                run->state = 'O';
                run = getNextP(run);
                break;
            } else{
                PCB* temp = getNextP(run);
                if(temp!=NULL && run->priority < temp->priority){
                    run->state = 'W';
                    deleteP(run);
                    insertProcessByPriority(run);
                    run = temp;
                    break;
                }
            }
        }
    }
}
void PriorityClass::deleteP(PCB* p){
    PCB* temp = head;
    if (temp->id == p->id){
        head = head->nextStruct;
        p->nextStruct = NULL;
        return ;
    }
    while(temp->nextStruct!=NULL){
        if(temp->nextStruct->id == p->id){
            temp->nextStruct = p->nextStruct;
            p->nextStruct = NULL;
            break;
        }
        temp = temp->nextStruct;
    }
    
}
PCB* PriorityClass::getNextP(PCB* p){
    PCB* temp = p->nextStruct;
    if (temp == NULL){
        return NULL;
    }
    while (temp!=p){
        if (temp->state != 'O'){
            break;
        }
        temp = temp->nextStruct;
    }
    if (temp!=p || temp->state != 'O'){
        return temp;
    } else {
        return NULL;
    }
    
}
void PriorityClass::showProcesses(){
    PCB* temp = getNextP(run);
    cout << "==============================" << endl;
    cout << "RUNNING PROC.    WAITING QUEUE" << endl;
    cout << "                 ";
    while(temp!=NULL){
        cout << temp->id << " ";
        temp = getNextP(temp);
    }
    cout<<endl;
    cout << "==============================" << endl;
    cout << "ID\t\t\t\t";
    temp = head;
    while (temp != NULL) {
        cout << temp->id << " ";
        temp = temp->nextStruct;
    }
    cout<<endl;
    cout << "PRIORITY\t\t";
    temp = head;
    while (temp != NULL) {
        cout << temp->priority << " ";
        temp = temp->nextStruct;
    }
    cout<<endl;
    cout << "CPUTIME\t\t\t";
    temp = head;
    while (temp != NULL) {
        cout << temp->timeOnCPU << " ";
        temp = temp->nextStruct;
    }
    cout<<endl;
    cout << "ALLTIME\t\t\t";
    temp = head;
    while (temp != NULL) {
        cout << temp->timeToFinish<< " ";
        temp = temp->nextStruct;
    }
    cout<<endl;
    cout << "STATE\t\t\t";
    temp = head;
    while (temp != NULL) {
        cout << temp->state << " ";
        temp = temp->nextStruct;
    }
    cout<<endl;
    cout << "NEXT\t\t\t";
    temp = head;
    while (temp->nextStruct != NULL) {
        cout << temp->nextStruct->id << " ";
        temp = temp->nextStruct;
    }
    cout << "0 ";
    cout<<endl;
    
}




void RoundRobinClass::createProcesses(){
    head = new PCB(1,3,5);
    PCB* p2 = new PCB(2,6,2);
    PCB* p3 = new PCB(3,2,4);
    PCB* p4 = new PCB(4,4,5);
    PCB* p5 = new PCB(5,8,4);
    
    head->nextStruct = p2;
    p2->nextStruct = p3;
    p3->nextStruct = p4;
    p4->nextStruct = p5;
    p5->nextStruct = head;
    tail = p5;
    
    
}
void RoundRobinClass::startProcesses(){
    run = head;
    while (run != NULL) {
        run->state = 'R';
        showProcesses();
        while (true){
            run->timeOnCPU++;
            if (run->timeToFinish == run->timeOnCPU){
                
                finishedQueue.push(run);
                run->state = 'O';
                run = getNextP(run);
                break;
            } else if(run->timeOnCPU % run->priority == 0){
                run->state = 'W';
                run = getNextP(run);
                break;
            }
        }
    }
}
PCB* RoundRobinClass::getNextP(PCB* p){
    PCB* temp = p->nextStruct;
    while (temp!=p){
        if (temp->state != 'O'){
            break;
        }
        temp = temp->nextStruct;
    }
    if (temp!=p || temp->state != 'O'){
        return temp;
    } else {
        return NULL;
    }
    
}
void RoundRobinClass::showProcesses(){
    PCB* temp = getNextP(run);
    cout << "==============================" << endl;
    cout << "RUNNING PROC.    WAITING QUEUE" << endl;
    cout << "                 ";
    while(temp!=run){
        cout << temp->id << " ";
        temp = getNextP(temp);
    }
    cout<<endl;
    cout << "==============================" << endl;
    cout << "ID\t\t\t\t";
    temp = head;
    cout << temp->id << " ";
    temp = temp->nextStruct;
    while (temp != head) {
        cout << temp->id << " ";
        temp = temp->nextStruct;
    }
    cout<<endl;
    cout << "ROBIN\t\t\t";
    temp = head;
    cout << temp->priority << " ";
    temp = temp->nextStruct;
    while (temp != head) {
        cout << temp->priority << " ";
        temp = temp->nextStruct;
    }
    cout<<endl;
    cout << "CPUTIME\t\t\t";
    temp = head;
    cout << temp->timeOnCPU << " ";
    temp = temp->nextStruct;
    while (temp != head) {
        cout << temp->timeOnCPU << " ";
        temp = temp->nextStruct;
    }
    cout<<endl;
    cout << "ALLTIME\t\t\t";
    temp = head;
    cout << temp->timeToFinish<< " ";
    temp = temp->nextStruct;
    while (temp != head) {
        cout << temp->timeToFinish<< " ";
        temp = temp->nextStruct;
    }
    cout<<endl;
    cout << "STATE\t\t\t";
    temp = head;
    cout << temp->state << " ";
    temp = temp->nextStruct;
    while (temp != head) {
        cout << temp->state << " ";
        temp = temp->nextStruct;
    }
    cout<<endl;
    cout << "NEXT\t\t\t";
    temp = head;
    cout << temp->nextStruct->id << " ";
    temp = temp->nextStruct;
    while (temp != head) {
        cout << temp->nextStruct->id << " ";
        temp = temp->nextStruct;
    }
    cout<<endl;
    
};
