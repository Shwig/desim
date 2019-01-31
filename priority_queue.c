#include "priority_queue.h"

/* Returns a random integer within the specified range
  min is lower bound, max is upper bound of the distribution. */
int rand_interval(unsigned int min, unsigned int max) {
  int this_rand = rand()%(max - min + 1) + min;
  return this_rand;
}

/* Create a new node in the Event priority queue
  Returns a pointer to the new Event node */
Event* new_event(int time, int event_type, int job_number) {
  Event* temp = (Event*)malloc(sizeof(Event));
  temp->time = time;
  temp->event_type = event_type;
  temp->job_number = job_number;
  temp->next = NULL;
  return temp;
}

/* Return the even_type of the event with the highest priority */
int get_type(Event** head) {
  return (*head)->event_type;
}

/* Add a new event to the priority queue. Events with
  a lower time value have greater priority and are moved towards
  the front of the queue */
void push_event(Event** head, int time, int event_type, int job_number) {

  Event* start = (*head);
  /* temp is the new node to be pushed into the queue */
  Event* temp = new_event(time, event_type, job_number);

  /* If the head of the list has time value greater than
    the new node, make the new node the head node */
  if ((*head)->time > time) {
    temp->next = *head;
    (*head) = temp;
  } else { // traverse and find position to insert the new node
    /* while there are more nodes after the starting position in the list and
      the time value of the next node is less than the time of the new
      node */
    while (start->next != NULL && start->next->time < time) {
      start = start->next;
    }

    temp->next = start->next;
    start->next = temp;
  }
}

/* Check if hte list is empty */
int isEmpty(Event** head) {
  return (*head) == NULL;
}

/* Remove the head element from the event queue by changing the head pointer
  and freeing the memory allocated to the old head pointer*/
void pop_event(Event** head) {
  Event* temp = *head;
  (*head) = (*head)->next;
  free(temp);
}

void print_event(Event *n) {
  while (n != NULL) {
    printf(" time:%d, type:%d, J#%d \n", n->time, n->event_type, n->job_number);
    n = n->next;
  }
}

Event* simulation_start(void) {
  Event* pq = new_event(0, JOB_ARRIVES, 1);
  push_event(&pq, 100, SIM_END, NULL);
  return pq;
}

// /* function to print the contents of a linked list
//    starting from the given node.
//    While the node is not NULL print the data in the node
//    traverse to the next node in the list. */
// void print_list(struct Node *n){
//   while (n != NULL){
//     printf(" %d ", n->data);
//     n = n->next;
//   }
// }
