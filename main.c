#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "priority_queue.h"
#include "fifo_queue.h"
#include "config_reader.h"

int main(int argc, char **argv) {

  // remember to free this later!
  Config *config = load_config();
  display_config(config);

  // seed random
  srand(config->conf_vals[SEED]);

  // time that the system will be initialized to
  int simulation_timer = config->conf_vals[INIT_TIME];
  int current_time, job_counter, cpu_counter, dsk1_counter, dsk2_counter = 0;

  // allocate space to keep track of priority q data after popping an event
  int *time, *job, *event;
  time = (int *)malloc(sizeof(int));
  job = (int *)malloc(sizeof(int));
  event = (int *)malloc(sizeof(int));

  //load the queue with the frst two events job arrives and sim finish
  Event* priority_q = simulation_start();

  //pinrt the queue
  print_queue(priority_q);

  // store the data members in the first Qnode
  printf("\n This event node will be popped: \n");
  peek(&priority_q, time, job, event);
  printf(" Event_time: %7d, Job_number#: %7d, Event_type: %2d \n", *time, *job, *event);

  pop_event(&priority_q);

  printf("\n Data from the popped node: \n");
  // peek(&priority_q, time, job, event);        <- This was the problem
  printf(" Event_time: %7d, Job_number#: %7d, Event_type: %2d \n", *time, *job, *event);

  print_queue(priority_q);


  //
  // while (sim_timer < config->conf_vals[FIN_TIME]) {
  //   sim_timer += rand_interval(config->conf_vals[ARRIVE_MIN], config->conf_vals[ARRIVE_MAX]);
  //   printf("%d\n", sim_timer);
  // }


  // Event* pq = simulation_start();
  // print_event(priority_q);
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

  free(time);
  free(job);
  free(event);
  return 0;
}
