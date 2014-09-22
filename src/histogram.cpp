#include "histogram.h"
#include <iostream>

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
	if(val != val) return;
	for(map<int,pair<double,double> >::iterator i = bin_map.begin(); i != bin_map.end(); ++i){
		if(i->first == 0){
			if (val < i->second.second){
				bin = i->first;
				break;
			}
		} else if (i->first == (bins-1)) {
			if(i->second.first <= val){
				bin = i->first;
				break;
			}
		} else {
			if(val >= i->second.first && val < i->second.second){
				bin = i->first;
				break;
			}
		}
	}
	
	histo[bin] += 1;
	//cout << "bin: "<< bin << " val: "<< val << " cnt: " << histo[bin] << endl;
}

void Histogram::normalize(double T){
	map<int,double> normed;
	if (T == 0) return;
	for(map<int,double>::iterator i = histo.begin(); i != histo.end(); ++i){
		normed.insert(make_pair(i->first,i->second/T));
		cout << i->first << ":" << normed[i->first] << endl;
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

	double bin_min = min;
	double bin_max = min+step;

	for (int j = 0; j < bins; ++j)
	{
		pair<double,double> tmp(bin_min,bin_max);
		bin_map.insert(make_pair(j,tmp));
		bin_max += (2*step);
		bin_min += step;
	}
}