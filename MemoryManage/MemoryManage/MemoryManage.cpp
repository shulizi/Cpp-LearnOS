#include "InstructionStruct.h"
#include "MemoryManage.h"
#include "stdlib.h"
#include <iostream>
using namespace std;

void MemoryManage::createInstructions(){

    
    for(int i =0;i<lengthOfIns;i++){
        instructions[i] = new InstructionStruct(rand()%10);
        cout<< instructions[i]->id<<" ";
    };
    cout<<endl;
    
};
void MemoryManage::startOPT(){
    HitRate = 0;
    indexOfIns = 0;
    for (int i = 0;i < lengthOfIns;i++){
        cout<<"insert "<<instructions[i]->id<<endl;
        insertInstructionOPT(instructions[i]);
        showPageTable();
        indexOfIns++;
    }
    cout<<"Hit Rate:"<<1.0*HitRate/lengthOfIns<<endl;
};
void MemoryManage::startLRU(){
    HitRate = 0;
    indexOfIns = 0;
    for (int i = 0;i < lengthOfIns;i++){
        cout<<"insert "<<instructions[i]->id<<endl;
        insertInstructionLRU(instructions[i]);
        showPageTable();
        indexOfIns++;
    }
    cout<<"Hit Rate:"<<1.0*HitRate/lengthOfIns<<endl;
};
void MemoryManage::startLFU(){
    HitRate = 0;
    indexOfIns = 0;
    for (int i = 0;i < lengthOfIns;i++){
        cout<<"insert "<<instructions[i]->id<<endl;
        insertInstructionLFU(instructions[i]);
        showPageTableLFU();
        indexOfIns++;
    }
    cout<<"Hit Rate:"<<1.0*HitRate/lengthOfIns<<endl;
};
void MemoryManage::insertInstructionLFU(InstructionStruct* in ){
    if(currentLengthOfPT == 0){
        head = in;
        tail = head;
        currentLengthOfPT = 1;
    }else if(currentLengthOfPT < lengthOfPT){
        
        tail->nextStruct = in;
        in->preStruct = tail;
        tail = in;
        currentLengthOfPT++;
        sortByFrequency();
        
    } else {
        InstructionStruct* temp = head;
        while(temp!=NULL){
            if(in->id == temp->id){
                HitRate++;
                temp->frequency++;
                sortByFrequency();
                
                return;
            }
            temp=temp->nextStruct;
        }
        
        tail->nextStruct = in;
        in->preStruct = tail;
        tail = in;
        sortByFrequency();
        deleteInstructionFromPT(tail);
    }
};
void MemoryManage::sortByFrequency(){
    InstructionStruct* temp = head;
    InstructionStruct* temp2;
    while(temp!=NULL){
        //当当前节点访问次数少于下一节点访问次数的时候调换两节点位置
        if(temp->preStruct!=NULL && temp->nextStruct!=NULL &&temp->nextStruct->nextStruct==NULL && temp->frequency<temp->nextStruct->frequency){//如果当前节点下一节点是尾巴节点
            
            temp2=temp->nextStruct;
            temp->preStruct->nextStruct = temp->nextStruct;
            temp->nextStruct->preStruct = temp->preStruct;
            temp->nextStruct = NULL;
            temp->preStruct = temp2;
            temp2->nextStruct = temp;
            tail = temp;
            
        }else if(temp==head && temp->frequency<temp->nextStruct->frequency){//如果当前节点是头节点
            temp->nextStruct->preStruct =NULL;
            temp2=temp->nextStruct;
            temp->nextStruct = temp2->nextStruct;
            temp2->nextStruct->preStruct = temp;
            temp->preStruct = temp2;
            temp2->nextStruct = temp;
            head = temp2;
            temp = head;//从头开始排序
            continue;
        }else if(temp->preStruct!=NULL && temp->nextStruct!=NULL && temp->frequency<temp->nextStruct->frequency){//如果当前节点和下一节点都是是中间节点
            temp2=temp->nextStruct;
            temp->preStruct->nextStruct = temp->nextStruct;
            temp->nextStruct->preStruct = temp->preStruct;
            temp->nextStruct = temp2->nextStruct;
            temp2->nextStruct->preStruct = temp;
            temp->preStruct = temp2;
            temp2->nextStruct = temp;
            temp = head;//从头开始排序
            continue;
        }
        temp = temp->nextStruct;
    }
};
void MemoryManage::insertInstructionLRU(InstructionStruct* in ){
    if(currentLengthOfPT == 0){
        head = in;
        tail = head;
        currentLengthOfPT = 1;
    }else {
        InstructionStruct* temp = head;
        while(temp!=NULL){//看是否命中
            if(in->id == temp->id){
                HitRate++;
                putInstructionFromPTToTail(temp);
                return;
            }
            temp=temp->nextStruct;
        }
        if(currentLengthOfPT < lengthOfPT){//刚开始页表未满，可以持续添加
            
            tail->nextStruct = in;
            in->preStruct = tail;
            tail = in;
            currentLengthOfPT++;
        } else {//页表满了后，要删除最先添加的指令
            deleteInstructionFromPT(head);
            tail->nextStruct = in;
            in->preStruct = tail;
            tail = in;
        }
        
    }
};
void MemoryManage::putInstructionFromPTToTail(InstructionStruct* in){
    if (in == head){
        head = head->nextStruct;
        in->nextStruct->preStruct = NULL;
        tail->nextStruct = in;
        in->preStruct = tail;
        in->nextStruct = NULL;
        tail = in;
        
    }else if(in != tail){

        in->preStruct->nextStruct = in->nextStruct;
        in->nextStruct->preStruct = in->preStruct;
        in->nextStruct = NULL;
        in->preStruct = tail;
        tail->nextStruct = in;
        tail = in;
        
    }
};
void MemoryManage::deleteInstructionFromPT(InstructionStruct* in){
    if (in == head){
        head = head->nextStruct;
        head->preStruct = NULL;
    }else if(in==tail){
        tail = tail->preStruct;
        tail->nextStruct = NULL;
        
    }else{
        
        in->preStruct->nextStruct = in->nextStruct;
        in->nextStruct->preStruct = in->preStruct;
    }
};
void MemoryManage::insertInstructionOPT(InstructionStruct* in){
    
    if(currentLengthOfPT == 0){//添加页表中第一个节点
        head = in;
        tail = head;
        currentLengthOfPT = 1;
        return;
    }
    InstructionStruct* temp = head;
    InstructionStruct* flagToDelete = NULL;//待删除节点
    int indexOfFound = -1;
    while(temp!=NULL){//看是否命中
        if(in->id == temp->id){
            HitRate++;
            return;
        }
        temp=temp->nextStruct;
    }
    if(currentLengthOfPT < lengthOfPT){//如果页表未满，则不需要删除指令
        
        tail->nextStruct = in;
        in->preStruct = tail;
        tail = in;
        currentLengthOfPT++;
        
    } else {//如果页表已满
        temp = head;
        while(temp !=NULL){
            int i = indexOfIns;
            for(;i<lengthOfIns;i++){
                if(temp->id == instructions[i]->id){
                    if(i > indexOfFound){//将最晚将要访问的节点作为待删除节点
                        flagToDelete = temp;
                        indexOfFound = i;
                    }
                    break;
                }
            }
            if ( i== lengthOfIns){//如果页表里的该节点不在后继指令中，则直接删除该节点
                deleteInstructionFromPT(temp);
                tail->nextStruct = in;
                in->preStruct = tail;
                tail = in;
                break;
            }
            
            temp = temp->nextStruct;
        }
        if(temp == NULL){//没有找到可删除节点，则删除在后继指令中最后一个访问的节点
            deleteInstructionFromPT(flagToDelete);
            tail->nextStruct = in;
            in->preStruct = tail;
            tail = in;
        }
    }
};
void MemoryManage::showPageTable(){
    InstructionStruct* temp = head;
    cout<<"descendant instruction:"<<endl;
    for (int i=indexOfIns;i<lengthOfIns;i++){
        cout<<instructions[i]->id<<" ";
    }
    cout<<endl<<"page table:";
    while(temp!= NULL){
        
        cout<<temp->id<<" ";
        temp = temp->nextStruct;
        
    }
    cout<<endl<<"-------------------"<<endl;
};
void MemoryManage::showPageTableLFU(){
    InstructionStruct* temp = head;
    cout<<"descendant instruction:"<<endl;
    for (int i=indexOfIns;i<lengthOfIns;i++){
        cout<<instructions[i]->id<<" ";
    }
    cout<<endl<<"page table:";
    while(temp!= NULL){
        
        cout<<temp->id<<"-"<<temp->frequency<<" ";
        temp = temp->nextStruct;
        
    }
    cout<<endl<<"-------------------"<<endl;
};
