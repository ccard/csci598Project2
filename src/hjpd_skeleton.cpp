#include "hjpd_skeleton.h"

using namespace std;

HJPD_Skeleton::HJPD_Skeleton(Skeleton skel, int refjoint){
	frame = skel.getFrame();
	this->refjoint = refjoint;

	for (int i = 1; i <= 20; ++i) {
		addJoint(i,skel.getJoint(i));
	}

	calcDisplace();
}

void HJPD_Skeleton::addJoint(int joint, vector<double> xyz){
	if(joints.find(joint) != joints.end()) return;

	if (xyz.size() != 3) return;
	if(xyz[0] == 0 && xyz[1] == 0 && xyz[2] == 0) return;

	joints.insert(make_pair(joint,xyz));	
}

void HJPD_Skeleton::calcDisplace(){
	vector<double> refj = getJoint(refjoint);

	for (map<int, vector<double> >::iterator i = joints.begin(); i != joints.end(); ++i){
		if (i->first == refjoint) continue;
		displacements.insert(i->first,calcVec(refj,i->second));
	}
}

vector<double> HJPD_Skeleton::calcVec(vector<double> joint1, vector<double> joint2){
	vector<double> vec_12;
	vec_12.push_back(joint2[0]-joint1[0]);
	vec_12.push_back(joint2[1]-joint1[1]);
	vec_12.push_back(joint2[2]-joint1[2]);
	return vec_12;
}