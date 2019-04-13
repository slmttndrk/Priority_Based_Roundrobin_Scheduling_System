#ifndef _read_
#define _read_
#include<iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
class code_num {		
public:
	int burst;
	string inst_name;
	code_num()
	{ }
	
	code_num(string _inst_name, int _burst) {
		burst = _burst;
		inst_name = _inst_name;
	}
};
class read {

public:
	vector<code_num> read_all(string txtName);
};
vector<code_num> read::read_all(string txtName)	
{
	txtName+=".txt";
	ifstream file(txtName.c_str());
	string content="";
	int burst;
	vector<code_num> v2;
	while (content!="exit") {
		file >> content >> burst;
		code_num code2(content, burst);
		v2.push_back(code2);
	}
	return v2;
	
}
#endif
