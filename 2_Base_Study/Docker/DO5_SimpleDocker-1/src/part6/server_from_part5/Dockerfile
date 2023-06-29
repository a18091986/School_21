FROM nginx

WORKDIR /server/

COPY ./nginx.conf /etc/nginx/nginx.conf
COPY ./web_server.c /server/server.c

RUN apt update  \
    && apt install -y nginx  \
    && apt install -y gcc  \
    && apt install -y libfcgi-dev  \
    && apt install -y spawn-fcgi \  
    && rm -rf /var/lib/apt/lists \
    && adduser --disabled-password us \
    && chown -R us:us /etc/nginx/ \
    && chown -R us:us /server/ \
    && chown -R us:us /var/cache/ \
    && chown -R us:us /var/run/


USER us

CMD gcc -o server server.c -lfcgi && spawn-fcgi -p 8080 server && nginx -g 'daemon off;'
