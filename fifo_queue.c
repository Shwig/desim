#include "fifo_queue.h"

/* Function creates a new linked list Qnode */
Qnode* new_node(int data) {
    struct Qnode *temp = (Qnode*)malloc(sizeof(Qnode));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

/* Functions returns a pointer to an empty queue*/
Queue *create_queue() {
    struct Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

/* Add an ellement to the rear of queue */
void en_queue( Queue *q, int data) {
    // Create a new node for the list to hold data
    Qnode *temp = new_node(data);

    // If queue is empty, then new node is both front and rear
    if (q->rear == NULL) {
       q->front = q->rear = temp;
       return;
    }

    // Add the new node at the end of queue and update the rear pointer
    q->rear->next = temp;
    q->rear = temp;
}

/* remove data from given queue q */
Qnode *de_queue(Queue *q) {
    // If queue is empty, return NULL.
    if (q->front == NULL) {
       return NULL;
     }

    // Store previous front and move front one node ahead
    Qnode *temp = q->front;
    q->front = q->front->next;

    // If front becomes NULL, then change rear also to NULL
    if (q->front == NULL) {
       q->rear = NULL;
     }
    return temp;
}
