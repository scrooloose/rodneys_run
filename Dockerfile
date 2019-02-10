FROM gcc

RUN mkdir /app
COPY . /app

WORKDIR /app
