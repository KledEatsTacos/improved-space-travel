#include "../include/IceGiantPlanet.h"

IceGiantPlanet new_IceGiantPlanet(const char* name, int dayLength, const char* date) {
    IceGiantPlanet this = (IceGiantPlanet)malloc(sizeof(struct ICE_GIANT_PLANET));
    

    Planet basePlanet = new_Planet(name, ICE_GIANT, dayLength, date);
    

    this->super = *basePlanet;
    

    free(basePlanet);
    

    this->super.passHour = &Planet_passHour;
    this->super.delete = (void (*)(struct PLANET*))&delete_IceGiantPlanet;
    
    return this;
}

void IceGiantPlanet_passHour(const IceGiantPlanet this) {

    Planet_passHour((Planet)this);
}

void delete_IceGiantPlanet(const IceGiantPlanet this) {
    if (this == NULL) return;
    

    free(this->super.name);
    this->super.time->delete(this->super.time);
    delete_PersonList(this->super.population, FALSE);
    

    free(this);
}
