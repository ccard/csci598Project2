#pragma once

/**
 * Author: Chris Card
 * 
 * This class stores the skeletel representation of
 * the HJPD
 */

#include "skeleton.h"
#include <map>
#include <vector>
#include <math.h>
#include <string>

class HJPD_Skeleton:
	public Skeleton
{
public:

	/**
	 * Contructor
	 *
	 * @param: the skeletion to create this object from
	 * @param: reftjoint to calculate the displacement from default is 3 the torso
	 */
	HJPD_Skeleton(Skeleton skel,int refjoint = 3);

 	/**
 	 * Adds a joint to the skeleton
 	 *
 	 * @param: the joint
 	 * @param: vec of x y z cords in that order
 	 */
 	void addJoint(int joint, std::vector<double> xyz);

 	/**
 	 * This returns the displace ments for each joint excluding the
 	 * the reference joint
 	 *
 	 * @return: map of joints to their displacements
 	 */
 	 std::map<int,std::vector<double> > getDisplace() const { return displacements; };
private:
	std::map<int,std::vector<double> > displacements
	int refjoint;

	/**
	 * Calculates the joint displacements from the reference
	 * joint
	 */
	void calcDisplace();

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