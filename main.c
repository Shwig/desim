#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "priority_queue.h"
#include "fifo_queue.h"
#include "config_reader.h"

int main(int argc, char **argv) {

  // load the config settings from config.file
  Config *config = load_config();
  display_config(config);

  // seed random num
  srand(config->conf_vals[SEED]);

  /* initialize the similation timer and finish_time to the same values
    contained in the config.file */
  int simulation_timer = config->conf_vals[INIT_TIME];
  int finish_time = config->conf_vals[FIN_TIME];

  // service parameters from the config file
  int arrive_params[2] = {config->conf_vals[ARRIVE_MIN],config->conf_vals[ARRIVE_MAX]};
  int cpu_params[2] = {config->conf_vals[CPU_MIN],config->conf_vals[CPU_MAX]};
  int disk1_params[2] = {config->conf_vals[DISK1_MIN],config->conf_vals[DISK1_MAX]};
  int disk2_params[2] = {config->conf_vals[DISK2_MIN],config->conf_vals[DISK2_MAX]};

  // counters
  int cpu_fintime, job_counter, cpu_counter, dsk1_counter, dsk2_counter = 0;

  /* flags for each of the system processes
    if process is busy flag is set to 1 */
  int cpu_busy, disk1_busy, disk2_busy = 0;

  // allocate space to keep track of priority q head data after popping an event
  int *event_time = (int *)malloc(sizeof(int));
  int *job_number = (int *)malloc(sizeof(int));
  int *event_type = (int *)malloc(sizeof(int));

  /* initialize queue with the first two events job arrives and sim finish
    usine init time and fin time from config.file*/
  Event *priority_q = simulation_start(simulation_timer, finish_time);

  // fifo queues for services CPU, disk_1, and disk_2
  Queue *cpu_q = create_queue();
  Queue *disk1_q = create_queue();
  Queue *disk2_q = create_queue();
  Qnode *n = NULL; // temp node to store return from de_queue()
  float f = 0;    // temporarily stores a float returned by rand_floater

  /* While the priority queue is not empty and the simulation_timer
    hasnt reached the FIN_TIME from config file*/
  while((!is_empty(&priority_q)) && (simulation_timer < finish_time)) {

    // get all the data about the head node;
    peek(&priority_q, event_time, job_number, event_type);

    // update simulation time to time of next event
    simulation_timer = *event_time;

    printf("\n\n\nThese are the queues before popping and entering the switch block:" );
    print_queue(priority_q);
    print_fifo(cpu_q);

    // pop the head node
    pop_event(&priority_q);

    switch(*event_type) {
      case JOB_ARRIVES :
        printf("\n\n*JOB_ARRIVES* Simulation_timer:%d", simulation_timer );
        job_arrives(&priority_q, arrive_params, &simulation_timer, *event_time, *job_number, *event_type);

        // if the cpu is NOT busy
        if (!cpu_busy) {
          send_to_cpu(&priority_q, cpu_params, &simulation_timer, *event_time, *job_number, *event_type);
          en_queue(cpu_q, *event_time, *job_number);
          cpu_busy = 1;

        } else { // else CPU is busy
          printf("\n   CPU was busy" );
          en_queue(cpu_q, *event_time, *job_number);

        }
      break;
      case FIN_CPU :
        printf("\n\n  **FIN_CPU** Simulation_timer:%d", simulation_timer );
        cpu_busy = 0;        // CPU is not buys
        n = de_queue(cpu_q); // (simulation timer - n->event_time) will give time processing at CPU

        // While the cpu fifo is not empty
        if (cpu_q->front != NULL) {
          get_fifo_head(&cpu_q, &n);
          printf("\n  CPU is now busy -> event_time:%d job_num:%d event_type:%d ", n->event_time, n->job_number, FIN_CPU );
          send_to_cpu(&priority_q, cpu_params, &simulation_timer, n->event_time, n->job_number, FIN_CPU);
          cpu_busy = 1;
        }

        // if rand_floater returns a value greater than QUIT_PROB job exits
        if ((f = rand_floater()) > config->QUIT_PROB) {
          printf("\n**This job Exits the system:\n Event_time: %7d, Job_number#: %7d, Event_type: %2d \n\n", *event_time, *job_number, *event_type);
          break;
        }

        // if is empty and the cpu is NOT busy
        // if () {
        //
        //   send_to_cpu(&priority_q, disk1_params, &simulation_timer, *event_time, *job_number, *event_type);
        //   en_queue(disk1_q, *event_time, *job_number);
        //   disk1_busy = 1;
        //
        // } else { // else CPU is busy
        //   printf("\n   CPU was busy" );
        //   en_queue(cpu_q, *event_time, *job_number);
        // 
        // }

      break;
      case FIN_DISK1 :
      printf("\n\n    ***FIN_DISK1*** Simulation_timer:%d", simulation_timer );
        printf("\n\n!!!This function does not handle event type4: not -> %d\n", *event_type );

      break;
      case FIN_DISK2 :
      printf("\n\n      ****FIN_DISK2**** Simulation_timer:%d", simulation_timer );
        printf("\n\n!!!This function does not handle event type5: not -> %d\n", *event_type );

      break;
      case SIM_END :
      printf("\n\n        *****SIM_END***** Simulation_timer:%d", simulation_timer );
      printf("\n\n*** Notice*** Event %d left the priority_q\n\nThe simulation has ended\n", *event_type );

      // default:
      //   // check for errors here maybe
      //     printf("\n\n!!!Default unknown event_type\n type -> %d\n", *event_type );
    }
    // printf("\nLenth of of fifo after switch is :%d", cpu_q->length);
    // print_fifo(cpu_q);

  } // end while
  // printf("\n  Queue after While loop: \n");
  print_queue(priority_q);


  free_event_queue(&priority_q);
  free(config);
  free(event_time);
  free(job_number);
  free(event_type);
  return 0;
}
