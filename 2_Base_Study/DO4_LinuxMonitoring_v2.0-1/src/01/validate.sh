#!/bin/bash

error_flag=0

regexp_dir_or_files_number='^[+]?[0-9]+$'
regexp_file_size='^[0-9]+(\.[0-9]+)?kb$'
regexp_letters_for_dirs='^[a-z]{1,7}$'
regexp_letters_for_file='^[a-z]{1,7}[.]{1}[a-z]{1,3}$'

# проверка существования пути, переданного в первом параметре
if ! [[ -d $ABS_PATH ]]; then
    echo -e "Error in first parameter: $ABS_PATH \n \
    path not exists or not a directory"
    error_flag=1
fi
# проверка числа папок
if ! [[ $DIRECTORIES_COUNT =~ $regexp_dir_or_files_number ]]; then
    echo -e "Error in second parameter: $DIRECTORIES_COUNT \n \
    dir count must be positive integer number"
    error_flag=1
fi
# проверка списка букв для названия папок (количества и состава)
if ! [[ $LETTERS_FOR_DIRS =~ $regexp_letters_for_dirs ]]; then
    echo -e "Error in third parameter: $LETTERS_FOR_DIRS \n \
    - count of letters for dirs names must be <= 7 \n \
    - dir names must consist of english letters only"
    error_flag=1
fi
# проверка числа файлов
if ! [[ $FILES_COUNT =~ $regexp_dir_or_files_number ]]; then
    echo -e "Error in fourth parameter: $FILES_COUNT \n \
    files count must be positive integer number"
    error_flag=1
fi

# проверка списка букв для названия файлов и расширения (количества и состава)
if ! [[ $LETTERS_FOR_FILES =~ $regexp_letters_for_file ]]; then
    echo -e "Error in fifth parameter: $LETTERS_FOR_FILES \n \
    - it must be 1..7 symbols in name \n \
    - it must be 1..3 symbols in extension \n \
    - name end extension must be separated by '.'"
    error_flag=1
fi

# проверка размера файлов 
if ! [[ $FILE_SIZE_KB =~ $regexp_file_size ]]; then
    echo -e "Error in six parameter: $FILE_SIZE_KB \n \
    - it must be positive integer or float number"
    error_flag=1
else
    size=$(echo "$FILE_SIZE_KB" | awk '{split($0,a,"kb"); print a[1]}') 
    if [[ $(echo "${FILE_SIZE_KB} > 100.0"|bc) -eq 1 ]]; then
    echo -e "Error in six parameter: $FILE_SIZE_KB \n \
    - file size must be 100 kb or less"
    fi
fi


if [[ $error_flag == 1 ]]; then
    echo "erorr, exit"
    exit
fi