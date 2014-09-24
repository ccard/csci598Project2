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
#endif

#include "filehandler.h"
#include "skeleton.h"
#include "histogram.h"
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <set>
#define _USE_MATH_DEFINES
#include <math.h>

class HOD
{
public:
	HOD(int levels = 3);

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
};