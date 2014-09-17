#pragma once

/**
 * Author: Chris Card
 * This class is responsible for reading
 * and writing skeletons to and from a file
 */

#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <sstream>
#include "skeleton.h"

class FileHandler
{
public:
	FileHandler(std::string file, bool read_write = true);
	
	bool getSkeleton(int &frame,int &joint,double &x,double &y, double &z);

	bool writeSkeleton(int &index,Skeleton s);

	bool eof(){return (read_write ? infile.eof() : outfile.eof()); };

	bool operator<< (std::string s);

	bool is_open(){ return (read_write ? infile.is_open() : outfile.is_open()); };

	void close(){ return (read_write ? infile.close() : outfile.close()); };
private:
	std::ifstream infile;
	std::ofstream outfile;
	bool read_write;
};