#!/bin/bash

function sort_answer_code {
    awk '{ print $0 }' $logs | sort -k 8 | cat -n
}

function uniq_ip {
    awk '{ print $1 }' $logs | uniq | sort | cat -n
}

function errors_requests {
    awk '{ if ($9 >= 400) print }' $logs | sort -k 3 | cat -n
}

function uniq_ip_among_errors_requests {
    awk '{ if ($9 >= 400) print $1 }' $logs | uniq | sort -k 1 | cat -n
}