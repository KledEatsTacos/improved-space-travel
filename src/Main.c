#include "../include/Main.h"

int main(int argc, char *argv[]) {
    const char* PLANETS_FILE = "Gezegenler.txt";
    const char* SHIPS_FILE = "Araclar.txt";
    const char* PEOPLE_FILE = "Kisiler.txt";
    
    PlanetListNode* planets = FileReader_readPlanets(PLANETS_FILE);
    SpaceshipListNode* ships = FileReader_readSpaceships(SHIPS_FILE);
    PersonListNode* people = FileReader_readPeople(PEOPLE_FILE);
    
    FileReader_placePeople(people, planets, ships);
    
    Simulation simulation = new_Simulation(planets, ships, people);
    simulation->start(simulation);
    

    delete_SpaceshipList(ships, TRUE);
    delete_PlanetList(planets, TRUE);
    

    PersonListNode* currentPerson = people;
    while (currentPerson != NULL) {
        PersonListNode* next = currentPerson->next;
        currentPerson->person->delete(currentPerson->person);
        free(currentPerson);
        currentPerson = next;
    }
    
    simulation->delete(simulation);
    
    return 0;
}
