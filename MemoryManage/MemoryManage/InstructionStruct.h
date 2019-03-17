#ifndef InstructionStruct_h
#define InstructionStruct_h
struct InstructionStruct{
    int id;
    InstructionStruct* preStruct;
    InstructionStruct* nextStruct;
    int frequency;
    InstructionStruct(int);
};
#endif
