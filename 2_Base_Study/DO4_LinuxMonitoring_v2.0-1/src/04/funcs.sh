function generate_ip {
    echo "$((RANDOM % 256)).$((RANDOM % 256)).$((RANDOM % 256)).$((RANDOM % 256))"
    # echo "192.168.2.222"
}

function get_method {
    echo "$(shuf methods -n1)"
}

function get_url {
    echo "$(shuf urls -n1)"
}

function get_code {
    echo "$(shuf codes -n1)"
}

function get_agent {
    echo "$(shuf agents -n1)"
}

function gen_num {
    echo "$((RANDOM % $1 + $2))"
}

function gen_datetime {
    echo "$(date  +'%d/%b/%Y:%H:%M:%S %z' -d "$1 days $2 seconds")"
}
