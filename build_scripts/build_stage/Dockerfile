# syntax=docker/dockerfile:1
FROM ubuntu:18.04
RUN apt update
RUN apt install -y \
	build-essential \
	git \
	python3-pip \
	libirrlicht-dev \
	libbullet-dev \
	python3-venv
RUN mkdir work
WORKDIR "/work"
RUN git clone https://github.com/pybind/pybind11.git
RUN cp -r pybind11/include/pybind11 /usr/include/
RUN python3 -m pip install --upgrade build
RUN bash

