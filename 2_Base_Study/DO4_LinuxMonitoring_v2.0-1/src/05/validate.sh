#!/bin/bash

if  [[ $CHOICE > 3 || $CHOICE < 1 ]]; then
    echo -e "parameter must be between 1 and 3"
    exit
fi