#!/bin/bash

closed_dirs_regexp='\/[s]?bin'

function create {
    while [[ $DIRECTORIES_COUNT_CREATED != $DIRECTORIES_COUNT ]]
    do
        ABS_PATH=$start_path
        cd $ABS_PATH
        choose_dir_path
    done
}

function choose_dir_path {
    # echo "$DIRECTORIES_COUNT_CREATED"
    random_num=$(echo $(( $RANDOM % 2 )))
    dirs_in_cur_dir=$(echo $(ls -l -d $ABS_PATH/* 2>/dev/null | wc -l))
    dir_name=""

    
    if [[ $dirs_in_cur_dir == 1 || $dirs_in_cur_dir == 0 || $random_num == 0  ]]; then :
        if [[ $letters_for_dirs_count < 5 ]]; then
            for (( i = 0; i < 6 - $letters_for_dirs_count; i++ )) do 
                dir_name+=${LETTERS_FOR_DIRS:0:1}
            done
            for (( j = 1; j < $dirs_in_cur_dir + 2; j++ )) do 
                dir_name+=${LETTERS_FOR_DIRS:0:$letters_for_dirs_count}
            done
        else
            dir_name+=${LETTERS_FOR_DIRS}
            for (( j = 1; j < $dirs_in_cur_dir + 2; j++ )) do 
                dir_name+=${LETTERS_FOR_DIRS:$letters_for_dirs_count-1}
            done
        fi
        DATE_PART=$(date +%D | awk -F / '{print $2$1$3}')   
        dir_name+="_$DATE_PART"
        if ! [[ $ABS_PATH/$dir_name =~ $closed_dirs_regexp ]]
        then
            sudo mkdir $ABS_PATH/$dir_name 2>/dev/null
            if [[ $(echo "$?") == 0 ]]; then 
                DIRECTORIES_COUNT_CREATED=$(($DIRECTORIES_COUNT_CREATED+1))
                cd $work_dir
                echo $DIRECTORIES_COUNT_CREATED "|" $ABS_PATH/$dir_name "|" $(date +'%e.%m.%Y') "|" >> log.txt
                create_files
            fi
        fi 
    else
        rand_dir_choice=$(echo $(( $RANDOM % $dirs_in_cur_dir )))        
        ABS_PATH="$( ls -l -d $ABS_PATH/* 2>/dev/null | awk '{print $9}' | awk -v "r=$rand_dir_choice" '(NR==r)')"
        if [[ $ABS_PATH ]]; then
            choose_dir_path
        else 
            ABS_PATH=$start_path
            choose_dir_path
        fi        
    fi
}
        
function create_files {
    FILES_COUNT=$(echo $(( 1 + $RANDOM % 100 )))
    for (( num = 0; num < $FILES_COUNT; num++ ))
    do
        file_name=""
        if [[ $letters_for_files_count < 5 ]]; then
            for (( i = 0; i < 6 - $letters_for_files_count; i++ )) do 
                file_name+=${LETTERS_FOR_FILES_NAMES:0:1}
            done
            for (( j = 1; j < $num + 2; j++ )) do 
                file_name+=${LETTERS_FOR_FILES_NAMES:0:$letters_for_files_count}
            done
        else
            file_name+=${LETTERS_FOR_FILES_NAMES}
            for (( j = 1; j < $num + 2; j++ )) do 
                file_name+=${LETTERS_FOR_FILES_NAMES:$letters_for_files_count-1}
            done
        fi
        DATE_PART=$(date +%D | awk -F / '{print $2$1$3}')   
        file_name+="_$DATE_PART.$FILE_EXT"
        sudo fallocate -l $size"MB" $ABS_PATH/$dir_name/$file_name 2>/dev/null
        FREE_SPACE_MB=$(df -h / |  head -2 | tail +2 | awk '{printf("%d", $4)}')
        if [[ $FREE_SPACE_MB -le 1 ]]; then 
            echo "Memory limit exceeded"
            
            end_nano=$(date +'%s%N')
            end_time=$(date +'%Y-%m-%d %H:%M:%S')
            DIFF=$((( $end_nano - $start_nano ) / 1000000 ))
            echo "End time: $end_time" > log.txt
            echo "Script work duration: $DIF" > log.txt

            echo -e "Start time: $start_time\nEnd time: $end_time\nDuration: $DIFF ms"
            exit
        fi
        echo $ABS_PATH$dir_name/$file_name "|" $(date +'%e.%m.%Y') "|" >> log.txt    
    done
}


