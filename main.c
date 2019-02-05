#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "priority_queue.h"
#include "fifo_queue.h"

int main(int argc, char **argv) {
  Queue *q = create_queue();
  en_queue(q, 10);
  en_queue(q, 20);
  de_queue(q);
  de_queue(q);
  en_queue(q, 30);
  en_queue(q, 40);
  en_queue(q, 50);
  Qnode *n = de_queue(q);
  if (n != NULL) {
    printf("Dequeued item is %d", n->data);
  }
    return 0;

  // Event* pq = simulation_start();
  // print_event(pq);
  // printf("\n");

  // Event* pq = new_event(0, SIM_START, 0);
  // push_event(&pq, 1, JOB_ARRIVES, 1);
  // push_event(&pq, 3, JOB_ARRIVES, 2);
  // push_event(&pq, 9, JOB_ARRIVES, 3);
  // push_event(&pq, 2, FIN_CPU, 1);
  // push_event(&pq, 6, FIN_CPU, 2);

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
