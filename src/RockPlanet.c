#include "../include/RockPlanet.h"

RockPlanet new_RockPlanet(const char* name, int dayLength, const char* date) {
    RockPlanet this = (RockPlanet)malloc(sizeof(struct ROCK_PLANET));
    

    Planet basePlanet = new_Planet(name, ROCK_PLANET, dayLength, date);
    

    this->super = *basePlanet;
    

    free(basePlanet);
    

    this->super.passHour = &Planet_passHour;
    this->super.delete = (void (*)(struct PLANET*))&delete_RockPlanet;
    
    return this;
}

void RockPlanet_passHour(const RockPlanet this) {

    this->super.time->increaseHour(this->super.time);
    

    PersonListNode* current = this->super.population;
    while (current != NULL) {

        current->person->passHour(current->person);
        current = current->next;
    }
    

    PersonListNode* alivePopulation = filter_AlivePersons(this->super.population);
    delete_PersonList(this->super.population, FALSE); 
    this->super.population = alivePopulation;
}

void delete_RockPlanet(const RockPlanet this) {
    if (this == NULL) return;
    

    free(this->super.name);
    this->super.time->delete(this->super.time);
    delete_PersonList(this->super.population, FALSE); 
    

    free(this);
}
