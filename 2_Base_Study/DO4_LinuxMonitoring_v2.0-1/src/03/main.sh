#!/bin/bash
chmod +x ./validate.sh ./funcs.sh

. ./funcs.sh

if [[ $# != 1 ]]; then
    echo "Script require 1 parameters"
    exit
fi

CHOICE=$1

source ./validate.sh $CHOICE

case "$CHOICE" in
1 ) clean_by_log;;
2 ) clean_by_time;;
3 ) clean_by_mask;;
esac
