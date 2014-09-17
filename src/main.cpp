/**
 * Author: Chris Card
 * 
 * runns the program for all test and trianing set
 * building 
 */
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "skeleton.h"
#include "filehandler.h"

using namespace std;

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

bool process_file(string file, string path, map<int,vector<map<int,Skeleton> > > &skels){
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
		
		if (skels.find(class_num) != skels.end()){
			skels[class_num].push_back(file_skel);
		} else {
			vector<map<int,Skeleton> > temp_vec;
			temp_vec.push_back(file_skel);
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

bool process_args(int argc, char const *argv[], string &file, string &path){
	if (argc != 3) {
		cerr << "Usage:" << endl;
		cerr << "parseSkeleton <path_to_data> <data_file_class_name>" << endl;
		cerr << "<path_to_data> : path to where the data resides" << endl;
		cerr << "<data_file_class_name> : must be in the expected format"<< endl;
		return false;
	} else {
		path = string(argv[1]);
		file = string(argv[2]);
		return true;
	}
}

int main(int argc, char const *argv[])
{
	string file,path;
	map<int,vector<map<int, Skeleton> > > skels;
	if (!process_args(argc,argv,file,path)) return 2;
	if (!process_file(file,path,skels)) return 2;
	cout << skels.size() << endl;
	return 0;
}