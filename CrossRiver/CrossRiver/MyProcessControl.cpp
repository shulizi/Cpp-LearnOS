#include "MyProcessControl.h"
#define len(x) (sizeof(x)/sizeof((x)[0]))
MyProcessControlClass::MyProcessControlClass(){
    
    //经典过河问题1
    string objects[] = {"爸爸","妈妈","儿子","女儿","仆人","狗"};//物种的名字
    int numbers[]={1,1,2,2,1,1};//每一个物种的数量，数组长度与objects保持一致（唯二需要手动保持一致的地方）
    bool isGoodArray[]={true,true,true,true,true,true};//每一个物种的好坏，关系到要不要将其运送到河的对岸。数组长度与objects保持一致（唯二需要手动保持一致的地方）
    string inhibitionArray[][2] = {};//物种间的天敌关系（数量上相互抑制的前提下，一方捕食另一方）
    string preyArray[][2] = {{"爸爸","儿子"},{"妈妈","女儿"},{"狗","爸爸"},{"狗","妈妈"},{"狗","儿子"},{"狗","女儿"}};//物种间的捕食关系
    string breedingArray[][2] = {{"妈妈","儿子"},{"爸爸","女儿"},{"仆人","狗"}};//物种间的饲养关系
    string competitiveArray[][2] ={};//物种间的竞争关系
    int boatMaxLoad = 2;//船的最大运载量
    string watermanArray[] = {"爸爸","妈妈","仆人"};
    
    /*
    //经典过河问题2
    string objects[] = {"人","怪"};//物种的名字
    int numbers[]={4,4};//每一个物种的数量，数组长度与objects保持一致（唯二需要手动保持一致的地方）
    bool isGoodArray[]={true,true};//每一个物种的好坏，关系到要不要将其运送到河的对岸。数组长度与objects保持一致（唯二需要手动保持一致的地方）
    string inhibitionArray[][2] = {{"怪","人"}};//物种间的敌人关系（数量上相互抑制的前提下，一方消灭另一方）
    string preyArray[][2] = {};//物种间的捕食关系
    string breedingArray[][2] = {};
    string competitiveArray[][2] ={};
    int boatMaxLoad = 3;//船的最大运载量
    string watermanArray[] = {"人","怪"};
    */
    /*
     //经典过河问题3
     string objects[] = {"人","狼","羊","草"};//物种的名字
     int numbers[]={1,1,1,1};//每一个物种的数量，数组长度与objects保持一致（唯二需要手动保持一致的地方）
     bool isGoodArray[]={true,true,true,true};//每一个物种的好坏，关系到要不要将其运送到河的对岸。数组长度与objects保持一致（唯二需要手动保持一致的地方）
     string inhibitionArray[][2] = {};//物种间的敌人关系（数量上相互抑制的前提下，一方消灭另一方）
     string preyArray[][2] = {{"狼","羊"},{"羊","草"}};//物种间的捕食关系
     string breedingArray[][2] = {{"人","狼"},{"人","羊"},{"人","草"}};
     string competitiveArray[][2] ={};
     int boatMaxLoad = 2;//船的最大运载量
     string watermanArray[] = {"人"};
     */
     /*
    string objects[] = {"人","蛇","狗","猫","老鼠"};//物种的名字
    int numbers[]={3,3,3,3,3};//每一个物种的数量，数组长度与objects保持一致（唯二需要手动保持一致的地方）
    bool isGoodArray[]={true,false,true,true,true};//每一个物种的好坏，关系到要不要将其运送到河的对岸。数组长度与objects保持一致（唯二需要手动保持一致的地方）
    string inhibitionArray[][2] = {{"蛇","人"},{"蛇","猫"}};//物种间的敌人关系（数量上相互抑制的前提下，一方消灭另一方）
    string preyArray[][2] = {{"蛇","老鼠"},{"猫","老鼠"}};//物种间的捕食关系
    string competitiveArray[][2] = {{"猫","狗"}};//物种间的竞争关系
    string breedingArray[][2] = {{"人","狗"},{"人","老鼠"}};
    string watermanArray[] = {"人"};
    int boatMaxLoad = 3;//船的最大运载量
    */
    
    initClass(len(objects), objects,numbers,isGoodArray,boatMaxLoad);
    
    setPredation(len(preyArray), preyArray);
    setCompetitive(len(competitiveArray), competitiveArray);
    setBreeding(len(breedingArray), breedingArray);
    setInhibition(len(inhibitionArray), inhibitionArray);
    setWaterman( len(watermanArray), watermanArray);
    
}
MyProcessControlClass::MyProcessControlClass(int objectsNumber ,string objects[],int numbers[],bool isGoodArray[],int boatMaxLoad){
    initClass(objectsNumber, objects, numbers, isGoodArray, boatMaxLoad);
}
void MyProcessControlClass::initClass(int objectsNumber ,string objects[],int numbers[],bool isGoodArray[],int boatMaxLoad){
    this->boatMaxLoad = boatMaxLoad;
    stateHashLengh = 1024*1024;//存放状态数组的长度（可满足最多9个物种各3只（27只），或者19个物种各1只（19只）的过河问题）
    
    serchedStateHash = new int[stateHashLengh];//保存所有已经探索过的状态
    heuristiHash = new int[stateHashLengh];//保存排序后的状态的hash
    boatLoadArray = new int[objectsNumber];//每个物种任意一次上船的数量
    headStateStruct = new StateStruct(1);//初始化船在岸的右边（括号内为0表示船在右边，在左边则为1）（技术手段船第一次摆渡无实际意义，只为开启循环）
    for(int i=0;i<stateHashLengh;i++){
        serchedStateHash[i] = -1;//无特殊说明，均用-1表示未更改状态
        heuristiHash[i] = -1;
    }
    for (int i=0;i<objectsNumber;i++){
        boatLoadArray[i] = 0;//设置f初始化船上各物种数量均为0
        headStateStruct->addObject(objects[i],numbers[i],numbers[i],isGoodArray[i]);
        
    }
    
    heuristic();
}

