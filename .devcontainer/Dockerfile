FROM ubuntu:latest

ENV TZ=Asia/Seoul LANG=ko_KR.UTF-8 LANGUAGE=ko_KR.UTF-8

USER root

# ✅ 1. 사용자 먼저 만들기
RUN useradd -m -s /bin/bash jungle && usermod -aG sudo jungle \
    && echo 'jungle:jungle' | chpasswd

# ✅ 2. 환경 설치 + zsh + oh-my-zsh
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    locales tzdata build-essential sudo gdb vim curl git wget \
    python3 cmake make gcc sudo valgrind telnet net-tools iproute2 zsh \
    && locale-gen ko_KR.UTF-8 && update-locale LANG=ko_KR.UTF-8 \
    && chsh -s /usr/bin/zsh jungle \
    && su - jungle -c "curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh | bash -s -- --unattended"

USER jungle
WORKDIR /home/jungle
