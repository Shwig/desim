#include "fifo_queue.h"

Qnode* new_empty_node() {
  Qnode *temp = (Qnode*)malloc(sizeof(Qnode));
  temp->event_time = 0;
  temp->job_number = 0;
  temp->next = NULL;
  return temp;
}

/* Function creates a new Qnode */
Qnode* new_node(int event_time, int job_number) {
    Qnode *temp = (Qnode*)malloc(sizeof(Qnode));
    temp->event_time = event_time;
    temp->job_number = job_number;
    temp->next = NULL;
    return temp;
}

/* Functions returns a pointer to an empty queue*/
Queue* create_queue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->length = 0;
    q->front = q->rear = NULL;
    return q;
}

/* Add an ellement to the rear of queue */
void en_queue(Queue *q, int event_time, int job_number) {

    // the new node to be inserted in the list
    Qnode *temp = new_node(event_time, job_number);

    printf("\n  ->New job en_queue \n");
    printf("     Event_time: %3d, Job_number#: %3d \n", temp->event_time, temp->job_number);
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
      printf("**********The Queue was empty************\n" );
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

     printf("\n  ->Job De_queued \n");
     printf("     Event_time: %3d, Job_number#: %3d \n", temp->event_time, temp->job_number);
     // printf(" ******Qnode before de_queue return is -> Event_time: %7d, Job_number#: %7d \n", temp->event_time, temp->job_number);
    return temp;
}

void print_fifo(Queue *q) {
  Qnode *temp = q->front;
  printf("\nThe fifo Queue:\n");
  while (q->front != NULL) {
    printf(" Event_time: %7d, Job_number#: %7d \n", q->front->event_time, q->front->job_number);
    q->front = q->front->next;
  }
  q->front = temp;
}
