TARGETS = entrance.o test.o card.o
CC = g++
CCFLAGS = -Wall -std=c++14 -O2

INCS = ./src/asx.h

all : $(TARGETS)
	$(CC) -o chipoker.run $(TARGETS)

test.o : ./vs2015-prj/chipoker/chipoker/test.cpp
	$(CC) -c ./vs2015-prj/chipoker/chipoker/test.cpp $(CCFLAGS)

card.o : ./src/card.cpp
	$(CC) -c ./src/card.cpp $(CCFLAGS)

entrance.o : ./src/entrance.cpp
	$(CC) -c ./src/entrance.cpp $(CCFLAGS)

clean :
	rm $(TARGETS) chipoker.run
