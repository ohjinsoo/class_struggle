all: main

main: main.cpp
	g++ -o main main.cpp Player.h Robot.cpp Human.cpp Gamestate.cpp Deck.cpp Card.cpp

clean:
	rm main.exe Player.h.gch Robot.o Human.o Gamestate.o Deck.o Card.o