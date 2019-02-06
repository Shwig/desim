#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "priority_queue.h"
#include "fifo_queue.h"
#include "config_reader.h"

int main(int argc, char **argv) {

  const char *conf_types[NUM_PARAMS] = {
    "SEED", "INIT_TIME", "FIN_TIME", "ARRIVE_MIN", "ARRIVE_MAX",
    "CPU_MIN", "CPU_MAX", "DISK1_MIN", "DISK1_MAX", "DISK2_MIN", "DISK2_MAX"
  };

  // remember to free this later!
  Config *cp = load_config();
  display_config(cp);

  // printf( "\nafter reading and setting values : \n" );
  // printf( "string : %s value : %d index : %d\n", conf_types[TIME_A], cp->conf_vals[TIME_A], TIME_A );
  // printf( "string : %s value : %d index : %d\n", conf_types[TIME_B], cp->conf_vals[TIME_B], TIME_B );
  // printf( "%f : PROB_QUIT\n", cp->PROB_QUIT );

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
