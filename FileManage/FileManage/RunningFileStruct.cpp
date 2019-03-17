//
//  RunningFileStruct.cpp
//  FileManage
//
//  Created by 杜李 on 2018/12/21.
//  Copyright © 2018年 杜李. All rights reserved.
//

#include "RunningFileStruct.h"
RunningFileStruct::RunningFileStruct(int fileOpenedId,int fileOpenedCode,FileStruct* fileStruct){
    this->fileOpenedId = fileOpenedId;
    this->fileOpenedCode = fileOpenedCode;
    this->fileStruct = fileStruct;
}
