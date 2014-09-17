#! /bin/bash

function check_command {
red='\e[0;31m' #red color for echo
green='\e[0;32m' #green color for echo
NC='\e[0m' #no color for echo

passed="${green}passed${NC}"
failed="${red}failed${NC}"

echo -n "Checking for ${1} ..... "
if ! type $1 &> /dev/null; then
	echo -e $failed
else
	echo -e $passed
fi
}

echo "Starting environmental checks ...."

check_command "g++"