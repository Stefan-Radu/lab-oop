### Celular Automata - Predator & Prey

Two tipes of creatures:
* predator
* prey

At each moment of time:
* The prey / Predator tries to move in a random direction.
* Health increases for prey and decreases for predator.
* When prey's health reaches a threshold:
  * They will reproduce, creating a new "Prey"
  * Their health resets to 1
* When predator's health reaches 0, they die and turn into "Nothing".
* When a predator moves on a prey's location:
  * They will eat it, turning it into a "predator" (reproducing)
  * Their health will increase by the amount of health the eaten prey had
