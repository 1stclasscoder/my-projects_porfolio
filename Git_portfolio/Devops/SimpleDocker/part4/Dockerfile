FROM nginx
COPY ./nginx.conf /etc/nginx/nginx.conf
COPY ./server.c /home/server.c
COPY ./scrypts.sh /home/scrypts.sh
RUN apt update && apt install -y gcc spawn-fcgi libfcgi-dev
WORKDIR /home/
ENTRYPOINT ["bash", "./scrypts.sh"]
