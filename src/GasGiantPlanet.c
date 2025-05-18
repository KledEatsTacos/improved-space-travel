#include "../include/GasGiantPlanet.h"

GasGiantPlanet new_GasGiantPlanet(const char* name, int dayLength, const char* date) {
    GasGiantPlanet this = (GasGiantPlanet)malloc(sizeof(struct GAS_GIANT_PLANET));
    

    Planet basePlanet = new_Planet(name, GAS_GIANT, dayLength, date);
    

    this->super = *basePlanet;
    

    free(basePlanet);
    
 
    this->super.passHour = &Planet_passHour;
    this->super.delete = (void (*)(struct PLANET*))&delete_GasGiantPlanet;
    
    return this;
}

void GasGiantPlanet_passHour(const GasGiantPlanet this) {

    Planet_passHour((Planet)this);
}

void delete_GasGiantPlanet(const GasGiantPlanet this) {
    if (this == NULL) return;
    

    free(this->super.name);
    this->super.time->delete(this->super.time);
    delete_PersonList(this->super.population, FALSE); 
    

    free(this);
}
