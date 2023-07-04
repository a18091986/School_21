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

cd ~/GIT/School_21/2_Base_Study/DO4_LinuxMonitoring_v2.0-1/src/01/out/
rm -rf *

touch log.txt
letters_for_dirs_count=${#LETTERS_FOR_DIRS}

for (( i = 0; i < DIRECTORIES_COUNT; i++ )) do
    create_dirs
    # create_files
done

