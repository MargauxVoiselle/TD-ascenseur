#include <time.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#include "display.h"
#include "elevator.h"
#include "person.h"

#define NB_FLOOR 5
#define NB_PERSON 5
#define TOTAL_PERSON NB_FLOOR * NB_PERSON
#define ELEVATOR_CAPACITY 3
#define CURRENT_FLOOR 0

int main()
{
    srand(time(NULL));   // ne doit être appelée qu'une seule fois
    
    // génération de la liste d'attente de personnes pour tous les étages
    PersonList **waitingLists = malloc(NB_FLOOR*sizeof(PersonList*));
    for (int currentFloor = 0 ; currentFloor < NB_FLOOR ; currentFloor++)
    {
        waitingLists[currentFloor] = NULL; // initialise la liste de personnes de l'étage currentFloor
        for (int j = 0 ; j < NB_PERSON ; j++)
        {
            int dest = rand() % (NB_FLOOR); // création d'une destination au hasard entre 0 et 5
            Person *p = createPerson(currentFloor, dest);
            waitingLists[currentFloor] = insert(p, waitingLists[currentFloor]);
        }
    }
    
    // Initialisation de l'immeuble et de l'ascenseur
    Elevator *elevator = create_elevator(ELEVATOR_CAPACITY, CURRENT_FLOOR , NULL);
    Building *building = create_building(NB_FLOOR, elevator, waitingLists);

    // Initialisation de l'affichage de ncurses
    initscr(); // initialise ncurses
    noecho();  // n'affiche pas à la fenêtre les touches rentrées
    halfdelay(2);

    WINDOW *win = newwin(HEIGHT, WIDTH, 0, 0);

    time_t start = time(NULL);
    // Boucle d'animation
    bool run=true;
    while (run)
    {
        // Réaction en fonction de la touche entrée (quitter avec 'q' ou continuer le jeu)
        int input = wgetch(win);
        if (input == 'q')
        {
            run = false;
        }
        else
        {
            int level = input - '0';
            if (0 <= level && level < NB_FLOOR)
            {
                building->elevator->targetFloor = level;
                building->elevator->update = 0;
            }
        }

        // Mise à jour de l'étage de l'ascenseur
        stepElevator(building);

        wclear(win); // nettoie la zone d'affichage
        box(win, 0,0); // affichage des bordures de la fenêtre

        DisplayBuilding(win, building);

        wrefresh(win); // rafraichissement de la fenêtre
    }

    endwin();

    // Affichage du chrono
    printf("The game lasted %lds\n", time(NULL) - start);
    
    // Affichage du résultat
    printf("%d persons out of %d reached their stage !\n", elevator->goal, TOTAL_PERSON);
    if (elevator->goal == TOTAL_PERSON)
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
