OBJS = player.o main.o engine.o position.o tiles/tile.o map.o tiles/floor.o tiles/wall.o map_parser.o tiles/empty_tile.o map_list.o tiles/stairs.o tiles/door.o viewport_calculator.o message_log.o mobile.o positionable.o melee_ai.o turn_timer.o node.o a_star_path_finder.o proximity_sorter.o weapon.o ranged_weapon.o melee_weapon.o item.o inventory.o map_meta_inf_parser.o key.o med_kit.o weapon_factory.o damage_strategy.o simple_damage_strategy.o radial_damage_strategy.o movement_strategy.o scent_movement_strategy.o mobile_factory.o
CFLAGS = -Wall -c -g
LFLAGS = -Wall -g -lncurses -ljsoncpp
CC = g++
EXECUTABLE = rogue

run: all
	./$(EXECUTABLE)

debug: all
	nemiver $(EXECUTABLE)

all: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(EXECUTABLE)

$(OBJS): %.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	find -name "*.o" -delete
	rm $(EXECUTABLE)

