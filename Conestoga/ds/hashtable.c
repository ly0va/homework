/*
 * FILE: Major2-LevPotomkin.c
 * PROJECT: Major Lab #2
 * AUTHOR: Lev Potomkin
 * DATE: Feb 20, 2019
 * DESCRIPTION: 
 *  This program contains an implementation of
 *  a simple hash table.
 *  It reads from a file `customers.dat` in the
 *  same directory, inserts `name, age` entries
 *  from a file into a hash table and ouputs the 
 *  sum of ages in a particular bucket to stdout.
 *  Bucket index is provided by a command line argument.
 * USAGE: ./a.out index
 * TEST FILE:
 *  Jane Doe, 1
 *  Jane Doe, 2
 *  Jane Doe, 3
 *  Jane Doe, 4
 *  Bob Jones, 5
 *  Alice Cooper, 6
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TOTAL_BUCKETS 256
#define MAX_SIZE 128

// A struct representing linked list node
struct node {
	char name[MAX_SIZE];
    int age;
	struct node *next;
};

void insert(struct node **buckets, char *name, int age);
int get_sum(struct node *bucket);
int hash(char* string);

int main(int argc, char **argv) {
    struct node* buckets[TOTAL_BUCKETS] = {};  // the hash table
    char buffer[MAX_SIZE] = "";
    char name[MAX_SIZE] = "";
    char age[MAX_SIZE] = "";
    char *comma = NULL;
    int index = atoi(argv[1]);
    FILE* input = fopen("customers.dat", "r");

    if (input != NULL) { // file exists
        for (int line = 1; fgets(buffer, sizeof buffer, input); line++) {
            comma = strchr(buffer, ','); // find a comma
            if (comma == NULL) {
                printf("Comma missing on line %d\n", line);
            } else {
                strncpy(name, buffer, comma-buffer);  // extract name
                strcpy(age, comma+1);                 // extract age
                insert(buckets, name, atoi(age));     // insert entry
            }
        }
        printf("%d\n", get_sum(buckets[index]));      // find the sum
    } else {
        printf("File not found\n");
    }

    return 0;
}

/*
 * FUNCTION: hash
 * DESCRIPTION: 
 *  Calculates a simple hash function on a string -
 *  a sum of all ASCII values modulo 256
 * PARAMETERS: 
 *  char* string: a string to be taken hash of
 * RETURNS:
 *  int: hash value of a given string
 */
int hash(char *string) {
    int length = strlen(string);
    unsigned char digest = 0;
    for (int i = 0; i < length; i++) {
        digest += string[i]; 
    }
    return digest;
}

/*
 * FUNCTION: insert
 * DESCRIPTION: 
 *  Inserts a (name, age) entry into the hash table
 * PARAMETERS: 
 *  struct node **buckets: a hash table to insert into
 *  char *name: first part of the entry - name
 *  int age: second part of the entry - age
 * RETURNS: none
 */
void insert(struct node **buckets, char *name, int age) {
    int index = hash(name);
    struct node *new_head = malloc(sizeof(struct node));
    strcpy(new_head->name, name);
    new_head->age = age;
    new_head->next = buckets[index];
    buckets[index] = new_head;
}

/*
 * FUNCTION: hash
 * DESCRIPTION: 
 *  Calculates the sum of ages found in a given bucket
 * PARAMETERS: 
 *  struct node *bucket: a given bucket
 * RETURNS:
 *  int: sum of ages found in a given bucket
 */
int get_sum(struct node *bucket) {
    int sum = 0;
    while (bucket != NULL) {
        sum += bucket->age;
        bucket = bucket->next;
    }
    return sum;
}
