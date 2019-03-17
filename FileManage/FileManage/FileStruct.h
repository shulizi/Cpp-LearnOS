#ifndef FileStruct_h
#define FileStruct_h
#include <string>
using namespace std;
struct FileStruct{
    string fileName;
    int fileLength;
    int fileAddress;
    int readCode;
    int writeCode;
    int executeCode;

    FileStruct(string fileName,int fileLength,int fileAddress,int readCode,int writeCode,int executeCode);
};
#endif 
