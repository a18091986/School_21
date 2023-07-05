sudo apt install -y goaccess
echo `LC_TIME="en_US.UTF-8" bash -c 'goaccess ../04/logs/*.txt --log-format=COMBINED --4xx-to-unique-count --enable-panel=STATUS_CODES -o report.html'`