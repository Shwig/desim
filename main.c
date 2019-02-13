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

  // start and end time of the simulation from config.file
  int simulation_timer = config->conf_vals[INIT_TIME];
  int end_time = config->conf_vals[FIN_TIME];

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
  Event *priority_q = simulation_start(simulation_timer, end_time);

  // fifo queues for services CPU, disk_1, and disk_2
  Queue *cpu_q = create_queue();
  // Queue *disk1_q = create_queue();
  // Queue *disk2_q = create_queue();
  Qnode *n = NULL; // temp node to store return from de_queue

  /* While the priority queue is not empty and the simulation_timer
    hasnt reached the FIN_TIME from config file*/
  while((!is_empty(&priority_q)) && (simulation_timer < end_time)) {

    // get all the data about the head node;
    peek(&priority_q, event_time, job_number, event_type);

    // update simulation time to time of next event
    simulation_timer = *event_time;

    // pop the head node
    pop_event(&priority_q);

    switch(*event_type) {
      case JOB_ARRIVES :
        printf("\n\nSimulation_timer:%d", simulation_timer );
        job_arrives(&priority_q, arrive_params, &simulation_timer, *event_time, *job_number, *event_type);

        // if cpu_q is empty and the cpu is NOT busy
        if (cpu_q->front == NULL && !cpu_busy) {
          // printf("\n\n*Case1* cpu_q is empty and CPU was not busy" );
          send_to_cpu(&priority_q, cpu_params, &simulation_timer, *event_time, *job_number, *event_type);
          cpu_busy = 1;

        } else if(cpu_busy) { // else CPU is busy
          // printf("\n   **Case2** CPU was busy" );
          en_queue(cpu_q, *event_time, *job_number);

        } else { // CPU not busy CPU queue is not empty
          // printf("\n\n     **Case3** CPU Not busy and CPU q isnt empty" );
          n = de_queue(cpu_q);
          send_to_cpu(&priority_q, cpu_params, &simulation_timer, n->event_time, n->job_number, FIN_CPU);
        }
      break;
      case FIN_CPU :
        cpu_busy = 0;
        printf("   ****CPU is no longer busy!!\n" );
        // printf("\n\n!!!This function does not handle event type3: not -> %d\n", *event_type );



      break;
      case FIN_DISK1 :
        printf("\n\n!!!This function does not handle event type4: not -> %d\n", *event_type );
      break;
      case FIN_DISK2 :
        printf("\n\n!!!This function does not handle event type5: not -> %d\n", *event_type );
      break;
      case SIM_END :
        printf("\n\n*** Notice*** Event %d left the priority_q\n\nThe simulation has ended\n", *event_type );
        printf("The time at simulation end is: %d\n", simulation_timer );
      // default:
      //   // check for errors here maybe
      //     printf("\n\n!!!Default unknown event_type\n type -> %d\n", *event_type );
    }
    // printf("\nLenth of of fifo after switch is :%d", cpu_q->length);
    // print_fifo(cpu_q);

  } // end while
  // printf("\n  Queue after While loop: \n");
  // print_queue(priority_q);


  free_event_queue(&priority_q);
  free(config);
  free(event_time);
  free(job_number);
  free(event_type);
  return 0;
}
