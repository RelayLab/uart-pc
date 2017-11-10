    %function []=oscil()
	clc,clear; %очистить вывод
	graphics_toolkit("fltk");
	%объявление констант, используемых микроконтроллером
	%можно найти в файле программы МК ../atmega/main.c
	f_cpu=19600000;
	adc_clock_divider=16;
	time_step=1/(f_cpu/adc_clock_divider);
	V_gnd=0;
	V_ref=1.1;
	adc_digits=1024;

	%дальше код самой программы. она открывает файл out.txt
	%читает каждое число, состоящее из двух байт и выводит на график
	[file,error]=fopen('out.txt','r'); %открыть файл только для чтения

	while(1)%бесконечный цикл

		clf();%очистить график
		read_data=[];%просто инициализация массива для хранения результатов

		while (~feof(file))%пока не достигнут конец файла

			bytes = fread(file,[1 2],'uint8'); %прочитать байт

			if(~feof(file))%если этот байт последний, то закончить чтение
				bytes = fread(file,[1 2],'uint8'); %иначе прочитать второй байт
				%число состоит из двух прочитанных байтов
				number = bytes(1)*256+bytes(1);
				read_data = [read_data number];%присоединить к общему массиву
			else
				break;
			end
		end
		fseek(file,0);%установить курсор на начало файла
		%вывести на график значения с учетом коэфф. в начале
		read_data = read_data*(V_ref-V_gnd)/adc_digits;
		time = [0:size(read_data,2)-1]*time_step;
		plot(time,read_data);
		pause(1);%обновлять график раз в 2 секунду
	end
%endfunction
