OBJS = player.o main.o engine.o position.o tile.o map.o floor.o wall.o map_parser.o path.o empty_tile.o map_list.o stairs.o door.o viewport_calculator.o message_log.o mobile.o positionable.o zombie.o melee_ai.o turn_timer.o node.o path_finder.o proximity_sorter.o weapon.o ranged_weapon.o melee_weapon.o item.o inventory.o map_meta_inf_parser.o key.o
CFLAGS = -Wall -c -g
LFLAGS = -Wall -g -lncurses -ljsoncpp
CC = g++
EXECUTABLE = rogue

run: all
	./$(EXECUTABLE)

all: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXECUTABLE)

$(OBJS): %.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o
	rm $(EXECUTABLE)

