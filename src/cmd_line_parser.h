#ifndef CMD_LINE_PARSER__H
#define CMD_LINE_PARSER__H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "messages.h"
#include "params_t.h"

#ifndef STD_STREAM_TOKEN
#define STD_STREAM_TOKEN "-"
#endif

#ifndef VERSION
#define VERSION "1.0.0"
#endif

typedef enum output_states_
{
	outOK,
	outERROR
} output_state;

void option_iterations(const char *args, params_t *params);
void option_rows_size(const char *args, params_t *params);
void option_columns_size(const char *args,
                         params_t *params);
output_state validate_stream_name(char *streamName);
output_state option_input_file(char *arg, params_t *params);
output_state option_output_prefix(char *arg,
                                  params_t *params);
void option_version(void);
void option_help(char *arg);
output_state parse_cmd_line(int argc, char **argv,
                            params_t *params);
void imprimir_uso();
void manejar_comandos(char *opt);

#endif
