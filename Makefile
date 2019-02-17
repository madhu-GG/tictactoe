.PHONY: clean

CXX=g++
STD=-std=c++11
INC_DIR=include
SRC_DIR=src

CXXFLAGS=$(STD) -I$(INC_DIR)

SRC:=$(shell find $(SRC_DIR) -name '*.cpp')
OBJS=$(patsubst %.cpp, %.o, $(SRC)) # list of object files

SFML_LIB:=-lsfml-graphics -lsfml-window -lsfml-system

tictactoe: $(OBJS)
	$(CXX) -o $@ $^ $(SFML_LIB)

clean:
	rm -f $(OBJS) tictactoe
