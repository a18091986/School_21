#!/bin/bash
chmod +x ./validate.sh ./funcs.sh

. ./funcs.sh

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

rm -r /home/behappyman/out/*

touch log.txt
LETTERS_FOR_FILES_NAMES=$(echo "$LETTERS_FOR_FILES" | awk '{split($0,a,"."); print a[1]}')
echo "$LETTERS_FOR_FILES_NAMES"
FILE_EXT=$(echo "$LETTERS_FOR_FILES" | awk '{split($0,a,"."); print a[2]}')
echo "$FILE_EXT"
letters_for_dirs_count=${#LETTERS_FOR_DIRS}
letters_for_files_count=${#LETTERS_FOR_FILES}
create

