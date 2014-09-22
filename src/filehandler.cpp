#include "filehandler.h"

using namespace std;

FileHandler::FileHandler(string file, bool read_write){
	this->read_write = read_write;
	if (read_write) {
		infile.open(file.c_str());
	} else {
		outfile.open(file.c_str(),ofstream::out);
	}
}

bool FileHandler::getSkeleton(int &frame,int &joint,double &x,double &y, double &z) {
	if (!read_write) return false;
	if (!infile.is_open()) return false;
	if (infile.eof()){
		frame = -1;
		return false;
	}

	string line;
	getline(infile,line);
	if(line.size() == 0) {
		frame = -1;
		return false;
	}
	
	stringstream stream(line);
	istream_iterator<string> begin(stream);
	istream_iterator<string> end;
	vector<string> vstring(begin,end);

	frame = atoi(vstring[0].c_str());
	joint = atoi(vstring[1].c_str());

	x = atof(vstring[2].c_str());
	y = atof(vstring[3].c_str());
	z = atof(vstring[4].c_str());
	return true;
}

bool FileHandler::writeSkeleton(int &index, Skeleton s){
	if(read_write) return false;
	if(!outfile.is_open()) return false;

	string l = s.toString(index);

	outfile.write(l.c_str(),l.size());
	return true;
}

bool FileHandler::operator<< (string s){
	if (read_write) return false;
	if(!outfile.is_open()) return false;

	outfile << s;
	//outfile.flush();
	return true;
}