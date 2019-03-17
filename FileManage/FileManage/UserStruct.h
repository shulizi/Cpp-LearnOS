//
//  Catalog.hpp
//  FileManage
//
//  Created by 杜李 on 2018/12/21.
//  Copyright © 2018年 杜李. All rights reserved.
//

#ifndef UserStruct_h
#define UserStruct_h
#include <string>
#include <iostream>
using namespace std;
#include "FileStruct.h"
struct UserStruct{
    int fileNumber;
    string userName;
    FileStruct* fileStructs[10];
    
    UserStruct(string userName);
    bool addFile(string fileName,int fileLength,int protectCode);
    bool changeFileCode(string fileName,int protectCode);
    bool deleteFile(string fileName);
};
#endif
