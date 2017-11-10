#include "main.h"
//записать входные аргументы в структуру input_args
void init_input_args(args* input_args,int argc,char** argv){
	int i=0;
	for (i=1;i<argc;i++){		//для каждого аргумента
		char* argument= argv[i];
		if (strlen(argument)<2){//если нет аргументов, то выдать ошибку
			fprintf(stderr,"Not enough input arguments.\n");
			exit(1);
		}
		const char * pointer_to_value = argument+2;//это значение аргумента, т.к. первые два символа это тире и флаг -b9600
		switch  (argument[1]){
			case 'p':
				input_args->com_port_number=atoi(pointer_to_value);
				break;
			case 'b':
				input_args->baud=atoi(pointer_to_value);
				break;
			case 's':
				input_args->buffer_size=atoi(pointer_to_value);
				break;
			case 'm':
				input_args->mode=calloc(strlen(pointer_to_value+1),1);
				strcpy(input_args->mode,pointer_to_value);
				break;
			case 'l':
				input_args->is_looped=atoi(pointer_to_value);
				break;
			case 'w':
				input_args->wait_ms=atoi(pointer_to_value);
				break;
			case 'a':
				input_args->is_append=atoi(pointer_to_value);
				break;
			default:
				fprintf(stderr,"Wrong arguments\n");
		}
	}
}
