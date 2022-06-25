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
    PersonList *personsStaying = NULL;
    int currentFloor = elevator->currentFloor; // étage de l'ascenseur
    PersonList *personsInElevator = elevator->persons; // personnes dans l'ascenseur
    int countOfPeopleInElevator = lengthPersonList(personsInElevator);
    Person *currentPerson = NULL;
    // pour toutes les personnes dans l'ascenseur
    for (int i = 0 ; i < countOfPeopleInElevator ; i++){
        currentPerson = personsInElevator->person;
        // si la personne doit descendre à cet étage
        if (currentPerson->dest == currentFloor){
            personsLeaving = insert(currentPerson, personsLeaving);
        }
        // si la personne ne descend pas à cet étage, elle reste
        else {
            personsStaying = insert(currentPerson, personsStaying);
        }
        personsInElevator = personsInElevator->next;
    }
    // mise à jour des personnes restantes dans l'ascenseur
    elevator->persons = personsStaying;

    return personsLeaving;
}

// fait entrer dans l'ascenseur les personnes qui attendent (sans dépasser la capacité de l'ascenseur) et renvoie la nouvelle liste d'attente
PersonList* enterElevator(Elevator *elevator, PersonList *waitingList){
    int lengthWaitingList = lengthPersonList(waitingList);
    int currentFloor = elevator->currentFloor;
    PersonList *personsInElevator = elevator->persons;
    int lengthPeopleInElevator = lengthPersonList(personsInElevator);
    while(lengthPeopleInElevator != elevator->capacity && waitingList){
        personsInElevator = insert(waitingList->person, personsInElevator);
        waitingList = waitingList->next;
        lengthPeopleInElevator++;
    }
    elevator->persons = personsInElevator;
    return waitingList;
}

// fonction qui simule le déplacement de l'ascenseur
void stepElevator(Building *building){
    if (building->elevator->currentFloor == building->elevator->targetFloor){
        exitElevator(building->elevator);
        int lengthCurrentWaitingList = lengthPersonList(*(building->waitingLists + building->elevator->currentFloor));
        *(building->waitingLists + building->elevator->currentFloor) = enterElevator(building->elevator, *(building->waitingLists + building->elevator->currentFloor));
    }
    else if (building->elevator->currentFloor > building->elevator->targetFloor){
        building->elevator->currentFloor--;
    }
    else{
        building->elevator->currentFloor++;
    }
}