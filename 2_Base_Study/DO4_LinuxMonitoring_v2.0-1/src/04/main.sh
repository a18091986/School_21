#!/bin/bash

. ./funcs.sh

# 200 - OK
# 201 - CREATED
# 400 - BAD_REQUEST
# 401 - UNAUTHORIZED
# 403 - FORBIDDEN
# 404 - NOT_FOUND
# 500 - INTERNAL_SERVER_ERROR
# 501 - NOT_IMPLEMENTED
# 502 - BAD_GATEWAY
# 503 - SERVICE_UNAVAILABLE

date="$(date +%Y)-$(date +%m)-$(date +%d) 00:00:00 $(date +%z)"

if ! [[ -d ./logs ]]; then
    mkdir logs
fi

seconds_plus=0

for (( i = 0; i < 5; i++ ))
do
    for (( j = 0; j < $(gen_num 900 100); j++ ))
    do
        ((seconds_plus+=$(gen_num 10 0)))
        ip=$(generate_ip)     
        date=$(gen_datetime $i $seconds_plus)
        echo "$ip - - [$date] \"$(get_method) $(get_url) HTTP/1.0\" $(get_code) \"-\" \"$(get_agent)\"" >> ./logs/log$(($i+1)).txt
    done
done







