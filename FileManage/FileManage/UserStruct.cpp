//
//  Catalog.cpp
//  FileManage
//
//  Created by 杜李 on 2018/12/21.
//  Copyright © 2018年 杜李. All rights reserved.
//

#include "UserStruct.h"

UserStruct::UserStruct(string userName){
    this->userName = userName;
    this->fileNumber = 0;
}
bool UserStruct::addFile(string fileName, int fileLength, int protectCode){
    int readCode = protectCode/100;
    int writeCode = protectCode/10 - protectCode/100*10;
    int executeCode = protectCode%10;
    if(this->fileNumber>=10){
        return false;
    }
    this->fileStructs[this->fileNumber] = new FileStruct(fileName,fileLength,this->fileNumber,readCode,writeCode,executeCode);
    fileNumber ++;
    return true;
}
bool UserStruct::deleteFile(string fileName){
    for(int i=0;i<fileNumber;i++){
        
        if(this->fileStructs[i]->fileName == fileName){
            delete this->fileStructs[i];
            this->fileStructs[i] = this->fileStructs[fileNumber-1];
            fileNumber --;
            return true;
        }

    }
    
    return false;
}
bool UserStruct::changeFileCode(string fileName, int protectCode){
    for(int i=0;i<fileNumber;i++){
        if(this->fileStructs[i]->fileName == fileName){
            this->fileStructs[i]->readCode = protectCode/100;
            this->fileStructs[i]->writeCode =protectCode/10 - protectCode/100*10;
            this->fileStructs[i]->executeCode = protectCode%10;
            return true;
        }
    }
    
    return false;
}
