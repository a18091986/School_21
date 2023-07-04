function create_names_for_dirs {
    touch log.txt
    for (( number=0; number <$count_dirs; number++ ))
    do
        dir_name=""
        if [[ ${#letters_dirs} -lt 4 ]]
        then
            create_dir_with_little_name
            create_files
        else
            create_dir_with_big_name
            create_files
        fi
    done
}

function create_dir_with_little_name {
    count=${#letters_dirs}
    for (( i=0; i<5-count; i++ ))
    do
        dir_name+="$(echo ${letters_dirs:0:1})"
    done
    dir_name+="$(echo ${letters_dirs:1:${#letters_dirs}})"
    dir_name+=$number
    dir_name+="_"
    dir_name+=$(date +"%d%m%y")
    mkdir $dir_name
    echo $path"/"$dir_name --- $(date +'%e.%m.%Y') ---  >> log.txt
}