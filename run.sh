#! /bin/bash

rad="RAD"
hjdp="HJDP"
hod="HOD"

radfile="rad"
radtfile="rad.t"
hjdpfile="hjdp"
hjdptfile="hjdp.t"
hodfile="hod"
hodtfile="hod.t"

exe="parseSkeleton"

function usage {
	echo "./run.sh <method>"
	echo "<method> = skeletal representation options are:"
	echo "           ${rad}"
	echo "           ${hjdp}"
	echo "           ${hod}"
}

function clearFiles {
	local __resvar=$1
	read -p "Delete output files [y or n]:" -n 1 -r
	echo
	if [[ $REPLY =~ ^[Yy]$ ]]; then
		eval $__resvar="'y'"
	else
		eval $__resvar="'n'"
	fi
}

function run {
	local message=$1
	local stmt=$2

	echo -n "${message} .... "
	local res=`eval $stmt`
	echo "done"
	echo "Output:"
	echo $res
}

if [[ $# -ne 1 ]]; then
	usage
else
	if [[ $1 != $rad && $1 != $hjdp && $1 != $hod ]]; then
		usage
	else
		trfile=""
		tefile=""
		if [[ $1 == $rad ]]; then
			trfile=$radfile
			tefile=$radtfile
		elif [[ $1 == $hjdp ]]; then
			trfile=$hjdpfile
			tefile=$hjdptfile
		elif [[ $1 == $hod ]]; then
			trfile=$hodfile
			tefile=$hodtfile
		fi

		#scaled training files
		trscale="${trfile}.scale"
		tescale="${tefile}.scale"
		modelfile="${trscale}.model"
		predfile="${tefile}.predict"

		#commands for svm
		scale="svm-scale"
		pred="svm-predict"
		trsvm="svm-train"

		#flags for svm
		argscale="-l -1 -u 1 -s ${trfile}.range1"
		argscalet="-r ${trfile}.range1"
		argtrain="-c 2 -g 2"

		#execution commands for svm
		exscale="${scale} ${argscale} ${trfile} > ${trscale}"
		exscalet="${scale} ${argscalet} ${tefile} > ${tescale}"
		extrain="${trsvm} ${argtrain} ${trscale} > ${trfile}.log"
		expred="${pred} ${tescale} ${modelfile} ${predfile}"

		#execution commands for my program to create the skeletons data
		train="./${exe} -tr ${1} \"./data/dataset/Train/\" human_actions.txt"
		test_p="./${exe} -te ${1} \"./data/dataset/Test/\" test_human_actions.txt"

		#Execution of my program and libsvm
		run "Creating training data" "${train}" 

		run "Creating testing data" "${test_p}"

		run "Scaling traing data" "${exscale}"

		run "Scaling testing data" "${exscalet}"

		run "Training svm" "${extrain}"

		run "Running prediction" "${expred}"

		clearFiles result
		
		if [[ $result == "y" ]]; then
			rem="rm ${trfile}*"
			run "Removing files" "${rem}"
		fi
	fi
fi