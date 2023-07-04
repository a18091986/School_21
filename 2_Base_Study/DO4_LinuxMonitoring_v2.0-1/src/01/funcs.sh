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
            :
        fi
        DATE_PART=$(date +%D | awk -F / '{print $2$1$3}')   
        dir_name+="_$DATE_PART"
        mkdir $dir_name
        # echo $path"/"$dir_name --- $(date +'%e.%m.%Y') ---  >> log.txt    
    done
}

# function create_dir_with_little_name {
#     count=${#letters_dirs}
#     for (( i=0; i<5-count; i++ ))
#     do
#         dir_name+="$(echo ${letters_dirs:0:1})"
#     done
#     dir_name+="$(echo ${letters_dirs:1:${#letters_dirs}})"
#     dir_name+=$number
#     dir_name+=$(date +"%d%m%y")
#     mkdir $dir_name
#     echo $path"/"$dir_name --- $(date +'%e.%m.%Y') ---  >> log.txt
# }

