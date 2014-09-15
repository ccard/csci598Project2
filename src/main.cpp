/**
 * Author: Chris Card
 * 
 * runns the program for all test and trianing set
 * building 
 */
#include <stdlib.h>
#include <iostream>
#include "skeleton.h"

using namespace std;

bool process_file(string file){
	return false;
}

bool process_args(int argc, char const *argv[], string &file){
	if (argc != 2) {
		cerr << "Usage:" << endl;
		cerr << "parseSkeleton <data_file>" << endl;
		cerr << "<data_file> : must be in the expected format"<< endl;
		return false;
	} else {
		file = string(argv[1]);
		return true;
	}
}

int main(int argc, char const *argv[])
{
	string file;
	if (!process_args(argc,argv,file)) return 2;
	process_file(file);
	return 0;
}