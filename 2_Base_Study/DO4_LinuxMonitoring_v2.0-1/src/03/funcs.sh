#!/bin/bash

function clean_by_log {
    logs="$(cat ../02/log.txt | awk -F'  ' '{print $1}')"
    reg='^\/'
    for i in $logs:
    do
        if [[ $i =~ $reg ]]
        then
            sudo rm -rf $i
        fi
    done
}

function clean_by_mask {
    read -p "Create mask (example: asdfgas_DDMMYY) " in
    mask=$(echo "$in" | awk -F'_' '{print $1}')
    date=$(echo "$in" | awk -F'_' '{print $2}')
    find_regexp=".*$mask.*$date.*"
    sudo find / -regex $find_regexp | sudo xargs rm -rf 
}

function clean_by_time {
    read -p "Enter start time (format: YYYY-MM-DD HH:MM) " start 
    read -p "Enter end time (format: YYYY-MM-DD HH:MM) " end

    find_regexp_files=".*[a-z]_[0-9][0-9][0-9][0-9][0-9][0-9].[a-z].*"
    find_regexp_dirs=".*_[0-9][0-9][0-9][0-9][0-9][0-9]$"

    tmp=`find / -newermt "$start" ! -newermt "$end" 2>/dev/null`
    
    for i in $tmp
    do
        if [[ $i =~ $find_regexp_files ]]; then
            sudo rm -rf $i
        fi
    done

    for i in $tmp
    do
        if [[ $i =~ $find_regexp_dirs ]]; then
            sudo rm -rf $i
        fi
    done
}