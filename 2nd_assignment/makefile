CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

main: main.o Game.o Creature.o
	$(CXX) $(CXXFLAGS) -o main main.o Game.o Creature.o

main.o: main.cpp Game.hpp Creature.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Game.o: Game.hpp

Creature.o: Creature.hpp

clean:
	rm *.o

run:
	./main
