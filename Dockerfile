# syntax=docker/dockerfile:1

FROM debian:trixie-slim

RUN apt-get update

RUN apt install -y build-essential
RUN apt install -y cmake
RUN apt install -y doxygen
RUN apt install -y graphviz

RUN apt install -y clang
RUN apt install -y clang-format

RUN apt install -y git
RUN apt install -y clang-tidy
RUN apt install -y iwyu
RUN apt install -y libboost-all-dev

RUN apt install -y python3 python3-pip

RUN apt install -y libssl-dev
RUN apt install -y zlib1g-dev

RUN printf "\nalias ls='ls --color=auto'\nalias ll='ls -alF'\n" >> /etc/bash.bashrc

RUN groupadd -g 1000 dev \
    && useradd -m -u 1000 -g dev -s /bin/bash -c "Dev User" dev

WORKDIR /workspace
