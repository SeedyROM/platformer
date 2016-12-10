CC= g++
FLAGS= -Wall -O3 -std=c++11 -g -ggdb
SFML_LIBS= -lsfml-window -lsfml-graphics -lsfml-system
EXEC_NAME= platformer

all:
	$(CC) main.cpp -o $(EXEC_NAME) $(FLAGS) $(SFML_LIBS)

asm:
	$(CC) -g -O0 -c -fverbose-asm -Wa,-adhln main.cpp -std=c++11 $(SFML_LIBS) > main.lst
