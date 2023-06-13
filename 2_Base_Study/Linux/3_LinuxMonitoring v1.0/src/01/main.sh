#!/bin/bash

reg_exp='^[+-]?[0-9]+(.[0-9]+)?$'

if [[ $# == 1 ]]; then
    if [[ $1 =~ $reg_exp ]]; then
        echo "Incorrect input: not string"
    else
        echo $1
    fi
else
    echo "Incorrect input: single argument required"
fi        