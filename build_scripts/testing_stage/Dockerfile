# syntax=docker/dockerfile:1
FROM ubuntu:18.04
RUN apt update && apt install -y \
	build-essential \
	git \
	libbullet-dev \
	libirrlicht-dev \
	python3-pip \
	python3-venv
RUN python3 -m pip install --upgrade pip
#RUN python3 -m pip install pytest
RUN python3 -m venv /venv
RUN chmod -R a+rwX /venv/