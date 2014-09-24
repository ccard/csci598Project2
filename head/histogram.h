#pragma once

/**
 * Author: Chris Card
 * This class stores a histo gram of n bins with a min and max
 */

 #include <map>
 #include <string>
 #include <vector>
 #include <set>
 #include <math.h>

 class Histogram
 {
 public:
 	Histogram(int bins,double min, double max);
 	
 	Histogram(){};

 	void addValue(double val);

 	void addValue(double _bin, double val);

 	void setValue(int _bin, double val);

 	void normalize(double T);

 	void makeLinear(std::vector<double> &linear);

 	int getBins(){ return bins; };
 	double getMin(){ return min; };
 	double getMax(){ return max; };

 	std::map<int,double> getHisto(){ return histo; };

 	Histogram operator<< (Histogram &hist);

 private:
 	double bins;
 	double min,max;
 	std::map<int, double> histo;
 	std::map<int,std::pair<double,double> > bin_map;

 	void init_histo();
};