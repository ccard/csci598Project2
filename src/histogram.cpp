#include "histogram.h"

using namespace std;

Histogram::Histogram(int bins,double min, double max){
	this->bins = bins;
	this->min = min;
	this->max = max;
	init_histo();
}

void Histogram::addValue(double val){
	int bin = 0;
	double prev_min;
	for(map<int,double>::iterator i = bin_map.begin(); i != bin_map.end(); ++i){
		if(i->first == 0){
			if (i->second > val){
				bin = i->first;
				break;
			}
			prev_min = i->second;
		} else if (i->first == bins-1) {
			if(i->second <= val){
				bin = i->first;
				break;
			}
			prev_min = i->second;
		} else {
			if(i->second > val && prev_min <= val){
				bin = i->first;
				break;
			}
			prev_min = i->second;
		}
	}

	histo[bin] += 1;
}

void Histogram::normalize(double T){
	map<int,double> normed;
	if (T == 0) return;
	for(map<int,double>::iterator i = histo.begin(); i != histo.end(); ++i){
		normed.insert(make_pair(i->first,i->second/T));
	}
	histo = normed;
}

void Histogram::makeLinear(vector<double> &linear){
	for(map<int,double>::iterator i = histo.begin(); i != histo.end(); ++i){
		linear.push_back(i->second);
	}
}

void Histogram::init_histo(){
	for(int i = 0; i < bins; ++i){
		histo.insert(make_pair(i,0.0));
	}

	double step = (max-min)/bins;

	double curr_max = min+step;

	for (int j = 0; j < bins; ++j)
	{
		bin_map.insert(make_pair(j,curr_max));
		curr_max += step;
	}
}