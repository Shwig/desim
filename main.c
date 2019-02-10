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

  // start and end time of the simulation from config.file
  int simulation_timer = config->conf_vals[INIT_TIME];
  int end_time = config->conf_vals[FIN_TIME];
  int arrive_params[4] = {
    config->conf_vals[ARRIVE_MIN],config->conf_vals[ARRIVE_MAX],
    config->conf_vals[CPU_MIN],config->conf_vals[CPU_MAX]
  };

  // counters and time vars
  int next_jtime, cpu_fintime, job_counter, cpu_counter, dsk1_counter, dsk2_counter = 0;

  // allocate space to keep track of priority q data after popping an event
  int *event_time, *job_number, *event_type;
  event_time = (int *)malloc(sizeof(int));
  job_number = (int *)malloc(sizeof(int));
  event_type = (int *)malloc(sizeof(int));

  /* initialize queue with the first two events job arrives and sim finish
    usine init time and fin time from config.file*/
  Event* priority_q = simulation_start(simulation_timer, end_time);

  printf("\n  Queue after init 0: \n");
  print_queue(priority_q);

  /* While the priority queue is not empty and the simulation_timer
    hasnt reached the FIN_TIME from config file*/
  while((!is_empty(&priority_q)) && (simulation_timer < end_time)) {

    //READ EVENT FROM Queue
    // get all the data about the head node;
    peek(&priority_q, event_time, job_number, event_type);

    // pop the head node
    pop_event(&priority_q);

    // if current event_type is a job arrival
    if (*event_type == JOB_ARRIVES ) {
      // current time of sim becomes time of the popped event
      simulation_timer = *event_time;
      printf("\n\nSimulation_timer:%d\n", simulation_timer );
      job_arrives(&priority_q, arrive_params, &simulation_timer, *event_time, *job_number, *event_type);
    } else {
      // current time of sim becomes time of the popped event
      simulation_timer = *event_time;
      printf("\n\n!!!This function does not handle event type: %d", *event_type );
      break;
    }

  } // end while
  printf("\n  Queue after While loop: \n");
  print_queue(priority_q);

  // //pinrt the queue
  // print_queue(priority_q);
  //
  // // store the data members in the first Qnode
  // printf("\nThis event node will be popped: \n");
  // peek(&priority_q, time, job, event);
  // printf(" Event_time: %7d, Job_number#: %7d, Event_type: %2d \n", *time, *job, *event);
  //
  // pop_event(&priority_q);
  //
  // printf("\nData from the popped node: \n");
  // // peek(&priority_q, time, job, event);        <- This was the problem
  // printf(" Event_time: %7d, Job_number#: %7d, Event_type: %2d \n", *time, *job, *event);
  //
  // print_queue(priority_q);


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

  free(event_time);
  free(job_number);
  free(event_type);
  return 0;
}
