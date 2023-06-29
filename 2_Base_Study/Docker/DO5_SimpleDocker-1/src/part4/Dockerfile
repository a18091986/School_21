FROM nginx
USER root
COPY ./nginx.conf /etc/nginx/nginx.conf
COPY ./server.c /home/server.c
COPY ./start.sh /home/start.sh
RUN apt-get update
RUN apt-get install -y gcc spawn-fcgi libfcgi-dev
WORKDIR /home/
ENTRYPOINT ["sh", "./start.sh"]