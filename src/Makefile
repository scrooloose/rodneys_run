OBJS = player.o main.o engine.o
CFLAGS = -Wall -c -g
LFLAGS = -Wall -g -lncurses
CC = g++
EXECUTABLE = rogue

run: clean all
	$(EXECUTABLE)

all: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXECUTABLE)

$(OBJS): %.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o
	rm $(EXECUTABLE)