void MyProcessControlClass::setPredation(int sizeOfArray,string relationshipArray[][2]){
    for(int i=0;i< sizeOfArray;i++){
        headStateStruct->setPredation(relationshipArray[i][0], relationshipArray[i][1]);
    }//设置捕食关系
    
}

void MyProcessControlClass::setInhibition(int sizeOfArray,string relationshipArray[][2]){
    for(int i=0;i< sizeOfArray;i++){
        headStateStruct->setInhibition(relationshipArray[i][0], relationshipArray[i][1]);
    }
}
void MyProcessControlClass::setCompetitive(int sizeOfArray,string relationshipArray[][2]){
    for(int i=0;i< sizeOfArray;i++){
        headStateStruct->setCompetitive(relationshipArray[i][0], relationshipArray[i][1]);
    }
}
void MyProcessControlClass::setBreeding(int sizeOfArray,string relationshipArray[][2]){
    for(int i=0;i< sizeOfArray;i++){
        headStateStruct->setBreeding(relationshipArray[i][0], relationshipArray[i][1]);
    }
}
void MyProcessControlClass::setWaterman(int sizeOfArray,string watermanArray[]){
    this->watermanArray = new string[sizeOfArray];
    this->lengthOfWatermanArray = sizeOfArray;
    for(int i=0;i<sizeOfArray;i++){
        
        this->watermanArray[i] = watermanArray[i];
    }
}
void MyProcessControlClass::heuristic(){
    int *b = getNextA(headStateStruct, boatLoadArray);
    int hash = 0;
    int lengthOfHashes = 0;
    int *weights = new int[stateHashLengh];
    int *hashes = new int[stateHashLengh];
    while(b!=NULL){
        
        hash = 0;
        int weight = 0;
        for(int i=0;i<headStateStruct->objectClassesNumber;i++){
            hash = hash*(headStateStruct->objectStructs[i]->totalNumber+1)+b[i];
            weight = weight + b[i]*headStateStruct->objectStructs[i]->isGood;
        }
        weights[lengthOfHashes] = weight;
        hashes[lengthOfHashes] = hash;
        lengthOfHashes++;
        b = getNextA(headStateStruct, b);
    }
    for(int i=0;i<lengthOfHashes;i++){
        for(int j=0;j<lengthOfHashes-i-1;j++){
            if(weights[j]<weights[j+1]){
                int temp = hashes[j];
                hashes[j] = hashes[j+1];
                hashes[j+1] = temp;
                temp = weights[j];
                weights[j] = weights[j+1];
                weights[j+1] = temp;
            }
        }
    }
    cout<<hashes[0]<<"-";
    cout<<weights[0]<<" ";
    for(int i=0;i<lengthOfHashes - 1;i++){
        cout<<hashes[i]<<"-";
        cout<<weights[i]<<" ";
        heuristiHash[hashes[i]] = hashes[i+1];
        if(hashes[i+1]==0){
            break;
        }
    }
    heuristiHash[0] = hashes[0];
}
void MyProcessControlClass::startSearch(){

    int *b = new int[headStateStruct->objectClassesNumber];
    for (int i=0;i<headStateStruct->objectClassesNumber;i++){//将b[]初始化
        b[i] = 0;
    }
    
    while((b = getNextOrderA(headStateStruct,b))!=NULL){//尝试将getNextOrderA换为getNextA，看看效果
        if (searchPath(headStateStruct,b)){
            successStateStructsStack.push(headStateStruct);
            showPath();
            break;
        }
        
        
    }
    
}
bool MyProcessControlClass::searchPath(StateStruct* p,int a[]){
    
    
    if(isOver(p)){
        
        cout<<"运送完毕"<<endl;
        return true;
    }
    cout<<"左岸有";
    for (int i=0;i<p->objectClassesNumber;i++){
        cout<<p->objectStructs[i]->leftBankNumber<<"个"<<p->objectStructs[i]->name<<" ";
    }
    cout<<"尝试将";
    for (int i=0;i<p->objectClassesNumber;i++){
        cout<<a[i]<<"个"<<p->objectStructs[i]->name<<" ";
    }
    if(p->boatSite == 1){
        if(isLegal(p,a) && !isSerched(p, a)){
            cout<<" 从船左岸移动到对岸，尝试成功。"<< endl;
        } else {
            cout<<" 从船左岸移动到对岸，尝试失败。"<< endl;
        }
    } else {
        if(isLegal(p,a) && !isSerched(p, a)){
            cout<<" 从船右岸移动到对岸，尝试成功。"<< endl;
        } else {
            cout<<" 从船右岸移动到对岸，尝试失败。"<< endl;
        }
    }
    
    
	if(isLegal(p,a)){
        if(isSerched(p, a)){
            return false;
        }
        StateStruct* temp = p;
        saveSearchedState(temp);//在开船之前将当前状态保存，因为开船后状态就变了
        
        p = new StateStruct(p);
        p->boating(a);

        int *b = new int[p->objectClassesNumber];
        for (int i=0;i<p->objectClassesNumber;i++){//将b[]初始化
            b[i] = 0;
        }

        while((b = getNextOrderA(p,b))!=NULL){//尝试将getNextOrderA换为getNextA，看看效果
            if (searchPath(p,b)){
                successStateStructsStack.push(p);
                return true;
            }
            
        
        }
        temp = p;
        saveSearchedState(temp);//开船之后，状态的所有子状态均失败，则将该状态保存，返回上一级

        cout<<"over"<<endl;
       
	
	}
    return false;
	
}
void MyProcessControlClass::showPath(){
    StateStruct* temp ;
    int n = 0;
    while(!successStateStructsStack.empty()){
        n++;
        
        temp = successStateStructsStack.top();
        successStateStructsStack.pop();
        if(temp->boatSite == 1){
            cout<<"船在左岸↘"<<endl;
        } else {
            cout<<"船在右岸↘"<<endl;
        }
        
        for(int i=0;i<temp->objectClassesNumber;i++){
            cout<<"\t\t"<<temp->objectStructs[i]->name<<"\t\t 左岸："<<temp->objectStructs[i]->leftBankNumber<<"\t\t右岸："<<temp->objectStructs[i]->totalNumber -  temp->objectStructs[i]->leftBankNumber<<endl;
        }
        
    }
    cout<<"总共运送"<<n<<"趟。"<<endl;
    
}
bool MyProcessControlClass::isOver(StateStruct* p){
    for(int i=0;i<p->objectClassesNumber;i++){
        if(p->objectStructs[i]->isGood == true && p->objectStructs[i]->leftBankNumber!=0){
            return false;
        }
    }
    return true;
}
int* MyProcessControlClass::getNextA(StateStruct* p, int a[]){
    int *b = new int[p->objectClassesNumber];
    int sum = 0;
    for(int i=0;i<p->objectClassesNumber;i++){
        sum += a[i];
        b[i] = a[i];
    }
    for(int i=0;i<p->objectClassesNumber;i++){
        b[i] = b[i]+1;
        if(b[i]>p->objectStructs[i]->totalNumber || sum + 1 > boatMaxLoad){
            sum -= b[i]-1;
            b[i] = 0;
            
        } else {
            
            return b;
        }
    }
    return NULL;
}
int* MyProcessControlClass::getNextOrderA(StateStruct* p, int a[]){
    if(p->boatSite == 0){
        return getNextA(p, a);
    }
    int *b = new int[p->objectClassesNumber];
    
    int hash = 0;
    for(int i=0;i<headStateStruct->objectClassesNumber;i++){
        b[i] = a[i];
        
        hash = hash*(headStateStruct->objectStructs[i]->totalNumber+1)+a[i];
    }
    hash = heuristiHash[hash];
    if(hash <=0 ){
        for(int i=0;i<headStateStruct->objectClassesNumber;i++){
            b[i] = 0;
        }
        return NULL;
    }
    int hash2=hash;
    for (int i=0;i<headStateStruct->objectClassesNumber;i++){
        
        b[headStateStruct->objectClassesNumber - i -1] = hash2%(headStateStruct->objectStructs[headStateStruct->objectClassesNumber - i -1]->totalNumber+1);
        hash2 = hash2 /(headStateStruct->objectStructs[headStateStruct->objectClassesNumber - i -1]->totalNumber+1);
    }
    return b;
}

