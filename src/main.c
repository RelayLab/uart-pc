#include "main.h"
/*This program uses simple cross-platform GPL library for RS-232 communication by Teunis van Beelen (more in ./RS-232/ folder) */

int main(int argc,char** argv)
{
	args input_args;//инициализация аргументов, переданный в командную строку
	init_input_args(&input_args,argc,argv);

	char * buffer=malloc(input_args.buffer_size);

	//открыть ком-порт
	if(RS232_OpenComport(
				input_args.com_port_number,
				input_args.baud,
				input_args.mode)){
		printf("Can not open comport\n");
		return(0);
	}

	FILE *file_to_write;
	//главный цикл, в котором читаются данные с порта и записываются в файл
	do{
		#ifdef _WIN32
			Sleep(input_args.wait_ms);
		#else
			usleep(input_args.wait_ms*1000);  /* sleep for 100 milliSeconds */
		#endif

		if (input_args.is_append){
			file_to_write=fopen("out.txt","w");
		}
		else{
			file_to_write=fopen("out.txt","w");
		}

		//прочитать в буфер заданное кол-во байт
		int bytes_read = RS232_PollComport(
				input_args.com_port_number,
				buffer,
				input_args.buffer_size-1);	//получить данные из ком-порта в буфер
		
	
		if (file_to_write==NULL){
			fprintf(stderr,"Can't open file to write.\n");
			exit(1);
		}

        	int i=0;
		for (i=0;i<bytes_read;i++){			//положить каждый прочитанный байт
			if (fputc((int) buffer[i],file_to_write)==EOF){
				fprintf(stderr,"Can't write to write.\n");
			}
		}
		fclose(file_to_write);//закрыть файл
	}while(input_args.is_looped);//если был входной аргумент, то зациклить запись в файл
	return(0);
}

