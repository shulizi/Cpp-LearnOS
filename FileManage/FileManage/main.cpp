//
//  main.c
//  FileManage
//
//  Created by 杜李 on 2018/12/21.
//  Copyright © 2018年 杜李. All rights reserved.
//
#include "FileManager.h"
#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    FileManager fileManager;
    string name;
    while(true){
        cout << "YOUR NAME: ";
        cin>>name;
        if (fileManager.loadUser(name)){
            break;
        }
        cout<<"ERROR MESSAGE:YOUR NAME IS NOT IN THE USER NAME TABLE,TRY AGAIN."<<endl;
    }
    cout<<"YOUR FILE DIRECTORY"<<endl;
    fileManager.showFiles();
    string commend;
    string fileName;
    int protectionCode;
    int wordsLength;
    int fileId;
    string rootPassword;
    string newRootPassword;
    while(1){
        cout<<"COMMAND NAME? ";
        cin>>commend;
        if(commend == "create"){
            
            cout<<"THE NEW FILE S NAME(LESS THAN 9 CHARS)?";
            cin>>fileName;
            
            cout<<"THE NEW FILE’S PROTECTION CODE?";
            cin>>protectionCode;
            if(fileManager.createFile(fileName, 0, protectionCode)){
                cout<<"ENTER THE OPEN MODE?";
                cin>>protectionCode;
                fileManager.openFile(fileName, protectionCode);
            }
            
        } else if(commend == "open"){
            cout<<"FILE NAME TO BE OPENED?";
            cin>>fileName;
            cout<<"ENTER THE OPEN MODE?";
            cin>>protectionCode;
            fileManager.openFile(fileName, protectionCode);
        } else if(commend == "read"){
            cout<<"OPEN FILE NUMBER?";
            cin>>fileId;
            fileManager.readFile(fileId);
        } else if(commend == "write"){
            cout<<"OPEN FILE NUMBER?";
            cin>>fileId;
            cout<<"HOW MANY CHARACTERS TO BE WRITTEN INTO THAT FILE?";
            cin>>wordsLength;
            fileManager.writeFile(fileId, wordsLength);
        } else if(commend == "delete"){
            cout<<"FILE NAME TO BE DELETED?";
            cin>>fileName;
            fileManager.deleteFile(fileName);
        } else if(commend == "close"){
            cout<<"THE OPENED FILE NUMBER TO BE CLOSED?";
            cin>>fileId;
            fileManager.closeFile(fileId);
        }else if(commend == "ccode"){
            cout<<"THE FILE'S NAME?";
            cin>>fileName;
            cout<<"THE NEW FILE'S PROTECT CODE?";
            cin>>protectionCode;
            cout<<"ROOT PASSWORD?";
            cin>>rootPassword;
            fileManager.changeFileCode(fileName, protectionCode, rootPassword);
        } else if(commend == "cpassword"){
            cout<<"ORIGIN ROOT PASSWORD?";
            cin>>rootPassword;
            cout<<"NEW ROOT PASSWORD?";
            cin>>newRootPassword;
            fileManager.changeRootPassword(rootPassword, newRootPassword);
        }  else if(commend == "bye"){
            cout<<"NOW YOUR FILE DIRECTORY IS FOLLOWING:";
            fileManager.showFiles();
            cout<<"GOOD BYE.";
            break;
        }  else {
            cout<<"COMMAND NAME GIVEN IS WRONG!IT SHOULD BE ONE OF FOLLOWING : create,delete,open,close,read,write,ccode,cpassword,bye.TRY AGAIN"<<endl;
        }
    }
    
    return 0;
}
