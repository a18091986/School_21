#!/bin/bash

bash info.sh

echo "Export data in file? [Y/n]"
read otvet
if [[ $otvet == 'y' || $otvet == 'Y' ]]
then
    FILE=$(date +%d_%m_%Y_%H_%M_%S.status)
    bash info.sh >> $FILE
fi