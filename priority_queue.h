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
  int time;
  int event_type;
  int job_number;
  struct Event *next;
} Event;

int rand_interval(unsigned int min, unsigned int max);
Event* new_event(int time, int event_type, int job_number);
void push_event(Event** head, int time, int event_type, int job_number);
int get_job(Event** head);
void pop_event(Event** head);
void print_event(Event *n);
Event* simulation_start(void);

#endif
