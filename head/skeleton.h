#pragma once

/**
 * This file contains the full
 * skeleton information and is not transformed 
 * into any other representation
 */
 #include <stdlib.h>
 #include <map>
 #include <string>
 #include <vector>

 class Skeleton
 {
 public:
 	const static char X = 'x';
 	const static char Y = 'y';
 	const static char Z = 'z';
 	Skeleton(int frame = -1){
 		this->frame = frame;
 	};

 	bool operator< (const Skeleton &other){
 		return frame < other.frame;
 	};

 	bool operator() (const Skeleton &rhs,const Skeleton &lhs){
 		return rhs.frame < lhs.frame;
 	};

 	int getFrame(){ return frame; };

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
 	 * Returns the x y and z cordites of the joint
 	 *
 	 * @param: the joint index
 	 *
 	 * @return: a tuple containing the <x,y,z> cords in that order
 	 */
 	std::vector<double> getJoint(int joint);

 	/**
 	 * Gets a joints specific x y or z cord
 	 *
 	 * @param: joint index
 	 * @param: cordinated desired
 	 *
 	 * @return: the value of the coridnate
 	 */
 	double getJointCord(int joint, char cord);

 	std::string toString(int &index);

 protected:
 	int frame;
 	std::map<int,std::vector<double> > joints;
 };