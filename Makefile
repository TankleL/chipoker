TARGETS = entrance.o
CC = clang++
CCFLAGS = -Wall -std=c++11

INCS = ./src/asx.h

all : $(TARGETS)
	$(CC) -o chipoker.run $(TARGETS)

entrance.o : ./src/entrance.cpp
	$(CC) -c ./src/entrance.cpp $(CCFLAGS)

clean :
	rm $(TARGETS) chipoker.run
