- Prometheus

<center>
<br>

![prometheus](./img/1.PNG)

prometheus version

<br>
</center>

<center>
<br>

![prometheus status](./img/2.PNG)

запуск ptometheus

<br>
</center>

- Grafana

-- для установки - vpn https://whoer.net/ru/vpn/trial

-- установка https://grafana.com/docs/grafana/latest/setup-grafana/installation/debian/

<center>
<br>

![graphana](./img/3.PNG)

graphana service

<br>
</center>

<center>
<br>

![graphana](./img/4.PNG)

graphana web

<br>
</center>

- Grafana Conf


<center>
<br>

![graphana_connect](./img/5.PNG)

graphana connect prometheus

<br>
</center>

- - disk I/O 

rate(node_disk_reads_completed_total{device="sda", instance="localhost:9100"}[1m])

rate(node_disk_writes_completed_total{device="sda", instance="localhost:9100"}[1m])

- - current mem usage

(node_memory_MemTotal_bytes{instance="localhost:9100"} - node_memory_MemFree_bytes{instance="localhost:9100"}) / node_memory_MemTotal_bytes{instance="localhost:9100"}

- - cpu

100 - (avg by (cpu)(irate(node_cpu_seconds_total{instance="localhost:9100",mode="idle"}[30m]))) * 100

- - hdd

node_filesystem_avail_bytes{instance="localhost:9100", mountpoint="/"} / 1024 / 1024 / 1000

<center>
<br>

![graphana_connect](./img/6.PNG)

graphana dash

<br>
</center>

- При запуске скрипта засорения файловой системы

<center>
<br>

![graphana_connect](./img/7.PNG)

graphana dash

<br>
</center>

- При запуске утилиты stress

<center>
<br>

![graphana_connect](./img/8.PNG)

graphana dash

<br>
</center>


