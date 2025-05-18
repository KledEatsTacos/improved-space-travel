#ifndef FILE_READER_H
#define FILE_READER_H

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


typedef struct PlanetListNode {
    Planet planet;
    struct PlanetListNode* next;
} PlanetListNode;


typedef struct SpaceshipListNode {
    Spaceship spaceship;
    struct SpaceshipListNode* next;
} SpaceshipListNode;


PlanetListNode* FileReader_readPlanets(const char* filePath);
SpaceshipListNode* FileReader_readSpaceships(const char* filePath);
PersonListNode* FileReader_readPeople(const char* filePath);
void FileReader_placePeople(PersonListNode* people, PlanetListNode* planets, SpaceshipListNode* ships);


PlanetListNode* new_PlanetListNode(Planet planet);
void add_PlanetListNode(PlanetListNode** head, Planet planet);
int count_PlanetList(PlanetListNode* head);
void delete_PlanetList(PlanetListNode* head, Boolean deletePlanets);
Planet find_PlanetByName(PlanetListNode* head, const char* name);


SpaceshipListNode* new_SpaceshipListNode(Spaceship spaceship);
void add_SpaceshipListNode(SpaceshipListNode** head, Spaceship spaceship);
int count_SpaceshipList(SpaceshipListNode* head);
void delete_SpaceshipList(SpaceshipListNode* head, Boolean deleteSpaceships);
Spaceship find_SpaceshipByName(SpaceshipListNode* head, const char* name);

#endif
