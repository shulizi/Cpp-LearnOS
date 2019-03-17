#ifndef PCB_h
#define PCB_h
struct PCB{
int ID;
int dynamicResourceIndex;
int dynamicResources[10];
int orderedResources[10];
int maxResource;
int currentResource;
int T;
bool isFound;
bool isOver;
PCB* nextStruct;
PCB* preStruct;
PCB(int,int[10],int);
PCB(int,int[10]);
};
#endif /* PCB_h */
