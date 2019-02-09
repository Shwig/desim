#include "priority_queue.h"

/* Returns a random integer within the specified range
  min is lower bound, max is upper bound of the distribution. */
int rand_interval(unsigned int min, unsigned int max) {
  int this_rand = rand()%(max - min + 1) + min;
  return this_rand;
}

/* Create a new node in the Event priority queue
  Returns a pointer to the new Event node */
Event* new_event(int time, int job_number, int event_type) {
  Event* temp = (Event*)malloc(sizeof(Event));
  temp->time = time;
  temp->job_number = job_number;
  temp->event_type = event_type;
  temp->next = NULL;
  return temp;
}

// /* Return the even_type of the event with the highest priority */
// int get_type(Event** head) {
//   return (*head)->event_type;
// }

/* Return the even_type of the event with the highest priority */
void peek(Event** head, int* t, int* j, int* e) {
  *t = (*head)->time;
  *j = (*head)->job_number;
  *e = (*head)->event_type;
}

/* Add a new event to the priority queue. Events with
  a lower time value have greater priority and are moved towards
  the front of the queue */
void push_event(Event** head, int time, int job_number, int event_type) {

  Event* start = (*head);
  /* temp is the new node to be pushed into the queue */
  Event* temp = new_event(time,  job_number, event_type);

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

/* Remove the head element from the event queue by changing the head pointer
  and freeing the memory allocated to the old head pointer*/
void pop_event(Event** head) {
  Event* temp = *head;
  (*head) = (*head)->next;
  free(temp);
}

void print_queue(Event *n) {
  printf("\nThe event Queue: \n" );
  while (n != NULL) {
    printf(" Event_time: %7d, Job_number#: %7d, Event_type: %2d \n", n->time, n->job_number, n->event_type);
    n = n->next;
  }
  printf("\n");
}

Event* simulation_start(void) {
  Event* pq = new_event(0, 1, JOB_ARRIVES);
  push_event(&pq, 100, 0, SIM_END);
  return pq;
}

/* Check if hte list is empty */
int is_empty(Event** head) {
  return (*head) == NULL;
}

/*  */
void free_event_queue(Event* head) {

   struct Event* tmp;
   while (head != NULL) {
       tmp = head;
       head = head->next;
       free(tmp);
    }
}
