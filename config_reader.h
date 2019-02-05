#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define LINE_LENGTH 20
#define NUM_PARAMS 5 //number of parameters we intend to read (except for floats)

typedef enum {TIME_A, TIME_B, PARAM_A, PARAM_B, OTHER}TYPES;

typedef struct Config {
  float PROB_QUIT;
  unsigned int conf_vals[NUM_PARAMS];
  const char* conf_types[NUM_PARAMS];
  TYPES TIME_A, TIME_B, PARAM_A, PARAM_B, OTHER;
} Config;



Config* load_config();

#endif
