#ifndef DynamicResource_h
#define DynamicResource_h
#include "PCB.h"

class DynamicResource{
private:
	PCB* head;
    int processesNumber;
	int systemMaxResources;
	int systemCurrentResources;
	bool handleDeadLock(PCB*);
	bool safe(PCB*);
	bool isAllFound();
	void setFound();
	PCB* findNextWaitingStruct(PCB*);
public:
	void createProcesses();
	void startProcesses();
	void startProcessesWithNohandleDeadLock();

};
#endif /* DynamicResource_h */
