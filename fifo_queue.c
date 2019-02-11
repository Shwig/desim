#include "fifo_queue.h"

/* Function creates a new Qnode */
Qnode* new_node(int event_time, int job_number) {
    struct Qnode *temp = (Qnode*)malloc(sizeof(Qnode));
    temp->event_time = event_time;
    temp->job_number = job_number;
    temp->next = NULL;
    return temp;
}

/* Functions returns a pointer to an empty queue*/
Queue* create_queue() {
    struct Queue *q = (Queue*)malloc(sizeof(Queue));
    q->length = 0;
    q->front = q->rear = NULL;
    return q;
}

/* Add an ellement to the rear of queue */
void en_queue(Queue *q, int event_time, int job_number) {

    // the new node to be inserted in the list
    Qnode *temp = new_node(event_time, job_number);

    // If queue is empty, then new node is both front and rear
    // because the list was empty length of the list is now 1
    if (q->rear == NULL) {
      q->front = q->rear = temp;
      q->length++;
      return;
    }

    // Add the new node at the end of queue and update the rear pointer
    // add one to the length of the queue
    q->rear->next = temp;
    q->rear = temp;
    q->length++;
}

/* remove data from given queue q */
Qnode* de_queue(Queue *q) {
    // If queue is empty, return NULL.
    if (q->front == NULL) {
       return NULL;
     }

    // Store previous front and move front one node ahead
    Qnode *temp = q->front;
    q->front = q->front->next;
    q->length--;

    // If front becomes NULL, then change rear also to NULL
    if (q->front == NULL) {
       q->rear = NULL;
     }

    return temp;
}
