CC = g++
CPPFLAGS = -g -std=c++11
LFLAGS =

default: test hra clean

#test: tests.o card.o deck.o stack.o foundation.o board.o
#	$(CC) -g -std=c++11 -o test tests.o card.o deck.o stack.o foundation.o board.o

hra: card.o deck.o stack.o foundation.o board.o game.o
	$(CC) $(LFLAGS) -Wall -g -std=c++11 -o hra card.o deck.o stack.o foundation.o board.o game.o

tests.o: tests.cpp
	$(CC) $(CPPFLAGS) -c tests.cpp

deck.o: deck.cpp
	$(CC) $(CPPFLAGS) -c deck.cpp

card.o: card.cpp
	$(CC) $(CPPFLAGS) -c card.cpp

stack.o: stack.cpp
	$(CC) $(CPPFLAGS) -c stack.cpp

foundation.o: foundation.cpp
	$(CC) $(CPPFLAGS) -c foundation.cpp

board.o: board.cpp
	$(CC) $(CPPFLAGS) -c board.cpp

game.o: game.cpp
	$(CC) $(CPPFLAGS) -c game.cpp

clean:
	rm -rf *.o

run:
	./test
