#include "hjpdcompute.h"

using namespace std;

HJPDCompute::HJPDCompute(){
	x_bins = 9;
	y_bins = 9;
	z_bins = 9;
	min_x = -1;
	max_x = 1;
	min_y = -1;
	max_y = 1;
	min_z = -1;
	max_z = 1;
}

HistogramsXYZ HJPDCompute::computeHistograms(set<HJPD_Skeleton> frame_skels){
	Histogram x(x_bins,min_x,max_x);
	Histogram y(y_bins,min_y,max_y);
	Histogram z(z_bins,min_z,max_z);

	for (set<HJPD_Skeleton>::iterator i = frame_skels.begin(); i != frame_skels.end(); ++i){
		map<int, vector<double> > dis =i->getDisplace();
		for (map<int, vector<double> >::iterator j = dis.begin(); j != dis.end(); ++j){
			x.addValue(j->second[X]);
			y.addValue(j->second[Y]);
			z.addValue(j->second[Z]);
		}
	}

	HistogramsXYZ tmp;
	tmp.push_back(x);
	tmp.push_back(y);
	tmp.push_back(z);
	return tmp;
}

HistogramsXYZ HJPDCompute::normalizeHisto(HistogramsXYZ hist, double t){
	hist[X].normalize(t);
	hist[Y].normalize(t);
	hist[Z].normalize(t);
	return hist;
}

vector<double> HJPDCompute::toOneD(HistogramsXYZ hist){
	vector<double> toret(x_bins+y_bins+z_bins);
	
	hist[X].makeLinear(toret);
	hist[Y].makeLinear(toret);
	hist[Z].makeLinear(toret);

	return toret;
}

bool HJPDCompute::write(FileHandler &f, map<int, vector<vector<double> > > &linear_hist){
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