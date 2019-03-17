//
//  FileManager.hpp
//  FileManage
//
//  Created by 杜李 on 2018/12/21.
//  Copyright © 2018年 杜李. All rights reserved.
//

#ifndef FileManager_h
#define FileManager_h

#include "UserStruct.h"
#include "RunningFileStruct.h"
#include <iostream>
#include <string>
using namespace std;
class FileManager {
private:
    RunningFileStruct* runningFileStructs[5];
    UserStruct* userStructs[10];
    UserStruct* currentUserStruct;
    string rootPassword;
    int getFreeFileId();
    bool isFileOpened(int fileId);
    bool isFileOpened(string fileName);
public:
    FileManager();
    void addUser(string userName);
    bool loadUser(string userName);
    bool createFile(string fileName,int fileLength,int protectCode);
    void openFile(string fileName,int openCode);
    void readFile(int fileId);
    void writeFile(int fileId,int wordsLength);
    void deleteFile(string fileName);
    void closeFile(int fileId);
    void changeFileCode(string fileName,int protectCode,string rootPassword);
    void changeRootPassword(string originRootPassword,string newRootPassword);
    void showFiles();
    
};



#endif /* FileManager_h */
