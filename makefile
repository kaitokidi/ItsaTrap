# Makefile super op

all: Player.o Socket.o Board.o main.o everything exe

exes: Player.o Socket.o Board.o main.o everything exese

exec: Player.o Socket.o Board.o main.o everything exece

Player.o: Player.cpp Player.hpp
	g++ -c Player.cpp -std=c++11

Socket.o: Socket.cpp Socket.hpp
	g++ -c Socket.cpp -std=c++11

Board.o: Board.cpp Board.hpp
	g++ -c Board.cpp -std=c++11

main.o: main.cpp
	g++ -c main.cpp -std=c++11

everything:
	g++ -o ggj Player.o Socket.o Board.o main.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio
		
exe:
	./ggj
	
exese:
	./ggj S
	
exece:
	./ggj c
	
clear:
	rm *.o
