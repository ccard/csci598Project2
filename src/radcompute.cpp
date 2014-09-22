#include "radcompute.h"

using namespace std;

RADCompute::RADCompute(){
	n_d_bins = 6;
	m_t_bins = 6;
	min_d = 0.5;
	max_d = 2;
	min_t = 0;
	max_t = M_PI;
}

Histograms RADCompute::computeHistograms(set<RAD_Skeleton> frame_skels){
	map<int, Histogram> d_hist,t_hist;
	for(set<RAD_Skeleton>::iterator i = frame_skels.begin(); i != frame_skels.end(); ++i){
		map<int, pair<double,double> > tmp = i->getJointsThetaRho();
		for(map<int, pair<double,double> >::iterator j = tmp.begin(); j != tmp.end(); ++j){
			if(d_hist.find(j->first) == d_hist.end()){
				Histogram h(n_d_bins,min_d,max_d);
				h.addValue(j->second.second);
				d_hist.insert(make_pair(j->first,h));
			} else {
				d_hist[j->first].addValue(j->second.second);
			}
			if(t_hist.find(j->first) == t_hist.end()){
				Histogram h(m_t_bins,min_t,max_t);
				h.addValue(j->second.first);
				d_hist.insert(make_pair(j->first,h));
			} else {
				t_hist[j->first].addValue(j->second.first);
			}
		}
	}

	return Histograms(d_hist,t_hist);
}

Histograms RADCompute::normalizeHisto(Histograms hist, int t){
	for(map<int,Histogram>::iterator i = hist.first.begin(); i != hist.first.end(); ++i){
		i->second.normalize(t);
	}

	for(map<int,Histogram>::iterator i = hist.second.begin(); i != hist.second.end(); ++i){
		i->second.normalize(t);
	}
	return hist;
}

vector<double> RADCompute::toOneD(Histograms hist){
	vector<double> v_ret(5*(n_d_bins+m_t_bins));
	for(map<int,Histogram>::iterator i = hist.first.begin(); i != hist.first.end(); ++i){
		i->second.makeLinear(v_ret);
	}

	for(map<int,Histogram>::iterator i = hist.second.begin(); i != hist.second.end(); ++i){
		i->second.makeLinear(v_ret);
	}

	return v_ret;
}

bool RADCompute::write(FileHandler &f, std::map<int, std::vector<std::vector<double> > > &linear_hist){
	return false;
}