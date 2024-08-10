# syntax=docker/dockerfile:1

FROM debian:bullseye-slim

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

RUN apt install -y python3 python3-pip
RUN pip install cpplint



RUN printf "\nalias ls='ls --color=auto'\n" >> ~/.bashrc
RUN printf "\nalias ll='ls -alF'\n" >> ~/.bashrc
