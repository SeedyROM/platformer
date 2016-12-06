CC= g++
FLAGS= -Wall -O3 -std=c++11
SFML_LIBS= -lsfml-window -lsfml-graphics -lsfml-system
EXEC_NAME= platformer

all:
	$(CC) main.cpp -o $(EXEC_NAME) $(FLAGS) $(SFML_LIBS)
