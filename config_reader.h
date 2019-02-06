#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LINE_LENGTH 20
#define NUM_PARAMS 11 //5number of parameters we intend to read (except for floats)

extern const char* conf_types[NUM_PARAMS];
typedef enum {
  SEED, INIT_TIME, FIN_TIME, ARRIVE_MIN, ARRIVE_MAX,
  CPU_MIN, CPU_MAX, DISK1_MIN, DISK1_MAX, DISK2_MIN, DISK2_MAX
}CONF_TYPES;

typedef struct Config {
  float QUIT_PROB;
  unsigned int conf_vals[NUM_PARAMS];
} Config;

Config* load_config();
void display_config(Config* conf);

#endif
