#pragma once

/**
 * Author: Chris Card
 *
 * This class computes the histograms for the x y and z displacements
 * and turns them into a libsvm format
 */

#ifndef HISTOGRAMS_XYZ_
#define HISTOGRAMS_XYZ_
	#include <map>
	#include "histogram.h"
	/**
	 * This new histogram object contains x y z diplacement histos in that order
	 */
	typedef std::vector<Histogram> HistogramsXYZ;
#endif

#include "filehandler.h"
#include "hjpd_skeleton.h"
#include "histogram.h"
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <set>
#define _USE_MATH_DEFINES
#include <math.h>

class HJPDCompute
{
public:
	
	const static int X = 0;
	const static int Y = 1;	
	const static int Z = 2;

	HJPDCompute();
	
	/** 
	 * Computes the x y and z histograms for a set of skeletons in belonging to the
	 * same instance
	 * 
	 * @param: set of skeletons that belong to the same instances
	 *
	 * @return: a histograms object containing the theta and rho histograms
	 */
	HistogramsXYZ computeHistograms(std::set<HJPD_Skeleton> frame_skels);
	
	/**
	 * This normalizes the histograms by dividing by t
	 *
	 * @param: the histogram object
	 * @param: the number of frames
	 *
	 * @return: the normalized histograms
	 */
	HistogramsXYZ normalizeHisto(HistogramsXYZ hist, double t);

	/**
	 * Forms a one dimensional vector of the normalize histograms
	 *
	 * @param: the histogramsXYZ to make into a oned vector
	 *
	 * @return: a vector of size 5(m+n)
	 */
	 std::vector<double> toOneD(HistogramsXYZ hist);

	/**
	 * Writes the data to a file in the libsvm format
	 *
	 * @param: the filehandler to write to
	 *
	 * @return: if it was successful
	 */
	bool write(FileHandler &f, std::map<int, std::vector<std::vector<double> > > &linear_hist);

private:
	int x_bins,y_bins,z_bins;
	double min_x,max_x,min_y,max_y,min_z,max_z;

};