#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <cstdio>
#include "read.h"
#include "process.h"	

using namespace std;
ofstream out("output.txt");

void Create_process(vector<process>& process_vector)
{
	ifstream file("definition.txt");
	string process_name="";
	string which_code;
	int arrival_time;
	int process_num = 0;
	int priority;
	while (file.peek()!=EOF)
	{
		file >> process_name >> priority >> which_code >> arrival_time;
		process newprocess(process_name, priority , which_code, arrival_time, process_num);
		process_num++;
		process_vector.push_back(newprocess);
	}
	file.close();
}
void writeQueue(priority_queue<process> readyQueue, int time){
    priority_queue<process> showQueue;
    out<<time<<":HEAD";
    showQueue=readyQueue;
    while(!showQueue.empty()){
		out << "-" <<showQueue.top().process_name << "[" << showQueue.top().index+1 << "]" ;
        showQueue.pop();
	}
    out<<"-TAIL"<<endl;
    
	
	cout<<time<<":HEAD";
    showQueue=readyQueue;
	while(!showQueue.empty() ){
		cout << "-" <<showQueue.top().process_name << "[" << showQueue.top().index+1 << "]" ;
        showQueue.pop();
	}
    cout<<"-TAIL"<<endl;
}



priority_queue<process> addQueue(priority_queue<process> readyQueue, vector<process>& process_vector, int time){
    priority_queue<process> copyQueue;
    for(int i=0;i<process_vector.size();i++){
    	if (process_vector[i].arrival_time <= time && !process_vector[i].IsFinish){
        	if(!readyQueue.empty()){
                bool var=false;
                copyQueue=readyQueue;
                for(int j=0;j<readyQueue.size();j++){
                    if(copyQueue.top().process_num==process_vector[i].process_num){
                        var=true;
                        break;
                    }
                    else{
                    	copyQueue.pop();
                    }
                }
                if(!var){
					readyQueue.push(process_vector[i]);
				}
			}
			else{
                readyQueue.push(process_vector[i]);
            }
        }
    }
	return readyQueue;
}

void run_process(vector<process>& process_vector){
    priority_queue<process> readyQueue;
    vector<code_num> instructions;
    int i=0;
    int time=0;
    read r;
    int isChanged=0;
    bool reflesh=false;
    while(true){
        readyQueue=addQueue(readyQueue,process_vector,time);
        if(isChanged!=readyQueue.size() || isChanged==0 ||reflesh){
        	if(!readyQueue.empty() || time==0){
        		writeQueue(readyQueue, time);
        		reflesh=false;
        	}
        }
        else if(process_vector[0].arrival_time==time){
        	writeQueue(readyQueue, time);
        }
		if(!readyQueue.empty()){
            instructions=r.read_all(readyQueue.top().which_code);
            for(int i = readyQueue.top().index; i < instructions.size(); i++){
                
                priority_queue<process> count_WaitingTime_Queue;
                count_WaitingTime_Queue=readyQueue;
                count_WaitingTime_Queue.pop();
                int firstWaiting=0;
                if(readyQueue.top().went==false){
                    firstWaiting = time-readyQueue.top().arrival_time;
                    process_vector[readyQueue.top().process_num].went=true;
                    process_vector[readyQueue.top().process_num].waitingTime+=firstWaiting;
                }
                while(!count_WaitingTime_Queue.empty()&&count_WaitingTime_Queue.top().went){
                    process_vector[count_WaitingTime_Queue.top().process_num].waitingTime+=instructions[i].burst;
                    count_WaitingTime_Queue.pop();
                }
                if(!count_WaitingTime_Queue.empty()&&!count_WaitingTime_Queue.top().went){
                	if(count_WaitingTime_Queue.size()>1){
                		count_WaitingTime_Queue.pop();
                		while(count_WaitingTime_Queue.size()>1){
                			if(count_WaitingTime_Queue.top().went){
                				process_vector[count_WaitingTime_Queue.top().process_num].waitingTime+=instructions[i].burst;
                			}
                			count_WaitingTime_Queue.pop();
                		}
                	}
                }
                time += instructions[i].burst;
                process_vector[readyQueue.top().process_num].index = i+1;
                if(instructions[i].inst_name == "exit"){
                    process_vector[readyQueue.top().process_num].IsFinish = true;
                    process_vector[readyQueue.top().process_num].turnAround_time=time-process_vector[readyQueue.top().process_num].arrival_time;
                    readyQueue.pop();
                    if(readyQueue.size()==0){
                        writeQueue(readyQueue, time);
                        reflesh=true;
                    }
                    break;
                }
                else{
		            readyQueue.pop();
                }
                break;	
            }
        }
        else
            time+=10;
            
        
        bool AllFinish = true;
        for(int i=0; i < process_vector.size(); i++){
            if(!process_vector[i].IsFinish)
                AllFinish=false;
        }
        if(AllFinish)
            break;
			
		isChanged=readyQueue.size()+1;
    }
    
	cout<<"------------------------------- \n"<<endl;
    out<<"------------------------------- \n"<<endl;
    for(int t=0;t<process_vector.size();t++){
    	cout << "Turnaround time for P["<<process_vector[t].process_num+1<<"] = "<<process_vector[t].turnAround_time<<" ms"<<endl;
        cout << "Waiting time for P["<<process_vector[t].process_num+1<<"] = "<<process_vector[t].waitingTime<<endl ;
        out << "Turnaround time for P["<<process_vector[t].process_num+1<<"] = "<<process_vector[t].turnAround_time<<" ms"<<endl;
        out << "Waiting time for P["<<process_vector[t].process_num+1<<"] = "<<process_vector[t].waitingTime<<endl ;
    }
    
}


int main() {
	vector<process> process;
	Create_process(process);
    run_process(process);
    
}
