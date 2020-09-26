/*
* FILE : listC.c
* PROJECT : SENG1050 - Lab 2
* PROGRAMMER : Potomkin Lev
* FIRST VERSION : 1/15/2019
* DESCRIPTION :
*    Implementation of doubly-linked list
*    with insert function.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Song {
	char name[21];
	int duration;
	char copyright;
};

struct Node {
	struct Song song;
	struct Node* right;
	struct Node* left;
};

void viewSongs(struct Node*);
void insert(struct Node**, struct Node**, int, char*, int, char);

int main(void) {
    struct Node* head = NULL;
    struct Node* tail = NULL;
    char option = 0;
    int duration = 0;
    char copyright = 0;
    char name[21] = ""; 
    int position = 0;
    int length = 0;
    
    do {
		printf("\nEnter + to add song, ? to view all songs, Q to quit: ");
		scanf(" %c", &option);
		
		if (option == '+') {
			printf("\nNAME: ");
			scanf("%s", name);
			printf("DURATION: ");
			scanf("%d", &duration);
			printf("COPYRIGHT? (0/1): ");
			scanf(" %c", &copyright);
			printf("POSITION (0-indexed): ");
			scanf("%d", &position);
			insert(&head, &tail, length-position, name, duration, copyright);
			length++;
		} else if (option == '?') {
			viewSongs(tail);
		} else if (option != 'Q') {
			printf("ERROR!\n");
		}
		
	} while (option != 'Q');
	
    return 0;
}

/* (head)-()-()-()-(tail) */
void insert(struct Node** head, struct Node** tail, 
            int position, char* name, int duration, char copyright) {
          
	int index = 0;  
    struct Node* current = *head;
	struct Node* inserted = malloc(sizeof(struct Node));
	strcpy(inserted->song.name, name);
	inserted->song.duration = duration;
	inserted->song.copyright = copyright;
	inserted->right = inserted->left = NULL;
	
	if (*head == NULL || *tail == NULL) {
	    *head = *tail = inserted;
	} else if (position == 0) {
	    inserted->right = *head;
	    (*head)->left = inserted;
	    *head = inserted;
	} else {
	    while (current != NULL && index < position) {
	        current = current->right;
	        index++;
	    }
	    if (current == NULL) {
	        inserted->left = (*tail);
	        (*tail)->right = inserted;
	        *tail = inserted;
	    } else {
	        inserted->left = current->left;
	        inserted->right = current;
	        current->left = inserted;
	        inserted->left->right = inserted;
	    }
	}
}

void viewSongs(struct Node* tail) {
	if (tail == NULL) {
		printf("\nNONE\n");
	}
	while (tail != NULL) {
		printf("\nNAME: %s\nDURATION: %d\nCOPYRIGHT: %c\n", 
		       tail->song.name, tail->song.duration, tail->song.copyright);
		tail = tail->left;
	}
}


