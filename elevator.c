#include <stdio.h>
#include <stdlib.h>

#include "elevator.h"

// création de l'ascenseur
Elevator *create_elevator(int capacity, int currentFloor, PersonList *persons){
    Elevator *elevator = malloc(sizeof(Elevator));
    elevator->capacity = capacity;
    elevator->currentFloor = currentFloor;
    elevator->persons = persons;
    return elevator;
}

// création de l'immeuble
Building *create_building(int nbFloor, Elevator *elevator, PersonList **waitingLists){
    Building *building = malloc(sizeof(Building));
    building->nbFloor = nbFloor;
    building->elevator = elevator;
    building->waitingLists = waitingLists;
    return building;
}

// renvoie la liste de personnes qui descendent à un étage
PersonList *exitElevator(Elevator *elevator){
    PersonList *personsLeaving = NULL;
    int currentFloor = elevator->currentFloor; // étage de l'ascenseur
    PersonList *persons = elevator->persons; // personnes dans l'ascenseur
    int peopleInElevator = lengthPersonList(persons);
    Person *currentPerson = NULL;
    // pour toutes les personnes dans l'ascenseur
    for (int i = 0 ; i < peopleInElevator ; i++){
        currentPerson = persons->person;
        // si la personne doit descendre à cet étage
        if (currentPerson->dest == currentFloor){
            personsLeaving = insert(currentPerson, personsLeaving);
        }
        persons = persons->next;
    }
    // IL RESTE À CHANGER LA LISTE DES PERSONNES QUI RESTENT DANS L'ASCENSEUR
    
    return personsLeaving;
}

PersonList* enterElevator(Elevator *e, PersonList *list){

}