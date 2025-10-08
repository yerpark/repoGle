FROM ubuntu:latest

ENV TZ=Asia/Seoul LANG=ko_KR.UTF-8 LANGUAGE=ko_KR.UTF-8

USER root

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    locales tzdata build-essential sudo gdb vim curl git wget \
    python3 cmake make gcc sudo valgrind telnet net-tools iproute2\
    && locale-gen ko_KR.UTF-8 && update-locale LANG=ko_KR.UTF-8\
    && apt install -y zsh curl git\
    && chsh -s /usr/bin/zsh jungle\
    && su - jungle -c "sh -c \"\$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)\" --unattended"

RUN useradd -m -s /bin/bash jungle && usermod -aG sudo jungle

# 암호 설정
RUN echo 'jungle:jungle' | chpasswd

USER jungle
WORKDIR /home/jungle