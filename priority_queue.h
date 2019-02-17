#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdio.h>
#include <stdlib.h>

/* these marcos will be used to define the job types
  in the priorty queue. */
#define SIM_END 0
#define SIM_START 1
#define JOB_ARRIVES 2
#define FIN_CPU 3
#define FIN_DISK1 4
#define FIN_DISK2 5

/* Event struct to create a priority queue based on time.
  A smaller time value indicates a higher priority in the queue */
typedef struct Event {
  int time, job_number, event_type;
  struct Event *next;
} Event;

int rand_interval(unsigned int min, unsigned int max);
float rand_floater();
Event* new_event(int time, int job_number, int event_type);
void push_event(Event** head, int time, int job_number, int event_type);
void peek(Event** head, int *t, int *j, int *e);
void pop_event(Event **head);
void print_queue(Event *n);
Event* simulation_start(int start, int end);
void handle_event(Event **pq, int *config, int *sim_timer, int event_time, int job_number, int event_type );
int is_empty(Event **head);
void free_event_queue(Event **head);

#endif
