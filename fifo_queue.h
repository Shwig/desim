#ifndef FIFO_QUEUE_H
#define FIFO_QUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Qnode {
  int data;
  struct Qnode *next;
}Qnode;

typedef struct Queue {
  struct Qnode *front, *rear;
}Queue;

Qnode* newNode(int data);

#endif
