//
//  FileManager.cpp
//  FileManage
//
//  Created by 杜李 on 2018/12/21.
//  Copyright © 2018年 杜李. All rights reserved.
//

#include "FileManager.h"

FileManager::FileManager(){
    for (int i=0;i<10;i++){
        userStructs[i] = NULL;
    }
    for (int i=0;i<5;i++){
        runningFileStructs[i] = NULL;
    }
    rootPassword = "000000";
    
    this->addUser("bob");
    currentUserStruct->addFile("file1", 10, 101);
    currentUserStruct->addFile("file2", 3003, 111);
    currentUserStruct->addFile("file3", 272, 001);
}
void FileManager::addUser(string userName){
    for (int i=0;i<10;i++){
        if(userStructs[i] == NULL){
            userStructs[i] = new UserStruct(userName);
            currentUserStruct = userStructs[i];
            return;
        }
    }
    
}
bool FileManager::loadUser(string userName){
    for (int i=0;i<10;i++){
        if(userStructs[i]!=NULL && userStructs[i]->userName  == userName){
            currentUserStruct = userStructs[i];
            return true;
        }
    }
    
    return false;
}
bool FileManager::createFile(string fileName,int fileLength,int protectCode){
    if (currentUserStruct->addFile(fileName, fileLength, protectCode)){
        cout<<"THE NEW FILE IS CREATED."<<endl;
        return true;
    } else {
        cout<<"ERROR MESSAGE:IT IS NOT ALLOWED TO CREATE MORE THAN 10 FILES !!!"<<endl;
        return false;
    }
}
void FileManager::showFiles(){
    cout<<"FILE NAME\tPROTECTION\tCODE LENGTH"<<endl;
    
    for (int i=0;i<currentUserStruct->fileNumber;i++){
        cout<<currentUserStruct->fileStructs[i]->fileName<<"\t\t";
        cout<<currentUserStruct->fileStructs[i]->readCode<<currentUserStruct->fileStructs[i]->writeCode<<currentUserStruct->fileStructs[i]->executeCode<<"\t\t\t";
        cout<<currentUserStruct->fileStructs[i]->fileLength<<endl;
    }
}
int FileManager::getFreeFileId(){
    for (int i=0;i<5;i++){
        if(runningFileStructs[i]==NULL){
            return i;
        }
    }
    return -1;
}
void FileManager::openFile(string fileName,int openCode){
    int fileId = getFreeFileId();
    if(fileId == -1){
        cout<<"ERROR MESSAGE:IT IS NOT ALLOWED TO OPEN MORE THAN 5 FILES !!! "<<endl;
        return;
    }
    for(int i=0;i<currentUserStruct->fileNumber;i++){
        if(currentUserStruct->fileStructs[i]->fileName == fileName){
            if(openCode/100 - currentUserStruct->fileStructs[i]->readCode == 1){
                cout<<"ERROR MESSAGE:IT IS NOT ALLOWED TO OPEN THIS FILE BY READ CODE!!!"<<endl;
                return;
            }
            if((openCode/10 - openCode/100*10)  - currentUserStruct->fileStructs[i]->writeCode == 1){
                cout<<"ERROR MESSAGE:IT IS NOT ALLOWED TO OPEN THIS FILE BY WRITE CODE !!!"<<endl;
                return;
            }
            if(openCode%10 - currentUserStruct->fileStructs[i]->executeCode == 1){
                cout<<"ERROR MESSAGE:IT IS NOT ALLOWED TO OPEN THIS FILE BY EXCECUTE CODE !!!"<<endl;
                return;
            }
            
            runningFileStructs[fileId] = new RunningFileStruct(fileId,openCode,currentUserStruct->fileStructs[i]);
            cout<<"THIS FILE IS OPENED,ITS OPEN NUMBER IS "<<fileId<<endl;
            return ;
        }
    }
    cout<<"ERROR MESSAGE:NO SUCH FILE !!!"<<endl;
}
void FileManager::deleteFile(string fileName){
    
    if(isFileOpened(fileName)){
        cout<<"ERROR MESSAGE:FILE IS NOT ALLOWED TO BE DELETED BECAUSE IT IS OPENED !!! "<<endl;
        return;
    }
    if(currentUserStruct->deleteFile(fileName)){
        cout<<"THE NEW FILE IS DELETED."<<endl;
        return ;
        
    }
    cout<<"ERROR MESSAGE:NO SUCH FILE !!!"<<endl;
    
    
}
bool FileManager::isFileOpened(string fileName){
    for (int i=0;i<5;i++){
        if(runningFileStructs[i]!=NULL && runningFileStructs[i]->fileStruct->fileName==fileName){
            return true;
        }
    }
    return false;
}
bool FileManager::isFileOpened(int fileId){
    for (int i=0;i<5;i++){
        if(runningFileStructs[i]!=NULL && runningFileStructs[i]->fileOpenedId==fileId){
            return true;
        }
    }
    return false;
}
void FileManager::closeFile(int fileId){
    
    if(!isFileOpened(fileId)){
        cout<<"ERROR MESSAGE:FILE IS NOT OPENED !!! "<<endl;
        return;
    }
    delete runningFileStructs[fileId];
    runningFileStructs[fileId] = NULL;
    cout<<"THE NEW FILE IS CLOSED."<<endl;
}
void FileManager::readFile(int fileId){
    if(!isFileOpened(fileId)){
        cout<<"ERROR MESSAGE:FILE IS NOT OPENED !!! "<<endl;
        return ;
    }
    if(runningFileStructs[fileId]->fileOpenedCode/100 == 0){
        cout<<"ERROR MESSAGE:IT IS NOT ALLOWED TO READ THIS FILE !!!"<<endl;
        return;
    }
    cout<<"FILE OPENED ID:";
    cout<<runningFileStructs[fileId]->fileOpenedId<<endl;
    cout<<"FILE OPENED CODE:";
    cout<<runningFileStructs[fileId]->fileOpenedCode<<endl;
    cout<<"FILE NAME:";
    cout<<runningFileStructs[fileId]->fileStruct->fileName<<endl;
    cout<<"FILE LENGTH:";
    cout<<runningFileStructs[fileId]->fileStruct->fileLength<<endl;
    cout<<"FILE ADDRESS:";
    cout<<runningFileStructs[fileId]->fileStruct->fileAddress<<endl;
}
void FileManager::writeFile(int fileId, int wordsLength){
    if(!isFileOpened(fileId)){
        cout<<"ERROR MESSAGE:FILE IS NOT OPENED !!! "<<endl;
        return ;
    }
    if(runningFileStructs[fileId]->fileOpenedCode/10 - runningFileStructs[fileId]->fileOpenedCode/100*10 == 0){
        cout<<"ERROR MESSAGE:IT IS NOT ALLOWED TO WRITE THIS FILE !!!"<<endl;
        return;
    }
    runningFileStructs[fileId]->fileStruct->fileLength += wordsLength;
}

void FileManager::changeFileCode(string fileName,int protectCode,string rootPassword){
    if(this->rootPassword!=rootPassword){
        cout<<"ERROR MESSAGE:WRONG PASSWORD !!! "<<endl;
        return ;
    }
    if(isFileOpened(fileName)){
        cout<<"ERROR MESSAGE:FILE IS OPENED !!! "<<endl;
        return ;
    }
    
    if(!currentUserStruct->changeFileCode(fileName, protectCode)){
        cout<<"ERROR MESSAGE:NO SUCH FILE !!! "<<endl;
        return ;
    }
    cout<<"FILE PROTECT CODE HAS BEEN CHANGED."<<endl;
}
void FileManager::changeRootPassword(string originRootPassword,string newRootPassword){
    if(this->rootPassword!=originRootPassword){
        cout<<"ERROR MESSAGE:WRONG PASSWORD !!! "<<endl;
        return ;
    }
    this->rootPassword = newRootPassword;
}
