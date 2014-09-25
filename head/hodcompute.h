#pragma once

/**
 * Author: Chris Card
 *
 * This class computes the HOD and temporal pyramid 
 * descriptor
 */

#ifndef HISTOGRAMS_TMP_
#define HISTOGRAMS_TMP_
	#include <map>
	#include "histogram.h"
	/**
	 * This new histogram object contains x y z diplacement histos in that order
	 */
	typedef std::map<int,std::vector<Histogram> > HistogramsTMP;

#define PI 3.14159265
#endif

#include "filehandler.h"
#include "skeleton.h"
#include "histogram.h"
#include <map>
#include <string>
#include <iterator>
#include <iostream>
#include <sstream>
#include <set>
#define _USE_MATH_DEFINES
#include <math.h>

class HODCompute
{
public: 

	const static int X= 0;
	const static int Y= 1;
	const static int Z= 2;

	HODCompute(int levels = 3);

	/**
	 * Creates the normlized histograms from the temporal pyramids
	 *
	 * @param: the set of skeletons to create the histo grams of
	 *
	 * @return: the histgram of the temporal pyramid concatinated
	 */
	Histogram createNormedHistogram(std::set<Skeleton> skels);

	/**
	 * Converts the histogram to a one d vector
	 *
	 * @param: the histogram
	 * 
	 * @return: the oned representation of the histogram
	 */
	std::vector<double> toOneD(Histogram hist);

	/**
	 * Writes the data to a file in the libsvm format
	 *
	 * @param: the filehandler to write to
	 *
	 * @return: if it was successful
	 */
	bool write(FileHandler &f, std::map<int, std::vector<std::vector<double> > > &linear_hist);
private:
	int levels,n_bins;
	double min,max;

	HistogramsTMP internal;
	
	/**
	 * This is a recursive helper function for creating the temporal pyramid
	 *
	 * @param: the current level of the pyramid
	 * @param: the set to make the current level of the pyramid with
	 *
	 * @return: the concatinated noramlized pyramid
	 */
	Histogram recursion(int level, std::set<Skeleton> skels);

	/**
	 * Calculates the trajectory histogram
	 *
	 * @param: the set of skeletons to create the histogram of
	 *
	 * @return: the 3d trajectory histogram
	 */
	Histogram trajectory(std::set<Skeleton> skels);

	/**
	 * Calculates the angle between 2d points in time
	 *
	 * @param: the first point, vec of length 2
	 * @param: the second point, vec of length 2
	 *
	 * @return the angle between 0 and 360
	 */
	 double calcAngle(std::vector<double> pt, std::vector<double> pt_1);

	/**
	 * Calaculates the magnitude between the points
	 *
	 * @param: the first point, vec of length 2
	 * @param: the second point, vec of length 2
	 *
	 * @return: the magnitude
	 */
	double calcMag(std::vector<double> pt, std::vector<double> pt_1);
};