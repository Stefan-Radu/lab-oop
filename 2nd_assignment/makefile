CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Wfatal-errors
LIBS = -lsfml-window -lsfml-graphics -lsfml-system
OBJECTS = main.o Game.o Creature.o Vec2D.o

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o main $(OBJECTS) $(LIBS)

main.o: main.cpp Game.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp $(LIBS)

Game.o: Game.cpp Game.hpp Vec2D.hpp Creature.hpp
	$(CXX) $(CXXFLAGS) -c Game.cpp $(LIBS)

Creature.o: Creature.cpp Creature.hpp
	$(CXX) $(CXXFLAGS) -c Creature.cpp

Vec2D.o: Vec2D.cpp Vec2D.hpp
	$(CXX) $(CXXFLAGS) -c Vec2D.cpp

clean:
	rm *.o

run:
	./main
