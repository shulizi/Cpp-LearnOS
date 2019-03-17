#ifndef MemoryManage_h
#define MemoryManage_h
#include <queue>
using namespace std;
class MemoryManage{
private:
    InstructionStruct* head;
    InstructionStruct* tail;
    int HitRate = 0;//命中率
    int indexOfIns = 0;//指令表index
    int lengthOfIns = 20;//指令表长度
    int lengthOfPT = 5;//页表最大长度
    int currentLengthOfPT = 0;//当前页表长度
    InstructionStruct* instructions[20];//（后继）指令表
    void deleteInstructionFromPT(InstructionStruct*);//从页表中删除某指令
    void putInstructionFromPTToTail(InstructionStruct*);//将指令从页表中某一位置挪动到页表尾部
    void sortByFrequency();//将页表中指令按访问次数排序
public:
    void createInstructions();//创建后继指令表
    void insertInstructionOPT(InstructionStruct*);//OPT将一个后继指令表中指令与页表中指令进行比较，没有命中则插入
    void insertInstructionLRU(InstructionStruct*);//LRU将一个后继指令表中指令与页表中指令进行比较，没有命中则插入
    void insertInstructionLFU(InstructionStruct*);//LFU将一个后继指令表中指令与页表中指令进行比较，没有命中则插入
    void showPageTable();//展示LRU和OPT下的页表
    void showPageTableLFU();//展示LFU下的页表
    void startOPT();//开始OPT
    void startLRU();//开始LRU
    void startLFU();//开始LFU
};
#endif 
