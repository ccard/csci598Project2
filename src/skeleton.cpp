#include "skeleton.h"
#include <limits>

using namespace std;

void Skeleton::addJoint(int joint, double x, double y, double z){
	if (joints.find(joint) != joints.end()) return;
	vector<double> tmp;
	tmp.push_back(x);
	tmp.push_back(y);
	tmp.push_back(z);
	joints.insert(make_pair(joint,tmp));
}

vector<double> Skeleton::getJoint(int joint){
	if (joints.find(joint) != joints.end())
	{
		return joints[joint];
	}
	vector<double> tmp;
	tmp.push_back(0);
	tmp.push_back(0);
	tmp.push_back(0);
	return tmp;
}

double Skeleton::getJointCord(int joint, char cord){
	if (joints.find(joint) == joints.end())
	{
		return numeric_limits<double>::max();
	}

	double cordinate;
	switch(cord){
		case Skeleton::X:
			cordinate = joints[joint][0];
			break;
		case Skeleton::Y:
			cordinate = joints[joint][1];
			break;
		case Skeleton::Z:
			cordinate = joints[joint][2];
			break;
		default:
			cordinate = numeric_limits<double>::max();
	}
	return cordinate;
}

string Skeleton::toString(int &index){
	return "";
}