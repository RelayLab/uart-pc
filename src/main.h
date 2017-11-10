#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "rs232.h"

struct args{
	int com_port_number;
	long baud;
	int buffer_size;
	char* mode;
	int is_looped;
	int wait_ms;
	int is_append;
};
typedef struct args args;

void init_input_args(args* input_args,int argc,char** argv);

