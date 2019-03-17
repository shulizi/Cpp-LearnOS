//
//  RunningFileStruct.hpp
//  FileManage
//
//  Created by 杜李 on 2018/12/21.
//  Copyright © 2018年 杜李. All rights reserved.
//

#ifndef RunningFileStruct_h
#define RunningFileStruct_h
#include "FileStruct.h"
#include <string>
using namespace std;
struct RunningFileStruct{
    int fileOpenedId;
    int fileOpenedCode;
    FileStruct* fileStruct;
    
    RunningFileStruct(int fileOpenedId,int fileOpenedCode,FileStruct* fileStruct);
};
#endif /* RunningFileStruct_h */
