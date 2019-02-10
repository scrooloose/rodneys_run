CFLAGS = -Wall -c -g
LFLAGS = -Wall -g -lncurses
CC = g++

SRC_DIR := src
OBJ_DIR := obj
SRC_FILES := $(wildcard $(SRC_DIR)/**/*.cpp $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
EXECUTABLE = rogue

run: link
	./$(EXECUTABLE) ./maps

link: build
	$(CC) $(LFLAGS) $(OBJ_FILES) -o $(EXECUTABLE)

build: create_dirs $(OBJ_FILES)

create_dirs:
	mkdir -p $(OBJ_DIR)/tiles $(OBJ_DIR)/json

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

debug: build
	nemiver $(EXECUTABLE)

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(EXECUTABLE)

