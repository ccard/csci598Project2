#pragma once

/**
 * Author: Chris Card
 * This class handles the computation of the RAD
 * skeletons and the creation of the file that will
 * be used to train the svm
 */

#ifndef HISTOGRAMS_H_
#define HISTOGRAMS_H_
	#include <map>
	#include "histogram.h"
	/**
	 * This new histogram object contains theta histogram first and rho histogram second
	 */
	typedef std::pair<std::map<int,Histogram>,std::map<int,Histogram> > Histograms;
#endif

#include "filehandler.h"
#include "rad_skeleton.h"
#include "histogram.h"
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <set>
#define _USE_MATH_DEFINES
#include <math.h>

class RADCompute
{
public:
	RADCompute();

	/**
	 * Computes the rho and theta histograms for a set of skeletons in belonging to the
	 * same instance
	 * 
	 * @param: set of skeletons that belong to the same instances
	 *
	 * @return: a histograms object containing the theta and rho histograms
	 */
	Histograms computeHistograms(std::set<RAD_Skeleton> frame_skels);
	
	/**
	 * This normalizes the histograms by dividing by t
	 *
	 * @param: the histogram object
	 * @param: the number of frames
	 *
	 * @return: the normalized histograms
	 */
	Histograms normalizeHisto(Histograms hist, int t);

	/**
	 * Forms a one dimensional vector of the normalize histograms
	 *
	 * @param: the histograms to make into a oned vector
	 *
	 * @return: a vector of size 5(m+n)
	 */
	 std::vector<double> toOneD(Histograms hist);

	/**
	 * Writes the data to a file in the libsvm format
	 *
	 * @param: the filehandler to write to
	 *
	 * @return: if it was successful
	 */
	bool write(FileHandler &f, std::map<int, std::vector<std::vector<double> > > &linear_hist);

private:
	int n_d_bins, m_t_bins;
	double min_d, max_d, min_t, max_t;
};