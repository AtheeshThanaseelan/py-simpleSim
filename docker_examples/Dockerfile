# syntax=docker/dockerfile:1
FROM ubuntu:18.04
RUN apt update
RUN apt install -y \
	build-essential \
	git \
	python3-pip \
	libirrlicht-dev \
	libbullet-dev
RUN mkdir work
WORKDIR "/work"
RUN git clone https://github.com/pybind/pybind11.git
RUN cp -r pybind11/include/pybind11 /usr/include/
RUN git clone https://github.com/AtheeshThanaseelan/CPlusPlus-Physics-Environment.git
RUN pip3 install CPlusPlus-Physics-Environment/sample/
RUN bash

