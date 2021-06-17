OBJS = main.cpp chip.cpp

CC = g++

COMPILER_FLAGS = -Wextra -Wall -pedantic 

LINKER_FLAGS = -lSDL2

EXE = exe

all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXE)
