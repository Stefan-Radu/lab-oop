### Celular Automata - Predator & Prey

The final goal of this automata is to simulate a world inhabited by two types of creatures: predators and prey.

Each creature moves in a random direction.

Prey is rewarded for staying alive. Thus at each moment its health rises by a certain amount. If it reached a certain treshold, the prey reproduces.

Predators are rewarded for hunting. They lose health at each moment, unless they move onto a cell where there is prey. In that case, the predator heals by consuming the prey and a new predator is born.
