
all: compile run

compile:	
	gcc -I ./include/ -o ./lib/Time.o -c ./src/Time.c
	gcc -I ./include/ -o ./lib/Person.o -c ./src/Person.c
	gcc -I ./include/ -o ./lib/Spaceship.o -c ./src/Spaceship.c
	gcc -I ./include/ -o ./lib/Planet.o -c ./src/Planet.c
	gcc -I ./include/ -o ./lib/RockPlanet.o -c ./src/RockPlanet.c
	gcc -I ./include/ -o ./lib/GasGiantPlanet.o -c ./src/GasGiantPlanet.c
	gcc -I ./include/ -o ./lib/IceGiantPlanet.o -c ./src/IceGiantPlanet.c
	gcc -I ./include/ -o ./lib/DwarfPlanet.o -c ./src/DwarfPlanet.c
	gcc -I ./include/ -o ./lib/FileReader.o -c ./src/FileReader.c
	gcc -I ./include/ -o ./lib/Simulation.o -c ./src/Simulation.c
	gcc -I ./include/ -o ./bin/Program ./lib/Time.o ./lib/Person.o ./lib/Spaceship.o ./lib/Planet.o ./lib/RockPlanet.o ./lib/GasGiantPlanet.o ./lib/IceGiantPlanet.o ./lib/DwarfPlanet.o ./lib/FileReader.o ./lib/Simulation.o ./src/Main.c -lm

run:
	./bin/Program

clean:
	rm -f ./lib/*.o
	rm -f ./bin/Program