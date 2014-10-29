/**
 * Author: Chris Card
 * 
 * runs the program for all test and trianing sets
 */
 
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <set>
#include "skeleton.h"
#include "filehandler.h"
#include "rad_skeleton.h"
#include "radcompute.h"
#include "histogram.h"
#include "hjpdcompute.h"
#include "hjpd_skeleton.h"
#include "hodcompute.h"

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

int buildRADData(string flag, map<int,vector<set<Skeleton> > > &skels){
	map<int, vector<set<RAD_Skeleton> > > rad_skels;
	for(map<int, vector<set<Skeleton> > >::iterator i = skels.begin(); i != skels.end(); ++i){
		vector<set<RAD_Skeleton> > tmp_v;
		
		for(vector<set<Skeleton> >::iterator j = i->second.begin(); j != i->second.end(); ++j){
			set<RAD_Skeleton> tmp_s;
			for(set<Skeleton>::iterator e = j->begin(); e != j->end(); ++e){
				tmp_s.insert(RAD_Skeleton(*e));
			}
			tmp_v.push_back(tmp_s);
		}
		
		rad_skels.insert(make_pair(i->first,tmp_v));
	}

	RADCompute radc;

	map<int,vector<vector<double> > > linear_data;

	for(map<int, vector<set<RAD_Skeleton> > >::iterator i = rad_skels.begin(); i != rad_skels.end(); ++i){
		vector<vector<double> > tmp_v;
		for(vector<set<RAD_Skeleton> >::iterator j = i->second.begin(); j != i->second.end(); ++j){
			Histograms hists = radc.computeHistograms(*j);
			hists = radc.normalizeHisto(hists,j->size());
			tmp_v.push_back(radc.toOneD(hists));
		}
		linear_data.insert(make_pair(i->first,tmp_v));
	}

	string filename = "rad";
	filename += flag == TEST ? ".t" : ""; 
	FileHandler out(filename,false);

	if(!radc.write(out,linear_data)){
		out.close();
		cerr << "please check error msgs" << endl;
		return 2;
	}
	out.close();
	return 0;
}

int buildHJDPData(string flag, map<int,vector<set<Skeleton> > > skels){
	map<int, vector<set<HJPD_Skeleton> > > hjpd_skels;
	for(map<int, vector<set<Skeleton> > >::iterator i = skels.begin(); i != skels.end(); ++i){
		vector<set<HJPD_Skeleton> > tmp_v;
		
		for(vector<set<Skeleton> >::iterator j = i->second.begin(); j != i->second.end(); ++j){
			set<HJPD_Skeleton> tmp_s;
			for(set<Skeleton>::iterator e = j->begin(); e != j->end(); ++e){
				tmp_s.insert(HJPD_Skeleton(*e));
			}
			tmp_v.push_back(tmp_s);
		}
		
		hjpd_skels.insert(make_pair(i->first,tmp_v));
	}

	HJPDCompute hjpdc;

	map<int,vector<vector<double> > > linear_data;

	for(map<int, vector<set<HJPD_Skeleton> > >::iterator i = hjpd_skels.begin(); i != hjpd_skels.end(); ++i){
		vector<vector<double> > tmp_v;
		for(vector<set<HJPD_Skeleton> >::iterator j = i->second.begin(); j != i->second.end(); ++j){
			HistogramsXYZ hists = hjpdc.computeHistograms(*j);
			hists = hjpdc.normalizeHisto(hists,j->size());
			tmp_v.push_back(hjpdc.toOneD(hists));
		}
		linear_data.insert(make_pair(i->first,tmp_v));
	}

	string filename = "hjpd";
	filename += flag == TEST ? ".t" : ""; 
	FileHandler out(filename,false);

	if(!hjpdc.write(out,linear_data)){
		out.close();
		cerr << "please check error msgs" << endl;
		return 2;
	}
	out.close();
	return 0;
}

int buildHODData(string flag, map<int,vector<set<Skeleton> > > skels){
	HODCompute hodc;

	map<int,vector<vector<double> > > linear_data;

	for(map<int, vector<set<Skeleton> > >::iterator i = skels.begin(); i != skels.end(); ++i){
		vector<vector<double> > tmp_v;
		for(vector<set<Skeleton> >::iterator j = i->second.begin(); j != i->second.end(); ++j){
			HistogramTMP hist = hodc.createNormedHistogram(*j);
			tmp_v.push_back(hodc.toOneD(hist));
		}
		linear_data.insert(make_pair(i->first,tmp_v));
	}

	string filename = "hod";
	filename += flag == TEST ? ".t" : ""; 
	FileHandler out(filename,false);

	if(!hodc.write(out,linear_data)){
		out.close();
		cerr << "please check error msgs" << endl;
		return 2;
	}
	out.close();
	return 0;
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
	
	int res = 0;
	if(method == RAD){
		res = buildRADData(flag,skels);
	} else if (method == HJPD) {
		res = buildHJDPData(flag,skels);
	} else if (method == HOD) {
		res = buildHODData(flag,skels);
	} else {
		cerr << "The wrong method flag " << method << ". Some how made it past the checks." << endl;
		showUsage();
		return 2;
	}

	return res;
}
