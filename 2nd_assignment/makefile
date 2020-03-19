CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Wfatal-errors
LIBS = -lsfml-window -lsfml-graphics -lsfml-system

main: main.o Game.o Creature.o
	$(CXX) $(CXXFLAGS) -o main main.o Game.o Creature.o $(LIBS)

main.o: main.cpp Game.hpp Creature.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp $(LIBS)

Game.o: Game.hpp

Creature.o: Creature.hpp

clean:
	rm *.o

run:
	./main
