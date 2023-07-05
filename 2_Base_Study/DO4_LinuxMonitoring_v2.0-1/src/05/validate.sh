#!/bin/bash

if  [[ $CHOICE > 4 || $CHOICE < 1 ]]; then
    echo -e "parameter must be between 1 and 4"
    exit
fi