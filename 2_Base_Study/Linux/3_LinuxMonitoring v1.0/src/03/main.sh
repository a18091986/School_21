#!/bin/bash

chmod +x func.sh info.sh colors.sh
source ./func.sh

input_check $1 $2 $3 $4 $#
if [[ $? == 1 ]]; then
    print $(background $1) $(font $2) $(background $3) $(font $4) 
fi