FROM python:3

WORKDIR /usr/src/app

COPY *.whl ./
RUN python -m pip install --upgrade pip
RUN python3 -m pip install pytest

#COPY . .

#CMD [ "python", "./your-daemon-or-script.py" ]