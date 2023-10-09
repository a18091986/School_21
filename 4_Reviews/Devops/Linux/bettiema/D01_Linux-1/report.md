## Part 1. Установка ОС

1. Узнайте версию Ubuntu, выполнив команду `cat /etc/issue`

    ![](screenshots/cat-etc-issue.png)

## Part 2. Создание пользователя

1. Вставьте скриншот вызова команды для создания пользователя

    ![](screenshots/sudo-useradd-G-adm-kitty.png)

2. Новый пользователь должен быть в выводе команды `cat /etc/passwd`

    ![](screenshots/cat-etc-passwd.png)

## Part 3. Настройка сети ОС

1. Задать название машины вида user-1

    ![](screenshots/start-user-1.png)

    ![](screenshots/final-user-1.png)

    >* sudo vim /etc/hostname
    >* reboot

2. Установить временную зону, соответствующую вашему текущему местоположению

    ![](screenshots/set-timezone.png)

    >* sudo timedatatectl
    >* timedatatectl list-timezones | grep Moscow
    >* sudo timedatatectl set-timezone Europe/Moscow
    >* sudo timedatatectl

3. Вывести названия сетевых интерфейсов с помощью консольной команды

    ![](screenshots/ifconfig-a.png)

    >* ifconfig -a

    Lo (loopback device) – виртуальный интерфейс, присутствующий по умолчанию в любом Linux. Он используется для отладки сетевых программ и запуска серверных приложений на локальной машине.

4. Используя консольную команду получить ip адрес устройства, на котором вы работаете, от DHCP сервера

    ![](screenshots/hostname-I.png)

    >* hostname -I 

    DHCP (Dynamic Host Configuration Protocol/протокол динамической конфигурации узла) — это сетевой протокол, позволяющий компьютерам автоматически получать IP-адрес и другие параметры, необходимые для работы в сети TCP/IP.

5. Определить и вывести на экран внешний ip-адрес шлюза (ip) и внутренний IP-адрес шлюза, он же ip-адрес по умолчанию (gw)

    ![](screenshots/external-IP.png) Внешний IP-адрес шлюза.

    >* wget -O  - -q icanhazip.com

    ![](screenshots/interior-IP.png) Внутренний IP-адрес шлюза.

    >* ip route

6. Задать статичные (заданные вручную, а не полученные от DHCP сервера) настройки ip, gw, dns (использовать публичный DNS серверы, например 1.1.1.1 или 8.8.8.8)

    ![](screenshots/start-sudo-vim-etc-netplan-00-installer-config.png)

    >* sudo vim /etc/netplan/00-installer-config.yalm

    ![](screenshots/final-sudo-vim-etc-netplan-00-installer-config.png)

7. Перезагрузить виртуальную машину. Убедиться, что статичные сетевые настройки (ip, gw, dns) соответствуют заданным в предыдущем пункте. Успешно пропинговать удаленные хосты 1.1.1.1 и ya.ru и вставить в отчёт скрин с выводом команды. В выводе команды должна быть фраза "0% packet loss"

    ![](screenshots/ping-1-1-1-1.png)

    >* ping 1.1.1.1

    ![](screenshots/ping-ya-ru.png)

    >* ping ya.ru

## Part 4. Обновление ОС

1. Обновить системные пакеты до последней на момент выполнения задания версии

    ![](screenshots/update.png)

    >* sudo apt update
    >* sudo apt full-upgrade
    
## Part 5. Использование команды **sudo**

1. Разрешить пользователю, созданному в [Part 2], выполнять команду sudo

    ![](screenshots/SUDO.png)

    >* sudo usermod -a -G sudo kitty
    >* su kitty
    >* cat /etc/hostname
    >* sudo hostname bettiema-2
    >* cat /etc/hostname
    >* su bettiema

    Sudo – это утилита для операционных систем семейства Linux, позволяющая пользователю запускать программы с привилегиями другой учётной записи, как правило, суперпользователя. В части запуска команд от имени root’а sudo является альтернативой утилите su. Правда, в отличие от su, которая запускает оболочку root’а и предоставляет суперполномочия всем дальнейшим инструкциям, sudo предоставляет только временное повышение привилегий.

## Part 6. Установка и настройка службы времени

1. Настроить службу автоматической синхронизации времени. Вывод следующей команды должен содержать `NTPSynchronized=yes`: \ `timedatectl show`

    ![](screenshots/sudo-timedatectl.png)

    >* sudo timedatectl
    >* timedatectl show