bool MyProcessControlClass::isLegal(StateStruct* p,int a[]){
    

    bool isNoWaterman = true;

    for(int i=0;i<p->objectClassesNumber;i++){
        for(int j=0;j<lengthOfWatermanArray;j++){
            if(p->objectStructs[i]->name == watermanArray[j] && a[i] != 0){
                
                isNoWaterman = false;
                break;
            }//船夫的数量必须不为0，不然谁开船呢？
        }
 
    }
    
    if(isNoWaterman)
        return false;
    
    for (int i=0;i<p->objectClassesNumber;i++){
        
        ObjectStruct* object = p->objectStructs[i];
        int p_n = a[i];
        int leftBankObjectNumber = object->leftBankNumber - p_n* (p->boatSite*2-1);//(p->boatSite*2-1)表示船在左边(boatSite=1)， 则 - p_n，否则+ p_n
        int rightBankObjectNumber = object->totalNumber - object->leftBankNumber + p_n* (p->boatSite*2-1);
        int leftBankMasterObjectNumber = 0;
        int rightBankMasterObjectNumber = 0;
        if(object->master!=NULL){
            leftBankMasterObjectNumber =object->master->leftBankNumber- a[p->getObjectIndex(object->master)]* (p->boatSite*2-1);
            rightBankMasterObjectNumber =object->master->totalNumber - object->master->leftBankNumber + a[p->getObjectIndex(object->master)]* (p->boatSite*2-1);
        }
        
        if(leftBankObjectNumber < 0 || rightBankObjectNumber<0 ){

            return false;
        }//设置左侧物种最小值
        
        for (int j=0;j<10;j++){
            if(object->preydator[j]!=NULL){//在master在的时候object受master保护，免受predator和natural enemy的捕食，调和和其它object的竞争关系（前提是object的predator、natural enemy和competitor不与master自身成捕食或竞争关系）
                
                ObjectStruct* preydator = object->preydator[j];
                int preydatorBoatingNumber = a[p->getObjectIndex(preydator)];
                int leftBankPreydatorNumber = preydator->leftBankNumber - preydatorBoatingNumber* (p->boatSite*2-1);
                int rightBankPreydatorNumber = preydator->totalNumber - preydator->leftBankNumber + preydatorBoatingNumber* (p->boatSite*2-1);
                
                ObjectStruct* preydatorMaster = object->preydator[j]->master;
                int leftBankPreydatorMasterNumber = 0;
                int rightBankPreydatorMasterNumber = 0;
                if (preydatorMaster!=NULL){
                    int preydatorMasterBoatingNumber = a[p->getObjectIndex(preydatorMaster)];
                    leftBankPreydatorMasterNumber = preydatorMaster->leftBankNumber - preydatorMasterBoatingNumber* (p->boatSite*2-1);
                    rightBankPreydatorMasterNumber = preydatorMaster->totalNumber - preydatorMaster->leftBankNumber + preydatorMasterBoatingNumber* (p->boatSite*2-1);
                }
                
                if(leftBankObjectNumber < 0 ||rightBankObjectNumber<0){
             
                    return false;
                }
                bool isInvalidMaster = false;
                for (int k=0;k<10;k++){
                    if (object->master!=NULL && object->master->preydator[k]!=NULL && object->master->preydator[k]->name== preydator->name){
                        isInvalidMaster = true;
                        break;
                    }
                }
                
                
                if(leftBankPreydatorMasterNumber == 0 &&(leftBankMasterObjectNumber==0 || isInvalidMaster)){//捕食者没有饲养员或饲养员不在场 的前提下：被捕食者没有饲养员或饲养员不在场 或者 被捕食者饲养员无法阻止捕食者
                    if(leftBankObjectNumber!=0 && leftBankPreydatorNumber!=0){
              
                        return false;
                    }
                }
                if(rightBankPreydatorMasterNumber == 0 && (rightBankMasterObjectNumber==0 || isInvalidMaster)){//捕食者没有饲养员或饲养员不在场 的前提下：被捕食者没有饲养员或饲养员不在场 或者 被捕食者饲养员无法阻止捕食者
                    if (object->master!=NULL){
                        cout<<object->master->name;
                    }
                    if(rightBankObjectNumber!=0 && rightBankPreydatorNumber!=0){
                 
                        return false;
                    }
                }
                
            }
            if(object->natualenemy[j]!=NULL){//在master在的时候object受master保护，免受predator和natural enemy的捕食，调和和其它object的竞争关系（前提是object的predator、natural enemy和competitor不与master自身成捕食或竞争关系）
                
                ObjectStruct* natualenemy = p->objectStructs[i]->natualenemy[j];
                int natualenemyBoatingNumber = a[p->getObjectIndex(natualenemy)];
                int leftBankNatualenemyNumber = natualenemy->leftBankNumber - natualenemyBoatingNumber* (p->boatSite*2-1);
                int rightBankNatualenemyNumber = natualenemy->totalNumber - natualenemy->leftBankNumber + natualenemyBoatingNumber* (p->boatSite*2-1);
                
                ObjectStruct* natualenemyMaster = object->natualenemy[j]->master;
                int leftBankNatualenemyMasterNumber = 0;
                int rightBankNatualenemyMasterNumber = 0;
                if (natualenemyMaster!=NULL){
                    int natualenemyMasterBoatingNumber = a[p->getObjectIndex(natualenemyMaster)];
                    leftBankNatualenemyMasterNumber = natualenemyMaster->leftBankNumber - natualenemyMasterBoatingNumber* (p->boatSite*2-1);
                    rightBankNatualenemyMasterNumber = natualenemyMaster->totalNumber - natualenemyMaster->leftBankNumber + natualenemyMasterBoatingNumber* (p->boatSite*2-1);
                }
                
                if(leftBankNatualenemyNumber < 0 ||rightBankNatualenemyNumber<0){
                   
                    return false;
                }
                
                bool isInvalidMaster = false;
                for (int k=0;k<10;k++){
                    if (object->master!=NULL && object->master->natualenemy[k]!=NULL && object->master->natualenemy[k]->name == natualenemy->name){
                        isInvalidMaster = true;
                        break;
                    }
                }
                
                if(leftBankNatualenemyMasterNumber == 0 &&(leftBankMasterObjectNumber==0 || isInvalidMaster)){//捕食者没有饲养员或饲养员不在场 的前提下：被捕食者没有饲养员或饲养员不在场 或者 被捕食者饲养员无法阻止捕食者
                    if(leftBankObjectNumber!=0 && leftBankObjectNumber < leftBankNatualenemyNumber){
               
                        return false;
                    }
                }
                if(rightBankNatualenemyMasterNumber == 0 &&(leftBankMasterObjectNumber==0 || isInvalidMaster)){//捕食者没有饲养员或饲养员不在场 的前提下：被捕食者没有饲养员或饲养员不在场 或者 被捕食者饲养员无法阻止捕食者
                    if(rightBankObjectNumber!=0 && rightBankObjectNumber < rightBankNatualenemyNumber){
           
                        return false;
                    }
                }
                
            }
            if(object->competitor[j]!=NULL ){
                ObjectStruct* competitor = object->competitor[j];
                
                
                ObjectStruct* competitorMaster = competitor->master;
                int competitorMasterBoatingNumber = 0;
                if (competitorMaster!=NULL){
                    competitorMasterBoatingNumber = a[p->getObjectIndex(competitorMaster)];
                }
                
                bool isInvalidMaster = false;
                for (int k=0;k<10;k++){
                    if (object->master!=NULL && object->master->competitor[k]!=NULL && object->master->competitor[k]->name == competitor->name){
                        isInvalidMaster = true;
                        break;
                    }
                }
                
                int masterBoatingNumber = 0;
                if (object->master!=NULL){
                    masterBoatingNumber = a[p->getObjectIndex(object->master)];
                }
                if(competitorMasterBoatingNumber == 0 && (isInvalidMaster || masterBoatingNumber == 0)){//竞争者的饲养员不存在或不在船上的前提下 在船上被竞争者的饲养员不能阻止其与竞争者竞争 或 在船上被竞争者的饲养员数量为0
                    if(competitor!=NULL && a[i]!=0 && a[p->getObjectIndex(competitor)]!=0){//竞争者不同坐一条船
    
                        return false;
                    }
                }
                
                
            }
        }
        
        
        
        
    }
    return true;
};
bool MyProcessControlClass::isSerched(StateStruct* p,int a[]){
    int hash =1 - p->boatSite;
    for(int i=0;i<p->objectClassesNumber;i++){
        hash = hash*(p->objectStructs[i]->totalNumber+1) + p->objectStructs[i]->leftBankNumber - a[i] * (p->boatSite*2-1);
    }
    if(serchedStateHash[hash] == 1){
        return true;
    }
    return false;
}
void MyProcessControlClass::saveSearchedState(StateStruct* p){

    int hash = p->boatSite;
    for(int i=0;i<p->objectClassesNumber;i++){
        hash = hash*(p->objectStructs[i]->totalNumber+1) + p->objectStructs[i]->leftBankNumber;
    }
    if(serchedStateHash[hash] == 1){//已经保存过了不需要再保存
        return ;
    }//避免重复保存
    
    serchedStateHash[hash] = 1;//1表示该状态已经被探究过了
    

    
};
