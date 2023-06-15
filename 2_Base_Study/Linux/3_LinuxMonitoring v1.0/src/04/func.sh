#!/bin/bash

source ./info.sh
source ./colors.sh

font() {
    colors=("$CLEAR", "$F_WHITE" "$F_RED" "$F_GREEN" "$F_BLUE" "$F_PURPLE" "$F_BLACK");
    echo ${colors[$1]};
}

background() {
    colors=("$CLEAR", "$B_WHITE" "$B_RED" "$B_GREEN" "$B_BLUE" "$B_PURPLE" "$B_BLACK");
    echo ${colors[$1]};
}

color() {
    colors=("" "white" "red" "green" "blue" "purple" "black")
    echo ${colors[$1]}   
}

print () {
    printf "${1}${2}HOSTNAME =${3}${4} $HOSTNAME${CLEAR}\n"
    printf "${1}${2}TIMEZONE =${3}${4} $TIMEZONE${CLEAR}\n"
    printf "${1}${2}USER =${3}${4} $USER${CLEAR}\n"
    printf "${1}${2}OS =${3}${4} $OS${CLEAR}\n"
    printf "${1}${2}DATE =${3}${4} $DATE${CLEAR}\n"
    printf "${1}${2}UPTIME =${3}${4} $UPTIME${CLEAR}\n"
    printf "${1}${2}UPTIME_SEC =${3}${4} $UPTIME_SEC${CLEAR}\n"
    printf "${1}${2}IP =${3}${4} $IP${CLEAR}\n"
    printf "${1}${2}MASK =${3}${4} $MASK${CLEAR}\n"
    printf "${1}${2}GATEWAY =${3}${4} $GATEWAY${CLEAR}\n"
    printf "${1}${2}RAM_TOTAL =${3}${4} $RAM_TOTAL${CLEAR}\n"
    printf "${1}${2}RAM_USED =${3}${4} $RAM_USED${CLEAR}\n"
    printf "${1}${2}RAM_FREE =${3}${4} $RAM_FREE${CLEAR}\n"
    printf "${1}${2}SPACE_ROOT =${3}${4} $SPACE_ROOT${CLEAR}\n"
    printf "${1}${2}SPACE_ROOT_USED =${3}${4} $SPACE_ROOT_USED${CLEAR}\n"
    printf "${1}${2}SPACE_ROOT_FREE =${3}${4} $SPACE_ROOT_FREE${CLEAR}\n\n"
}

print_colors() {

    if [[ $5 == 0 ]]; then
        printf "Column 1 background = $1 ($(color $1))\n"
    else
        printf "Column 1 background = default ($(color $1))\n"
    fi
    if [[ $6 == 0 ]]; then
        printf "Column 1 font color = $2 ($(color $2))\n"
    else
        printf "Column 1 font color = default ($(color $2))\n"
    fi
    if [[ $7 == 0 ]]; then
        printf "Column 2 background = $3 ($(color $3))\n"
    else
        printf "Column 2 background = default ($(color $3))\n"
    fi
    if [[ $8 == 0 ]]; then
        printf "Column 2 font color = $4 ($(color $4))\n"
    else
        printf "Column 2 font color = default ($(color $4))\n"
    fi
}

input_check() {
    reg_exp='[1-6]'    
    if [[ $1 != 0 ]]; then
        echo "Incorrect parameters count - start script without parameters, repeat"
    elif [[ $2 != $reg_exp ]] || [[ $3 != $reg_exp ]] || [[ $4 != $reg_exp ]] || [[ $5 != $reg_exp ]]; then
        echo "Parameters values not in range 1-6, repeat"
    elif [[ $2 == $3 ]] || [[ $4 == $5 ]]; then
        echo "Font and background are same, repeat"
    else
        return 1
    fi
}

