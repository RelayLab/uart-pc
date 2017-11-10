//function []=oscil()
	f_cpu=19600000
	adc_clock_divider=16
	time_step=1/(f_cpu/adc_clock_divider)
	V_gnd=0
	V_ref=1.1
	adc_digits=1024
	clc() //очистить вывод
	//a=gca()
	//a.auto_scale="on"
	//a.data_bounds=[0 0;1e-6 1.1];
	mclose('all')
	[file,error]=mopen('out.txt','rb')//открыть файл только для чтения
	//matlab:[file,error]=fopen('out.txt','r')
	while(1)//бесконечный цикл
		clf()//очистить график
		read_data=[]//просто инициализация массива для хранения результатов
		while (~meof(file))//пока не достигнут конец файла
			//matlab:while (~feof(file))
			bytes(1,1) = mget(1,'uc',file);//прочитать байт
			if(~meof(file))//если этот байт последний, то закончить чтение
				bytes(1,2) = mget(1,'uc',file);
			else
				break;
			end
			//matlab:bytes = fread(file,[1 2],'uint8');
			number = bytes(1,1)*256+bytes(1,2)//число состоит из двух прочитанных байтов
			read_data = [read_data number]//присоединить к общему массиву
		end
		mseek(0)//установить курсор на начало файла
		//matlab:fseek(0)
		read_data = read_data*(V_ref-V_gnd)/adc_digits
		time = [0:size(read_data,2)-1]*time_step
		plot(time,read_data)
		sleep(2000)//обновлять график раз в 2 секунду
	end
//endfunction
