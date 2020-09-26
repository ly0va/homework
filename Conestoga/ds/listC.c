/*
* FILE : listC.c
* PROJECT : SENG1050 - Lab 2
* PROGRAMMER : Potomkin Lev
* FIRST VERSION : 1/15/2019
* DESCRIPTION :
*    Implementation of singly-linked list.
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
	struct Node* next;
};

void viewSongs(struct Node*);
struct Node* addSong(struct Node*, char*, int, char);

int main(void) {
    struct Node* head = NULL;
    char option = 0;
    int duration = 0;
    char copyright = 0;
    char name[21] = ""; 
    
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
			head = addSong(head, name, duration, copyright);
		} else if (option == '?') {
			viewSongs(head);
		} else if (option != 'Q') {
			printf("ERROR!\n");
		}

	} while (option != 'Q');

    return 0;
}

struct Node* addSong(struct Node* head, char* name, 
					 int duration, char copyright) {
	struct Node* added = malloc(sizeof(struct Node));
	added->next = head;
	strcpy(added->song.name, name);
	added->song.duration = duration;
	added->song.copyright = copyright;
	return added;
}

void viewSongs(struct Node* head) {
	if (head == NULL) {
		printf("\nNONE\n");
	}
	while (head != NULL) {
		printf("\nNAME: %s\nDURATION: %d\nCOPYRIGHT: %c\n", 
		       head->song.name, head->song.duration, head->song.copyright);
		head = head->next;
	}
}
