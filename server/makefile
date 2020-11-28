CC=g++
FLAGS=-lws2_32 -std=c++2a -lpthread
OBJS=game.o player.o server.o

all: $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -o server.exe

server.o: server.cpp
	$(CC) $(FLAGS) -c server.cpp

game.o: game.cpp
	$(CC) $(FLAGS) -c game.cpp

player.o: player.cpp
	$(CC) $(FLAGS) -c player.cpp

run:
	server.exe
