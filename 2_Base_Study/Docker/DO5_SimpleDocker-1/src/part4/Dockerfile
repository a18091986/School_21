FROM nginx

WORKDIR /home/

COPY ./nginx.conf /etc/nginx/nginx.conf
COPY ./web_server.c /home/server.c

RUN apt-get update && \
    apt-get install -y gcc spawn-fcgi libfcgi-dev && \
    gcc server.c -lfcgi -o server && \
    spawn-fcgi -p 8080 ./server && \
    service nginx start

