#include "cmd_line_parser.h"

void option_iterations(const char *args, params_t *params)
{
    int iterations;

    if (sscanf(args, "%d", &iterations) != 1 || iterations <= 0)
    {
        fprintf(stderr, "invalid iterations specification.\n");
        exit(EXIT_FAILURE);
    }

    params->i = iterations;
}

void option_rows_size(const char *args, params_t *params)
{
    int rows;

    if (sscanf(args, "%d", &rows) != 1 || rows <= 0)
    {
        fprintf(stderr, "invalid rows specification.\n");
        exit(EXIT_FAILURE);
    }

    params->N = rows;
}

void option_columns_size(const char *args, params_t *params)
{
    int cols;

    if (sscanf(args, "%d", &cols) != 1 || cols <= 0)
    {
        fprintf(stderr, "invalid columns specification.\n");
        exit(EXIT_FAILURE);
    }

    params->M = cols;
}

output_state validate_stream_name(char *streamName)
{
    if (streamName == NULL)
    {
        return outERROR;
    }

    /* strcmp() returns 0 if identical. */
    if (!strcmp(streamName, ".") || !strcmp(streamName, "..") ||
        !strcmp(streamName, "/") || !strcmp(streamName, "//"))
    {
        return outERROR;
    }

    return outOK;
}

output_state option_input_file(char *arg, params_t *params)
{
    if (validate_stream_name(arg) == outERROR)
    {
        fprintf(stderr, ERROR_INVALID_INPUT_STREAM);
        return outERROR;
    }

    /* We cover the optional enhancement to print the PBM images to the terminal. */
    if (strcmp(arg, STD_STREAM_TOKEN) == 0)
    {
        params->inputStream = stdin;
    }
    else
    {
        params->inputStream = fopen(arg, "r");
    }

    if ((params->inputStream) == NULL)
    {
        fprintf(stderr, ERROR_OPENING_INPUT_STREAM);
        return outERROR;
    }

    return outOK;
}

output_state option_output_prefix(char *arg, params_t *params)
{
    if (validate_stream_name(arg) == outERROR)
    {
        fprintf(stderr, ERROR_INVALID_OUTPUT_STREAM);
        return outERROR;
    }

    if (strcmp(arg, STD_STREAM_TOKEN) == 0)
    {
        params->outputStream = stdout;
        params->prefix = NULL;
    }
    else
    {
        params->outputStream = NULL;
        params->prefix = arg;
    }

    return outOK;
}

void option_version(void)
{
    fprintf(stderr, "%s\n", VERSION);

    exit(EXIT_SUCCESS);
}

void option_help(char *arg)
{
    fprintf(stderr, "Uso:\n");
    fprintf(stderr, " %s -h\n", arg);
    fprintf(stderr, " %s -V\n", arg);
    fprintf(stderr, " %s i M N inputfile [-o outputprefix]\n", arg);

    fprintf(stderr, "Opciones:\n");
    fprintf(stderr, " -h, --help\tImprime este mensaje.\n");
    fprintf(stderr, " -V, --version\tDa la versión del programa.\n");
    fprintf(stderr, " -o Prefijo de los archivos de salida.\n");

    fprintf(stderr, "Ejemplos:\n");
    fprintf(stderr, " %s 10 20 20 glider -o estado\n", arg);
    fprintf(stderr, " Representa 10 iteraciones del Juego de la Vida en una matriz de 20x20,\n");
    fprintf(stderr, " con un estado inicial tomado del archivo ‘‘glider’’.\n");
    fprintf(stderr, " Los archivos de salida se llamarán estado_n.pbm.\n");
    fprintf(stderr, " Si no se da un prefijo para los archivos de salida,\n");
    fprintf(stderr, " el prefijo será el nombre del archivo de entrada.\n");

    exit(EXIT_SUCCESS);
}

output_state parse_cmd_line(int argc, char **argv, params_t *params)
{
    if ((argc != 2) && ((argc == 5) || (argc == 7)))
    {

        /* Process fixed options. */
        option_iterations(argv[1], params);
        option_rows_size(argv[2], params);
        option_columns_size(argv[3], params);
        option_input_file(argv[4], params);
        /* Set the default values. */
        params->outputStream = NULL;
        params->prefix = argv[4];
    }

    /* 'version' and 'help' have no arguments. Output has an optional one.*/
    /* The options are distinguished by the ASCII code of the
 * 'char' variables. */
    struct option cmd_line_options[] = {{"version", no_argument, NULL, 'V'},
                                        {"help", no_argument, NULL, 'h'},
                                        {"output", required_argument, NULL, 'o'},
                                        {0, 0, 0, 0}};

    char *optstring = "Vho:";
    int index_ptr = 0;
    int option_code;
    output_state option_state = outERROR;
    char *program_name = argv[0];
    while ((option_code = getopt_long(argc, argv, optstring, cmd_line_options, &index_ptr)) != -1)
    {
        switch (option_code)
        {
        case 'V':
            option_version();
            break;
        case 'h':
            option_help(program_name);
            break;
        case 'o':
            option_state = option_output_prefix(optarg, params);
            break;
        case '?':
            /* getopt_long already printed an error message. */
            option_state = outERROR;
            break;
        }
        if (option_state == outERROR)
        {
            return outERROR;
        }
    }

    return outOK;
}