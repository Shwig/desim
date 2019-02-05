#include "config_reader.h"

Config* load_config() {

  Config* this_config = (Config*)malloc(sizeof(Config));
  this_config->conf_types = {"TIME_A", "TIME_B", "PARAM_A", "PARAM_B", "OTHER"};
  //
  // // opens the config file
  // FILE * fp;
  // fp = fopen( "config.file", "r" );
  //
  // // buffers for config file line reading
  // char search_str[LINE_LENGTH];
  // char line[LINE_LENGTH];
  //
  // // for line in config file
  // int i;
  // while ( fgets( line, LINE_LENGTH, fp ) != NULL ) {
  //     // for parameter names we are searching for
  //     sscanf( line, "PROB_QUIT %f\n", this_config->PROB_QUIT );
  //     for (i=0;i<NUM_PARAMS;i++) {
  //     strcpy( search_str, this_config->conf_types[i] );
  //     strcat( search_str, " %d\n" );
  //     sscanf( line, search_str, this_config->conf_vals[i] );
  //   }
  // }
  //
  // // closes config file
  // fclose(fp);

  return this_config;
}
