#ifndef _process_
#define _process_
#include<iostream>
#include <fstream>
#include <string>
#include "read.h"

using namespace std;
class process {
public:
	string process_name;
	string which_code;
	int arrival_time;
	int turnAround_time = 0;
	int waitingTime = 0;
	bool IsFinish;
	int process_num;
	int index = 0;
	int priority;
	bool went;
	process(string _name,int _priority, string _code, int _Arrival_time, int _process_num);
    process(const process& other);
    process& operator=(const process& other);



    bool operator==(const process& other) const;
    bool operator<(const process& other) const;
	
};

process::process(string _name,int _priority, string _code, int _Arrival_time, int _process_num )
{
	process_num = _process_num;
	IsFinish = false;
	went=false;
	process_name = _name;
	arrival_time = _Arrival_time;
	turnAround_time;
	which_code = _code;
	index;
	priority=_priority;
	
}

process::process(const process &other){
	this->process_num=other.process_num;
	this->IsFinish=other.IsFinish;
	this->went=other.went;
	this->process_name=other.process_name;
	this->arrival_time=other.arrival_time;
	this->turnAround_time=other.turnAround_time;
	this->which_code=other.which_code;
	this->index=other.index;
	this->priority=other.priority;
	
}

process& process::operator = (const process &other){
	this->process_num=other.process_num;
	this->IsFinish=other.IsFinish;
	this->went=other.went;
	this->process_name=other.process_name;
	this->arrival_time=other.arrival_time;
	this->turnAround_time=other.turnAround_time;
	this->which_code=other.which_code;
	this->index=other.index;
	this->priority=other.priority;
	return *this;
}

bool process::operator==(const process &other) const {
    return this->priority==other.priority;
}


bool process::operator<(const process &other) const {
    return this->priority > other.priority || (this->priority==other.priority && this->arrival_time>other.arrival_time);
}

#endif
