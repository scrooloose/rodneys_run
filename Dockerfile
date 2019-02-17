FROM gcc

RUN apt-cache update && apt-get install -y gdb

RUN mkdir /app
COPY . /app

WORKDIR /app

RUN make -j4
CMD ["./rogue ./maps"]
