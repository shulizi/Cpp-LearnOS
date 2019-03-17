#include <iostream>
#include <queue>

#include "ProcessControl.h"
#include "MyProcessControl.h"
using namespace std;



int main(){
    string commend;
    cout << "TYPE THE ALGORITHM(priority/robin/another):" << endl;
    cin >> commend;
    if (commend == "priority"){
        cout <<endl<< "OUTPUT OF PRIORITY" << endl;
        PriorityClass priorityC;
        priorityC.createProcesses();
        priorityC.startProcesses();
    } else if (commend == "robin"){
        cout << "OUTPUT OF ROBIN" << endl;
        RoundRobinClass roundRobin;
        roundRobin.createProcesses();
        roundRobin.startProcesses();
    } else if (commend == "another"){
        cout << "OUTPUT OF MY PROCESS CONTROL ALGORITHM" << endl;
        MyProcessControlClass myProcessControl;
        myProcessControl.createProcesses();
        myProcessControl.startProcesses();
    } else {
        cout << "NO SUCH ALGORITHM" << endl;
    }
	return 0;
}
