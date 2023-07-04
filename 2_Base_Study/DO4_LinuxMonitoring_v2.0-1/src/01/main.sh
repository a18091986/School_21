#!/bin/bash
chmod +x ./validate.sh ./funcs.sh

if [[ $# != 6 ]]; then
    echo "Script require 6 parameters"
    exit
fi


ABS_PATH=$1
DIRECTORIES_COUNT=$2
LETTERS_FOR_DIRS=$3
FILES_COUNT=$4
LETTERS_FOR_FILES=$5
FILE_SIZE_KB=$6

source ./validate.sh $ABS_PATH \
                     $DIRECTORIES_COUNT \
                     $LETTERS_FOR_DIRS \
                     $FILES_COUNT $LETTERS_FOR_FILES \
                     $FILE_SIZE_KB

create_names_for_dirs
