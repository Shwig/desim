#include <stdio.h>
#include <stdlib.h>

/* Node is a linked list node */
typedef struct Node {
  int data;
  struct Node *next;
} Node;

/* Event struct to create a priority queue based on time.
  A smaller time value indicates a higher priority in the queue */
typedef struct Event{
  int time;
  int event_type;
  int job_number;
  struct Event *next;
} Event;

int rand_interval(unsigned int min, unsigned int max);
Event* new_event(int time, int event_type, int job_number);
void push_event(Event** head, int time, int event_type, int job_number);
void pop_event(Event** head);
void print_event(Event *n);
void print_list(struct Node *);
