CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Wfatal-errors
LIBS = -lsfml-window -lsfml-graphics -lsfml-system

main: main.o Game.o Creature.o Vec2D.o
	$(CXX) $(CXXFLAGS) -o main main.o Game.o Creature.o Vec2D.o $(LIBS)

main.o: main.cpp Game.hpp Creature.hpp Vec2D.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp $(LIBS)

Game.o: Game.cpp Game.hpp Vec2D.o
	$(CXX) $(CXXFLAGS) -c Game.cpp Vec2D.cpp $(LIBS)

Creature.o: Creature.cpp Creature.hpp
	$(CXX) $(CXXFLAGS) -c Creature.cpp

Vec2D.o: Vec2D.cpp Vec2D.hpp
	$(CXX) $(CXXFLAGS) -c Vec2D.cpp

clean:
	rm *.o

run:
	./main
