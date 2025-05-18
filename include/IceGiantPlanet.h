#ifndef ICE_GIANT_PLANET_H
#define ICE_GIANT_PLANET_H

#include "Planet.h"

struct ICE_GIANT_PLANET {
    struct PLANET super; 
};
typedef struct ICE_GIANT_PLANET* IceGiantPlanet;


IceGiantPlanet new_IceGiantPlanet(const char* name, int dayLength, const char* date);


void IceGiantPlanet_passHour(const IceGiantPlanet this);
void delete_IceGiantPlanet(const IceGiantPlanet this);

#endif
