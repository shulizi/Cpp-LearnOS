#include "DynamicResource.h"

#include <iostream>

using namespace std;

void DynamicResource::createProcesses(){
	systemCurrentResources = 0;
	systemMaxResources = 10;
    processesNumber = 3;
   
    int a1[10] = {2, 1, 3, 2, -1,0};
    int a2[10] = {2, 5, -2, 2, 1,0};
    int a3[10] = {6, 3,-3, 2, 1, -1,-2,0};
	head = new PCB(1,a1,8);
	PCB* p2 = new PCB(2,a2,8);
	PCB* p3 = new PCB(3,a3,9);
    
	head->nextStruct = p2;
	p2->nextStruct = p3;
    p3->nextStruct = NULL;
    
    
    cout << "CLAIM OF PROCESS 1 IS:\t";
    for (int i=0;i<10;i++){
        cout<<a1[i]<<"\t";
        if (a1[i] == 0) break;
    }
    cout << endl;
    cout << "CLAIM OF PROCESS 2 IS:\t";
    for (int i=0;i<10;i++){
        cout<<a2[i]<<"\t";
        if (a2[i] == 0) break;
    }
    cout << endl;
    cout << "CLAIM OF PROCESS 3 IS:\t";
    for (int i=0;i<10;i++){
        cout<<a3[i]<<"\t";
        if (a3[i] == 0) break;
    }
    cout << endl;
    cout << "THE SYSTEM ALLOCTION PROCESS IS AS FOLLOWS:"<<endl;
}
void DynamicResource::startProcessesWithNohandleDeadLock(){
    PCB* temp = head;
    cout << "\t\tPROCESS CLAIM ALLOCATION REMAINDER"<<endl;
    while(temp!=NULL){
        
        cout <<"\t\t"<< temp->ID<<"\t\t";
        cout << temp->dynamicResources[temp->dynamicResourceIndex]<<"\t\t";
        cout << temp->currentResource<<"\t\t";
        cout << systemMaxResources - systemCurrentResources<<endl;
        
        if (temp->maxResource > systemMaxResources){
            cout << "ERROR:RESOURCE EXCEEDING" << endl;
            break;
        }
        
        if(isAllFound()){
            cout << "THE WHOLE WORK CAN NOT BE COMPLETED" << endl;
            break;
        }
        if(!handleDeadLock(temp)){
            cout << "IF ALLOCATED,DEADLOCK MAY OCCUR" << endl;
            break;
        }
        setFound();
        
        systemCurrentResources += temp->dynamicResources[temp->dynamicResourceIndex];
        temp->currentResource += temp->dynamicResources[temp->dynamicResourceIndex];
        temp->dynamicResourceIndex ++;
        cout<<"RESOURCE IS ALLOCATED TO PROCESS "<<temp->ID<<endl;
        if(systemCurrentResources>systemMaxResources){
            cout<< "THE REMAINDER IS LESS THAN PROCESS "<<temp->ID<<" CLAIMS"<<endl;
            break;
        }
        if(temp->dynamicResources[temp->dynamicResourceIndex] == 0){
            cout<< "PROCESS "<<temp->ID << "  HAS FINISHED, RETURN ITS RESOURSE."<<endl;
            temp->isOver = true;
            systemCurrentResources -= temp->currentResource;
            
        }
        temp = findNextWaitingStruct(temp);
    }
}
void DynamicResource::startProcesses(){
	PCB* temp = head;
    cout << "\t\tPROCESS CLAIM ALLOCATION REMAINDER"<<endl;
	while(temp!=NULL){
        
        cout <<"\t\t"<< temp->ID<<"\t\t";
        cout << temp->dynamicResources[temp->dynamicResourceIndex]<<"\t\t";
        cout << temp->currentResource<<"\t\t";
        cout << systemMaxResources - systemCurrentResources<<endl;
        
		if (temp->maxResource > systemMaxResources){
			cout << "ERROR:RESOURCE EXCEEDING" << endl;
			break;
		}
		
		if(isAllFound()){
			cout << "THE WHOLE WORK CAN NOT BE COMPLETED" << endl;
			break;
		}
		
		if(!handleDeadLock(temp)){
			cout << "IF ALLOCATED,DEADLOCK MAY OCCUR" << endl;
			temp->isFound = true;
			temp = findNextWaitingStruct(temp);
			continue;
		}
		
		setFound();
        
        
		systemCurrentResources += temp->dynamicResources[temp->dynamicResourceIndex];
		temp->currentResource += temp->dynamicResources[temp->dynamicResourceIndex];
        temp->dynamicResourceIndex ++;
        cout<<"RESOURCE IS ALLOCATED TO PROCESS "<<temp->ID<<endl;
        if(systemCurrentResources>systemMaxResources){
            cout<< "THE REMAINDER IS LESS THAN PROCESS "<<temp->ID<<" CLAIMS"<<endl;
            break;
        }
		if(temp->dynamicResources[temp->dynamicResourceIndex] == 0){
			cout<< "PROCESS "<<temp->ID << "  HAS FINISHED, RETURN ITS RESOURSE"<<endl;
			temp->isOver = true;
			systemCurrentResources -= temp->currentResource;
			
		}
		temp = findNextWaitingStruct(temp);
	}
    if (temp == NULL){
        cout << "THE WHOLE WORK IS COMPLETED" << endl;
    }
}
bool DynamicResource::isAllFound(){
	PCB* temp = head;
	while(temp!=NULL){
		if(temp ->isFound == false && temp->isOver == false){
			return false;
		}
		temp = temp->nextStruct;
	}
	return true;

}
void DynamicResource::setFound(){
	PCB* temp = head;
	while(temp!=NULL){
		temp->isFound = false;
		temp = temp->nextStruct;
	}
}
PCB* DynamicResource::findNextWaitingStruct(PCB* p){
	PCB* temp = p->nextStruct;
	while(temp!=NULL){
		if(temp->isOver == false){
			
			return temp;
		}
		temp = temp->nextStruct;
	}
	temp = head;
	while(temp!=p->nextStruct){
		if(temp->isOver == false){
			
			return temp;
		}
		temp = temp->nextStruct;

	}
	return NULL;
};
bool DynamicResource::handleDeadLock(PCB* p){
	
	if(p->isOver){
		return false;
	}
    systemCurrentResources += p->dynamicResources[p->dynamicResourceIndex];//模拟分配
    p->currentResource += p->dynamicResources[p->dynamicResourceIndex];//模拟分配
    
    if(safe(p)){//判断分配是否安全
        p->currentResource -= p->dynamicResources[p->dynamicResourceIndex];//因为是模拟分配，所以要将分配的资源回收
        systemCurrentResources -= p->dynamicResources[p->dynamicResourceIndex];
        
        return true;
        
    }else{
        p->currentResource -= p->dynamicResources[p->dynamicResourceIndex];//因为是模拟分配，所以要将分配的资源回收
        systemCurrentResources -= p->dynamicResources[p->dynamicResourceIndex];
    }
	
	return false;
	

};
bool DynamicResource::safe(PCB* p){
    int remainResource = systemMaxResources - systemCurrentResources;//系统剩余资源
	PCB* temp = head;
    int findTime = 0;
	while(temp!=NULL){//对T（判断是否可完成）赋初值
		if(!temp->isOver){
			temp->T = 1;
		}
		temp = temp->nextStruct;
	}
	temp = head;
	while(temp != NULL){
        findTime += 1;
		if(temp->T == 1 && temp->isOver == false){//没有完成的进程
			if(temp->currentResource + remainResource >= temp->maxResource){//如果能够完成
				temp->T = 0;
                remainResource += temp->currentResource;//释放该进程资源，系统剩余资源增加
                findTime = 0;
                temp = head;
			} else{
				temp = temp->nextStruct;
			}
		} else{
			temp = temp->nextStruct;
		}
        if (findTime >processesNumber){//如果遍历一遍，没有可完成的进程，退出
            break;
        }
	}
    temp = head;
    while (temp!=NULL){//判断是否所有进程可完成
        if (temp->T == 1)
            return false;
        temp = temp->nextStruct;
    }
	return true;
};


