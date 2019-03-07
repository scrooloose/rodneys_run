CPPFLAGS = -Wall -c -ggdb
LFLAGS = -Wall -ggdb -lncurses -ldl -lboost_filesystem -lboost_system
CC = g++

SRC_DIR := src
OBJ_DIR := obj
SRC_FILES := $(wildcard $(SRC_DIR)/**/*.cpp $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
EXECUTABLE = rogue

run: link
	./$(EXECUTABLE) ./maps; stty sane; setterm -cursor on

debug: build
	gdb --args rogue ./maps

link: build
	$(CC) $(OBJ_FILES) -o $(EXECUTABLE) $(LFLAGS)

build: create_dirs $(OBJ_FILES)

create_dirs:
	mkdir -p $(OBJ_DIR)/tiles $(OBJ_DIR)/ui $(OBJ_DIR)/json

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(EXECUTABLE)

