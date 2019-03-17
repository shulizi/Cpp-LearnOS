#ifndef MyProcessControl_h
#define MyProcessControl_h
#include "StateStruct.h"
#include <iostream>
#include <stack>
#include <unordered_map>
using namespace std;
class MyProcessControlClass{
private:
	int* serchedStateHash;//已经探索过的状态组成的数组
    int* heuristiHash;//运载方案排序后组成的数组
	StateStruct* headStateStruct;//第一个状态
    int* boatLoadArray;//船上乘客每个物种的数量组成的数组
    int boatMaxLoad;//船的最大载客量
    int stateHashLengh;//状态hash数组的长度
    int lengthOfWatermanArray;//能够划船的人的数组长度
    string* watermanArray;//能够划船的人的数组
    stack<StateStruct* > successStateStructsStack;//成功方案的各个状态组成的数组
	void saveSearchedState(StateStruct*);//保存已经探究过的状态
    bool isSerched(StateStruct*,int a[]);//预估在a[]方案下运载过河后的状态是否是先前探究过的状态
	bool isLegal(StateStruct*,int a[]);//判断a[]方案是否合法（不能超载，不能打破约束）
    bool isOver(StateStruct*);//判断当前状态是否是结束状态
    int* getNextA(StateStruct* , int a[]);//获得下一个运载方案
    int* getNextOrderA(StateStruct* ,int a[]);//获得下一个排序后的运载方案（启发）
    void heuristic();//启发函数排序
    void initClass(int objectsNumber ,string objects[],int numbers[],bool isGoodArray[],int boatMaxLoad);
public:
    MyProcessControlClass();
	MyProcessControlClass(int objectsNumber ,string objects[],int numbers[],bool isGoodArray[],int boatMaxLoad);
    void setPredation(int sizeOfArray,string relationshipArray[][2]);
    void setInhibition(int sizeOfArray,string relationshipArray[][2]);
    void setCompetitive(int sizeOfArray,string relationshipArray[][2]);
    void setBreeding(int sizeOfArray,string relationshipArray[][2]);
    void setWaterman(int sizeOfArray,string watermanArray[]);
	bool searchPath(StateStruct*,int a[]);//循环搜索路径
	void showPath();//展示搜索过后的路径
	void startSearch();//开始搜索路径
	
};
#endif /* MyProcessControl_h */
