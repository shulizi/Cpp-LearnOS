#include <stdlib.h>
#include "FileStruct.h"

FileStruct::FileStruct(string fileName,int fileLength,int fileAddress,int readCode,int writeCode,int executeCode){
    this->fileName = fileName;
    this->fileLength = fileLength;
    this->fileAddress = fileAddress;
    this->readCode = readCode;
    this->writeCode = writeCode;
    this->executeCode = executeCode;
}

