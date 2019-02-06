#include "config_reader.h"

Config* load_config() {

  Config* this_config = (Config*)malloc(sizeof(Config));

  const char *config_params[NUM_PARAMS] = {
    "SEED", "INIT_TIME", "FIN_TIME", "ARRIVE_MIN", "ARRIVE_MAX",
    "CPU_MIN", "CPU_MAX", "DISK1_MIN", "DISK1_MAX", "DISK2_MIN", "DISK2_MAX"
  };

  // opens the config file
  FILE * fp;
  fp = fopen( "config.file", "r" );

  // buffers for config file line reading
  char search_str[LINE_LENGTH];
  char line[LINE_LENGTH];

  // for line in config file
  while ( fgets( line, LINE_LENGTH, fp ) != NULL ) {
      // for parameter names we are searching for
      sscanf( line, "QUIT_PROB %f\n", &this_config->QUIT_PROB );
      for (int i=0;i<NUM_PARAMS;i++) {
      strcpy( search_str, config_params[i] );
      strcat( search_str, " %d\n" );
      sscanf( line, search_str, &this_config->conf_vals[i] );
    }
  }

  // closes config file
  fclose(fp);

  return this_config;
}

void display_config(Config* cp) {

  const char *config_params[NUM_PARAMS] = {
    "SEED", "INIT_TIME", "FIN_TIME", "ARRIVE_MIN", "ARRIVE_MAX",
    "CPU_MIN", "CPU_MAX", "DISK1_MIN", "DISK1_MAX", "DISK2_MIN", "DISK2_MAX"
  };

  for (int i = 0; i < NUM_PARAMS; i++) {
    printf( "Type: %-11s  value: %7d  index: %2d\n", config_params[i], cp->conf_vals[i], i );
  }
  printf( "\n%f: QUIT_PROB\n\n", cp->QUIT_PROB );
}
