#include "../include/DwarfPlanet.h"

DwarfPlanet new_DwarfPlanet(const char* name, int dayLength, const char* date) {
    DwarfPlanet this = (DwarfPlanet)malloc(sizeof(struct DWARF_PLANET));
    

    Planet basePlanet = new_Planet(name, DWARF_PLANET, dayLength, date);
    

    this->super = *basePlanet;
    
  
    free(basePlanet);
    

    this->super.passHour = &Planet_passHour;
    this->super.delete = (void (*)(struct PLANET*))&delete_DwarfPlanet;
    
    return this;
}

void DwarfPlanet_passHour(const DwarfPlanet this) {


    Planet_passHour((Planet)this);
}

void delete_DwarfPlanet(const DwarfPlanet this) {
    if (this == NULL) return;
    

    free(this->super.name);
    this->super.time->delete(this->super.time);
    delete_PersonList(this->super.population, FALSE); 
    

    free(this);
}
