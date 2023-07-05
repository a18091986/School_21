#!/bin/bash
chmod +x ./validate.sh ./funcs.sh

. ./funcs.sh

logs=$(find ../04/logs/ -type f)

if [[ $# != 1 ]]; then
    echo "Script require 1 parameters"
    exit
fi

CHOICE=$1

source ./validate.sh $CHOICE

case "$CHOICE" in
1 ) sort_answer_code;;
2 ) uniq_ip;;
3 ) errors_requests;;
4 ) uniq_ip_among_errors_requests;;
esac