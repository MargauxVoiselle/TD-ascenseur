#include <time.h>
#include <stdlib.h>
#include <ncurses.h>

#include "display.h"
#include "elevator.h"
#include "person.h"


int main()
{
    srand(time(NULL));   // ne doit être appelée qu'une seule fois
    
    // génération de la liste d'attente de personnes pour tous les étages
    int nbFloor = 5;
    int nbPerson = 5; // par étage initialement
    PersonList **waitingLists = malloc(nbFloor*sizeof(PersonList*));
    for(int currentFloor = 0 ; currentFloor < nbFloor ; currentFloor++)
    {
        waitingLists[currentFloor] = NULL; // initialise la liste de personnes de l'étage currentFloor
        for(int j = 0 ; j < nbPerson ; j++)
        {
            int dest = rand() % (nbFloor); // création d'une destination au hasard entre 0 et 5
            Person *p = createPerson(currentFloor, dest);
            waitingLists[currentFloor] = insert(p, waitingLists[currentFloor]);
        }
    }
    
    // initialisation de l'immeuble et de l'ascenseur
    int capacity = 3;
    int currentFloor = 0;
    Elevator *elevator = create_elevator(capacity, currentFloor , NULL);
    Building *building = create_building(nbFloor, elevator, waitingLists);

    // Initialize ncurse display
    initscr(); // initialize ncurses
    noecho();  // do not display in window the pressed keys
    halfdelay(2);

    WINDOW *win = newwin(HEIGHT, WIDTH, 0, 0);

    // Animation loop
    bool run=true;
    while(run)
    {
        // Generate people in function of input (or quit if 'q')
        int input = wgetch(win);
        if (input == 'q')
        {
            run = false;
        }
        else
        {
            int level = input - '0';
            if (0 <= level && level < nbFloor)
            {
                building->elevator->targetFloor = level;
                building->elevator->update = 0;
            }
        }

        // Update state machine of elevator !!!!
        stepElevator(building);

        wclear(win); // clear display area
        box(win, 0,0); // display border of window

        DisplayBuilding(win, building);

        wrefresh(win); // actual display function

    }

    endwin(); // correct ending of ncurses

    printf("%d persons out of %d reached their stage !\n", elevator->goal, nbFloor * nbPerson);
    if (elevator->goal == nbFloor * nbPerson)
    {
        printf("==========================\n");
        printf("Congratulations, you won !\n");
        printf("==========================\n");
    }
    else
    {
        printf("===============================\n");
        printf("Oh no ... You lost, try again !\n");
        printf("===============================\n");
    }
    
    return 0;
}
