FROM debian:latest
WORKDIR /nginx_fastcgi_server
RUN apt update  \
    && apt install -y nginx  \
    && apt install -y gcc  \
    && apt install -y libfcgi-dev  \
    && apt install -y spawn-fcgi  \
    && rm -rf /var/lib/apt/lists
COPY web_server.c ./server.c
COPY nginx.conf ../etc/nginx/nginx.conf
CMD gcc -o fcgi server.c -lfcgi && spawn-fcgi -p 8080 fcgi && nginx -g 'daemon off;'

