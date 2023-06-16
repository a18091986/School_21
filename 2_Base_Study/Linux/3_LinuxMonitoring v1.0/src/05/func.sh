#!\bin\bash

top_10_exe() {
    exe_files_top_10=`sudo find $1 -type f -executable -exec du -h {} \; 2>/dev/null | sort -rh | head -10`
    exe_files_top_count=`echo "$exe_files_top_10" | wc -l`
    idx=0
    while [[ $idx != $exe_files_top_count ]]
    do
        path=`echo "$exe_files_top_10" | awk '{print $2}' | awk "NR==$(( $idx + 1 ))"`
        size=`echo "$exe_files_top_10" | awk '{print $1}' | awk "NR==$(( $idx + 1 ))"`            
        md=`md5sum $path | awk '{print $1}'`

        printf "$(( $idx + 1 )) - $path, $size, $md\n"
        idx=$(( $idx + 1 ))
    done
}

