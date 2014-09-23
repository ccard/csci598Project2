#! /bin/bash

rad="RAD"
hjdp="HJDP"
hod="HOD"

exe="parseSkeleton"

function usage {
	echo "./run.sh <method>"
	echo "<method> = skeletal representation options are:"
	echo "           ${rad}"
	echo "           ${hjdp}"
	echo "           ${hod}"
}

if [[ $# -ne 1 ]]; then
	usage
else
	if [[ $1 != $rad && $1 != $hjdp && $1 != $hod ]]; then
		usage
	else
		echo -n "Creating training data .... "
		train="./${exe} -tr ${1} \"./data/dataset/Train/\" human_actions.txt"
		res_train=`eval $train`
		echo "done"
		echo "Output:"
		echo $res_train

		echo -n "Creating testing data .... "
		test_p="./${exe} -te ${1} \"./data/dataset/Test/\" test_human_actions.txt"
		res_test=`eval $test_p`
		echo "done"
		echo "Output:"
		echo $res_test
	fi
fi