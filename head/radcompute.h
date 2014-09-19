#pragma once

/**
 * Author: Chris Card
 * This class handles the computation of the RAD
 * skeletons and the creation of the file that will
 * be used to train the svm
 */

#include "filehandler.h"
#include "rad_skeleton.h"
#include <map>
#include <string>
#include <set>

class RADCompute
{
public:
	RADCompute();

	/**
	 * This new histogram object contains theta histogram first and rho histogram second
	 */
	typedef std::pair<std::map<int,double>,std::map<int,double> > Histograms;
	
	/**
	 * stores the histograms 

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
	 * This normalizes the histograms
	 */
	Histograms normalizeHisto(Histograms hist, int t);

	
};