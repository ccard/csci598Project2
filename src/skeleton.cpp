#include "skeleton.h"
#include <limits>

using namespace std;

void Skeleton::addJoint(int joint, double x, double y, double z){
	pair<double,double> tmpyz(y,z);
	pair<double,pair<double,double> > tmp(x,tmpyz);
	joints.insert(make_pair(joint,tmp));
}

pair<double,pair<double,double> > Skeleton::getJoint(int joint){
	if (joints.find(joint) != joints.end())
	{
		return joints[joint];
	}
	pair<double,double> tmp(0,0);
	return pair<double,pair<double,double> >(0,tmp);
}

double Skeleton::getJointCord(int joint, char cord){
	if (joints.find(joint) == joints.end())
	{
		return numeric_limits<double>::max();
	}

	double cordinate;
	switch(cord){
		case Skeleton::X:
			cordinate = joints[joint].first;
			break;
		case Skeleton::Y:
			cordinate = joints[joint].second.first;
			break;
		case Skeleton::Z:
			cordinate = joints[joint].second.second;
			break;
		default:
			cordinate = numeric_limits<double>::max();
	}
	return cordinate;
}

string Skeleton::toString(int &index){
	return "";
}