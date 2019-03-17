#ifndef PCB_h
#define PCB_h
struct PCB{
    int id;
    int priority;
    int timeOnCPU;
    int timeToFinish;
    char state;
    PCB* nextStruct;
    PCB(int,int,int);
};
#endif /* ProcessStruct_h */
