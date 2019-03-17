//
//  main.cpp
//  MShell
//
//  Created by 杜李 on 2019/3/1.
//  Copyright © 2019年 杜李. All rights reserved.
//

#include <iostream>
#include <unistd.h>//getcwd,chdir
#include <dirent.h>//Dir,opendir
#include <vector>
using namespace std;
string username="lee";
string rootDir="/Users/duli/Library/Developer/Xcode/DerivedData/MShell-fmlxihtouyumnffrfpnpflvqsxsu/Build/";
string currentDir;

string getDir(){
    const int MAXPATH=250;
    char buffer[MAXPATH];
    getcwd(buffer, MAXPATH);
    string dir = buffer;
    return dir;
}
bool cd(string d)
{
    if(chdir(d.c_str()) == -1)
    {
        cout<<"error:no such directory!"<<endl;
        return false;
    }
    return true;
}
void ls(string d){
    if (d.compare("")==0){
        d = ".";
    }
    string originDir = getDir();
    if (!cd(d)){
        return;
    }
    
    struct dirent *dirp;
    DIR* dir = opendir("./");
    while ((dirp = readdir(dir)) != nullptr) {
        if (dirp->d_type == DT_REG) {
            cout<<dirp->d_name<<" ";
            
        } else if (dirp->d_type == DT_DIR) {
            cout<<dirp->d_name<<" ";
        }
    }
    cout<<endl;
    closedir(dir);
    
    cd(originDir);
    
}


void pwd(string d){
    if (d.compare("")==0){
        d = ".";
    }
    string dir = getDir();
    if (!cd(d)){
        return;
    }
    cout<<getDir()<<endl;
    cd(dir);
}
void init_commend(){
    cout << username<<":";
    currentDir = getDir();
    currentDir.replace(0,currentDir.find(rootDir)+rootDir.length(),"~/");
    cout <<currentDir<< "$ ";
}
void init_once(){
    cout <<"Welcome to my Shell!"<<endl;
    init_commend();
}
string Get_comln(){
    string commend;
    getline(cin, commend);
    return commend;
}
vector<string> Get_simcom(string commend){
    string::size_type pos;
    string::size_type size = commend.size();
    vector<string> simcoms;
    
    for (string::size_type i = 0; i<size; i++) {
        pos = commend.find(" ", i);
        if (pos<size) {
            string s = commend.substr(i, pos - i);
            
            simcoms.push_back(s);
            i = pos;
        }
        
    }
    pos = commend.rfind(" ");
    string s = commend.substr(pos+1,size);
    simcoms.push_back(s);
    return simcoms;
}
string Get_simarg_simcommend(vector<string> simcoms){
    
    return simcoms.front();
}
vector<string> Get_simarg_parameter(vector<string> simcoms){
    vector<string> parameter;
    
    for(vector<string>::iterator i=simcoms.begin()+1;i<simcoms.end();i++){
        if ((*i).compare("")){
            parameter.push_back(*i);
        }
    }
    return parameter;
}
void Check(string simcommend,vector<string>parameter){
    if(simcommend == "ls"){
        if(parameter.empty()){
            ls(".");
        }else if (parameter.size()==1){
            ls(parameter.front());
        }
        else{
            for(vector<string>::iterator i=parameter.begin();i<parameter.end();i++){
                cout<<*i<<":"<<endl;
                ls(*i);
            }
        }
        
    } else if(simcommend == "pwd"){
        if(parameter.empty()){
            pwd("");
        }else{
            for(vector<string>::iterator i=parameter.begin();i<parameter.end();i++){
                string s = (*i);
//                if (s.find(".")!=string::npos){
//                    s.replace(s.find("."),s.find(".")+1, "");
//                }
                
                pwd(s);
            }
        }
    } else if(simcommend == "cd"){
        if(parameter.empty()){
            cd(rootDir);
        }else{
            cd(parameter.front());
        }
    } else{
        cout<<"commend error:no such commend!"<<endl;
    }
}
int main(int argc, char** argv)
{
    init_once();
    
    string commend;
    while(commend != "exit") {
        commend = Get_comln();
        vector<string> simcoms = Get_simcom(commend);
        string simcommend =Get_simarg_simcommend(simcoms);
        vector<string> parameter = Get_simarg_parameter(simcoms);
        
        
        Check(simcommend,parameter);
        init_commend();
    }
}


