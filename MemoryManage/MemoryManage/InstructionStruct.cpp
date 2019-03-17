#include <stdlib.h>
#include "InstructionStruct.h"

InstructionStruct::InstructionStruct(int id){
    this->id = id;
    this->nextStruct = NULL;
    this->preStruct = NULL;
    this->frequency = 0;
}
