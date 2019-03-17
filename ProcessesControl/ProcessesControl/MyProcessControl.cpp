#include "MyProcessControl.h"
using namespace std;

void MyProcessControlClass::createProcesses(){
	lengthOfPBP = 0;
	PCB* p1 = new PCB(1,6,4);
	PCB* p2 = new PCB(2,6,2);
	PCB* p3 = new PCB(3,4,4);
	PCB* p4 = new PCB(4,4,5);
	PCB* p5 = new PCB(5,8,10);
	PCB* p6 = new PCB(6,4,2);
    
	insertProcessByPriority(p1);
	insertProcessByPriority(p2);
	insertProcessByPriority(p3);
	insertProcessByPriority(p4);
	insertProcessByPriority(p5);
	insertProcessByPriority(p6);
    
    finishedhead = NULL;
    finishedtail = NULL;

};
void MyProcessControlClass::insertProcessByPriority(PCB* p){

    if(p->nextStruct == NULL){
        p->nextStruct = p;
    }
	
	if (lengthOfPBP == 0){
		processesByPriority[0] = p;
		lengthOfPBP++;
		return;
	}
	int i = 0;
	for (;i < lengthOfPBP;i++){

		if(p->priority > processesByPriority[i]->priority){
            
			for (int j = lengthOfPBP;j > i;j--){
				processesByPriority[j] = processesByPriority[j-1];
			}
			processesByPriority[i] = p;
			lengthOfPBP++;
			break;
		}else if (p->priority == processesByPriority[i]->priority){
            
			p->nextStruct = processesByPriority[i]->nextStruct;
			processesByPriority[i]->nextStruct = p;
			break;
		}

	}

	if (i == lengthOfPBP){
		processesByPriority[lengthOfPBP] = p;
		lengthOfPBP++;
	}
}
void MyProcessControlClass::deleteP(PCB* h,PCB* p){
    
    PCB* temp = h;
    while(temp->nextStruct!=h){
        
        if(temp->nextStruct->id == p->id){
            temp->nextStruct = p->nextStruct;
            return;
        }
        temp = temp->nextStruct;
    }
    if(temp->nextStruct->id == p->id){
        temp->nextStruct = p->nextStruct;
        h = p->nextStruct;
        return;
    }
}
void MyProcessControlClass::startProcesses(){
	
	while (lengthOfPBP != 0) {
        run = processesByPriority[0];
		while (true){
            
            run->state = 'R';
            showProcesses();
			run->timeOnCPU ++;
			run->priority -= 3;
            
			if (run->timeToFinish == run->timeOnCPU){//当前节点是否已经执行完毕
                run->state = 'O';
                if (finishedhead == NULL){//将执行完毕的节点加入结束链表
                    finishedhead = run;
                    finishedtail = run;
                } else {//将执行完毕的节点加入结束链表
                    finishedtail->nextStruct = run;
                    finishedtail = run;
                }
				if(processesByPriority[0] -> nextStruct != processesByPriority[0]){//判断当前优先度组是否还有其它节点
                    deleteP(processesByPriority[0], run);
                    run = run->nextStruct;
                    
				} else {//若当前优先度组没有其它节点，将该组删除
					for (int i = 0;i < lengthOfPBP - 1;i++){
						processesByPriority[i] = processesByPriority [i+1];
					}
					lengthOfPBP--;
                    break;
				}

                
			}
            run->state = 'W';
            processesByPriority[0] = processesByPriority[0]->nextStruct;//遍历执行当前优先度组的所有节点
            run = processesByPriority[0];
            if(lengthOfPBP > 1 && run->priority < processesByPriority[1]->priority){//若改组的所有节点优先度都小于下一个组的优先度，则进行优先度的重排序

				for (int i = 0;i < lengthOfPBP - 1;i++){
					processesByPriority[i] = processesByPriority [i+1];
				}
				lengthOfPBP--;
				insertProcessByPriority(run);

				break;
			}

		}
	}
};

void MyProcessControlClass::showProcesses(){
	cout << "==============================" << endl;
	cout << "ID\tPR\tCP\tAL\tST\tNE" << endl;
	for (int i = 0;i < lengthOfPBP;i++){
		PCB* temp = processesByPriority[i];
		PCB* head = processesByPriority[i];
        
		do {
			cout << temp->id << "\t";
			cout << temp->priority << "\t";
            cout << temp->timeOnCPU<< "\t";
            cout << temp->timeToFinish << "\t";
            cout << temp->state<< "\t";
            if (temp->nextStruct!=NULL){
                cout << temp->nextStruct->id << "\t" << endl;
            } else {
                cout << "0\t" << endl;
            }
            
			temp = temp->nextStruct;

		}while (temp != head);
		cout << "----------------------------" << endl;
	}
    PCB* temp = finishedhead;
    
    while (temp!=finishedtail){
        cout << temp->id << "\t";
        cout << temp->priority << "\t";
        cout << temp->timeOnCPU<< "\t";
        cout << temp->timeToFinish << "\t";
        cout << temp->state<< "\t"<<endl;
        temp = temp->nextStruct;
    }
    if (temp!=NULL){
        cout << temp->id << "\t";
        cout << temp->priority << "\t";
        cout << temp->timeOnCPU<< "\t";
        cout << temp->timeToFinish << "\t";
        cout << temp->state<< "\t"<<endl;
    }
    
}


