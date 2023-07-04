function create {
    for (( n = 0; n < $DIRECTORIES_COUNT; n++ ))
    do
        dir_name=""
        if [[ $letters_for_dirs_count < 4 ]]; then
            for (( i = 0; i < 5 - $letters_for_dirs_count; i++ )) do 
                dir_name+=${LETTERS_FOR_DIRS:0:1}
            done
            for (( j = 1; j < $n + 2; j++ )) do 
                dir_name+=${LETTERS_FOR_DIRS:0:$letters_for_dirs_count}
            done
        else
            dir_name+=${LETTERS_FOR_DIRS}
            for (( j = 1; j < $n + 2; j++ )) do 
                dir_name+=${LETTERS_FOR_DIRS:$letters_for_dirs_count-1}
            done
        fi
        DATE_PART=$(date +%D | awk -F / '{print $2$1$3}')   
        dir_name+="_$DATE_PART"
        mkdir $ABS_PATH/$dir_name
        echo $ABS_PATH$dir_name "|" $(date +'%e.%m.%Y') "|" >> log.txt
        create_files 
    done
}

function create_files {
    
    for (( num = 0; num < $FILES_COUNT; num++ ))
    do
        file_name=""
        if [[ $letters_for_files_count < 4 ]]; then
            for (( i = 0; i < 5 - $letters_for_files_count; i++ )) do 
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
          
        fallocate -l $FILE_SIZE_KB"KB" $ABS_PATH/$dir_name/$file_name
        FREE_SPACE_MB=$(df / |  head -2 | tail +2 | awk '{printf("%d", $4)}')
        if [[ $FREE_SPACE_MB -le 1048576 ]]; then 
            echo "Memory limit exceeded"
            exit 1
        fi
        echo $ABS_PATH$dir_name/$file_name "|" $(date +'%e.%m.%Y') "|" >> log.txt    
    done
}


