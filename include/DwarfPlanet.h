#ifndef DWARF_PLANET_H
#define DWARF_PLANET_H

#include "Planet.h"

struct DWARF_PLANET {
    struct PLANET super;
};
typedef struct DWARF_PLANET* DwarfPlanet;


DwarfPlanet new_DwarfPlanet(const char* name, int dayLength, const char* date);


void DwarfPlanet_passHour(const DwarfPlanet this);
void delete_DwarfPlanet(const DwarfPlanet this);

#endif
