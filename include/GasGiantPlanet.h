#ifndef GAS_GIANT_PLANET_H
#define GAS_GIANT_PLANET_H

#include "Planet.h"

struct GAS_GIANT_PLANET {
    struct PLANET super; 
};
typedef struct GAS_GIANT_PLANET* GasGiantPlanet;


GasGiantPlanet new_GasGiantPlanet(const char* name, int dayLength, const char* date);


void GasGiantPlanet_passHour(const GasGiantPlanet this);
void delete_GasGiantPlanet(const GasGiantPlanet this);

#endif
