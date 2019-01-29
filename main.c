#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "desim_functions.h"

/* these marcos will be used to define the job types
  in the priorty queue. */
#define SIM_END 0
#define SIM_START 1
#define ARR_CPU 2
#define FIN_CPU 3
#define FIN_DISK1 4
#define FIN_DISK2 5

int main(int argc, char **argv){

  Event* pq = new_event(0, SIM_START, 0);
  push_event(&pq, 1, ARR_CPU, 1);
  push_event(&pq, 3, ARR_CPU, 2);
  push_event(&pq, 9, ARR_CPU, 3);
  push_event(&pq, 2, FIN_CPU, 1);
  push_event(&pq, 6, FIN_CPU, 2);

  print_event(pq);
  printf("\n");

  // srand(1);
  // printf("%d\n", rand_interval(8,9));
  //
  // printf("\n");

  // Node* head = NULL;
  // Node* second = NULL;
  // Node* third = NULL;
  //
  // // allocate 3 nodes in the heap
  // head = (Node*)malloc(sizeof(struct Node));
  // second = (Node*)malloc(sizeof(struct Node));
  // third = (Node*)malloc(sizeof(struct Node));
  //
  // head->data = 1; // assign data to the first node
  // head->next = second; // reference to the next list node
  //
  // second->data = 2;
  // second->next = third;
  //
  // third->data = 3;
  // third->next = NULL;
  //
  // print_list(head);

  return 0;
}
