function create_dirs {
    for (( n = 0; n < $DIRECTORIES_COUNT; n++ ))
    do
        dir_name=""
        if [[ $letters_for_dirs_count < 4 ]]; then
            for (( i = 0; i < 5 - $letters_for_dirs_count; i++ )) do 
                dir_name+=${LETTERS_FOR_DIRS:0:1}
            done
            for (( j = 1; j < $n + 2; j++ )) do 
                dir_name+=${LETTERS_FOR_DIRS:1:letters_for_dirs_count}
            done
        else
            dir_name+=${LETTERS_FOR_DIRS}
            for (( j = 1; j < $n + 2; j++ )) do 
                dir_name+=${LETTERS_FOR_DIRS:-1:}
            done
        fi
        DATE_PART=$(date +%D | awk -F / '{print $2$1$3}')   
        dir_name+="_$DATE_PART"
        mkdir $ABS_PATH/$dir_name
        echo $ABS_PATH"/"$dir_name "|" $(date +'%e.%m.%Y') "|" >> log.txt    
    done
}


