#include <iostream>
#include <queue>
#include "DynamicResource.h"
#include "OrderedResource.h"
using namespace std;

int main(){
	
    DynamicResource  dynamicResourceAllocation;
    cout << "OPTION =0"<<endl;
    dynamicResourceAllocation.createProcesses();
    dynamicResourceAllocation.startProcesses();
    cout << "OPTION =1"<<endl;
    dynamicResourceAllocation.createProcesses();
    dynamicResourceAllocation.startProcessesWithNohandleDeadLock();
    
    OrderedResource orderedResourceAllocation;
    orderedResourceAllocation.createProcesses();
    orderedResourceAllocation.startProcesses();
	return 0;
}
