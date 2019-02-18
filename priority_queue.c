#include "priority_queue.h"

/* Returns a random integer within the specified range
  min is lower bound, max is upper bound of the distribution. */
int rand_interval(unsigned int min, unsigned int max) {
  int this_rand = rand()%(max - min + 1) + min;
  return this_rand;
}
/* Return a random float value in range [0,1]*/
float rand_floater() {
  return ((float)rand()/RAND_MAX);
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

/* Add a new event to the priority queue. Events with
  a lower time value have greater priority and are moved towards
  the front of the queue */
void push_event(Event **head, int time, int job_number, int event_type) {

  Event *start = (*head);
  /* temp is the new node to be pushed into the queue */
  Event *temp = new_event(time,  job_number, event_type);

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

/* copy the data elements of the head node */
void peek(Event **head, int *t, int *j, int *e) {
  *t = (*head)->time;
  *j = (*head)->job_number;
  *e = (*head)->event_type;
}

void print_queue(Event *n) {
  printf("\nThe event Queue: \n" );
  while (n != NULL) {
    printf(" Event_time: %7d, Job_number#: %7d, Event_type: %2d \n", n->time, n->job_number, n->event_type);
    n = n->next;
  }
  printf("\n");
}

Event* simulation_start(int start, int end) {
  Event *pq = new_event(start, 1, JOB_ARRIVES);
  push_event(&pq, end, 0, SIM_END);
  return pq;
}

/* Calculate the time the job will finish at the cpu and add it
  to the priority q */
void handle_event(Event **pq, int *config, int *sim_timer,
  int event_time, int job_number, int event_type ){

    int calculated_time = 0;

    switch(event_type) {

      // Deterimen time of next job arrival, push event into queue, report
      case JOB_ARRIVES :
        // deterimine arrival time of next job
        calculated_time = (*sim_timer) + rand_interval(config[0], config[1]);
        // push next job arrival into the priority queue
        push_event(&(*pq), calculated_time, (job_number ++), event_type);
        // report details about the changes to the priority queue
        printf("\n  ->Priority Queue update: \n     Event_time: %3d, Job_number#: %3d, Event_type: %2d \n",
          calculated_time, (job_number + 1), event_type);
      break;

      // Deterimen time process will finish, push event into queue, report
      case FIN_CPU :
      case FIN_DISK1 :
      case FIN_DISK2 :
        // calculate time the service will finish processing
        calculated_time = (*sim_timer) + rand_interval(config[0], config[1]);
        // add next finish event to the
        push_event(&(*pq), calculated_time, job_number, event_type);
        // report what happened
        printf("\n  ->Priority Queue update: \n     Event_time: %3d, Job_number#: %3d, Event_type: %2d \n",
          calculated_time, job_number, event_type);
      break;
      default:
      printf("\n\n **** Unknown Case Error ****\n  event_type %d was passed as function argg \n Location:\n File-> 'priorty_queue.c'\n Function-> 'handle_event()' \n\n ", event_type);
      break;
    }
}

/* Check if the list is empty notify stdout
  return true if head node points to NULL*/
int is_empty(Event **head) {
  if((*head) == NULL) {
    printf("\n  **The priority Queue is empty! \n");
  }
  return (*head) == NULL;
}

/* Remove the head element from the event queue by changing the head pointer
  and freeing the memory allocated to the old head pointer*/
void pop_event(Event **head) {
  Event *temp = *head;
  (*head) = (*head)->next;
  free(temp);
}

/*  empty the queue by popping all the nodes*/
void free_event_queue(Event **head) {
  while (*head != NULL) {
    pop_event(&(*head));
  }
}
