#!/bin/bash

# tz=`wget -qO- --no-check-certificate 'https://timezoneapi.io/api/ip/?token=ajbcoNxdlzoSHPTMsmIf' | grep -Po '"offset_tzid":.*?[^\\\\]"' | cut -d ":" -f 2 | cut -d "\"" -f 2 | tr -d '\\\\'`
# echo $tz
# timedatectl set-timezone $tz

echo HOSTNAME = `hostname`
# TIMEZONE = временная зона в виде: America/New_York UTC -5 (временная зона, должна браться из системы и быть корректной для текущего местоположения)
echo TIMEZONE = `cat /etc/timezone` UTC `date +%-:::z`
# USER = текущий пользователь который запустил скрипт
echo USER = $USER
# OS = тип и версия операционной системы
echo OS = `cat /etc/issue | cut -d " " -f 1,2,3`
# DATE = текущее время в виде: 12 May 2020 12:24:36
echo DATE = `date | cut -d " " -f 2-5`
# UPTIME = время работы системы
echo UPTIME = `uptime -p`
# UPTIME_SEC = время работы системы в секундах
echo UPTIME_SEC = `cat /proc/uptime | cut -d " " -f 1`
# IP = ip-адрес машины в любом из сетевых интерфейсов
echo IP = `hostname -I | awk '{print $1}'`
# MASK = сетевая маска любого из сетевых интерфейсов в виде: xxx.xxx.xxx.xxx
echo MASK = `ifconfig | grep 'netmask' | head -1 |cut -d " " -f 13`
# GATEWAY = ip шлюза по умолчанию
echo GATEWAY = `ip r | grep -m1 'default' | cut -d " " -f 3`
# RAM_TOTAL = размер оперативной памяти в Гб c точностью три знака после запятой в виде: 3.125 GB
echo RAM_TOTAL = `free | grep -m1 "Mem"  | awk '{printf("%.3f Gb", $2/(1024*1024))}'`
# RAM_USED = размер используемой памяти в Гб c точностью три знака после запятой
echo RAM_USED = `free | grep -m1 "Mem"  | awk '{printf("%.3f Gb", $3/(1024*1024))}'`
# RAM_FREE = размер свободной памяти в Гб c точностью три знака после запятой
echo RAM_FREE = `free | grep -m1 "Mem"  | awk '{printf("%.3f Gb", $4/(1024*1024))}'`
# SPACE_ROOT = размер рутового раздела в Mб с точностью два знака после запятой в виде: 254.25 MB
echo SPACE_ROOT = `df -k /root/ | tail +2 | awk '{printf("%.2f MB", $2/1024)}'`
# SPACE_ROOT_USED = размер занятого пространства рутового раздела в Mб с точностью два знака после запятой
echo SPACE_ROOT_USED = `df -k /root/ | tail +2 | awk '{printf("%.2f MB", $3/1024)}'`
# SPACE_ROOT_FREE = размер свободного пространства рутового раздела в Mб с точностью два знака после запятой
echo SPACE_ROOT_FREE = `df -k /root/ | tail +2 | awk '{printf("%.2f MB", $4/1024)}'`

# После вывода значений предложить записать данные в файл (предложить пользователю ответить Y/N).
# Ответы Y и y считаются положительными, все прочие - отрицательными. При согласии пользователя, в текущей директории создать файл содержащий информацию, которая была выведена на экран.
# Название файла должно иметь вид: DD_MM_YY_HH_MM_SS.status (Время в имени файла должно указывать момент сохранения данных).
