#ifndef FIFO_QUEUE_H
#define FIFO_QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Qnode {
  int job_number, event_time;
  struct Qnode *next;
}Qnode;

typedef struct Queue {
  int length;
  struct Qnode *rear, *front;
}Queue;

Qnode* new_empty_node();
Qnode* new_node(int event_time, int job_number);
Queue* create_queue();
void en_queue( Queue *q, int event_time, int job_number);
Qnode* de_queue(Queue *q);
void print_fifo(Queue *q);
void get_fifo_head(Queue **head, Qnode **node);
void free_fifo_queue(Queue **head);

#endif
