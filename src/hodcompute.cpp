#include "hodcompute.h"

using namespace std;

HODCompute::HODCompute(int levels){
	this->levels = levels;
	min = -15;
	max = 15;
	n_bins = 8;
}

HistogramTMP HODCompute::createNormedHistogram(set<Skeleton> skels){
	Histogram xy = recursion(1,1,skels);
	Histogram yz = recursion(1,2,skels);
	Histogram xz = recursion(1,3,skels);
	xy.normalize(pow(2,levels)-1);
	yz.normalize(pow(2,levels)-1);
	xz.normalize(pow(2,levels)-1);
	HistogramTMP h;
	h.push_back(xy);
	h.push_back(yz);
	h.push_back(xz);
	return h;
}

vector<double> HODCompute::toOneD(HistogramTMP hist){
	vector<double> ret;
	hist[0].makeLinear(ret);
	hist[1].makeLinear(ret);
	hist[2].makeLinear(ret);
	return ret;
}

bool HODCompute::write(FileHandler &f, map<int, vector<vector<double> > > &linear_hist){
	if(!f.is_open()) return false;
	string err_msg = "";
	bool aborted = false;
	for(map<int, vector<vector<double> > >::iterator i = linear_hist.begin(); i != linear_hist.end(); ++i){
		int class_label = i->first;
		for(vector<vector<double> >::iterator j = i->second.begin(); j != i->second.end(); ++j){
			int inst_idx = 0;
			string inst_str = "";
			for(vector<double>::iterator e = j->begin(); e != j->end(); ++e){
				char buff[100];
				sprintf(buff,"%d:%5.7f ",++inst_idx,*e);
				inst_str += buff;
				
			}
			char *buff;
			buff = (char *)malloc(sizeof(char)*(inst_str.size()+100));
			sprintf(buff,"%d %s\n",class_label,inst_str.c_str());
			inst_str = string(buff);
			delete []buff;
			bool worked = f << inst_str;
			if(!worked){
			 	aborted = true;
				err_msg += "Failed to write: " + inst_str + " : to the file\n";
				break;
			}
		}
		if(aborted) break;
	}

	if(aborted){
		cerr << err_msg << endl;
	}
	return !aborted;
}

Histogram HODCompute::recursion(int level,int hist, set<Skeleton> skels){
	Histogram h = trajectory(skels,hist);
	if (level == levels) return h;

	++level;
	Skeleton first = *(skels.begin());
	int half = first.getFrame()+ceil(skels.size()/2.0);
	
	set<Skeleton>::iterator mid = skels.find(half);
	set<Skeleton> left(skels.begin(),mid);
	set<Skeleton> right(mid,skels.end());

	return recursion(level,hist,left) << recursion(level,hist,right);
}

Histogram HODCompute::trajectory(set<Skeleton> skels,int hist){
	Histogram xy(n_bins,min,max);
	Histogram yz(n_bins,min,max);
	Histogram xz(n_bins,min,max);
	set<Skeleton>::iterator last = skels.end();
	last--;
	set<Skeleton>::iterator next;

	for(set<Skeleton>::iterator i = skels.begin(); i != last; ++i){
		Skeleton t,t_1;
		t = *i;
		next = i;
		t_1 = *(++next);
		for(int j = 1; j <= 20; ++j){
			vector<double> jointcord_t = t.getJoint(j);
			vector<double> jointcord_t1 = t_1.getJoint(j);
			vector<double> xy_t, xy_t1, yz_t, yz_t1, xz_t, xz_t1;
			
			switch(hist){
				case 1:
					//forming xy points
					xy_t.push_back(jointcord_t[X]);
					xy_t.push_back(jointcord_t[Y]);
					xy_t1.push_back(jointcord_t1[X]);
					xy_t1.push_back(jointcord_t1[Y]);
					break;
				case 2:
					//forming yz points
					yz_t.push_back(jointcord_t[Y]);
					yz_t.push_back(jointcord_t[Z]);
					yz_t1.push_back(jointcord_t1[Y]);
					yz_t1.push_back(jointcord_t1[Z]);
					break;
				case 3:
					//form xz points
					xz_t.push_back(jointcord_t[X]);
					xz_t.push_back(jointcord_t[Z]);
					xz_t1.push_back(jointcord_t1[X]);
					xz_t1.push_back(jointcord_t1[Z]);
					break;
			}
			//Calc angles and mags and addin to appropriate histogram
			double xy_mag, xy_ang, yz_mag, yz_ang, xz_mag, xz_ang;
			switch(hist){
				case 1:
					xy_mag = calcMag(xy_t, xy_t1); 
					xy_ang = calcAngle(xy_t, xy_t1);
					break;
				case 2:
					yz_mag = calcMag(yz_t, yz_t1); 
					yz_ang = calcAngle(yz_t, yz_t1);
					break;
				case 3:			
					xz_mag = calcMag(xz_t, xz_t1); 
					xz_ang = calcAngle(xz_t, xz_t1);
					break;
			}
			switch(hist){
				case 1:
					xy.addValue(xy_ang,xy_mag);
					break;
				case 2:
					yz.addValue(yz_ang,yz_mag);
					break;
				case 3:
					xz.addValue(xz_ang,xz_mag);
					break;
			}
		}
	}

	Histogram traj;// = xy << yz << xz;

	switch(hist){
		case 1:
			traj = xy;
			break;
		case 2:
			traj = yz;
			break;
		case 3:
			traj = xz;
			break;
	}

	traj.normalize(skels.size());

	return traj;
}

double HODCompute::calcAngle(vector<double> pt, vector<double> pt_1){
	double dot = (pt[0]*pt_1[0]) + (pt[1]*pt_1[1]);
	double det = (pt[0]*pt_1[1]) - (pt[1]*pt_1[0]);
	double rad = atan2(det,dot);
	return (rad*180/PI);
}

double HODCompute::calcMag(vector<double> pt, vector<double> pt_1){
	vector<double> vec;
	vec.push_back(pt_1[0]-pt[0]);
	vec.push_back(pt_1[1]-pt[1]);

	double inter = pow(vec[0],2)+pow(vec[1],2);
	return sqrt(inter);
}