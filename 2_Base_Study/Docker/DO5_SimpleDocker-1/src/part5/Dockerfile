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
    && adduser --disabled-password user \
    && chown -R user:user /etc/nginx/ \
    && chown -R user:user /server/ \
    && chown -R user:user /var/log/nginx/ \
    && chown -R user:user /var/lib/nginx/

USER user 

CMD gcc -o server server.c -lfcgi && spawn-fcgi -p 8080 server && nginx -g 'daemon off;'
