/**
 * Author: Chris Card
 * 
 * runns the program for all test and trianing set
 * building 
 */
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <set>
#include "skeleton.h"
#include "filehandler.h"
#include "rad_skeleton.h"

using namespace std;

const static string TRAIN = "-tr";
const static string TEST = "-te";

const static string RAD = "RAD";
const static string HJPD = "HJPD";
const static string HOD = "HOD";

vector<string> comma_split(string s){
	vector<string> split;
	int current,next = -1;
	do{
		current = next+1;
		next = s.find_first_of(" ,",current);
		split.push_back(s.substr(current,next-current));
	} while (next != string::npos);
	return split;
}

bool process_file(string file, string path, map<int,vector<set<Skeleton> > > &skels){
	ifstream infile(file.c_str());
	string line = "-1-1";
	string err_msg = "";
	bool aborted = false;

	while(getline(infile,line)) {
		vector<string> class_file = comma_split(line);
		int class_num = atoi(class_file[0].c_str());
		string data_file = class_file[1];

		FileHandler skel_file(path+data_file);
		if (!skel_file.is_open()) {
			aborted = true;
			err_msg += "Failed to open skeleton file\n";
			break;
		}

		map<int,Skeleton> file_skel;
		bool internal = false;
		do {
			int frame,joint;
			double x,y,z;
			if(!skel_file.getSkeleton(frame,joint,x,y,z)){
				if (frame == -1) break;
				internal = true;
				err_msg += "Failed to read skeleton data\n";
				break;
			}
			
			if (file_skel.find(frame) != file_skel.end()){
				file_skel[frame].addJoint(joint,x,y,z);
			} else {
				Skeleton temp_skel(frame);
				temp_skel.addJoint(joint,x,y,z);
				file_skel.insert(make_pair(frame,temp_skel));
			}
		} while (!skel_file.eof());

		skel_file.close();
		if (internal) {
			aborted = true;
			break;
		}
		
		set<Skeleton> class_set;
		for(map<int,Skeleton>::iterator i = file_skel.begin(); i != file_skel.end(); ++i){
			class_set.insert(i->second);
		}

		if (skels.find(class_num) != skels.end()){
			skels[class_num].push_back(class_set);
		} else {
			vector<set<Skeleton> > temp_vec;
			temp_vec.push_back(class_set);
			skels.insert(make_pair(class_num,temp_vec));
		}
	}
	infile.close();
	if(aborted || line == "-1-1"){
		cerr << "Error while reading the file: " << line << endl;
		cerr << err_msg << endl;
	}
	return !aborted;
}

void buildRADData(string flag,map<int,vector<set<Skeleton> > > skels){

}

void buildHJDPData(string flag,map<int,vector<set<Skeleton> > > skels){
	
}
void buildHODData(string flag,map<int,vector<set<Skeleton> > > skels){
	
}

void showUsage(){
	cerr << "Usage:" << endl;
	cerr << "parseSkeleton <flag> <method> <path_to_data> <data_file_class_name>" << endl;
	cerr << "<flag> : to create training data " << TRAIN << ", to creat testing data " << TEST << endl;
	cerr << "<method> : " << RAD << ", " << HJPD << ", " << HOD << endl;
	cerr << "<path_to_data> : path to where the data resides" << endl;
	cerr << "<data_file_class_name> : must be in the expected format"<< endl;
}

bool process_args(int argc, char const *argv[],string &flag, string &method,string &file, string &path){
	if (argc != 5) {
		showUsage();
		return false;
	} else {
		flag = string(argv[1]);
		method = string(argv[2]);
		path = string(argv[3]);
		file = string(argv[4]);
		if(flag != TEST && flag != TRAIN){
			showUsage();
			return false;
		}
		if (method != RAD && method != HJPD && method != HOD)
		{
			showUsage();
			return false;
		}
		return true;
	}
}

int main(int argc, char const *argv[])
{
	string flag,method,file,path;
	map<int,vector<set<Skeleton> > > skels;
	if (!process_args(argc,argv,flag,method,file,path)) return 2;
	if (!process_file(file,path,skels)) return 2;
	cout << skels.size() << endl;
	
	if(method == RAD){
		buildRADData(flag,skels);
	} else if (method == HJPD) {
		buildHJDPData(flag,skels);
	} else if (method == HOD) {
		buildHODData(flag,skels);
	} else {
		cerr << "The wrong method flag " << method << ". Some how made it past the checks." << endl;
		showUsage();
		return 2;
	}

	return 0;
}