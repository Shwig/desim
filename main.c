#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "priority_queue.h"
#include "fifo_queue.h"
#include "config_reader.h"

int main(int argc, char **argv) {

  // load the config settings from config.file
  Config *config = load_config();
  // print the loaded config to the terminal
  // display_config(config);

  // seed for random nums
  srand(config->conf_vals[SEED]);

  /* initialize the similation timer and finish_time to the same values
    contained in the config.file */
  int simulation_timer = config->conf_vals[INIT_TIME];
  int finish_time = config->conf_vals[FIN_TIME];

  // system service parameters from the config file
  int arrive_params[2] = {config->conf_vals[ARRIVE_MIN],config->conf_vals[ARRIVE_MAX]};
  int cpu_params[2] = {config->conf_vals[CPU_MIN],config->conf_vals[CPU_MAX]};
  int disk1_params[2] = {config->conf_vals[DISK1_MIN],config->conf_vals[DISK1_MAX]};
  int disk2_params[2] = {config->conf_vals[DISK2_MIN],config->conf_vals[DISK2_MAX]};

  // counters
  int exit_total = 0;
  // int cpu_counter = 0;
  // int disk1_counter = 0;
  // int disk2_counter = 0;

  // cpu stat vars
  // int cpuq_counter = 0;
  // int cpuq_len_sum = 0;
  // int cpuq_max_len = 0;

  // make this a function
  // cpuq_len_sum += cpu_q->length;
  // cpu_counter ++;
  // if (cpu_q->lelength > cpuq_max_len) {
  //   cpuq_max_len = cpu_q->lelength;
  // }

  // allocate space to keep track of priority q head data after popping an event
  int *event_time = (int *)malloc(sizeof(int));
  int *job_number = (int *)malloc(sizeof(int));
  int *event_type = (int *)malloc(sizeof(int));

  // fifo queues for services CPU, disk_1, and disk_2
  Queue *cpu_q = create_queue();
  Queue *disk1_q = create_queue();
  Queue *disk2_q = create_queue();

  Qnode *n = NULL;       // temp node to store return from de_queue()
  float f = 0;           // temporarily stores a float returned by rand_floater
  float disk_prob = .46; // probability to break tie if disk1 and disk2 queue are the same length
  int disk_q_diff = 0;   // holds the calculated difference in length off two fifo queues

  /* flags for each of the services
    if service is busy flag is set to 1 */
  int cpu_busy = 0;
  int disk1_busy = 0;
  int disk2_busy = 0;

  /* initialize queue with the first two events job arrives and sim finish
    usine init time and fin time from config.file*/
  Event *priority_q = simulation_start(simulation_timer, finish_time);

  /* While the priority queue is not empty and the simulation_timer
    hasnt reached the FIN_TIME from config file*/
  while((!is_empty(&priority_q)) && (simulation_timer < finish_time)) {

    // get all the data about the head node;
    peek(&priority_q, event_time, job_number, event_type);

    // update simulation time to time of next event
    simulation_timer = *event_time;

    // pop the head node
    pop_event(&priority_q);

    switch(*event_type) {

      case JOB_ARRIVES :
        // printf("\n\n*JOB_ARRIVES* Simulation_timer:%d", simulation_timer );
        handle_event(&priority_q, arrive_params, &simulation_timer, *event_time, *job_number, JOB_ARRIVES);
        // if the cpu is NOT busy
        if (!cpu_busy) {
          handle_event(&priority_q, cpu_params, &simulation_timer, *event_time, *job_number, FIN_CPU);
          en_queue(cpu_q, *event_time, *job_number);
          cpu_busy = 1;
        } else { // else CPU is busy
          en_queue(cpu_q, *event_time, *job_number);
        }
      break;

      case FIN_CPU :
        // printf("\n\n  **FIN_CPU** Simulation_timer:%d", simulation_timer );
        cpu_busy = 0;              // service no longer busy
        n = de_queue(cpu_q);       // (simulation timer - n->event_time) will give time processing at CPU
        // While the cpu fifo is not empty
        if (cpu_q->front != NULL) {
          get_fifo_head(&cpu_q, &n);
          handle_event(&priority_q, cpu_params, &simulation_timer, n->event_time, n->job_number, FIN_CPU);
          cpu_busy = 1;
        }

        // if rand_floater returns a value greater than QUIT_PROB job exits
        if ((f = rand_floater()) > config->QUIT_PROB) {
          printf("\n\n  **This job Exits the system:\n     Event_time: %3d, Job_number#: %3d, Event_type: %2d \n", *event_time, *job_number, *event_type);
          exit_total ++;
          break;
        }

        // calculate the difference in disk1 and disk2 queue length
        disk_q_diff = disk2_q->length - disk1_q->length;

        // if disk2 queue is longer
        if (disk_q_diff > 0) {

          if (!disk1_busy) {  // if disk is not busy handle the event
            handle_event(&priority_q, disk1_params, &simulation_timer, *event_time, *job_number, FIN_DISK1);
            en_queue(disk1_q, *event_time, *job_number);
            disk1_busy = 1;
          } else {            // disk is busy send job to disk1 fifo queue
            en_queue(disk1_q, *event_time, *job_number);
          }

        } else if (disk_q_diff < 0) { // disk1 queue is longer

          if (!disk2_busy) {  // if disk is not busy handle the event
            handle_event(&priority_q, disk2_params, &simulation_timer, *event_time, *job_number, FIN_DISK2);
            en_queue(disk2_q, *event_time, *job_number);
            disk2_busy = 1;
          } else {            // disk is busy send job to disk2 fifo queue
            en_queue(disk2_q, *event_time, *job_number);
          }

        } else {             // queues are the same size choose a random disk queue
          if (rand_floater() < disk_prob ) {
            if (!disk1_busy) {
              handle_event(&priority_q, disk1_params, &simulation_timer, *event_time, *job_number, FIN_DISK1);
              en_queue(disk1_q, *event_time, *job_number);
              disk1_busy = 1;
            } else {
              en_queue(disk1_q, *event_time, *job_number);
            }
          } else {
            if (!disk2_busy) {
              handle_event(&priority_q, disk2_params, &simulation_timer, *event_time, *job_number, FIN_DISK2);
              en_queue(disk2_q, *event_time, *job_number);
              disk2_busy = 1;
            } else {
              en_queue(disk2_q, *event_time, *job_number);
            }
          }
        }
      break;

      case FIN_DISK1 :
        // printf("\n\n    ***FIN_DISK1*** Simulation_timer:%d", simulation_timer );
        disk1_busy = 0;              // service no longer busy
        n = de_queue(disk1_q);       // (simulation timer - n->event_time) will give time processing at disk

        // While the cpu fifo is not empty
        if (disk1_q->front != NULL) {
          get_fifo_head(&disk1_q, &n);
          handle_event(&priority_q, disk1_params, &simulation_timer, n->event_time, n->job_number, FIN_DISK1);
          disk1_busy = 1;
        }

        if (!cpu_busy) {       // if the cpu is NOT busy send the job back to the cpu
          handle_event(&priority_q, cpu_params, &simulation_timer, *event_time, *job_number, FIN_CPU);
          en_queue(cpu_q, *event_time, *job_number);
          cpu_busy = 1;
        } else {               // else CPU is busy sned the job to the cpu queueu
          en_queue(cpu_q, *event_time, *job_number);
        }
      break;

      case FIN_DISK2 :
        // printf("\n\n      ****FIN_DISK2**** Simulation_timer:%d", simulation_timer );
        disk2_busy = 0;              // service no longer busy
        n = de_queue(disk2_q);       // (simulation timer - n->event_time) will give time processing at disk

        // While the cpu fifo is not empty
        if (disk2_q->front != NULL) {
          get_fifo_head(&disk2_q, &n);
          handle_event(&priority_q, disk1_params, &simulation_timer, n->event_time, n->job_number, FIN_DISK2);
          disk2_busy = 1;
        }

        if (!cpu_busy) {       // if the cpu is NOT busy send the job back to the cpu
          handle_event(&priority_q, cpu_params, &simulation_timer, *event_time, *job_number, FIN_CPU);
          en_queue(cpu_q, *event_time, *job_number);
          cpu_busy = 1;
        } else {               // else CPU is busy sned the job back to the cpu queue
          en_queue(cpu_q, *event_time, *job_number);
        }
      break;

      case SIM_END :
      printf("\n\n                 Simulation_timer:%d", simulation_timer );
      printf("\n\n*** SIM_END*** Event %d left the priority_q\n\nThe simulation has ended\n", *event_type );
      break;

      default:           // check for errors here maybe ?
          printf("\n\n!!!!!!Default unknown event_type!!!!!!!\n type -> %d\n", *event_type );
    }

  } // end while
  print_queue(priority_q);
  printf("At simulation end fifo queue lengths are: \n");
  printf("CPU_Q length: %d \n", cpu_q->length );
  printf("Disk1_Q length: %d \n", disk1_q->length );
  printf("Disk2_Q length: %d \n", disk2_q->length );
  printf("\nTotal job exits: %d \n", exit_total );

  // free up allocated memory before exit
  free_event_queue(&priority_q);
  free(config);
  free(event_time);
  free(job_number);
  free(event_type);
  return 0;
}
