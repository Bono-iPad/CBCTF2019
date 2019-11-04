FROM ubuntu:18.04

RUN apt-get update && apt-get -y upgrade
RUN apt install -y socat curl netcat
RUN groupadd -r user && useradd -r -g user user

WORKDIR /home/user/
USER user
COPY  --chown=root:user ./key_check /home/user/key_check
COPY  --chown=root:user ./README.txt /home/user/README.txt

EXPOSE 12345
CMD ["socat", "TCP-LISTEN:12345,reuseaddr", "EXEC:/home/user/key_check"]