## Part 7. Установка и использование текстовых редакторов

1. Установить текстовые редакторы **VIM** (+ любые два по желанию **NANO**, **MCEDIT**, **JOE** и т.д.)

    ![](screenshots/vim-nano-mc.png)

    >* sudo apt install vim
    >* sudo apt install nano
    >* sudo apt install mcedit

2. Используя каждый из трех выбранных редакторов, создайте файл *test_X.txt*, где X -- название редактора, в котором создан файл. Напишите в нём свой никнейм, закройте файл с сохранением изменений
 

    ![](screenshots/vim-nickname.png)

    >* vim test_VIM.txt
    >* I -> ESC -> Shift + : -> :wq! -> ENTER

    ![](screenshots/nano-nickname.png)

    >* nano test_NANO.txt
    >* CTRL + X -> Y -> ENTER

    ![](screenshots/mc-nickname.png)

    >* mcedit test_mcedit.txt
    >* SOFT KEYBOARD: F2 -> F10

3. Используя каждый из трех выбранных редакторов, откройте файл на редактирование, отредактируйте файл, заменив никнейм на строку "21 School 21", закройте файл без сохранения изменений

    ![](screenshots/vim-school.png)

    >* :q! -> ENTER

    ![](screenshots/nano-school.png)

    >* CTRL + X -> N -> ENTER

    ![](screenshots/mc-school.png)

    >* SOFT KEYBOARD: F10

4. Используя каждый из трех выбранных редакторов, отредактируйте файл ещё раз (по аналогии с предыдущим пунктом), а затем освойте функции поиска по содержимому файла (слово) и замены слова на любое другое

    ![](screenshots/vim-search.png)

    >* /<поиск> -> ENTER

    ![](screenshots/vim-replaced1.png)

    ![](screenshots/vim-replaced2.png)

    >* :s/<слово под замену>/<на что нужно заменить> -> ENTER

    ![](screenshots/nano-search.png)

    >* CRTL + W -> <поиск> -> ENTER

    ![](screenshots/nano-replaced1.png)

    ![](screenshots/nano-replaced2.png)

    >* CRTL + \ -> Y -> ENTER

    ![](screenshots/mc-search.png)

    >* SOFT KEYBOARD: F7

    ![](screenshots/mc-replaced1.png)

    ![](screenshots/mc-replaced2.png)

    ![](screenshots/mc-replaced3.png)

    ![](screenshots/mc-replaced4.png)

    >* SOFT KEYBOARD: F4

## Part 8. Установка и базовая настройка сервиса **SSHD**

1. Установить службу SSHd

    ![](screenshots/install-SSHD.png)

    >* sudo apt-get install ssh
    >* sudo apt install openssh-server

2. Добавить автостарт службы при загрузке системы

    ![](screenshots/autostart.png)

    >* sudo systemctl enable ssh
    >* systemctl status ssh

3. Перенастроить службу SSHd на порт 2022

    ![](screenshots/port2022.png)

    >* sudo vim /etc/ssh/sshd_config

    ![](screenshots/restart.png)

    >* systemctl restart sshd

4. Используя команду ps, показать наличие процесса sshd. Для этого к команде нужно подобрать ключи

    ![](screenshots/ps-sshd.png)

    >* ps -e | grep sshd

    ```
    ps - покажет список процессов в данном терминале.
    ps -e | less - перечислит процессы, которые были запущены всеми пользователями, с возможностью прокрутки списка.
    ps -p <PID> - покажет процесс, с конкретным PID.
    ps -u <user> - покажет процесс, выполняемый конкретным пользователем.
    ps -r - покажет все работающие (runnig) процессы.
    *ps -t - покажет все работающие процессы, связанные с этим терминалом.
    ```

5. Перезагрузить систему. Вывод команды netstat -tan должен содержать `tcp 0 0 0.0.0.0:2022 0.0.0.0:* LISTEN`

    >* reboot

    ![](screenshots/netstat-tan.png)

    ```
    -t (--tcp) - отображает соединения только по tcp.
    -a (--all) - вывод всех активных подключений TCP.
    -n (--numeric) - вывод активных подключений TCP с отображением адресов и номеров портов в числовом формате.
    Proto - название протокола (протокол TCP или протокол UDP).
    Recv-Q - очередь получения сети.
    Send-Q - сетевая очередь отправки.
    Local Address - адрес локального компьютера и используемый номер порта.
    Foreign Address - адрес и номер удаленного компьютера к которому подключен сокет.
    State - состояние сокета.
    0.0.0.0 - IP-адрес на локальной машине.
    ```

