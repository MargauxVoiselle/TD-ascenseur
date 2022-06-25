#include <time.h>
#include <stdlib.h>
#include <ncurses.h>

#include "elevator.h"
#include "person.h"

#define HEIGHT 30
#define WIDTH 40
#define PERSON_WIDTH 3

void DisplayPersonList(WINDOW *win, PersonList *list, int level, int offset) {
  while(list != NULL) {
    // display 25 for a person going from floor 2 to floor 5
    mvwaddch(win, level, offset, '0' + list->person->src);
    mvwaddch(win, level, offset+1, '0' + list->person->dest);
    list = list->next;
    offset+= PERSON_WIDTH;
  }
}

void DisplayElevator(WINDOW *win, int nbFloor, Elevator *e, int offset) {
  //Display elevator
  // [23 24 31 30 42]
 
  int level = 3*(nbFloor - e->currentFloor); // 3 lines per level
  mvwaddch(win, level, offset+1, '[');
  DisplayPersonList(win, e->persons, level, offset+2);
  mvwaddch(win, level, offset+2+ (PERSON_WIDTH*e->capacity), ']');
}

void DisplayBuilding(WINDOW *win, Building *b) {
  int offset = 1;

  // display wall
  // |                |
  // |[23 24 31 30 42]| 31 32
  // |                |
  int right_wall = offset + 3 + (PERSON_WIDTH*b->elevator->capacity);
  for(int i=0; i < b->nbFloor; ++i) {
    int level = 3*i+1;
    mvwaddch(win,level,  offset,'|');
    mvwaddch(win,level+1,offset,'|');
    mvwaddch(win,level,  right_wall,'|');
    mvwaddch(win,level+1,right_wall,'|');
  }
  for(int i=offset+1; i < right_wall; i++) {
    mvwaddch(win,3*(b->nbFloor)+1,i,'_');
  }

  DisplayElevator(win, b->nbFloor, b->elevator, offset);

  for(int i=0; i < b->nbFloor; i++) {
    int level = 3*(b->nbFloor - i);
    DisplayPersonList(win,b->waitingLists[i], level, right_wall + 2);
  }
}


int main() {
    srand(time(NULL));   // ne doit être appelée qu'une seule fois

    
    // génération de la liste d'attente de personnes pour tous les étages -- OK --
    int nbFloor = 5;
    // int lengthList = 0;
    PersonList **waitingLists = malloc(nbFloor*sizeof(PersonList*));
    for(int currentFloor = 0 ; currentFloor < nbFloor ; currentFloor++) {
        waitingLists[currentFloor] = NULL; // initialise la liste de personnes de l'étage currentFloor
        int nbPerson = 5; // 5 personnes dans la file d'attente waitingLists[currentFloor]
        for(int j = 0 ; j < nbPerson ; j++) {
            printf("Coucou\n");
            int dest = rand() % (nbFloor); // création d'une destination au hasard entre 0 et 5
            Person *p = createPerson(currentFloor, dest);
            waitingLists[currentFloor] = insert(p, waitingLists[currentFloor]);
        }
        // printPersonList(waitingLists[currentFloor]); // affiche la liste de personnes en attente dans chaque étage
        // lengthList = lengthPersonList(waitingLists[currentFloor]);
        // printf("Il y a %d personnes dans la file d'attente !\n", lengthList);
    }
    
    
    // initialisation de l'immeuble et de l'ascenseur --OK--
    int capacity = 3;
    int currentFloor = 0;
    Elevator *elevator = create_elevator(capacity, currentFloor , NULL);
    Building *building = create_building(nbFloor, elevator, waitingLists);

    // test
    // PersonList *persons = NULL;
    // Person *person = createPerson(0, 1);
    // persons = insert(person, persons);
    // person = createPerson(0, 2);
    // persons = insert(person, persons);
    // printf("Les personnes dans l'ascenseur sont :");
    // printPersonList(persons);
    // Elevator *elevator = create_elevator(4, 0, persons);
    // elevator->currentFloor = 1;
    // PersonList *personsLeaving = exitElevator(elevator);
    // printf("Les personnes qui sortent sont : \n");
    // printPersonList(personsLeaving);
    // printf("Les personnes qui restent sont :\n");
    // printPersonList(elevator->persons);
    // int length = lengthPersonList(elevator->persons);
    // printf("%d\n", length);
    // Elevator *elevator = create_elevator(4, 0, persons);
    // PersonList *peopleInWaitingList = NULL;
    // person = createPerson(0, 3);
    // peopleInWaitingList = insert(person, peopleInWaitingList);
    // person = createPerson(0, 2);
    // peopleInWaitingList = insert(person, peopleInWaitingList);
    // person = createPerson(0, 1);
    // peopleInWaitingList = insert(person, peopleInWaitingList);
    // printf("Les personnes attendant sont :\n");
    // printPersonList(peopleInWaitingList);
    // printf("--------------\n");
    // printf("Les personnes dans l'ascenseur sont : \n");
    // printPersonList(elevator->persons);
    // PersonList *waitingList = enterElevator(elevator, peopleInWaitingList);
    // printf("Les personnes attendant maintenant sont :\n");
    // printPersonList(waitingList);
    // printf("Les personnes dans l'ascenseur sont : \n");
    // printPersonList(elevator->persons);


  // Initialize ncurse display
  initscr(); // initialize ncurses
  noecho();  // do not display in window the pressed keys
  halfdelay(2);

  WINDOW *win = newwin(HEIGHT, WIDTH, 0, 0);

  // Animation loop
  bool run=true;
  while(run) {
    // Generate people in function of input (or quit if 'q')
    int input = wgetch(win);
    if(input == 'q') {
      run = false;
    } else {
      int level = input - '0';
      if(0 <= level && level < nbFloor) {
	building->elevator->targetFloor = level;
      }
    }

    // Update state machine of elevator !!!!

    stepElevator(building);

    wclear(win);   // clear display area
    box(win, 0,0); // display border of window

    DisplayBuilding(win, building);

    wrefresh(win); // actual display function

  }

  endwin(); // correct ending of ncurses

  return 0;
}
