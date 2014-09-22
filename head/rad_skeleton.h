#pragma once

/**
 * Author: Chris Card
 * This class repressents the RAD skeleton and the data it
 * represents theta  and d of joints
 */

#include "skeleton.h"
#include <stdlib.h>
#include <map>
#include <string>
#include <math.h>
#include <vector>

class RAD_Skeleton:
 	public Skeleton
{
public:
	const static int CENT = 1;
	const static int HEAD = 4;
	const static int HANDLEFT = 8;
	const static int HANDRIGHT = 12;
	const static int FOOTLEFT = 16;
	const static int FOOTRIGHT = 20;

 	RAD_Skeleton(Skeleton skel);
 	
 	/**
 	 * Adds a joint to the skeleton
 	 *
 	 * @param: joint index
 	 * @param: x cordinate
 	 * @param: y cordinate
 	 * @param: z cordinate
 	 */
 	void addJoint(int joint,double x, double y, double z);

 	/**
 	 * This method gets the theta and distance(rho) of each joint
 	 * where rho is the distance from body centroid and theta is the angle between two 
 	 * body extremities
 	 *
 	 * @return: map from the joint to pair<theta,rho> 
 	 */
 	std::map<int, std::pair<double,double> > getJointsThetaRho() const{ return jointThetaRho; };

private:

	std::map<int, std::pair<double,double> > jointThetaRho;

	/**
	 * Adds a theta and rho value to jointthetarho map
	 *
	 * @param: primary joint
	 * @param: joint to find angle against
	 */
	void addThetaRho(int joint1, int joint2);

	/**
	 * Calculates theta between joint1 and joint2 and rho of joint1
	 *
	 * @param: the primary joint for rho
	 * @param: the joint to use to calculate the theta with
	 * @param: stores the resulting theta
	 * @param: stores the resulting rho
	 */ 
	void calcThetaRho(int joint1, int joint2, double &theta, double &rho);

	/**
	 * Calculates the rho of a joint between the centroid and the joint
	 *
	 * @param: the joint vector to use
	 *
	 * @return: the rho value
	 */
	double calcRho(std::vector<double> joint);

	/**
	 * Calculest the theta value between two joints
	 *
	 * @param: the vector of the joint of interest
	 * @param: the vector of the joint to find the angle of
	 *
	 * @return: the theta value
	 */
	double calcTheta(std::vector<double> joint1, std::vector<double> joint2);

	/**
	 * Calculates the dot product of two vectors
	 *
	 * @param: first vector
	 * @param: the second vector
	 *
	 * @return: the dotporduct
	 */
	double dot(std::vector<double> v1, std::vector<double> v2);

	/**
	 * Calculates the vector between two points
	 *
	 * @param: joint1 start of the vector
	 * @param: joint2 the end of the vector
	 *
	 * @return: the vector between the two points
	 */
	std::vector<double> calcVec(std::vector<double> joint1, std::vector<double> joint2);
};	