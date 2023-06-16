#!/bin/bash

chmod +x func.sh print.sh
reg_exp='.*/$'
START=$(date +%s%N)

# source ./print.sh

if [[  $# != 1 ]]; then
    echo "Script require 1 parameter"
elif [[ ! -d $1 ]]; then
    echo "directory not exists"
elif [[ $1 =~ $reg_exp ]]; then
    source ./print.sh $1
else
    echo "path must end with /"
fi

END=$(date +%s%N)
DIFF_INT=$((($END - $START)/1000000000))
DIFF=`echo "scale=1; ($END - $START)/1000000000" | bc`

if [[ DIFF_INT -eq 0 ]]; then
    echo "Script execution time (in seconds) = 0$DIFF"
else
    echo "Script execution time (in seconds) = $DIFF"
fi





