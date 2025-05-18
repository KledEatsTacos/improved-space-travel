#ifndef SIMULATION_H
#define SIMULATION_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Boolean.h"
#include "Person.h"
#include "Planet.h"
#include "RockPlanet.h"
#include "GasGiantPlanet.h"
#include "IceGiantPlanet.h"
#include "DwarfPlanet.h"
#include "Spaceship.h"
#include "FileReader.h"

struct SIMULATION {
    PlanetListNode* planets;
    SpaceshipListNode* ships;
    PersonListNode* allPeople;
    int hourCounter;
    Boolean simulationComplete;
    
    void (*start)(struct SIMULATION*);
    void (*delete)(struct SIMULATION*);
};
typedef struct SIMULATION* Simulation;

Simulation new_Simulation(PlanetListNode* planets, SpaceshipListNode* ships, PersonListNode* allPeople);
void Simulation_start(const Simulation this);
void delete_Simulation(const Simulation this);

#endif
