#! /bin/bash

rad="RAD"
hjpd="HJPD"
hod="HOD"

radfile="rad"
radtfile="rad.t"
hjdpfile="hjpd"
hjdptfile="hjpd.t"
hodfile="hod"
hodtfile="hod.t"

exe="parseSkeleton"

function usage {
	echo "./run.sh <method>"
	echo "<method> = skeletal representation options are:"
	echo "           ${rad}"
	echo "           ${hjpd}"
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
	local cap_out=$3

	if [[ $cap_out == "n" ]]; then
		eval $stmt
	else
		echo -n "${message} .... "
		local res=`eval $stmt`
		echo "done"
		echo "Output:"
		echo $res
	fi
}

if [[ $# -ne 1 ]]; then
	usage
else
	if [[ $1 != $rad && $1 != $hjpd && $1 != $hod ]]; then
		usage
	else
		trfile=""
		tefile=""
		if [[ $1 == $rad ]]; then
			trfile=$radfile
			tefile=$radtfile
		elif [[ $1 == $hjpd ]]; then
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
		argscale="-l 0 -u 1 -s ${trfile}.range1"
		argscalet="-r ${trfile}.range1"
		argtrain="-c 8 -g 0.125"

		if [[ $1 == $rad ]]; then
			argtrain="-c 8 -g 0.125"			
		elif [[ $1 == $hjpd ]]; then
			argtrain="-c 8 -g 2"
		elif [[ $1 == $hod ]]; then
			argtrain="-c 8 -g 0.125"
		fi

		#execution commands for svm
		exscale="${scale} ${argscale} ${trfile} > ${trscale}"
		exscalet="${scale} ${argscalet} ${tefile} > ${tescale}"
		extrain="${trsvm} ${argtrain} ${trscale} > ${trfile}.log"
		expred="${pred} ${tescale} ${modelfile} ${predfile}"

		#execution commands for my program to create the skeletons data
		train="./${exe} -tr ${1} \"./data/dataset/Train/\" human_actions.txt"
		test_p="./${exe} -te ${1} \"./data/dataset/Test/\" test_human_actions.txt"
		create_confusion="./confusionmatrix.rb test_human_actions.txt ${predfile}"

		#Execution of my program and libsvm
		run "Creating training data" "${train}" 

		run "Creating testing data" "${test_p}"

		run "Scaling traing data" "${exscale}"

		run "Scaling testing data" "${exscalet}"

		run "Training svm" "${extrain}"

		run "Running prediction" "${expred}"

		run "Creating confusionmatrix (confusion_out.txt)" "${create_confusion}" "n"

		clearFiles result
		
		if [[ $result == "y" ]]; then
			rem="rm ${trfile}*"
			run "Removing files" "${rem}"
		fi
	fi
fi