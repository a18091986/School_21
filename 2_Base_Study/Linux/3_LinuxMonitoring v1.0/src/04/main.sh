#!/bin/bash

chmod +x func.sh info.sh colors.sh
source ./func.sh
source ./conf
source ./default

default_flags_arr=(0 0 0 0)

if [[ $column1_background == "" && $column1_font_color == "" ]]; then
    column1_background=$column1_background_default;
    column1_font_color=$column1_font_color_default;
    default_flags_arr[0]=1
    default_flags_arr[1]=1
fi

if [[ $column2_background == "" && $column2_font_color == "" ]]; then
    column2_background=$column2_background_default;
    column2_font_color=$column2_font_color_default;
    default_flags_arr[2]=1
    default_flags_arr[3]=1
fi

if [[ $column1_background == "" ]]; then
    if [[ $column1_font_color == $column1_font_color_default  ]]; then
        column1_background=$column1_background_default;
    else
        column1_background=$column1_font_color_default;
    fi
    default_flags_arr[0]=1
fi

if [[ $column1_font_color == "" ]]; then
    if [[ $column1_background == $column1_background_default  ]]; then
        column1_font_color=$column1_font_color_default;
    else
        column1_font_color=$column1_background_default;
    fi
    default_flags_arr[1]=1
fi

if [[ $column2_background == "" ]]; then
    if [[ $column2_font_color == $column2_font_color_default  ]]; then
        column2_background=$column2_background_default;
    else
        column2_background=$column2_font_color_default;
    fi
    default_flags_arr[2]=1
fi

if [[ $column2_font_color == "" ]]; then
    if [[ $column2_background == $column2_background_default  ]]; then
        column2_font_color=$column2_font_color_default;
    else
        column2_font_color=$column2_background_default;
    fi
    default_flags_arr[3]=1
fi

color_arr=($column1_background $column1_font_color $column2_background $column2_font_color)

input_check $# \
            $column1_background \
            $column1_font_color \
            $column2_background \
            $column2_font_color


if [[ $? == 1 ]]; then
    print $(background $column1_background) \
          $(font $column1_font_color) \
          $(background $column2_background) \
          $(font $column2_font_color)

    print_colors ${color_arr[0]} ${color_arr[1]} ${color_arr[2]} ${color_arr[3]} \
                 ${default_flags_arr[0]} ${default_flags_arr[1]} \
                 ${default_flags_arr[2]} ${default_flags_arr[3]}
fi

    

