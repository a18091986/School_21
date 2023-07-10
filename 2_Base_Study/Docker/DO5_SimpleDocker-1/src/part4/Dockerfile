FROM nginx

WORKDIR /home/

RUN apt update  \
    && apt install -y nginx  \
    && apt install -y gcc  \
    && apt install -y libfcgi-dev  \
    && apt install -y spawn-fcgi  
    
COPY ./nginx.conf /etc/nginx/nginx.conf
COPY ./web_server.c /home/server.c
CMD gcc -o server server.c -lfcgi && spawn-fcgi -p 8080 server && nginx -g 'daemon off;'
