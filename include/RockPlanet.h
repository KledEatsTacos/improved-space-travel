#ifndef ROCK_PLANET_H
#define ROCK_PLANET_H

#include "Planet.h"

struct ROCK_PLANET {
    struct PLANET super;  
};
typedef struct ROCK_PLANET* RockPlanet;


RockPlanet new_RockPlanet(const char* name, int dayLength, const char* date);


void RockPlanet_passHour(const RockPlanet this);
void delete_RockPlanet(const RockPlanet this);

#endif
