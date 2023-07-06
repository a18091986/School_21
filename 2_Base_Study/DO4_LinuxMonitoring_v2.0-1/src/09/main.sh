#!/bin/bash
chmod +x ./info.sh
touch index.html

sudo cp ./prometheus.yml /etc/prometheus/prometheus.yml
sudo systemctl restart prometheus

while sleep 5
do
    ./info.sh > index.html
done
    sleep 3
done