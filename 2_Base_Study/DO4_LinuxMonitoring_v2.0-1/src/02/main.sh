#!/bin/bash
chmod +x ./validate.sh ./funcs.sh

work_dir=$(pwd)
start_path="/test_dir"

. ./funcs.sh

if [[ $# != 3 ]]; then
    echo "Script require 3 parameters"
    exit
fi


LETTERS_FOR_DIRS=$1
LETTERS_FOR_FILES=$2
FILE_SIZE_MB=$3

source ./validate.sh $LETTERS_FOR_DIRS \
                     $LETTERS_FOR_FILES \
                     $FILE_SIZE_MB

sudo rm -rf /test_dir/*
rm log.txt
touch log.txt

LETTERS_FOR_FILES_NAMES=$(echo "$LETTERS_FOR_FILES" | awk '{split($0,a,"."); print a[1]}')
FILE_EXT=$(echo "$LETTERS_FOR_FILES" | awk '{split($0,a,"."); print a[2]}')
letters_for_dirs_count=${#LETTERS_FOR_DIRS}
letters_for_files_count=${#LETTERS_FOR_FILES_NAMES}

DIRECTORIES_COUNT=$(echo $(( 1 + $RANDOM % 100 )))
DIRECTORIES_COUNT_CREATED=0

start_nano=$(date +'%s%N')
start_time=$(date +'%Y-%m-%d %H:%M:%S')
echo "Start time: $start_time" > log.txt

create

end_nano=$(date +'%s%N')
end_time=$(date +'%Y-%m-%d %H:%M:%S')
DIFF=$((( $end_nano - $start_nano ) / 1000000 ))
echo "End time: $end_time" > log.txt
echo "Script work duration: $DIF" > log.txt

echo -e "Start time: $start_time\nEnd time: $end_time\nDuration: $DIFF ms"
