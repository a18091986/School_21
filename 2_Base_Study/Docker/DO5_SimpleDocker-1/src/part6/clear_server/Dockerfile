FROM nginx

WORKDIR /server/

COPY ./nginx.conf /etc/nginx/nginx.conf

RUN apt update 

CMD nginx -g 'daemon off;'
