#include "../include/Person.h"

Person new_Person(const char* name, int age, int lifeRemaining, const char* currentVehicle) {
    Person this = (Person)malloc(sizeof(struct PERSON));
    
    this->name = strdup(name);
    this->age = age;
    this->lifeRemaining = lifeRemaining;
    this->currentVehicle = strdup(currentVehicle);
    

    this->passHour = &Person_passHour;
    this->isAlive = &Person_isAlive;
    this->getName = &Person_getName;
    this->getAge = &Person_getAge;
    this->getLifeRemaining = &Person_getLifeRemaining;
    this->getCurrentVehicle = &Person_getCurrentVehicle;
    this->setCurrentVehicle = &Person_setCurrentVehicle;
    this->toString = &Person_toString;
    this->delete = &delete_Person;
    
    return this;
}

void Person_passHour(const Person this) {
    this->lifeRemaining--;
}

Boolean Person_isAlive(const Person this) {
    return (this->lifeRemaining > 0) ? TRUE : FALSE;
}

char* Person_getName(const Person this) {
    return strdup(this->name);
}

int Person_getAge(const Person this) {
    return this->age;
}

int Person_getLifeRemaining(const Person this) {
    return this->lifeRemaining;
}

char* Person_getCurrentVehicle(const Person this) {
    return strdup(this->currentVehicle);
}

void Person_setCurrentVehicle(const Person this, const char* currentVehicle) {
    free(this->currentVehicle);
    this->currentVehicle = strdup(currentVehicle);
}

char* Person_toString(const Person this) {

    int bufferSize = strlen(this->name) + 50 + strlen(this->currentVehicle);
    char* result = (char*)malloc(bufferSize);
    
    sprintf(result, "%s (Age: %d, Life Remaining: %d hours, Location: %s)",
            this->name, this->age, this->lifeRemaining, this->currentVehicle);
    
    return result;
}

void delete_Person(const Person this) {
    if (this == NULL) return;
    
    free(this->name);
    free(this->currentVehicle);
    free(this);
}
