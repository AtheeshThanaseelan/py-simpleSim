# syntax=docker/dockerfile:1
FROM python:3.7-alpine
WORKDIR /code
RUN apk add --no-cache gcc musl-dev linux-headers
EXPOSE 16543
COPY . .
CMD ["ip", "a"]
CMD ["python", "physpeer.py"]
RUN sh