## Part 9. Установка и использование утилит **top**, **htop**

1. Установить и запустить утилиты top и htop

    ![](screenshots/top.png)

    >* top

    ```
    uptime - 27 min
    количество авторизованных пользователей - 1 user
    общая загрузка системы - load average:
    общее количество процессов - Tasks:
    загрузка cpu - %Cpu(s):
    загрузка памяти - MiB Mem:
    ```

    ![](screenshots/top-mem.png)
    
    >* Shift + M

    pid процесса занимающего больше всего памяти

    ![](screenshots/top-time.png)

    >* Shift + P

    pid процесса, занимающего больше всего процессорного времени

    ![](screenshots/htop-pid.png)

    htop сортировка по PID

    ![](screenshots/htop-cpu.png)

    htop сортировка по PERCENT_CPU

    ![](screenshots/htop-mem.png)

    htop сортировка по PERCENT_MEM

    ![](screenshots/htop-time.png)

    htop сортировка по TIME

    ![](screenshots/htop-sshd.png)

    htop фильтр по процессу sshd

    ![](screenshots/htop-syslog.png)

    htop поиск процесса syslog

    ![](screenshots/htop-info.png)

    htop с добавленным выводом hostname, clock и uptime

## Part 10. Использование утилиты **fdisk**

1. Запустить команду fdisk -l

    ![](screenshots/htop-info.png)

    >* sudo fdisk -l

    Disk /dev/sda: 25 GiB, 26843545600 bytes, 52428800 sectors
    Disk model: VBOX HARDDISK

## Part 11. Использование утилиты **df**

1. Запустить команду df

    ![](screenshots/df.png)

    >* df /

    ```
    bytes
    ```

    ![](screenshots/dfTh.png)

    >* df -Th /

    ```
    ext4
    ```

## Part 12. Использование утилиты **du**

1. Запустить команду du.

    ![](screenshots/du.png)

    >* du

2. Вывести размер папок /home, /var, /var/log (в байтах, в человекочитаемом виде)

    ![](screenshots/duhome.png)

    >* sudo du -h /home

    ![](screenshots/duvar.png)

    >* sudo du -h /var

    ![](screenshots/duvarlog.png)

    >* sudo du -h /var/log

3. Вывести размер всего содержимого в /var/log (не общее, а каждого вложенного элемента, используя *)

    ![](screenshots/duvarlog*.png)

    >* sudo du -h /var/log/*

## Part 13. Установка и использование утилиты **ncdu**

1. Установить утилиту ncdu

    ![](screenshots/installncdu.png)

    >* sudo apt install ncdu

2. Вывести размер папок /home, /var, /var/log

    ![](screenshots/ncduhome.png)

    >* ncdu /home

    ![](screenshots/ncduvar.png)

    >* ncdu /var

    ![](screenshots/ncduvarlog.png)

    >* ncdu /var/log

## Part 14. Работа с системными журналами

1. Открыть для просмотра: /var/log/dmesg

    ![](screenshots/varlogdmesg.png)

    >* cat /var/log/dmesg

2. Открыть для просмотра: /var/log/syslog

    ![](screenshots/varlogsyslog.png)

    >* cat /var/log/syslog

3. Открыть для просмотра: /var/log/auth.log

    ![](screenshots/varlogauthlog.png)

    >* cat /var/log/auth.log

4. Написать в отчёте время последней успешной авторизации, имя пользователя и метод входа в систему

    ![](screenshots/sessionopened.png)

    >* cat /var/log/auth.log | grep session

5. Перезапустить службу SSHd.

    >* sudo systemctl restart ssh.service

6. Вставить в отчёт скрин с сообщением о рестарте службы (искать в логах)

    ![](screenshots/restartsshd.png)

    >* sudo systemctl restart ssh.service
    >* grep "ssh" /var/log/syslog

## Part 15. Использование планировщика заданий **CRON**

1. Используя планировщик заданий, запустите команду uptime через каждые 2 минуты

    ![](screenshots/CRONuptime.png)

    >* crontab -e
    >* crontab -l

    ![](screenshots/CRON.png)

    >* cat /var/log/syslog | grep CRON

2. Удалите все задания из планировщика заданий

    ![](screenshots/CRONR.png)

    >* crontab -l
    >* crontab -r