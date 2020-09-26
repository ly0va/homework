/*
* FILE : fifo.c
* PROJECT : Mini Lab 3
* AUTHOR : Potomkin Lev
* DATE : 04.02.2019
* DESCRIPTION : 
*   This file contains an implementation of a simple circular buffer.
*   Console menu interface is provided for testing purposes - 
*   an infinite loop with `read` and `write` options.
*
*
* PSEUDOCODE : 
*
*   function readFrom(buffer):
*       if buffer is empty:
*           print error
*       else:
*           print the value at the consumer end
*           shift the pointer to the consumer end
*
*   function writeTo(buffer):
*       if buffer is full:
*           print error
*       else:
*           store the value at the producer end
*           shift the pointer to the producer end
*/

#include <stdio.h>
#define MAX_LENGTH 4

struct fifo {
    int buffer[MAX_LENGTH];  // the buffer itself
    int in;                  // producer end
    int out;                 // consumer end
    int length;              // current length
};

void write(struct fifo* myFifo);
void read(struct fifo* myFifo);

int main(void) {
    char option = '0';
    int value = 0;
    struct fifo myFifo = {{}, 0, 0, 0};

    while (1) {
        // Menu interface
        puts("\n1. Read\n2. Write\n");
        printf("Enter an option: ");
        scanf(" %c", &option);
        switch (option) {
            case '1': 
                read(&myFifo);
                break;
            case '2':
                write(&myFifo);
                break;
            default:
                puts("Invalid option!");
        }
    }
    return 0;
}

/*
* FUNCTION : write
* DESCRIPTION : 
*   Reads an int value from stdin and stores it in the circular buffer.
*   If the buffer is full, error is printed.
* PARAMETERS : 
*   struct fifo* myFifo : a buffer to store into
* RETURNS : none
*/
void write(struct fifo* myFifo) {
    int value = 0;
    if (myFifo->length == MAX_LENGTH) {
        puts("ERROR! Buffer is full!");
    } else {
        printf("Enter a value: ");
        scanf(" %d", &value);
        myFifo->buffer[myFifo->in] = value;
        myFifo->in = (myFifo->in + 1) % MAX_LENGTH;
        myFifo->length++;
        puts("Writing complete");
    }
}

/*
* FUNCTION : read
* DESCRIPTION : 
*   Reads a value from a given circular buffer and prints it to stdout.
*   If empty, error is printed.
* PARAMETERS : 
*   struct fifo* myFifo : a buffer to read from
* RETURNS : none
*/
void read(struct fifo* myFifo) {
    if (myFifo->length == 0)  {
        puts("ERROR! Buffer is empty!");
    } else {
        printf("You read %d\n", myFifo->buffer[myFifo->out]);
        myFifo->out = (myFifo->out + 1) % MAX_LENGTH;
        myFifo->length--;
    }
}
