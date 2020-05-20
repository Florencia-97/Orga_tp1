/*--------------------------------------------------------------

DESCRIPCION

----------------------------------------------------------- */
#ifndef CMD_LINE_PARSER__H
#define CMD_LINE_PARSER__H

#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>

#include "params_t.h"

/* Some messages. */
#ifndef ERROR_INVALID_INPUT_STREAM
#define ERROR_INVALID_INPUT_STREAM "ERROR: Invalid input stream.\n"
#endif

#ifndef ERROR_OPENING_INPUT_STREAM
#define ERROR_OPENING_INPUT_STREAM "ERROR: Can't open input stream.\n"
#endif

#ifndef ERROR_INVALID_OUTPUT_STREAM
#define ERROR_INVALID_OUTPUT_STREAM "ERROR: Invalid output stream.\n"
#endif

#ifndef ERROR_OPENING_OUTPUT_STREAM
#define ERROR_OPENING_OUTPUT_STREAM "ERROR: Can't open output stream.\n"
#endif

#ifndef ERROR_OUTPUT_STREAM_WRITING_MSG
#define ERROR_OUTPUT_STREAM_WRITING_MSG \
    "ERROR: Output error when writing stream.\n"
#endif
#ifndef ERROR_INPUT_STREAM_READING_MSG
#define ERROR_INPUT_STREAM_READING_MSG \
    "ERROR: Input error when reading stream.\n"
#endif

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
void option_columns_size(const char *args, params_t *params);
output_state validate_stream_name(char *streamName);
output_state option_input_file(char *arg, params_t *params);
output_state option_output_prefix(char *arg, params_t *params);
void option_version(void);
void option_help(char *arg);
output_state parse_cmd_line(int argc, char **argv, params_t *params);
void imprimir_uso();
void manejar_comandos(char *opt);

#endif