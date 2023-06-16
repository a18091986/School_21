#!/bin/bash

source ./func.sh

# Скрипт должен выводить следующую информацию о каталоге, указанном в параметре:
# - Общее число папок, включая вложенные
# - Топ 5 папок с самым большим весом в порядке убывания (путь и размер)
# - Общее число файлов
# - Число конфигурационных файлов (с расширением .conf), текстовых файлов, исполняемых файлов, логов (файлов с расширением .log), архивов, символических ссылок
# - Топ 10 файлов с самым большим весом в порядке убывания (путь, размер и тип)
# - Топ 10 исполняемых файлов с самым большим весом в порядке убывания (путь, размер и хеш)
# - Время выполнения скрипта

# Скрипт должен вывести на экран информацию в виде:

# ```
# Total number of folders (including all nested ones) = 6  
echo "Total number of folders (including all nested ones) = `sudo find $1 -type d 2>/dev/null | wc -l`"

# TOP 5 folders of maximum size arranged in descending order (path and size):  
# 1 - /var/log/one/, 100 GB  
# 2 - /var/log/two/, 100 MB  
# etc up to 5
echo "TOP 5 folders of maximum size arranged in descending order (path and size):"
echo "$(sudo du $1 -h 2>/dev/null | sort -rh | head -n 5 | awk 'BEGIN{i=1} {printf "%d - %s, %s\n", i, $2, $1; i++}')"
#echo "`sudo du $1 | awk {'printf "%4s  %70s %d \n", $1, $2, length'} | sort -rnk1,3 | awk {'printf "%4s\t%s\n",$1,$2'} | head -5`"
#echo "`sudo du -b /home/behappyman/GIT_TEST | awk {'printf "%4s  %70s %d \n", $1, $2, length'} | sort -rnk1,3 | numfmt --to=iec | awk {'printf "%s, %s\n",$2,$1'} | head -n 5 | nl -s ' - '`"


# Total number of files = 30
echo "Total number of files = `sudo find $1 -type f 2>/dev/null | wc -l`"

# Number of:  
# Configuration files (with the .conf extension) = 1 
echo "Number of:"
echo "Configuration files (with the .conf extension) = `sudo find $1 -type f -name '*.conf' 2>/dev/null | wc -l`"
# Text files = 10  
echo "Text files = `sudo find $1 -type f -name '*.txt' 2>/dev/null | wc -l`"
# Executable files = 5
echo "Executable files = `sudo find $1 -type f -executable 2>/dev/null | wc -l`"
echo "Executable files = `sudo find $1 -type f -perm /a=x 2>/dev/null | wc -l`"
# Log files (with the extension .log) = 2  
echo "Log files (with the extension .log) = `sudo find $1 -type f -name '*.log' 2>/dev/null | wc -l`"
# Archive files = 3  
echo "Archive files = `sudo find $1 -type f -regex '.*\(zip\|rar\|7z\|tar\)' 2>/dev/null | wc -l`"
# Symbolic links = 4  
echo "Symbolic links = `sudo find $1 -type l 2>/dev/null | wc -l`"
    
# TOP 10 files of maximum size arranged in descending order (path, size and type):  
# 1 - /var/log/one/one.exe, 10 GB, exe  
# 2 - /var/log/two/two.log, 10 MB, log  
# etc up to 10  
echo "TOP 10 files of maximum size arranged in descending order (path, size and type):  "
echo "`sudo find $1 -type f -exec du -h {} \; 2>/dev/null | sort -rh | head -10 | awk 'BEGIN{i=1} {printf "%d - %s, %s\n", i, $2, $1; i++}'`"

# TOP 10 executable files of the maximum size arranged in descending order (path, size and MD5 hash of file)  
# 1 - /var/log/one/one.exe, 10 GB, 3abb17b66815bc7946cefe727737d295  
# 2 - /var/log/two/two.exe, 9 MB, 53c8fdfcbb60cf8e1a1ee90601cc8fe2  
# etc up to 10  
# Script execution time (in seconds) = 1.5
# ```
echo "TOP 10 executable files of the maximum size arranged in descending order (path, size and MD5 hash of file)"
top_10_exe $1
# echo "`sudo find $1 -type f -perm /a=x -exec du -h {} \; 2>/dev/null | sort -rh | head -10 | cat -n | awk '{print $1 " - " $3 ", " $2}'`"



