#include "rad_skeleton.h"

using namespace std;

RAD_Skeleton::RAD_Skeleton(Skeleton skel){
	vector<double> xyz;
	xyz = skel.getJoint(CENT);
	addJoint(CENT,xyz[0],xyz[1],xyz[2]);

	xyz = skel.getJoint(HEAD);
	addJoint(HEAD,xyz[0],xyz[1],xyz[2]);

	xyz = skel.getJoint(HANDLEFT);
	addJoint(HANDLEFT,xyz[0],xyz[1],xyz[2]);

	xyz = skel.getJoint(HANDRIGHT);
	addJoint(HANDRIGHT,xyz[0],xyz[1],xyz[2]);

	xyz = skel.getJoint(FOOTLEFT);
	addJoint(FOOTLEFT,xyz[0],xyz[1],xyz[2]);

	xyz = skel.getJoint(FOOTRIGHT);
	addJoint(FOOTRIGHT,xyz[0],xyz[1],xyz[2]);

	double rho,theta;
	pair<double,double> tmp_thrh;

	addThetaRho(HEAD,HANDLEFT);
	addThetaRho(HANDLEFT,FOOTLEFT);
	addThetaRho(FOOTLEFT,FOOTRIGHT);
	addThetaRho(FOOTRIGHT,HANDRIGHT);
	addThetaRho(HANDRIGHT,HEAD);
}

void RAD_Skeleton::addJoint(int joint,double x, double y, double z){
	switch(joint){
		case CENT: case HEAD: case HANDLEFT: case HANDRIGHT: case FOOTRIGHT: case FOOTLEFT:
			break;
		default:
			return;
	}
	if(joints.find(joint) != joints.end()) return;

	vector<double> tmp_xyz;
	tmp_xyz.push_back(x);
	tmp_xyz.push_back(y);
	tmp_xyz.push_back(z);
	joints.insert(make_pair(joint,tmp_xyz));
}

void RAD_Skeleton::addThetaRho(int joint1, int joint2){
	if (jointThetaRho.find(joint1) != jointThetaRho.end()) return;
	double rho,theta;
	pair<double,double> tmp_thrh;

	calcThetaRho(HEAD,HANDLEFT,theta,rho);
	tmp_thrh = make_pair(theta,rho);
	jointThetaRho.insert(make_pair(HEAD,tmp_thrh));
}

void RAD_Skeleton::calcThetaRho(int joint1, int joint2, double &theta, double &rho){
	vector<double> j1,j2;
	j1 = calcVec(getJoint(CENT),getJoint(joint1));
	j2 = calcVec(getJoint(CENT),getJoint(joint2));
	rho = calcRho(j1);
	theta = calcTheta(j1,j2);
}

double RAD_Skeleton::calcRho(vector<double> joint){
	double x_2 = pow(joint[0],2);
	double y_2 = pow(joint[1],2);
	double z_2 = pow(joint[3],2);
	return sqrt(x_2+y_2+z_2);
}

double RAD_Skeleton::calcTheta(vector<double> joint1, vector<double> joint2){
	double numerator = dot(joint1,joint2);
	double denominator = calcRho(joint1)*calcRho(joint2);
	return acos(numerator/denominator);
}

double RAD_Skeleton::dot(vector<double> v1, vector<double> v2){
	vector<double> d;
	d.push_back(v1[0]*v2[0]);	
	d.push_back(v1[1]*v2[1]);
	d.push_back(v1[2]*v2[2]);
	return (d[0]+d[1]+d[2]);
}

vector<double> RAD_Skeleton::calcVec(vector<double> joint1, vector<double> joint2){
	vector<double> vec_12;
	vec_12.push_back(joint2[0]-joint1[0]);
	vec_12.push_back(joint2[1]-joint1[1]);
	vec_12.push_back(joint2[2]-joint1[2]);
	return vec_12;
}