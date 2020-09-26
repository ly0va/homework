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
void erase(struct Node**, struct Node**, int);
void swap(struct Node*);
void sort(struct Node**, struct Node**, int);

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
		printf("\nEnter + to add song, - to delete song, "
		       "? to view all songs, S to sort, Q to quit: ");
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
		} else if (option == '-') {
		    if (head == NULL || tail == NULL) {
		        printf("\nCAN'T!\n");
		    } else {
		        printf("\nPOSITION (0-indexed): ");
		        scanf("%d", &position);
		        erase(&head, &tail, length-position-1);
		        length--;
		    }
		} else if (option == '?') {
			viewSongs(tail);
		} else if (option == 'S') {
		    sort(&head, &tail, length);
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

void erase(struct Node** head, struct Node** tail, int position) {
    int index = 0;
    struct Node* current = *head;
    if (*head == *tail) {
        free(*head);
        *head = *tail = NULL;
    }
    else if (position == 0) {
        *head = (*head)->right;
        free((*head)->left);
        (*head)->left = NULL;
    } else {
        while (current->right != NULL && index < position) {
            current = current->right;
            index++;
        }
        if (current->right == NULL) {
            *tail = (*tail)->left;
            free((*tail)->right);
            (*tail)->right = NULL;
        } else {
            current->left->right = current->right;
            current->right->left = current->left;
            free(current);
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

void swap(struct Node* current) {
    struct Node* next = current->right;
    next->left = current->left;
    current->right = next->right;
    current->left = next;
    next->right = current;
    if (next->left != NULL) {
        next->left->right = next;
    }
    if (current->right != NULL) {
        current->right->left = current;
    }
}

void sort(struct Node** head, struct Node** tail, int length) {
    struct Node* current = NULL;
    while (length--) {
        for (current = *head; current->right != NULL; current = current->right) {
            if (current->song.duration < current->right->song.duration) {
                swap(current);
                current = current->left;
            }
        }
		while ((*head)->left != NULL) {
			*head = (*head)->left;
		}
		while ((*tail)->right != NULL) {
			*tail = (*tail)->right;
		}
    }
}



// аниме топчик, особенно дракошки <b>няшные</b> 
// <div style="width:400px;height:300px;background:url(https://s3.amazonaws.com/media-us-standrad/wp-content/uploads/2017/10/30172212/Screen-Shot-2017-10-30-at-10.21.10-AM.png)"></div>