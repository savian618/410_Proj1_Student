/***
 * KP Utils
 */
#include <numeric>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "utilities.h"
#include "stdlib.h"

using namespace std;


vector <process_stats> v;

//********************** private to this compilation unit **********************

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}

int loadData(const char* filename, bool ignoreFirstRow) {
	v.clear();
	fstream file;
	file.open((filename));
	string line;
	vector <string> vLD;

	if (!file.is_open()){
		return COULD_NOT_OPEN_FILE;
	}

	if(ignoreFirstRow == true){
		int i = 0;
		while(getline(file, line)){
			if(i == 0){
				i++;
				continue;
			}
			else{
				vLD.push_back(line);
			}
		}
	}
	else{
		if(file.is_open()){
			while(getline(file, line)){
				vLD.push_back(line);
			}
		}
	}

	file.close();
	for(long unsigned int i = 0; i < vLD.size(); i++){
		vector<int> temp;
		string s;
		int j = 0;
		string l = vLD[i];
		for(long unsigned int i = 0; i < l.length(); i++){
			if (l[i] == CHAR_TO_SEARCH_FOR){
				stringstream ss(s);
				ss >> j;
				temp.push_back(j);
				s = "";
			}
			else{
				s += l[i];
			}
		}
		stringstream ss(s);
		ss >> j;
		temp.push_back(j);
		process_stats tempV;
		tempV = {
				temp[0],
				temp[1],
				temp[2],
				temp[3]
		};
		if(temp[0] == NULL || temp[1] == NULL || temp[2] == NULL || temp[3] == NULL){
			continue;
		}
		else{
			v.push_back(tempV);
		}
	}

	return SUCCESS;
}

bool sortCPU(process_stats a, process_stats b){
	return a.cpu_time > b.cpu_time;
}
bool sortStart(process_stats a, process_stats b){
	return a.start_time > b.start_time;
}

bool sortIO(process_stats a, process_stats b){
	return a.io_time > b.io_time;
}

bool sortProcess(process_stats a, process_stats b){
	return a.process_number > b.process_number;
}

//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {
	if (mySortOrder == SORT_ORDER::CPU_TIME){
		sort(v.begin(), v.end(), sortCPU);
	}
	if (mySortOrder == SORT_ORDER::START_TIME){
			sort(v.begin(), v.end(), sortStart);
	}
	if (mySortOrder == SORT_ORDER::IO_TIME){
			sort(v.begin(), v.end(), sortIO);
	}
	if (mySortOrder == SORT_ORDER::PROCESS_NUMBER){
			sort(v.begin(), v.end(), sortProcess);
	}
}

process_stats getNext() {
	process_stats myFirst = v[0];
	v.erase((v.begin()));

	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){

	return v.size();
}


