#include "fifo_queue.h"

/* Function creates a new linked list Qnode */
Qnode* newNode(int data) {
    struct Qnode *temp = (struct Qnode*)malloc(sizeof(struct Qnode));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

/* Functions returns a pointer to an empty queue*/
Queue *createQueue() { 
    struct Queue *q = (struct Queue*)malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}
